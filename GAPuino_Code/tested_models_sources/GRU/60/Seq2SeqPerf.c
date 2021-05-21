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
#include "coeffGRU/CoeffDecoder16_12.h"
#include "coeffGRU/CoeffEncoder16_12.h"


#define STACK_SIZE ( 1024 * 2)
#define CID        ( 0 )

#define neuroni 60
#define step_in 27
#define step_out 9

static rt_perf_t *cluster_perf;

short int *input;

PI_L2 short int h_0[neuroni] = {0};
PI_L2 short int Z[2*neuroni] ;
PI_L2 short int prod1[neuroni] ;
PI_L2 int prod2[neuroni] ;
PI_L2 short int OutDense[step_out];

short int *In;

int *Enc_GRU_bias1;
short int *Enc_GRU_kernel1;
short int *Enc_GRU_rec_kernel1;

int *Enc_GRU_bias2;
short int *Enc_GRU_kernel2;
short int *Enc_GRU_rec_kernel2;

int *Dec_GRU_bias1;
short int *Dec_GRU_rec_kernel1;

int *Dec_GRU_bias2;
short int *Dec_GRU_rec_kernel2;

int *DENSE_bias;
short int *DENSE_kernel;

unsigned int GRU_bias_Size;
unsigned int GRU_kernel_Size;
unsigned int GRU_rec_kernel_Size;


extern char *L1_Memory;



static void cluster_main(rt_perf_t *perf)
{	printf ("cluster master start\n");
	unsigned int instr, cycles;
	unsigned int Iterazione = 0;
	int Norm = 12;

	rt_perf_init(perf);
	rt_perf_conf(perf, (1<<RT_PERF_CYCLES) | (1<<RT_PERF_INSTR));
	rt_perf_reset(perf);

	for (unsigned int num_in=0;num_in<1;num_in++){
		unsigned int First = num_in*step_in;
		for(unsigned int i=0; i<neuroni;i++){
			h_0[i] = 0;
		}
		rt_perf_start(perf);

		EncGRUlayer(&In[First],Iterazione, h_0, Enc_GRU_kernel1, Enc_GRU_rec_kernel1, Enc_GRU_bias1, Enc_GRU_kernel2, Enc_GRU_rec_kernel2, Enc_GRU_bias2, Z, prod1, prod2, Norm);
		DecGRUlayer(Iterazione, h_0, Dec_GRU_rec_kernel1, Dec_GRU_bias1,Dec_GRU_rec_kernel2, Dec_GRU_bias2,DENSE_kernel, DENSE_bias, OutDense, Z, prod1, prod2, Norm);

		rt_perf_stop(perf);
		rt_perf_save(perf);
		instr = rt_perf_get(perf, RT_PERF_INSTR);
		cycles = rt_perf_get(perf, RT_PERF_CYCLES);

		for(unsigned int i=0; i<step_out;i++){
			printf("Uscita[%d]= %d \n",i,OutDense[i]);
		}
		printf("\n\tPerformance of Seq2Seq: cycles %d instructions %d\n", cycles, instr);
	}

}

void test_on_cluster()
{
	printf("Starting the test function\n");
	rt_perf_t *perf = cluster_perf;

  //function use of printf to explicitly show the function duration
	cluster_main(perf);
}

void run_Seq2Seq(void)
{
    printf("Entering main controller\n");
    uint32_t errors = 0;
	uint32_t units=60;

	/*Calcolo spazio per i coefficienti*/
	GRU_bias_Size=(3 * units * sizeof(int));
	GRU_kernel_Size=(3 * units * sizeof(short int));
	GRU_rec_kernel_Size=(3 * units * sizeof(short int) * units);


	/*Carico i coefficienti e gli ingressi*/
	Enc_GRU_bias1 = Encoder_Gru_Bias1;
	Enc_GRU_kernel1 = Encoder_Gru_Kernel1;
	Enc_GRU_rec_kernel1 = Encoder_Gru_Recurrent_Kernel1;

	Enc_GRU_bias2 = Encoder_Gru_Bias2;
	Enc_GRU_kernel2 = Encoder_Gru_Kernel2;
	Enc_GRU_rec_kernel2 = Encoder_Gru_Recurrent_Kernel2;

	Dec_GRU_bias1 = Decoder_Gru_Bias1;
	Dec_GRU_rec_kernel1 = Decoder_Gru_Kernel1;
	Dec_GRU_rec_kernel1 = Decoder_Gru_Recurrent_Kernel1;


	Dec_GRU_bias2 = Decoder_Gru_Bias2;
	Dec_GRU_rec_kernel2 = Decoder_Gru_Kernel2;
	Dec_GRU_rec_kernel2 = Decoder_Gru_Recurrent_Kernel2;

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


	cluster_perf = rt_alloc(RT_ALLOC_L2_CL_DATA, sizeof(rt_perf_t));


    /* Prepare cluster task and send it to cluster. */
    struct pi_cluster_task task = {0};
    task.entry = test_on_cluster;
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
    return pmsis_kickoff((void *) run_Seq2Seq);
}
