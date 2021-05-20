/*
 * Copyright (C) 2017 GreenWaves Technologies
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 *
 */

#ifndef __ENCODERDECODERKERNEL_H__
#define __ENCODERDECODERKERNEL_H__
#include "Gap.h"

typedef struct {
    short int * __restrict__ In;
	unsigned int Iterazione;
    short int * __restrict__ H_0; 
    unsigned int W_H; //neuroni
    short int * __restrict__ Kernel;
    short int * __restrict__ Rec_Kernel;
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;
    short int * __restrict__ Z;
    unsigned int OutFirstCol;
    unsigned int Norm;
} KerZComputation16_ArgT;

typedef struct {
    short int * __restrict__ H_0; 
    unsigned int W_H; //neuroni
    short int * __restrict__ Kernel;
    short int * __restrict__ Rec_Kernel;
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;
    short int * __restrict__ Z;
    unsigned int OutFirstCol;
    unsigned int Norm;
} KerZComputationDec16_ArgT;

typedef struct {
	short int *__restrict__ Z ;
    short int * __restrict__ C_0;
    unsigned int W_C; 
    short int * __restrict__ H_0;
    unsigned int Norm;
} KerLSTMlayer16_ArgT;

typedef struct {
	short int *__restrict__ In ;
    unsigned int InSize; 
    short int * __restrict__ Filter;
    int * __restrict__ Bias;
    unsigned int Norm;
    short int * __restrict__ Out;
    unsigned int Iterazione;
} KerDENSElayer16_ArgT;

void KerZComputation16(
        KerZComputation16_ArgT *Arg
        );

void KerZComputationDec16(
        KerZComputationDec16_ArgT *Arg
        );

void KerLSTMlayer16(
    KerLSTMlayer16_ArgT *Arg
        );

void KerDENSElayer16(
    KerDENSElayer16_ArgT *Arg
        );

#endif
