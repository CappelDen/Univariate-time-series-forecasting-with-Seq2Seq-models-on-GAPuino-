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
	Hard Sigmoid function(ingresso(32,24)) risultato(16,12)   27=Norm+16
	Da aggiustare
**************************************************************************************************************************************/

short int hard_sig(int z, unsigned int Norm) {
	unsigned int inv=0;
	int i = (z>>Norm); //(32,12)
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
		r =  __builtin_pulp_macs(p0_2, i,Acc); 		
	else
		r = 0;

	if (inv==1)
		{r=(p1-r)>>Norm;
		return r=(short int) r;}
	else
		return r=(short int) (r>>Norm);

}


/**************************************************************************************************************************************
	ENCODER
**************************************************************************************************************************************/

void KerZEnc16(KerZEnc16_ArgT *Arg)

{
    short int * __restrict__ In = Arg->In;//16,12
	unsigned int Iterazione = Arg-> Iterazione;
    short int * __restrict__ H_0 = Arg->H_0; //16,12
    unsigned int W_H = Arg->W_H; //neuroni
    short int * __restrict__ Kernel = Arg->Kernel;//16,12
    short int * __restrict__ Rec_Kernel = Arg->Rec_Kernel;//16,12
    unsigned int W_Rec_Kernel = Arg->W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias = Arg->Bias;//32,24
    short int * __restrict__ Z = Arg->Z;//16,12
    unsigned int OutFirstCol = Arg->OutFirstCol;
    unsigned int Norm = Arg->Norm;

    unsigned int Col,i;
	int S;

    unsigned int CoreId = gap_coreid();
    unsigned int ChunkCell = ChunkSize(W_Rec_Kernel);
    unsigned int First = CoreId*ChunkCell, Last  = Min(W_Rec_Kernel, First+ChunkCell);

	for (Col=First; Col<Last; Col++) {
            S = Bias[Col+OutFirstCol]+ In[Iterazione]*Kernel[Col+OutFirstCol];
			//if(CoreId==0&&Iterazione==1&&Col==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}

            for (i=0; i<W_H/2; i++) {
				//if(CoreId==0&&Iterazione==1&&Col==0){printf("H_0[%d]=%d     Rec_Kernel[%d]=%d\n",2*i,H_0[(2*i  )],(2*i  )*W_Rec_Kernel+Col,Rec_Kernel[(2*i  )*W_Rec_Kernel+Col]);}
                S = S + H_0[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
				//if(CoreId==0&&Iterazione==1&&Col==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}
				//if(CoreId==0&&Iterazione==1&&Col==0){printf("H_0[%d]=%d     Rec_Kernel[%d]=%d\n",2*i+1,H_0[(2*i+1 )],(2*i+1)*W_Rec_Kernel+Col,Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col]);}
                S = S + H_0[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];
				//if(CoreId==0&&Iterazione==1&&Col==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}

            }
            if (W_H&0x1) S += H_0[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];//32,22
			//if(CoreId==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}

			Z[Col+OutFirstCol] = hard_sig(S,Norm);
			//if(CoreId==0){printf("Z [%d]=%d\n",Col+OutFirstCol,Z[Col+OutFirstCol]);}		
    }
    gap_waitbarrier(0);
}


void KerProd16(KerProd16_ArgT *Arg)
{
    short int * __restrict__ Z = Arg->Z;
    short int * __restrict__ H_0 = Arg->H_0; //16,12
    unsigned int W_H = Arg->W_H; //neuroni
	short int * __restrict__ prod1 = Arg->prod1;
	int * __restrict__ prod2 = Arg->prod2;
    unsigned int Norm = Arg->Norm;

    unsigned int CoreId = gap_coreid();
    unsigned int ChunkCell = ChunkSize(W_H);
    unsigned int First = CoreId*ChunkCell, Last  = Min(W_H, First+ChunkCell);
	
	short int *z = &Z[0];
	short int *r = &Z[W_H];
	unsigned int Col;
	int S1,S2;
//calcolo prodotto necessario per h_tilde
    for (Col=First; Col<Last; Col++) {
            S1 = r[Col]*H_0[Col];
			S2 = z[Col]*H_0[Col];
			prod1[Col] = gap_clip(gap_roundnorm_reg(S1, Norm), 15);
			prod2[Col] = S2;
    }
	gap_waitbarrier(0);
}

void KerGRUEnclayer16(KerGRUEnclayer16_ArgT *Arg)
{
	short int *__restrict__ Z = Arg->Z;
	short int *__restrict__ In = Arg->In;
	unsigned int Iterazione = Arg-> Iterazione;
    short int * __restrict__ H_0 = Arg->H_0;
	unsigned int W_H= Arg-> W_H;//neuroni
    short int * __restrict__ Kernel = Arg->Kernel;	
    short int * __restrict__ Rec_Kernel = Arg->Rec_Kernel;
    unsigned int W_Rec_Kernel = Arg->W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias = Arg->Bias;
	short int * __restrict__ prod1 = Arg->prod1;
	int * __restrict__ prod2 = Arg->prod2;
	unsigned int OutFirstCol = Arg->OutFirstCol;
	unsigned int Norm = Arg->Norm;
	
    unsigned int CoreId = gap_coreid();
    unsigned int ChunkCell = ChunkSize(W_Rec_Kernel);
    unsigned int First = CoreId*ChunkCell, Last  = Min(W_Rec_Kernel, First+ChunkCell);

    unsigned int Col,i;
	short int h_tilde;
	short int one = 1<<Norm;
	int h1,h2,S;
	unsigned short int index;

//calcolo h_tilde
	for (Col=First; Col<Last; Col++) {
 			index = Col + OutFirstCol;
            S = Bias[index]+ In[Iterazione]*Kernel[index];
		//if(CoreId==0&&Col==0){printf("Bias[%d]=%d  In[%d]=%d   Kernel[%d]=%d  W_Rec_kernel=%d\n",index,Bias[index],Iterazione,In[Iterazione] ,index,Kernel[index],W_Rec_Kernel);}
            for (i=0; i<W_H/2; i++) {
				//if(CoreId==0&&Col==0){printf("prod1[%d]=%d     Rec_Kernel[%d]=%d\n",2*i,prod1[(2*i  )],(2*i  )*W_Rec_Kernel+Col,Rec_Kernel[(2*i  )*W_Rec_Kernel+Col]);}
                S = S + prod1[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
				//if(CoreId==0&&Col==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}
				//if(CoreId==0&&Col==0){printf("prod1[%d]=%d     Rec_Kernel[%d]=%d\n",2*i+1,prod1[(2*i+1 )],(2*i+1)*W_Rec_Kernel+Col,Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col]);}

                S = S + prod1[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];
				//if(CoreId==0&&Col==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}

            }
            if (W_H&0x1) S += prod1[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];//32,24
			
			S = S>>Norm;
			h_tilde = tan_h((short int) S);//approssimazione per eccesso
			h1 = (one - Z[index])*h_tilde;
			//if(CoreId==0&&Col==0){printf("Z[%d]=%d     \n",index,Z[index]);}
			h2 = prod2[index];
			H_0[index] = (short int) gap_addroundnorm_reg(h1,h2,Norm);			
    }
	gap_waitbarrier(0);
}


/**************************************************************************************************************************************
	DECODER
**************************************************************************************************************************************/


void KerZDec16(KerZDec16_ArgT *Arg)

{
    short int * __restrict__ H_0 = Arg->H_0; //16,12
    unsigned int W_H = Arg->W_H; //neuroni
    short int * __restrict__ Rec_Kernel = Arg->Rec_Kernel;//16,12
    unsigned int W_Rec_Kernel = Arg->W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias = Arg->Bias;//32,24
    short int * __restrict__ Z = Arg->Z;//16,12
    unsigned int OutFirstCol = Arg->OutFirstCol;
    unsigned int Norm = Arg->Norm;

    unsigned int Col,i;
	int S;

    unsigned int CoreId = gap_coreid();
    unsigned int ChunkCell = ChunkSize(W_Rec_Kernel);
    unsigned int First = CoreId*ChunkCell, Last  = Min(W_Rec_Kernel, First+ChunkCell);
	//if(CoreId==0){for(unsigned int c=0;c<W_H;c++){printf("H_0[%d]=%d\n",c,H_0[c]);}}
	for (Col=First; Col<Last; Col++) {
            S = Bias[Col+OutFirstCol];
            for (i=0; i<W_H/2; i++) {
				//if(CoreId==0&&Col==0){printf("H_0[%d]=%d     Rec_Kernel[%d]=%d\n",2*i,H_0[(2*i  )],(2*i  )*W_Rec_Kernel+Col,Rec_Kernel[(2*i  )*W_Rec_Kernel+Col]);}

                S = S + H_0[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
				//if(CoreId==0&&Col==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}
				//if(CoreId==0&&Col==0){printf("H_0[%d]=%d     Rec_Kernel[%d]=%d\n",2*i+1,H_0[(2*i+1 )],(2*i+1)*W_Rec_Kernel+Col,Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col]);}

                S = S + H_0[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];
				//if(CoreId==0&&Col==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}

            }
            if (W_H&0x1) S += H_0[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];//32,22
			Z[Col+OutFirstCol] = hard_sig(S,Norm);
			//if(CoreId==0){printf("Z [%d]=%d\n",Col+OutFirstCol,Z[Col+OutFirstCol]);}						
    }
    gap_waitbarrier(0);
}



void KerGRUDeclayer16(KerGRUDeclayer16_ArgT *Arg)
{
	short int *__restrict__ Z = Arg->Z;
    short int * __restrict__ H_0 = Arg->H_0;
	unsigned int W_H= Arg-> W_H;//neuroni
    short int * __restrict__ Rec_Kernel = Arg->Rec_Kernel;
    unsigned int W_Rec_Kernel = Arg->W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias = Arg->Bias;
	short int * __restrict__ prod1 = Arg->prod1;
	int * __restrict__ prod2 = Arg->prod2;
	unsigned int OutFirstCol = Arg->OutFirstCol;
	unsigned int Norm = Arg->Norm;
	
    unsigned int CoreId = gap_coreid();
//    unsigned int ChunkCell = ChunkSize(W_Rec_Kernel);
//    unsigned int First = CoreId*ChunkCell, Last  = Min(W_Rec_Kernel, First+ChunkCell);

   unsigned int ChunkCell = ChunkSizeMod(W_Rec_Kernel,CoreId);
	unsigned int First = 0;	
	if (CoreId>=(W_Rec_Kernel&(7)))
		First = CoreId*ChunkCell+(W_Rec_Kernel&(7));
	else
		First = CoreId*ChunkCell;
	unsigned int Last = Min(First+ChunkCell, W_Rec_Kernel);

    unsigned int Col,i;
	short int h_tilde;
	short int one = 1<<Norm;
	int h1,h2,S;
	unsigned short int index;

//calcolo h_tilde
	for (Col=First; Col<Last; Col++) {
 			index = Col + OutFirstCol;
            S = Bias[index];
            for (i=0; i<W_H/2; i++) {
				//if(CoreId==0&&Col==0){printf("prod1[%d]=%d     Rec_Kernel[%d]=%d\n",2*i,prod1[(2*i  )],(2*i  )*W_Rec_Kernel+Col,Rec_Kernel[(2*i  )*W_Rec_Kernel+Col]);}
                S = S + prod1[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
				//if(CoreId==0&&Col==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}
				//if(CoreId==0&&Col==0){printf("prod1[%d]=%d     Rec_Kernel[%d]=%d\n",2*i+1,prod1[(2*i+1 )],(2*i+1)*W_Rec_Kernel+Col,Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col]);}

                S = S + prod1[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];
				//if(CoreId==0&&Col==0){printf("S [%d]=%d\n",Col+OutFirstCol,S);}

            }
            if (W_H&0x1) S += prod1[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];//32,24
			
			S = S>>Norm;
			h_tilde = tan_h((short int) S);//approssimazione per eccesso
			h1 = (one - Z[index])*h_tilde;
			h2 = prod2[index];
			H_0[index] = (short int) gap_addroundnorm_reg(h1,h2,Norm);			
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
	unsigned int ChunkCell = ChunkSize(InSize);
	unsigned int First = CoreId*ChunkCell, Last = Min(First+ChunkCell, InSize);
/*	
	unsigned int ChunkCell = ChunkSizeMod(InSize, CoreId);
	unsigned int First = 0;
	if (CoreId>=(InSize&(7)))
		First = CoreId*ChunkCell+(InSize&(7));
	else
		First = CoreId*ChunkCell;
	unsigned int Last = Min(First+ChunkCell, InSize);
*/
	unsigned int Size = Last-First;// n.neuroni per ciascun core

	int Acc=0;
	for (unsigned int j=0;j<Size;j++) {
		Acc= gap_macs(Acc,(int)In[First+j],(int)Filter[First+j]);
	}
	Reduct[CoreId] = Acc;

	gap_waitbarrier(0);
	if (CoreId==0) {
		Acc = *Bias;
		for (int j=0;j<gap_ncore();j++) Acc += Reduct[j];
		Out[Iterazione] = gap_clip(gap_roundnorm_reg(Acc, Norm),15);
		//printf("fine dense layer\n");
	}

	gap_waitbarrier(0);

		
}
