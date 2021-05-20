#ifndef __ENCDECLAYE_H__
#define __ENCDECLAYE_H__

#include "AutoTilerLibTypes.h"
#include "EncDecKernel.h"
#define _L1_Memory_SIZE 44512
#define _L2_Memory_SIZE 0
extern char *L1_Memory; /* Size given for generation: 45000 bytes, used: 44512 bytes */
extern char *L2_Memory; /* Size used for generation: 0 bytes */
extern void Encoder(
		short int * __restrict__ In,
		unsigned int step_in,
		unsigned int Iterazione,
		short int * __restrict__ H_0,
		short int * __restrict__ C_0,
		short int * __restrict__ Kernel,
		short int * __restrict__ Rec_Kernel,
		int * __restrict__ Bias,
		short int * __restrict__ Z,
		unsigned int Norm);
extern void Decoder(
		unsigned int step_out,
		unsigned int Iterazione,
		short int * __restrict__ H_0,
		short int * __restrict__ C_0,
		short int * __restrict__ Kernel,
		short int * __restrict__ Rec_Kernel,
		int * __restrict__ Bias,
		short int * __restrict__ Dense_Kernel,
		int * __restrict__ Dense_Bias,
		short int * __restrict__ Out,
		short int * __restrict__ Z,
		unsigned int Norm);
#endif
