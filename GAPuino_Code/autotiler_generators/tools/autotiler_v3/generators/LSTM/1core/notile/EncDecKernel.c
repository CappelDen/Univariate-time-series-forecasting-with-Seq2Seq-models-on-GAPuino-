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

void KerZComputation16( short int * __restrict__ In,
						unsigned int Iterazione,
						short int * __restrict__ H_0,
						unsigned int W_H,
						short int * __restrict__ Kernel,
						short int * __restrict__ Rec_Kernel,
						unsigned int W_Rec_Kernel,
						int * __restrict__ Bias,
						short int * __restrict__ Z,
						unsigned int OutFirstCol,
						unsigned int Norm)

{


    unsigned int Col, i;

	for (Col=0; Col<W_Rec_Kernel; Col++) {
            int S = Bias[Col+OutFirstCol]+ In[Iterazione]*Kernel[Col+OutFirstCol];
            for (i=0; i<W_H/2; i++) {
                S = S + H_0[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
                S = S + H_0[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];
            }
            if (W_H&0x1) S += H_0[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];
			Z[Col+OutFirstCol] = gap_clip(gap_roundnorm_reg(S, Norm), 15);//approssimazione per eccesso
    }
}


void KerZComputationDec16(short int * __restrict__ H_0,
							unsigned int W_H,
							short int * __restrict__ Kernel,
							short int * __restrict__ Rec_Kernel,
							unsigned int W_Rec_Kernel,  
							int * __restrict__ Bias,
							short int * __restrict__ Z,
							unsigned int OutFirstCol,
							unsigned int Norm)

{


    unsigned int Col, i;


    for (Col=0; Col<W_Rec_Kernel; Col++) {
            int S = Bias[Col+OutFirstCol];
            for (i=0; i<W_H/2; i++) {
                S = S + H_0[(2*i  )] * Rec_Kernel[(2*i  )*W_Rec_Kernel+Col];
                S = S + H_0[(2*i+1)] * Rec_Kernel[(2*i+1)*W_Rec_Kernel+Col];
            }
            if (W_H&0x1) S += H_0[W_H-1]*Rec_Kernel[Col+((W_H - 1)*W_Rec_Kernel)];
			Z[Col+OutFirstCol] = gap_clip(gap_roundnorm_reg(S, Norm), 15);//approssimazione per eccesso

    }
}


void KerLSTMlayer16(	short int *__restrict__ Z, 
    					short int * __restrict__ C_0, 
						unsigned int W_C,
    					short int * __restrict__ H_0 ,
						unsigned int Norm )
{

	

	short int i[W_C];
	short int f[W_C];
	short int c_tilde[W_C];
	short int o[W_C];
	int C_n[W_C];
	int H_n[W_C]; 

    unsigned int j;
	
	for (j=0; j<W_C; j++) {
		i[j] = hard_sig(Z[j],Norm);//16,12
		f[j] = hard_sig(Z[W_C+j],Norm);//16,12
		c_tilde[j] = tan_h(Z[2*W_C+j]);//16,12
		o[j] = hard_sig(Z[3*W_C+j],Norm);//16,12

		C_n[j] = f[j]*C_0[j];//32,24
		C_n[j] = C_n[j]+(i[j]*c_tilde[j]);//32,12
		C_n[j] = C_n[j]>>Norm;

		H_n[j] = tan_h((short int) C_n[j]);//16,12
		H_n[j] = o[j]*H_n[j];//32,12
		H_n[j] = H_n[j]>>Norm;
		
		C_0[j] =(short int) C_n[j];
		H_0[j] =(short int) H_n[j];
	}
}

/**************************************************************************************************************************************
	DENSE input short int(16,12)
**************************************************************************************************************************************/
void KerDENSElayer16(	short int * __restrict__ In,
						unsigned int InSize,
						short int * __restrict__ Filter,
						int * __restrict__ Bias,
						unsigned int Norm,
						short int * __restrict__ Out,
						unsigned int Iterazione)

{

	

	int Acc= *Bias;
	for (unsigned int j=0;j<InSize;j++) {
		Acc= gap_macs(Acc,(int)In[j],(int)Filter[j]);
	}

	Out[Iterazione] = gap_clip(gap_roundnorm_reg(Acc, Norm),15);
		
}
