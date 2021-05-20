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
#include "UtilityFunc16_11.h"


#define Min(a, b)               (((a)<(b))?(a):(b))

static int CoreCountDynamic = 1;
static int ActiveCore = gap_ncore();

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
	Hard Sigmoid function(ingresso(16,11)) risultato(16,11)   27=Norm+16
**************************************************************************************************************************************/

short int hard_sig(short int z, unsigned int Norm) {
	unsigned int inv=0;
	int i = z<<16; //(32,27)
	int p2_5 = -335544320;//-2.5(32,27)
	int Acc = 2097152;//0.5(32,22)
	int p0_2 = 26843546;//0.2(32,27)
	int p1 = 4194304; //1(32,22)

	int r;	
	if (i>0) {
		i=-i;
		inv=1;
		}
	if (i>=p2_5)
		r = gap_machhs(Acc, p0_2, i); //32,22		
	else
		r = 0;

	if (inv==1)
		{r=(p1-r)>>Norm;
		return r=(short int) r;}
	else
		return r=(short int) (r>>Norm);

}


/**************************************************************************************************************************************
	Bias  modificato in int e aggiungo norm alla funzione dell'LSTM e come input a hard sigmoid
**************************************************************************************************************************************/

void KerZComputation16(KerZComputation16_ArgT *Arg)

{
    short int * __restrict__ In = Arg->In;
	unsigned int Iterazione = Arg-> Iterazione;
    short int * __restrict__ H_0 = Arg->H_0; 
    unsigned int W_H = Arg->W_H; //neuroni
    short int * __restrict__ Kernel = Arg->Kernel;
    short int * __restrict__ Rec_Kernel = Arg->Rec_Kernel;
    unsigned int W_Rec_Kernel = Arg->W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias = Arg->Bias;
    short int * __restrict__ Z = Arg->Z;
    unsigned int OutFirstCol = Arg->OutFirstCol;
    unsigned int Norm = Arg->Norm;

    unsigned int Col, i;

    unsigned int CoreId = gap_coreid();
    //unsigned int ChunkCell = ChunkSize(W_Rec_Kernel);
    //unsigned int First = CoreId*ChunkCell, Last  = Min(W_Rec_Kernel, First+ChunkCell);

	unsigned int ChunkCell = ChunkSizeMod(W_Rec_Kernel,CoreId);
	unsigned int First = 0;	
	if (CoreId>=(W_Rec_Kernel&(7)))
		First = CoreId*ChunkCell+(W_Rec_Kernel&(7));
	else
		First = CoreId*ChunkCell;
	unsigned int Last = Min(First+ChunkCell, W_Rec_Kernel);

	short int BuffCol[W_H];
	v2s *VH0 = (v2s *) H_0;
	v2s *VBuff = (v2s *) &BuffCol;
	int S = 0;

	for (Col=First; Col<Last; Col++) {
		for (i=0;i<W_H; i++) {
			BuffCol[i] = Rec_Kernel[i*W_Rec_Kernel+Col];
			}
        
		S = Bias[Col+OutFirstCol]+ In[Iterazione]*Kernel[Col+OutFirstCol];

		for (i=0; i<W_H/4; i++) {
			S = gap_sumdotp2(VH0[2*i  ], VBuff[2*i  ], S);
			S = gap_sumdotp2(VH0[2*i+1], VBuff[2*i+1], S);
		}
		for (i=(W_H/4)*4; i<W_H; i++) {
		S += H_0[i] * BuffCol[i];
		}

		Z[Col+OutFirstCol] = gap_clip(gap_roundnorm_reg(S, Norm), 15);//approssimazione per eccesso
		
    }
    gap_waitbarrier(0);
}


void KerZComputationDec16(KerZComputationDec16_ArgT *Arg)

{
    short int * __restrict__ H_0 = Arg->H_0; 
    unsigned int W_H = Arg->W_H; //neuroni
    short int * __restrict__ Kernel = Arg->Kernel;
    short int * __restrict__ Rec_Kernel = Arg->Rec_Kernel;
    unsigned int W_Rec_Kernel = Arg->W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias = Arg->Bias;
    short int * __restrict__ Z = Arg->Z;
    unsigned int OutFirstCol = Arg->OutFirstCol;
    unsigned int Norm = Arg->Norm;

    unsigned int Col, i;

    unsigned int CoreId = gap_coreid();
    unsigned int ChunkCell = ChunkSizeMod(W_Rec_Kernel,CoreId);
	unsigned int First = 0;	
	if (CoreId>=(W_Rec_Kernel&(7)))
		First = CoreId*ChunkCell+(W_Rec_Kernel&(7));
	else
		First = CoreId*ChunkCell;
	unsigned int Last = Min(First+ChunkCell, W_Rec_Kernel);

	short int BuffCol[W_H];
	v2s *VH0 = (v2s *) H_0;
	v2s *VBuff = (v2s *) &BuffCol;
	int S = 0;

	for (Col=First; Col<Last; Col++) {
		for (i=0;i<W_H; i++) {
			BuffCol[i] = Rec_Kernel[i*W_Rec_Kernel+Col];
			}
        
		S = Bias[Col+OutFirstCol];
		for (i=0; i<W_H/4; i++) {
			S = gap_sumdotp2(VH0[2*i  ], VBuff[2*i  ], S);
			S = gap_sumdotp2(VH0[2*i+1], VBuff[2*i+1], S);
		}
		for (i=(W_H/4)*4; i<W_H; i++) {
		S += H_0[i] * BuffCol[i];
		}

		Z[Col+OutFirstCol] = gap_clip(gap_roundnorm_reg(S, Norm), 15);//approssimazione per eccesso
	}

    gap_waitbarrier(0);
}


void KerLSTMlayer16(KerLSTMlayer16_ArgT *Arg)
{
	short int *__restrict__ Z = Arg->Z;
    short int * __restrict__ C_0 = Arg->C_0;
	unsigned int W_C = Arg-> W_C;//neuroni
    short int * __restrict__ H_0 = Arg->H_0; 
	unsigned int Norm = Arg->Norm;
	

	unsigned int CoreId = gap_coreid();
    //unsigned int ChunkCell = ChunkSize(W_C);
    //unsigned int First = CoreId*ChunkCell, Last  = Min(W_C, First+ChunkCell);
    unsigned int ChunkCell = ChunkSizeMod(W_C,CoreId);
	unsigned int First = 0;
	if (CoreId>=(W_C&(7)))
		First = CoreId*ChunkCell+(W_C&(7));
	else
		First = CoreId*ChunkCell;
	unsigned int Last = Min(First+ChunkCell, W_C);
	unsigned int Size = Last-First;

	short int i[Size];
	short int f[Size];
	short int c_tilde[Size];
	short int o[Size];
	int C_n[Size];
	int H_n[Size]; 

    unsigned int j;
	
	for (j=0; j<Size; j++) {
		i[j] = hard_sig(Z[First+j],Norm);//16,12
		f[j] = hard_sig(Z[First+W_C+j],Norm);//16,12
		//c_tilde[j] = Z[First+2*W_C+j];//16,12
		c_tilde[j] = tan_h(Z[First+2*W_C+j]);//16,12
		o[j] = hard_sig(Z[First+3*W_C+j],Norm);//16,12

		C_n[j] = f[j]*C_0[First+j];//32,24
		C_n[j] = C_n[j]+(i[j]*c_tilde[j]);//32,12
		C_n[j] = C_n[j]>>Norm;

		H_n[j] = tan_h((short int) C_n[j]);//16,12
		H_n[j] = o[j]*H_n[j];//32,12
		H_n[j] = H_n[j]>>Norm;
		
		C_0[First+j] =(short int) C_n[j];
		H_0[First+j] =(short int) H_n[j];
	}
	gap_waitbarrier(0);
}


/**************************************************************************************************************************************
	DENSE input short int(16,12)
**************************************************************************************************************************************/
void KerDENSElayer16(KerDENSElayer16_ArgT *Arg)

{
	short int * __restrict__ In = Arg->In;//16,12
	unsigned int InSize = Arg->InSize;//lunghezza sequenza di ingresso
	short int * __restrict__ Filter = Arg->Filter;//16,12
	int * __restrict__ Bias = Arg->Bias;//32,24
	unsigned int Norm = Arg->Norm;//12
	short int * __restrict__ Out = Arg->Out;//16,12
	unsigned int Iterazione = Arg->Iterazione;
	
	static L1_CL_MEM int Reduct[8];

	unsigned int CoreId = gap_coreid();
	unsigned int ChunkCell = ChunkSizeMod(InSize, CoreId);
	unsigned int First = 0;
	if (CoreId>=(InSize&(7)))
		First = CoreId*ChunkCell+(InSize&(7));
	else
		First = CoreId*ChunkCell;
	unsigned int Last = Min(First+ChunkCell, InSize);
	unsigned int Size = Last-First;// n.neuroni per ciascun core
	
    	unsigned int j;

	v2s *VIn1 = (v2s *) (&In[First]);
	v2s *VBuff = (v2s *) (&Filter[First]);

	int Acc=0;
	for (j=0;j<Size/4;j++) {
		Acc = gap_sumdotp2(VIn1[2*j  ], VBuff[2*j  ], Acc);
		Acc = gap_sumdotp2(VIn1[2*j+1], VBuff[2*j+1], Acc);

	}
    	for (j=(Size/4)*4; j<Size; j++) {
		Acc += In[First + j] * Filter[First+j];
	}
		
	Reduct[CoreId] = Acc;

	gap_waitbarrier(0);
	if (CoreId==0) {
		Acc = *Bias;
		for (j=0;j<gap_ncore();j++) Acc += Reduct[j];
		Out[Iterazione] = gap_clip(gap_roundnorm_reg(Acc, Norm),15);
		//printf("fine dense layer\n");
	}

	gap_waitbarrier(0);
		
}


