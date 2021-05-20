/*
 * Copyright (C) 2017 GreenWaves Technologies
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 *
 */

#include <stdio.h>
#include "Gap.h"
#include "EncDecKernel.h"
#include "UtilityFunc16_12.h"


#define Min(a, b)               (((a)<(b))?(a):(b))

static int CoreCountDynamic = 1;
static int ActiveCore = gap_ncore();
/*
static inline unsigned int __attribute__((always_inline)) ChunkSize(unsigned int X)

{
        unsigned int NCore;
        unsigned int Log2Core;
        unsigned int Chunk;

        if (CoreCountDynamic) NCore = ActiveCore; else NCore = gap_ncore();
        Log2Core = gap_fl1(NCore);
        Chunk = (X>>Log2Core) + ((X&(NCore-1))!=0);
        return Chunk;
}
*/
static inline unsigned int __attribute__((always_inline)) ChunkSizeMod(unsigned int X, unsigned int CoreId)

{
	unsigned int NCore;
	unsigned int Log2Core;
	unsigned int Chunk;
	unsigned int Reminder;

	if (CoreCountDynamic) NCore = ActiveCore; else NCore = gap_ncore();
	Log2Core = gap_fl1(NCore);
	Chunk = (X>>Log2Core);
	Reminder = X&(NCore-1);
	if (Reminder != 0) {
		if(CoreId<Reminder) Chunk = Chunk+1;
	}
	return Chunk;
}


/**************************************************************************************************************************************
	Hard Sigmoid function(ingresso(32,24)) risultato(16,12)   27=Norm+16
	Da aggiustare
**************************************************************************************************************************************/

short int hard_sig(int z, unsigned int Norm) {
	unsigned int inv=0;
	int i = z>>Norm; //(32,12)
	int p2_5 = -10240;//-2.5(32,12)
	int Acc = 8388608;//0.5(32,24)
	int p0_2 = 819;//0.2(32,12)
	int p1 = 16777216; //1(32,24)

	int r;	
	if (i>0) {
		i=-i;
		inv=1;
		}
	if (i>=p2_5)
		r =  __builtin_pulp_macs(Acc, p0_2, i); 		
	else
		r = 0;

	if (inv==1)
		{r=(p1-r)>>Norm;
		return r=(short int) r;}
	else
		return r=(short int) (r>>Norm);

}

void KerGRUEncLayer16(KerGRUEncLayer16_ArgT *Arg)

{
    short int * __restrict__ In = Arg->In;//16,12
	unsigned int Iterazione = Arg-> Iterazione;
    short int * __restrict__ H_0 = Arg->H_0; //16,12
    unsigned int W_H = Arg->W_H; //neuroni
    short int * __restrict__ Kernel_z = Arg->Kernel_z;//16,12
    short int * __restrict__ Kernel_r = Arg->Kernel_r;//16,12
    short int * __restrict__ Kernel_h = Arg->Kernel_h;//16,12
    short int * __restrict__ Rec_Kernel_z = Arg->Rec_Kernel_z;//16,12
    short int * __restrict__ Rec_Kernel_r = Arg->Rec_Kernel_r;//16,12
    short int * __restrict__ Rec_Kernel_h = Arg->Rec_Kernel_h;//16,12
    unsigned int W_Rec_Kernel = Arg->W_Rec_Kernel;  //neuroni ma possono avere tiling  
    int * __restrict__ Bias_z = Arg->Bias_z;//32,24
    int * __restrict__ Bias_r = Arg->Bias_r;//32,24
    int * __restrict__ Bias_h = Arg->Bias_h;//32,24
    unsigned int OutFirstCol = Arg->OutFirstCol;
    unsigned int Norm = Arg->Norm;

    unsigned int CoreId = gap_coreid();
    unsigned int ChunkCell = ChunkSizeMod(W_Rec_Kernel,CoreId);
	unsigned int First = 0;

	if (CoreId>=(W_Rec_Kernel&(7)))
		First = CoreId*ChunkCell+(W_Rec_Kernel&(7));
	else
		First = CoreId*ChunkCell;
	unsigned int Last = Min(First+ChunkCell, W_Rec_Kernel);
    unsigned int Size = Last-First;

    short int z[W_Rec_Kernel],r[W_Rec_Kernel],h_tilde[W_Rec_Kernel];
    short int prod1[]
    unsigned int Col; 
    unsigned int i=0;
	int S;
//calcolo z
    for (Col=First; Col<Last; Col++,i++) {
        S = Bias_z[Col+OutFirstCol]+ In[Iterazione]*Kernel_z[Col+OutFirstCol];
        for (i=0; i<W_H/2; i++) {
            S = S + H_0[(2*i  )] * Rec_Kernel_z[(2*i  )*W_Rec_Kernel+Col];
            S = S + H_0[(2*i+1)] * Rec_Kernel_z[(2*i+1)*W_Rec_Kernel+Col];
        }
        if (W_H&0x1) S += H_0[W_H-1]*Rec_Kernel_z[Col+((W_H - 1)*W_Rec_Kernel)];//32,22
        z[i] = hard_sig(S,Norm);
    }
//calcolo r
   i=0; 
    for (Col=First; Col<Last; Col++,i++) {
        S = Bias_r[Col+OutFirstCol]+ In[Iterazione]*Kernel_r[Col+OutFirstCol];
        for (i=0; i<W_H/2; i++) {
            S = S + H_0[(2*i  )] * Rec_Kernel_r[(2*i  )*W_Rec_Kernel+Col];
            S = S + H_0[(2*i+1)] * Rec_Kernel_r[(2*i+1)*W_Rec_Kernel+Col];
        }
        if (W_H&0x1) S += H_0[W_H-1]*Rec_Kernel_r[Col+((W_H - 1)*W_Rec_Kernel)];//32,22
        r[i] = hard_sig(S,Norm);
    }    

}