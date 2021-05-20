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

void KerZEnc16(    short int * __restrict__ In,//16,12
	unsigned int Iterazione,
    short int * __restrict__ H_0, //16,12
    unsigned int W_H, //neuroni
    short int * __restrict__ Kernel,//16,12
    short int * __restrict__ Rec_Kernel,//16,12
    unsigned int W_Rec_Kernel,  //4*neuroni  
    int * __restrict__ Bias,//32,24
    short int * __restrict__ Z,//16,12
    unsigned int OutFirstCol,
    unsigned int Norm)

{


    unsigned int Col,i;
	int S;

	for (Col=0; Col<W_Rec_Kernel; Col++) {
            S = Bias[Col+OutFirstCol]+ In[Iterazione]*Kernel[Col+OutFirstCol];
            for (i=0; i<W_H/2; i++) {
                S = S + H_0[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
                S = S + H_0[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];
            }
            if (W_H&0x1) S += H_0[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];//32,22
			Z[Col+OutFirstCol] = hard_sig(S,Norm);
    }
}


void KerProd16(    short int * __restrict__ Z,
    short int * __restrict__ H_0, //16,12
    unsigned int W_H, //neuroni
	short int * __restrict__ prod1,
	int * __restrict__ prod2,
    unsigned int Norm)
{

	
	short int *z = &Z[0];
	short int *r = &Z[W_H];
	unsigned int Col;
	int S1,S2;
//calcolo prodotto necessario per h_tilde
    for (Col=0; Col<W_H; Col++) {
            S1 = r[Col]*H_0[Col];
			S2 = z[Col]*H_0[Col];
			prod1[Col] = gap_clip(gap_roundnorm_reg(S1, Norm), 15);
			prod2[Col] = S2;
    }
}

void KerGRUEnclayer16(	short int *__restrict__ Z,
	short int *__restrict__ In,
	unsigned int Iterazione,
    short int * __restrict__ H_0,
	unsigned int W_H,//neuroni
    short int * __restrict__ Kernel,	
    short int * __restrict__ Rec_Kernel,
    unsigned int W_Rec_Kernel,  //4*neuroni  
    int * __restrict__ Bias,
	short int * __restrict__ prod1,
	int * __restrict__ prod2,
	unsigned int OutFirstCol,
	unsigned int Norm)
{

	
    unsigned int Col,i;
	short int h_tilde;
	short int one = 1<<Norm;
	int h1,h2,S;
	unsigned short int index;

//calcolo h_tilde
	for (Col=0; Col<W_Rec_Kernel; Col++) {
 			index = Col + OutFirstCol;
            S = Bias[index]+ In[Iterazione]*Kernel[index];
            for (i=0; i<W_H/2; i++) {
                S = S + prod1[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
                S = S + prod1[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];

            }
            if (W_H&0x1) S += prod1[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];//32,24
			
			S = S>>Norm;
			h_tilde = tan_h((short int) S);//approssimazione per eccesso
			h1 = (one - Z[index])*h_tilde;
			h2 = prod2[index];
			H_0[index] = (short int) gap_addroundnorm_reg(h1,h2,Norm);			
    }

}


/**************************************************************************************************************************************
	DECODER
**************************************************************************************************************************************/


void KerZDec16(    
	short int * __restrict__ H_0, //16,12
    unsigned int W_H, //neuroni
    short int * __restrict__ Rec_Kernel,//16,12
    unsigned int W_Rec_Kernel,  //4*neuroni  
    int * __restrict__ Bias,//32,24
    short int * __restrict__ Z,//16,12
    unsigned int OutFirstCol,
    unsigned int Norm)

{

    unsigned int Col,i;
	int S;

    
	for (Col=0; Col<W_Rec_Kernel; Col++) {
            S = Bias[Col+OutFirstCol];
            for (i=0; i<W_H/2; i++) {

                S = S + H_0[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
                S = S + H_0[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];
            }
            if (W_H&0x1) S += H_0[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];//32,22
			Z[Col+OutFirstCol] = hard_sig(S,Norm);
    }

}



void KerGRUDeclayer16(
	short int *__restrict__ Z,
    short int * __restrict__ H_0,
	unsigned int W_H,//neuroni
    short int * __restrict__ Rec_Kernel,
    unsigned int W_Rec_Kernel,  //4*neuroni  
    int * __restrict__ Bias,
	short int * __restrict__ prod1,
	int * __restrict__ prod2,
	unsigned int OutFirstCol,
	unsigned int Norm)
{	
    unsigned int Col,i;
	short int h_tilde;
	short int one = 1<<Norm;
	int h1,h2,S;
	unsigned short int index;

//calcolo h_tilde
	for (Col=0; Col<W_Rec_Kernel; Col++) {
 			index = Col + OutFirstCol;
            S = Bias[index];
            for (i=0; i<W_H/2; i++) {
                S = S + prod1[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
                S = S + prod1[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];
            }
            if (W_H&0x1) S += prod1[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];//32,24
			
			S = S>>Norm;
			h_tilde = tan_h((short int) S);//approssimazione per eccesso
			h1 = (one - Z[index])*h_tilde;
			h2 = prod2[index];
			H_0[index] = (short int) gap_addroundnorm_reg(h1,h2,Norm);			
    }

}

/**************************************************************************************************************************************
	DENSE input short int(16,12)
**************************************************************************************************************************************/
void KerDENSElayer16(
	short int * __restrict__ In,//16,12
	unsigned int InSize,//lunghezza sequenza di ingresso
	short int * __restrict__ Filter,//16,12
	int * __restrict__ Bias,//32,24
	unsigned int Norm,//12
	short int * __restrict__ Out,//16,12
	unsigned int Iterazione)

{
	int Acc=*Bias;
	for (unsigned int j=0;j<InSize;j++) {
		Acc= gap_macs(Acc,(int)In[j],(int)Filter[j]);
	}
	Out[Iterazione] = gap_clip(gap_roundnorm_reg(Acc, Norm),15);
	
}
