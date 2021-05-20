#ifndef __ENCDECLAYE_H__
#define __ENCDECLAYE_H__

#include "AutoTilerLibTypes.h"
#include "EncDecKernel.h"
#define _L1_Memory_SIZE 47212
#define _L2_Memory_SIZE 0
extern char *L1_Memory; /* Size given for generation: 48000 bytes, used: 47212 bytes */
extern char *L2_Memory; /* Size used for generation: 0 bytes */
extern void EncGRUlayer(
		short int * __restrict__ In,
		unsigned int Iterazione,
		short int * __restrict__ H_0,
		short int * __restrict__ Kernel,
		short int * __restrict__ Rec_Kernel,
		int * __restrict__ Bias,
		short int * __restrict__ Kernel2,
		short int * __restrict__ Rec_Kernel2,
		int * __restrict__ Bias2,
		short int * __restrict__ Z,
		short int * __restrict__ prod1,
		int * __restrict__ prod2,
		unsigned int Norm);
extern void DecGRUlayer(
		unsigned int Iterazione,
		short int * __restrict__ H_0,
		short int * __restrict__ Rec_Kernel,
		int * __restrict__ Bias,
		short int * __restrict__ Rec_Kernel2,
		int * __restrict__ Bias2,
		short int * __restrict__ Dense_Kernel,
		int * __restrict__ Dense_Bias,
		short int * __restrict__ Out,
		short int * __restrict__ Z,
		short int * __restrict__ prod1,
		int * __restrict__ prod2,
		unsigned int Norm);
#endif
