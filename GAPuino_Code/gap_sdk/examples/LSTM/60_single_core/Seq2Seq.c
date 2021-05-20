/*
 * Copyright (C) 2017 GreenWaves Technologies
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 *
 */

#include <stdio.h>
#include "pmsis.h"
#include "Gap.h"
#include "EncDecLayer.h"
#include "coeff/coeff16_11.h"

#define STACK_SIZE ( 1024 * 2)
#define CID        ( 0 )

#define neuroni 60
#define step_in 27
#define step_out 9

short int *input;

PI_L2 short int h_0[neuroni] = {0};
PI_L2 short int c_0[neuroni] = {0};
PI_L2 short int z[4*neuroni] ;
PI_L2 short int OutDense[9];

short int *In;

int *Enc_LSTM_bias;
short int *Enc_LSTM_kernel;
short int *Enc_LSTM_rec_kernel;

int *Dec_LSTM_bias;
short int *Dec_LSTM_kernel;
short int *Dec_LSTM_rec_kernel;

int *DENSE_bias;
short int *DENSE_kernel;

unsigned int LSTM_bias_Size;
unsigned int LSTM_kernel_Size;
unsigned int LSTM_rec_kernel_Size;


extern char *L1_Memory;



static void cluster_main()
{	printf ("cluster master start\n");
	//unsigned int step_in = 27;
	//unsigned int step_out = 9;
	unsigned int Iterazione = 0;
	int Norm = 11;

		for(unsigned int i=0; i<neuroni;i++){
			h_0[i] = 0;
			c_0[i] = 0;
		}
		
		Encoder(In, step_in,Iterazione, h_0, c_0, Enc_LSTM_kernel, Enc_LSTM_rec_kernel, Enc_LSTM_bias, z, Norm);
		//for(unsigned int i=0; i<neuroni;i++){
			//printf("Encoder z[%d]: %d  \n",i+3*neuroni,z[i+3*neuroni]);			
			//printf("Encoder H[%d]: %d  ",i, h_0[i]);
			//printf("Encoder C[%d]: %d  \n",i, c_0[i]);
		//}
		//for(unsigned int i=0; i<4*neuroni;i++){
		//	printf("\nZ di %d = %d  ",i,z[i]);
		//}

		Decoder(step_out, Iterazione, h_0, c_0, Dec_LSTM_kernel, Dec_LSTM_rec_kernel, Dec_LSTM_bias, DENSE_kernel, DENSE_bias, OutDense, z, Norm);
		//for(unsigned int i=0; i<neuroni;i++){
			//printf("H[%d]: %d  ",i, h_0[i]);
			//printf("C[%d]: %d  \n",i, c_0[i]);
		//}
		for(unsigned int i=0; i<step_out;i++){
			printf("Uscita[%d]= %d \n",i,OutDense[i]);
		}
	
}


void run_MatMult(void)
{
    printf("Entering main controller\n");
    uint32_t errors = 0;
	uint32_t units=60;
	
	/*Calcolo spazio per i coefficienti*/
	LSTM_bias_Size=(4 * units * sizeof(int));
	LSTM_kernel_Size=(4 * units * sizeof(short int));
	LSTM_rec_kernel_Size=(4 * units * sizeof(short int) * units);

	
	/*Carico i coefficienti e gli ingressi*/
	Enc_LSTM_bias = Encoder_Lstm_Bias;
	Enc_LSTM_kernel = Encoder_Lstm_Kernel;
	Enc_LSTM_rec_kernel = Encoder_Lstm_Recurrent_Kernel;

	Dec_LSTM_bias = Decoder_Lstm_Bias;
	Dec_LSTM_kernel = Decoder_Lstm_Kernel;
	Dec_LSTM_rec_kernel = Decoder_Lstm_Recurrent_Kernel;	

	DENSE_bias = Dense_Bias;
	DENSE_kernel = Dense_Kernel;
	
	In = Ingressi;
	
	


  	/* Alloco spazio per le uscite e le variabili d'appoggio */

	//c_0 = (int *) pi_l2_malloc(units*sizeof(int));    
	//h_0 = (int *) pi_l2_malloc(units*sizeof(int));

	


	
	printf("Opening the Cluster\n");
    struct pi_device cluster_dev;
    struct pi_cluster_conf conf;
    /* Init cluster configuration structure. */
    pi_cluster_conf_init(&conf);
    conf.id = (uint32_t) CID;   /* Cluster ID. */
    /* Configure & open cluster. */
    pi_open_from_conf(&cluster_dev, (void *) &conf);
    if (pi_cluster_open(&cluster_dev))
    {
        printf("Cluster open failed !\n");
        pmsis_exit(-2);
    }

    /* Allocate the predetermined memory size in the shared L1 memory that the cluster can act on. */
    L1_Memory = (char *) pi_l1_malloc(&cluster_dev, _L1_Memory_SIZE);
    if (L1_Memory == NULL )
    {
        printf("Memory Allocation Error! Quit...\n");
        pmsis_exit(-3);
    }





    /* Prepare cluster task and send it to cluster. */
    struct pi_cluster_task task = {0};
    task.entry = cluster_main;
    task.arg = NULL;
    task.stack_size = (uint32_t) STACK_SIZE;

    /* Offloading Task to cluster. */
    pi_cluster_send_task_to_cl(&cluster_dev, &task);

    pi_l1_free(&cluster_dev, L1_Memory, _L1_Memory_SIZE);

    printf("Close cluster after end of computation.\n");
 	pmsis_exit(errors);
}

int main(void)
{
    printf("\n\n\t *** NeuralNet ***\n\n");
    return pmsis_kickoff((void *) run_MatMult);
}



