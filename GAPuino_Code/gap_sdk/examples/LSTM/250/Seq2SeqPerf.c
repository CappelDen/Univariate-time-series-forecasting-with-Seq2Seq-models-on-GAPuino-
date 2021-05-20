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
#include "bsp/fs.h"
#include "bsp/ram.h"
#include "bsp/flash/hyperflash.h"
#include "bsp/ram/hyperram.h"

#define  BUFFER_SIZE   (1024)
#define STACK_SIZE ( 1024 * 2)
#define CID        ( 0 )

#define neuroni 250
#define step_in 27
#define step_out 9

static rt_perf_t *cluster_perf;

static struct pi_device flash;
static struct pi_device fs;
static struct pi_device ram;
static struct pi_hyperflash_conf flash_conf;
static struct pi_fs_conf fs_conf;
static struct pi_hyperram_conf ram_conf;

short int *input;
pi_fs_file_t *file;
int16_t *buff;


PI_L2 short int h_0[neuroni] = {0};
PI_L2 short int c_0[neuroni] = {0};
PI_L2 short int z[4*neuroni] ;
PI_L2 short int OutDense[9];

short int *In;

int *Enc_LSTM_bias;
short int *Enc_LSTM_kernel;
PI_L2 uint32_t *Enc_LSTM_rec_kernel;

int *Dec_LSTM_bias;
short int *Dec_LSTM_kernel;
PI_L2 uint32_t *Dec_LSTM_rec_kernel;

int *DENSE_bias;
short int *DENSE_kernel;

unsigned int LSTM_bias_Size;
unsigned int LSTM_kernel_Size;
unsigned int LSTM_rec_kernel_Size;


extern char *L1_Memory;
extern char *L2_Memory;


static void cluster_main(rt_perf_t *perf)
{	printf ("cluster master start\n");
    unsigned int instr, cycles;
	unsigned int Iterazione = 0;
	int Norm = 11;

	rt_perf_init(perf);
	rt_perf_conf(perf, (1<<RT_PERF_CYCLES) | (1<<RT_PERF_INSTR));
	rt_perf_reset(perf);

    for(unsigned int i=0; i<neuroni;i++){
			h_0[i] = 0;
			c_0[i] = 0;
    }
    rt_perf_start(perf);

    //Encoder(ram,In, step_in,Iterazione, h_0, c_0, Enc_LSTM_kernel, *Enc_LSTM_rec_kernel, Enc_LSTM_bias, z, Norm);

    Decoder(ram, step_out, Iterazione, h_0, c_0, Dec_LSTM_kernel, *Dec_LSTM_rec_kernel, Dec_LSTM_bias, DENSE_kernel, DENSE_bias, OutDense, z, Norm);

	rt_perf_stop(perf);
  	rt_perf_save(perf);
	instr = rt_perf_get(perf, RT_PERF_INSTR);
	cycles = rt_perf_get(perf, RT_PERF_CYCLES);	    
   
    //for(unsigned int i=0; i<step_out;i++){
    //	printf("Uscita[%d]= %d \n",i,OutDense[i]);
    //}
	
    printf("\n\tPerformance of Seq2Seq: cycles %d instructions %d\n", cycles, instr);

}

void test_on_cluster()
{
	printf("Starting the test function\n");
	rt_perf_t *perf = cluster_perf;

  //function use of printf to explicitly show the function duration
	cluster_main(perf);
}


void CopyFileFromFlashToL3(struct pi_device *fs, char *file_name, uint32_t *hyper_buff)
{
    printf("Loading weights \"%s\" from FS to L3\n", file_name);
    
    /* Open file from filesystem. */
    file = pi_fs_open(fs, file_name, 0);
    if (file == NULL)
    {
        printf("File open failed !\n");
        pmsis_exit(-1);
    }
    
    /* Allocate memory in ram memory to copy file. */
    if (pi_ram_alloc(&ram, hyper_buff,(__uint32_t) file->size))
    {
        printf("Ram malloc failed !\n");
        pmsis_exit(-2);
    }
    
    printf("Hyperram alloc : %lx %u\n", *hyper_buff, file->size);

    uint32_t size_total = 0;
    uint32_t size = 0;
    pi_task_t task;
    do
    {
        /* First read from filesystem(on flash) to a buffer in L2 memory. */
        size = pi_fs_read_async(file, buff, BUFFER_SIZE, pi_task_block(&task));
        pi_task_wait_on(&task);
        size = ((size + 3) & ~3);
        if (size)
        {	
			pi_ram_write(&ram, (uint32_t) (*hyper_buff+size_total), buff, size);
            size_total += size;
        }
    } while (size_total < file->size);
    printf("Loading layer \"%s\" from FS to L3, hyper %lx size = %ld\n", file_name, *hyper_buff, size_total);

    pi_fs_seek(file, 0);
    pi_fs_close(file);

}

void run_MatMult(void)
{
    printf("Entering main controller\n");
    uint32_t errors = 0;
	uint32_t units=250;
	
	/*Calcolo spazio per i coefficienti*/
	LSTM_bias_Size=(4 * units * sizeof(int));
	LSTM_kernel_Size=(4 * units * sizeof(short int));
	LSTM_rec_kernel_Size=(4 * units * sizeof(short int) * units);

    Enc_LSTM_rec_kernel = (uint32_t *) pmsis_l2_malloc(sizeof(__uint32_t));
    Dec_LSTM_rec_kernel = (uint32_t *) pmsis_l2_malloc(sizeof(__uint32_t));    
	buff = (int16_t *) pmsis_l2_malloc(BUFFER_SIZE);
    if (buff == NULL)
    {
        printf("Buffer alloc failed !\n");
        pmsis_exit(-1);
    }

	    /* Init & open ram. */
    pi_hyperram_conf_init(&ram_conf);
    pi_open_from_conf(&ram, &ram_conf);
    if (pi_ram_open(&ram))
    {
        printf("Error ram open !\n");
        pmsis_l2_malloc_free(buff, (uint32_t) BUFFER_SIZE);
        pmsis_exit(-2);
    }
    
    /* Init & open flash. */
    pi_hyperflash_conf_init(&flash_conf);
    pi_open_from_conf(&flash, &flash_conf);
    if (pi_flash_open(&flash))
    {
        printf("Error flash open !\n");
        pmsis_l2_malloc_free(buff, (uint32_t) BUFFER_SIZE);
        pi_ram_close(&ram);
        pmsis_exit(-3);
    }
    
    /* Open filesystem on flash. */
    pi_fs_conf_init(&fs_conf);
    fs_conf.flash = &flash;
    pi_open_from_conf(&fs, &fs_conf);

    int32_t err = pi_fs_mount(&fs);
    if (err)
    {
        printf("Error FS mounting : %ld !\n", err);
        pmsis_l2_malloc_free(buff, (uint32_t) BUFFER_SIZE);
        pi_flash_close(&ram);
        pi_ram_close(&ram);    
        pmsis_exit(-4);
    }
    printf("FS mounted.\n");
	printf("%lx\n",*Enc_LSTM_rec_kernel);

    CopyFileFromFlashToL3(&fs, "Dec_rec_ker.dat", Dec_LSTM_rec_kernel);
    CopyFileFromFlashToL3(&fs, "Enc_rec_ker.dat", Enc_LSTM_rec_kernel);

    pi_fs_unmount(&fs);
    printf("FS unmounted.\n");
    pi_flash_close(&flash);

	/*Carico i coefficienti e gli ingressi*/
	Enc_LSTM_bias = Encoder_Lstm_Bias;
	Enc_LSTM_kernel = Encoder_Lstm_Kernel;
	//Enc_LSTM_rec_kernel = Encoder_Lstm_Recurrent_Kernel;

	Dec_LSTM_bias = Decoder_Lstm_Bias;
	Dec_LSTM_kernel = Decoder_Lstm_Kernel;
	//Dec_LSTM_rec_kernel = Decoder_Lstm_Recurrent_Kernel;	

	DENSE_bias = Dense_Bias;
	DENSE_kernel = Dense_Kernel;
	
	In = Ingressi;

    pmsis_l2_malloc_free(buff, (uint32_t) BUFFER_SIZE);

  	/* Alloco spazio per le uscite e le variabili d'appoggio */

	//c_0 = (int *) pi_l2_malloc(units*sizeof(int));    
	//h_0 = (int *) pi_l2_malloc(units*sizeof(int));
	
	
	printf("Opening the Cluster\n");
    struct pi_device cluster_dev;
    struct pi_cluster_conf conf;
    // Init cluster configuration structure. 
    pi_cluster_conf_init(&conf);
    conf.id = (uint32_t) CID;   // Cluster ID. 
    // Configure & open cluster. 
    pi_open_from_conf(&cluster_dev, (void *) &conf);
    if (pi_cluster_open(&cluster_dev))
    {
        printf("Cluster open failed !\n");
        pmsis_exit(-2);
    }

    //Allocate the predetermined memory size in the shared L1 memory that the cluster can act on. 
    L1_Memory = (char *) pi_l1_malloc(&cluster_dev, _L1_Memory_SIZE);
    L2_Memory = (char *) pi_l2_malloc(_L2_Memory_SIZE);
    if (L1_Memory == NULL )
    {
        printf("Memory Allocation Error! Quit...\n");
        pmsis_exit(-3);
    }


	cluster_perf = rt_alloc(RT_ALLOC_L2_CL_DATA, sizeof(rt_perf_t));

    // Prepare cluster task and send it to cluster. 
    struct pi_cluster_task task = {0};
    task.entry = test_on_cluster;
    task.arg = NULL;
    task.stack_size = (uint32_t) STACK_SIZE;

    //Offloading Task to cluster. 
    pi_cluster_send_task_to_cl(&cluster_dev, &task);

    pi_l1_free(&cluster_dev, L1_Memory, _L1_Memory_SIZE);
    pmsis_l2_malloc_free(L2_Memory,_L2_Memory_SIZE);

    printf("Close cluster after end of computation.\n");

    pi_ram_free(&ram, *Enc_LSTM_rec_kernel, (uint32_t) LSTM_rec_kernel_Size);
    pi_ram_free(&ram,*Dec_LSTM_rec_kernel, (uint32_t) LSTM_rec_kernel_Size);
    pi_ram_close(&ram);	
	
 	pmsis_exit(errors);
}

int main(void)
{
    printf("\n\n\t *** NeuralNet ***\n\n");
    return pmsis_kickoff((void *) run_MatMult);
}



