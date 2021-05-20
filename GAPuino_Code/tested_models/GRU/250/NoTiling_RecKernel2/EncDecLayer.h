#ifndef __ENCDECLAYE_H__
#define __ENCDECLAYE_H__

#include "AutoTilerLibTypes.h"
#include "EncDecKernel.h"
#define _L1_Memory_SIZE 43612
#define _L2_Memory_SIZE 15000
extern char *L1_Memory; /* Size given for generation: 45000 bytes, used: 43612 bytes */
extern char *L2_Memory; /* Size used for generation: 15000 bytes */
extern void EncGRUlayer(
		struct pi_device HyperRam,
		short int * __restrict__ In,
		unsigned int Iterazione,
		short int * __restrict__ H_0,
		short int * __restrict__ Kernel,
		uint32_t Rec_Kernel,
		int * __restrict__ Bias,
		short int * __restrict__ Kernel2,
		short int * __restrict__ Rec_Kernel2,
		int * __restrict__ Bias2,
		short int * __restrict__ Z,
		short int * __restrict__ prod1,
		int * __restrict__ prod2,
		unsigned int Norm);
extern void DecGRUlayer(
		struct pi_device HyperRam,
		unsigned int Iterazione,
		short int * __restrict__ H_0,
		uint32_t Rec_Kernel,
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
