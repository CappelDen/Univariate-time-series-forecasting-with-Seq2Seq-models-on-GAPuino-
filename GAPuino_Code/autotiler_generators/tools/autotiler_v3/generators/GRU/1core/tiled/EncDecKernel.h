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
    short int * __restrict__ In;//16,12
	unsigned int Iterazione;
    short int * __restrict__ H_0; //16,12
    unsigned int W_H; //neuroni
    short int * __restrict__ Kernel;//16,12
    short int * __restrict__ Rec_Kernel;//16,12
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;//32,24
    short int * __restrict__ Z;//16,12
    unsigned int OutFirstCol;
    unsigned int Norm;
} KerZEnc16_ArgT;

typedef struct {
    short int * __restrict__ H_0; //16,12
    unsigned int W_H; //neuroni
    short int * __restrict__ Rec_Kernel;//16,12
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;//32,24
    short int * __restrict__ Z;//16,12
    unsigned int OutFirstCol;
    unsigned int Norm;
} KerZDec16_ArgT;

typedef struct {
    short int * __restrict__ Z;
    short int * __restrict__ H_0; //16,12
    unsigned int W_H; //neuroni
	short int * __restrict__ prod1;
	int * __restrict__ prod2;
    unsigned int Norm;
} KerProd16_ArgT;

typedef struct {
	short int *__restrict__ Z;
    short int * __restrict__ In;
	unsigned int Iterazione;
    short int * __restrict__ H_0;
	unsigned int W_H;//neuroni
	short int * __restrict__ Kernel;
    short int * __restrict__ Rec_Kernel;
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;
	short int * __restrict__ prod1;
	int * __restrict__ prod2;
	unsigned int OutFirstCol;
	unsigned int Norm;
} KerGRUEnclayer16_ArgT;

typedef struct {
	short int *__restrict__ Z;
    short int * __restrict__ H_0;
	unsigned int W_H;//neuroni
    short int * __restrict__ Rec_Kernel;
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;
	short int * __restrict__ prod1;
	int * __restrict__ prod2;
	unsigned int OutFirstCol;
	unsigned int Norm;
} KerGRUDeclayer16_ArgT;

typedef struct {
	short int *__restrict__ In ;
    unsigned int InSize; 
    short int * __restrict__ Filter;
    int * __restrict__ Bias;
    unsigned int Norm;
    short int * __restrict__ Out;
    unsigned int Iterazione;
} KerDENSElayer16_ArgT;

void KerZEnc16(
    short int * __restrict__ In;//16,12
	unsigned int Iterazione;
    short int * __restrict__ H_0; //16,12
    unsigned int W_H; //neuroni
    short int * __restrict__ Kernel;//16,12
    short int * __restrict__ Rec_Kernel;//16,12
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;//32,24
    short int * __restrict__ Z;//16,12
    unsigned int OutFirstCol;
    unsigned int Norm;        
        );

void KerZDec16(
    short int * __restrict__ H_0; //16,12
    unsigned int W_H; //neuroni
    short int * __restrict__ Rec_Kernel;//16,12
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;//32,24
    short int * __restrict__ Z;//16,12
    unsigned int OutFirstCol;
    unsigned int Norm;
        );

void KerProd16(
    short int * __restrict__ Z;
    short int * __restrict__ H_0; //16,12
    unsigned int W_H; //neuroni
	short int * __restrict__ prod1;
	int * __restrict__ prod2;
    unsigned int Norm;
        );

void KerGRUEnclayer16(
	short int *__restrict__ Z;
    short int * __restrict__ In;
	unsigned int Iterazione;
    short int * __restrict__ H_0;
	unsigned int W_H;//neuroni
	short int * __restrict__ Kernel;
    short int * __restrict__ Rec_Kernel;
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;
	short int * __restrict__ prod1;
	int * __restrict__ prod2;
	unsigned int OutFirstCol;
	unsigned int Norm;
        );

void KerGRUDeclayer16(
	short int *__restrict__ Z;
    short int * __restrict__ H_0;
	unsigned int W_H;//neuroni
    short int * __restrict__ Rec_Kernel;
    unsigned int W_Rec_Kernel;  //4*neuroni  
    int * __restrict__ Bias;
	short int * __restrict__ prod1;
	int * __restrict__ prod2;
	unsigned int OutFirstCol;
	unsigned int Norm;
        );


void KerDENSElayer16(
	short int *__restrict__ In ;
    unsigned int InSize; 
    short int * __restrict__ Filter;
    int * __restrict__ Bias;
    unsigned int Norm;
    short int * __restrict__ Out;
    unsigned int Iterazione;
        );

#endif
