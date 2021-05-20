#include "EncDecLayer.h"
L1_CL_MEM AT_L1_POINTER L1_Memory;
L2_MEM AT_L2_POINTER L2_Memory;
void EncGRUlayer(
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
		unsigned int Norm)

{
	/* Shared L1: 23456 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaR_Evt7;
	AT_L2_EVENT DmaR_Evt8;
	AT_L2_EVENT DmaW_Evt1;
	AT_L2_EVENT DmaW_Evt2;
	AT_L2_EVENT DmaW_Evt3;
	AT_L2_EVENT DmaW_Evt4;
	KerZEnc16_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;
	KerProd16_ArgT S_KerArg1, *KerArg1 = &S_KerArg1;
	KerGRUEnclayer16_ArgT S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _C_In;
	unsigned int _SC_In;
	unsigned int _C_H_0;
	unsigned int _SC_H_0;
	unsigned int _C_Kernel;
	unsigned int _SC_Kernel;
	unsigned int _C_Rec_Kernel;
	unsigned int _SC_Rec_Kernel;
	unsigned int _C_Bias;
	unsigned int _SC_Bias;
	unsigned int _C_Kernel2;
	unsigned int _SC_Kernel2;
	unsigned int _C_Rec_Kernel2;
	unsigned int _SC_Rec_Kernel2;
	unsigned int _C_Bias2;
	unsigned int _SC_Bias2;
	unsigned int _C_Z;
	unsigned int _SC_Z;
	unsigned int _C_prod1;
	unsigned int _SC_prod1;
	unsigned int _C_prod2;
	unsigned int _SC_prod2;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 54 [Tile0, 1:[27x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[27x1], 2]
		Tile0: [0, 54, 54], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: H_0, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile0, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile0, 1:[120x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[120x1], 2]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 14400 [Tile0, 1:[60x120], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x120], 2]
		Tile0: [0, 14400, 14400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Bias, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 480 [Tile0, 1:[120x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[120x1], 4]
		Tile0: [0, 480, 480], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Kernel2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile0, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Rec_Kernel2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 7200 [Tile0, 1:[60x60], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x60], 2]
		Tile0: [0, 7200, 7200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Bias2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile0, 1:[60x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 4]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Z, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile0, 1:[120x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[120x1], 2]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: prod1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile0, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: prod2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile0, 1:[60x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 4]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_H = (unsigned int) (60);
	KerArg0->W_Rec_Kernel = (unsigned int) (120);
	KerArg1->W_H = (unsigned int) (60);
	KerArg2->W_H = (unsigned int) (60);
	KerArg2->W_Rec_Kernel = (unsigned int) (60);
	/*================================= Read Tiles Prolog ===============================*/
	_C_In=0; _SC_In=54;
	_C_H_0=0; _SC_H_0=120;
	_C_Kernel=0; _SC_Kernel=240;
	_C_Rec_Kernel=0; _SC_Rec_Kernel=14400;
	_C_Bias=0; _SC_Bias=480;
	_C_Kernel2=0; _SC_Kernel2=120;
	_C_Rec_Kernel2=0; _SC_Rec_Kernel2=7200;
	_C_Bias2=0; _SC_Bias2=240;
	_C_Z=0; _SC_Z=240;
	_C_prod1=0; _SC_prod1=120;
	_C_prod2=0; _SC_prod2=240;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*================================= Read Tiles ======================================*/
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_C_In), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0),
				_SC_In, 0, &DmaR_Evt1);
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait current DMA read In */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+56),
				_SC_H_0, 0, &DmaR_Evt2);
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait current DMA read H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+_C_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+176),
				_SC_Kernel, 0, &DmaR_Evt3);
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait current DMA read Kernel */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+_C_Rec_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+416),
				_SC_Rec_Kernel, 0, &DmaR_Evt4);
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait current DMA read Rec_Kernel */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_C_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+14816),
				_SC_Bias, 0, &DmaR_Evt5);
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait current DMA read Bias */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel2+_C_Kernel2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+15296),
				_SC_Kernel2, 0, &DmaR_Evt6);
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait current DMA read Kernel2 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel2+_C_Rec_Kernel2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+15416),
				_SC_Rec_Kernel2, 0, &DmaR_Evt7);
		AT_L2_WAIT(0, &DmaR_Evt7); /* Wait current DMA read Rec_Kernel2 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+_C_Bias2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22616),
				_SC_Bias2, 0, &DmaR_Evt8);
		AT_L2_WAIT(0, &DmaR_Evt8); /* Wait current DMA read Bias2 */
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (short int * __restrict__) (L1_Memory+0);
		KerArg0->Iterazione = (unsigned int) (Iterazione);
		KerArg0->H_0 = (short int * __restrict__) (L1_Memory+56);
		KerArg0->Kernel = (short int * __restrict__) (L1_Memory+176);
		KerArg0->Rec_Kernel = (short int * __restrict__) (L1_Memory+416);
		KerArg0->Bias = (int * __restrict__) (L1_Memory+14816);
		KerArg0->Z = (short int * __restrict__) (L1_Memory+22856);
		KerArg0->OutFirstCol = (unsigned int) (0);
		KerArg0->Norm = (unsigned int) (Norm);
		AT_FORK(gap_ncore(), (void *) KerZEnc16, (void *) KerArg0);
		__CALL(KerZEnc16, KerArg0);
		KerArg1->Z = (short int * __restrict__) (L1_Memory+22856);
		KerArg1->H_0 = (short int * __restrict__) (L1_Memory+56);
		KerArg1->prod1 = (short int * __restrict__) (L1_Memory+23096);
		KerArg1->prod2 = (int * __restrict__) (L1_Memory+23216);
		KerArg1->Norm = (unsigned int) (Norm);
		AT_FORK(gap_ncore(), (void *) KerProd16, (void *) KerArg1);
		__CALL(KerProd16, KerArg1);
		KerArg2->Z = (short int * __restrict__) (L1_Memory+22856);
		KerArg2->In = (short int * __restrict__) (L1_Memory+0);
		KerArg2->Iterazione = (unsigned int) (Iterazione);
		KerArg2->H_0 = (short int * __restrict__) (L1_Memory+56);
		KerArg2->Kernel = (short int * __restrict__) (L1_Memory+15296);
		KerArg2->Rec_Kernel = (short int * __restrict__) (L1_Memory+15416);
		KerArg2->Bias = (int * __restrict__) (L1_Memory+22616);
		KerArg2->prod1 = (short int * __restrict__) (L1_Memory+23096);
		KerArg2->prod2 = (int * __restrict__) (L1_Memory+23216);
		KerArg2->OutFirstCol = (unsigned int) (0);
		KerArg2->Norm = (unsigned int) (Norm);
		AT_FORK(gap_ncore(), (void *) KerGRUEnclayer16, (void *) KerArg2);
		__CALL(KerGRUEnclayer16, KerArg2);
		/*================================= Write Tiles =====================================*/
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+56),
				_SC_H_0, 1, &DmaW_Evt1);
		AT_L2_WAIT(0, &DmaW_Evt1); /* Wait current DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22856),
				_SC_Z, 1, &DmaW_Evt2);
		AT_L2_WAIT(0, &DmaW_Evt2); /* Wait current DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod1+_C_prod1), ((AT_L2_INT_ADDR_TYPE) L1_Memory+23096),
				_SC_prod1, 1, &DmaW_Evt3);
		AT_L2_WAIT(0, &DmaW_Evt3); /* Wait current DMA write prod1 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod2+_C_prod2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+23216),
				_SC_prod2, 1, &DmaW_Evt4);
		AT_L2_WAIT(0, &DmaW_Evt4); /* Wait current DMA write prod2 */
		/*============================= End Write Tiles =====================================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_In = 0;
		
		_SC_H_0 = 0;
		
		_SC_H_0 = 0;
		
		_SC_Kernel = 0;
		
		_SC_Rec_Kernel = 0;
		
		_SC_Bias = 0;
		
		_SC_Kernel2 = 0;
		
		_SC_Rec_Kernel2 = 0;
		
		_SC_Bias2 = 0;
		
		_SC_Z = 0;
		
		_SC_prod1 = 0;
		
		_SC_prod2 = 0;
		
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	/*============================ End Write Tiles Epilog ===============================*/
}
void DecGRUlayer(
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
		unsigned int Norm)

{
	/* Shared L1: 23184 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaR_Evt7;
	AT_L2_EVENT DmaW_Evt1;
	AT_L2_EVENT DmaW_Evt2;
	AT_L2_EVENT DmaW_Evt3;
	AT_L2_EVENT DmaW_Evt4;
	AT_L2_EVENT DmaW_Evt5;
	KerZDec16_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;
	KerProd16_ArgT S_KerArg1, *KerArg1 = &S_KerArg1;
	KerGRUDeclayer16_ArgT S_KerArg2, *KerArg2 = &S_KerArg2;
	KerDENSElayer16_ArgT S_KerArg3, *KerArg3 = &S_KerArg3;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _C_H_0;
	unsigned int _SC_H_0;
	unsigned int _C_Rec_Kernel;
	unsigned int _SC_Rec_Kernel;
	unsigned int _C_Bias;
	unsigned int _SC_Bias;
	unsigned int _C_Rec_Kernel2;
	unsigned int _SC_Rec_Kernel2;
	unsigned int _C_Bias2;
	unsigned int _SC_Bias2;
	unsigned int _C_Dense_Kernel;
	unsigned int _SC_Dense_Kernel;
	unsigned int _C_Dense_Bias;
	unsigned int _SC_Dense_Bias;
	unsigned int _C_Z;
	unsigned int _SC_Z;
	unsigned int _C_Out;
	unsigned int _SC_Out;
	unsigned int _C_prod1;
	unsigned int _SC_prod1;
	unsigned int _C_prod2;
	unsigned int _SC_prod2;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: H_0, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile0, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 14400 [Tile0, 1:[60x120], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x120], 2]
		Tile0: [0, 14400, 14400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Bias, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 480 [Tile0, 1:[120x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[120x1], 4]
		Tile0: [0, 480, 480], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Rec_Kernel2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 7200 [Tile0, 1:[60x60], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x60], 2]
		Tile0: [0, 7200, 7200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Bias2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile0, 1:[60x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 4]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Dense_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile0, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Dense_Bias, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4 [Tile0, 1:[1x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x1], 4]
		Tile0: [0, 4, 4], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Z, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile0, 1:[120x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[120x1], 2]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 18 [Tile0, 1:[9x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[9x1], 2]
		Tile0: [0, 18, 18], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: prod1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile0, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	Ker Arg: prod2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile0, 1:[60x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[60x1], 4]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0], T2: [Tile0: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_H = (unsigned int) (60);
	KerArg0->W_Rec_Kernel = (unsigned int) (120);
	KerArg1->W_H = (unsigned int) (60);
	KerArg2->W_H = (unsigned int) (60);
	KerArg2->W_Rec_Kernel = (unsigned int) (60);
	KerArg3->InSize = (unsigned int) (60);
	/*================================= Read Tiles Prolog ===============================*/
	_C_H_0=0; _SC_H_0=120;
	_C_Rec_Kernel=0; _SC_Rec_Kernel=14400;
	_C_Bias=0; _SC_Bias=480;
	_C_Rec_Kernel2=0; _SC_Rec_Kernel2=7200;
	_C_Bias2=0; _SC_Bias2=240;
	_C_Dense_Kernel=0; _SC_Dense_Kernel=120;
	_C_Dense_Bias=0; _SC_Dense_Bias=4;
	_C_Z=0; _SC_Z=240;
	_C_Out=0; _SC_Out=18;
	_C_prod1=0; _SC_prod1=120;
	_C_prod2=0; _SC_prod2=240;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*================================= Read Tiles ======================================*/
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0),
				_SC_H_0, 0, &DmaR_Evt1);
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait current DMA read H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+_C_Rec_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+120),
				_SC_Rec_Kernel, 0, &DmaR_Evt2);
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait current DMA read Rec_Kernel */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_C_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+14520),
				_SC_Bias, 0, &DmaR_Evt3);
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait current DMA read Bias */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel2+_C_Rec_Kernel2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+15000),
				_SC_Rec_Kernel2, 0, &DmaR_Evt4);
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait current DMA read Rec_Kernel2 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+_C_Bias2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22200),
				_SC_Bias2, 0, &DmaR_Evt5);
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait current DMA read Bias2 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Kernel+_C_Dense_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22440),
				_SC_Dense_Kernel, 0, &DmaR_Evt6);
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait current DMA read Dense_Kernel */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Bias+_C_Dense_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22560),
				_SC_Dense_Bias, 0, &DmaR_Evt7);
		AT_L2_WAIT(0, &DmaR_Evt7); /* Wait current DMA read Dense_Bias */
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->H_0 = (short int * __restrict__) (L1_Memory+0);
		KerArg0->Rec_Kernel = (short int * __restrict__) (L1_Memory+120);
		KerArg0->Bias = (int * __restrict__) (L1_Memory+14520);
		KerArg0->Z = (short int * __restrict__) (L1_Memory+22564);
		KerArg0->OutFirstCol = (unsigned int) (0);
		KerArg0->Norm = (unsigned int) (Norm);
		AT_FORK(gap_ncore(), (void *) KerZDec16, (void *) KerArg0);
		__CALL(KerZDec16, KerArg0);
		KerArg1->Z = (short int * __restrict__) (L1_Memory+22564);
		KerArg1->H_0 = (short int * __restrict__) (L1_Memory+0);
		KerArg1->prod1 = (short int * __restrict__) (L1_Memory+22824);
		KerArg1->prod2 = (int * __restrict__) (L1_Memory+22944);
		KerArg1->Norm = (unsigned int) (Norm);
		AT_FORK(gap_ncore(), (void *) KerProd16, (void *) KerArg1);
		__CALL(KerProd16, KerArg1);
		KerArg2->Z = (short int * __restrict__) (L1_Memory+22564);
		KerArg2->H_0 = (short int * __restrict__) (L1_Memory+0);
		KerArg2->Rec_Kernel = (short int * __restrict__) (L1_Memory+15000);
		KerArg2->Bias = (int * __restrict__) (L1_Memory+22200);
		KerArg2->prod1 = (short int * __restrict__) (L1_Memory+22824);
		KerArg2->prod2 = (int * __restrict__) (L1_Memory+22944);
		KerArg2->OutFirstCol = (unsigned int) (0);
		KerArg2->Norm = (unsigned int) (Norm);
		AT_FORK(gap_ncore(), (void *) KerGRUDeclayer16, (void *) KerArg2);
		__CALL(KerGRUDeclayer16, KerArg2);
		KerArg3->In = (short int * __restrict__) (L1_Memory+0);
		KerArg3->Filter = (short int * __restrict__) (L1_Memory+22440);
		KerArg3->Bias = (int * __restrict__) (L1_Memory+22560);
		KerArg3->Norm = (unsigned int) (Norm);
		KerArg3->Out = (short int * __restrict__) (L1_Memory+22804);
		KerArg3->Iterazione = (unsigned int) (Iterazione);
		AT_FORK(gap_ncore(), (void *) KerDENSElayer16, (void *) KerArg3);
		__CALL(KerDENSElayer16, KerArg3);
		/*================================= Write Tiles =====================================*/
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0),
				_SC_H_0, 1, &DmaW_Evt1);
		AT_L2_WAIT(0, &DmaW_Evt1); /* Wait current DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22564),
				_SC_Z, 1, &DmaW_Evt2);
		AT_L2_WAIT(0, &DmaW_Evt2); /* Wait current DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22804),
				_SC_Out, 1, &DmaW_Evt3);
		AT_L2_WAIT(0, &DmaW_Evt3); /* Wait current DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod1+_C_prod1), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22824),
				_SC_prod1, 1, &DmaW_Evt4);
		AT_L2_WAIT(0, &DmaW_Evt4); /* Wait current DMA write prod1 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod2+_C_prod2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22944),
				_SC_prod2, 1, &DmaW_Evt5);
		AT_L2_WAIT(0, &DmaW_Evt5); /* Wait current DMA write prod2 */
		/*============================= End Write Tiles =====================================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_H_0 = 0;
		
		_SC_H_0 = 0;
		
		_SC_Rec_Kernel = 0;
		
		_SC_Bias = 0;
		
		_SC_Rec_Kernel2 = 0;
		
		_SC_Bias2 = 0;
		
		_SC_Dense_Kernel = 0;
		
		_SC_Dense_Bias = 0;
		
		_SC_Z = 0;
		
		_SC_Out = 0;
		
		_SC_prod1 = 0;
		
		_SC_prod2 = 0;
		
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	/*============================ End Write Tiles Epilog ===============================*/
}
