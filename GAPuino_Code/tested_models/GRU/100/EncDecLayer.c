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
	/* Shared L1: 47512 bytes, L2 buffer: 0 bytes */
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
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _C_H_0, _N_H_0;
	unsigned int _SP_H_0, _SC_H_0, _SN_H_0;
	unsigned int _N_Kernel;
	unsigned int _SN_Kernel;
	unsigned int _N_Rec_Kernel;
	unsigned int _SN_Rec_Kernel;
	unsigned int _LN_Rec_Kernel;
	unsigned int _N_Bias;
	unsigned int _SN_Bias;
	unsigned int _N_Kernel2;
	unsigned int _SN_Kernel2;
	unsigned int _N_Bias2;
	unsigned int _SN_Bias2;
	unsigned int _C_Z;
	unsigned int _SP_Z, _SC_Z;
	unsigned int _C_prod1;
	unsigned int _SP_prod1, _SC_prod1;
	unsigned int _C_prod2;
	unsigned int _SP_prod2, _SC_prod2;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 1][Tile0 Dim: 4]
	Ker Arg: In, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 54 [Tile1, 1:[27x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[27x1], 2]
		Tile0: [0, 54, 54], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: H_0, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 200 [Tile1, 1:[100x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 2]
		Tile0: [0, 200, 200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Kernel, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile1, 1:[200x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[200x1], 2]
		Tile0: [0, 400, 400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 40000 [Tile0, 4:[100x53, 2:100x53, 100x41], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[100x53, 2:100x53, 100x41], 2]
		Tile0: [0, 10600, 106], Tile1: [106, 10600, 106], Tile2; [212, 10600, 106]
		T0: [Tile0: 0], T1: [Tile0: 1], T2: [Tile0: 0 +1/6]
	Ker Arg: Bias, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 800 [Tile1, 1:[200x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[200x1], 4]
		Tile0: [0, 800, 800], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Kernel2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 200 [Tile1, 1:[100x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 2]
		Tile0: [0, 200, 200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Rec_Kernel2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 20000 [Tile1, 1:[100x100], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x100], 2]
		Tile0: [0, 20000, 20000], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Bias2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile1, 1:[100x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 4]
		Tile0: [0, 400, 400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Z, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile1, 1:[200x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[200x1], 2]
		Tile0: [0, 400, 400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: prod1, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 200 [Tile1, 1:[100x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 2]
		Tile0: [0, 200, 200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: prod2, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile1, 1:[100x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 4]
		Tile0: [0, 400, 400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/

	KerArg0->W_H = (unsigned int) (100);
	KerArg0->Norm = (unsigned int) (Norm);
	KerArg1->W_H = (unsigned int) (100);
	KerArg1->Norm = (unsigned int) (Norm);

	KerArg2->W_H = (unsigned int) (100);
	KerArg2->Rec_Kernel = (short int * __restrict__) (L1_Memory+3512);
	KerArg2->Norm = (unsigned int) (Norm);
	/*================================= Read Tiles Prolog ===============================*/
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+0), 54, 0, &DmaR_Evt1);
	_C_H_0=0; _SC_H_0=200;
	_SP_H_0=0;
	_N_H_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+0), 200, 0, &DmaR_Evt2);
	_N_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+712+0), 400, 0, &DmaR_Evt3);
	_N_Rec_Kernel=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+26312+0), 10600, 400, 106, 0, &DmaR_Evt4);
	_N_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1512+0), 800, 0, &DmaR_Evt5);
	_N_Kernel2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3112+0), 200, 0, &DmaR_Evt6);
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3512), 20000, 0, &DmaR_Evt7);
	AT_L2_WAIT(0, &DmaR_Evt7); /* Wait previous DMA read Rec_Kernel2 */
	_N_Bias2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+23512+0), 400, 0, &DmaR_Evt8);
	_C_Z=0; _SC_Z=400;
	_SP_Z=0;
	_C_prod1=0; _SC_prod1=200;
	_SP_prod1=0;
	_C_prod2=0; _SC_prod2=400;
	_SP_prod2=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile1 */
		int T1Ind_Last = 1, T1Ind_NextLast = 1;
		/*================================= Prepare Tiles ===================================*/
		_SN_In = 0;
		
		_SN_H_0 = 0;
		
		_SN_Kernel = 0;
		
		_SN_Bias = 0;
		
		_SN_Kernel2 = 0;
		
		_SN_Bias2 = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+56*((T1Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read H_0 */
		if (_SN_H_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_N_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+200*((T1Ind_Total+1)%3)),
					_SN_H_0, 0, &DmaR_Evt2);
		}
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Kernel */
		if (_SN_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+_N_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+712+400*((T1Ind_Total+1)%2)),
					_SN_Kernel, 0, &DmaR_Evt3);
		}
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1512+800*((T1Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt5);
		}
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Kernel2 */
		if (_SN_Kernel2) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel2+_N_Kernel2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3112+200*((T1Ind_Total+1)%2)),
					_SN_Kernel2, 0, &DmaR_Evt6);
		}
		AT_L2_WAIT(0, &DmaR_Evt8); /* Wait previous DMA read Bias2 */
		if (_SN_Bias2) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+_N_Bias2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+23512+400*((T1Ind_Total+1)%2)),
					_SN_Bias2, 0, &DmaR_Evt8);
		}
		/*============================= End Read Tiles ======================================*/
		for(Iterazione=0;Iterazione<27;Iterazione++){
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3);
			/*================================= Prepare Tiles ===================================*/
			_SN_Rec_Kernel = 0;
			if (!(T0Ind_Last)) {
				_N_Rec_Kernel = _N_Rec_Kernel + (106); _LN_Rec_Kernel = ((T0Ind_NextLast)?82:106); _SN_Rec_Kernel = (100*_LN_Rec_Kernel); 
			} else {
				_N_Rec_Kernel = _N_Rec_Kernel + (-318); _LN_Rec_Kernel = (106); _SN_Rec_Kernel = (100*_LN_Rec_Kernel); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Rec_Kernel */
			if (_SN_Rec_Kernel) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+_N_Rec_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+26312+10600*((T0Ind_Total+1)%2)),
						_SN_Rec_Kernel, 400, _LN_Rec_Kernel, 0, &DmaR_Evt4);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (short int * __restrict__) (L1_Memory+0+56*((T1Ind_Total)%2));
			KerArg0->Iterazione = (unsigned int) (Iterazione);
			KerArg0->H_0 = (short int * __restrict__) (L1_Memory+112+200*((T1Ind_Total)%3));
			KerArg0->Kernel = (short int * __restrict__) (L1_Memory+712+400*((T1Ind_Total)%2));
			KerArg0->Rec_Kernel = (short int * __restrict__) (L1_Memory+26312+10600*((T0Ind_Total)%2));
			KerArg0->W_Rec_Kernel = (unsigned int) ((T0Ind_Last)?41:53);
			KerArg0->Bias = (int * __restrict__) (L1_Memory+1512+800*((T1Ind_Total)%2));
			KerArg0->Z = (short int * __restrict__) (L1_Memory+24312+400*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned int) ((T0Ind)*53);
			AT_FORK(gap_ncore(), (void *) KerZEnc16, (void *) KerArg0);
			__CALL(KerZEnc16, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg1->Z = (short int * __restrict__) (L1_Memory+24312+400*((T1Ind_Total)%2));
		KerArg1->H_0 = (short int * __restrict__) (L1_Memory+112+200*((T1Ind_Total)%3));
		KerArg1->prod1 = (short int * __restrict__) (L1_Memory+25112+200*((T1Ind_Total)%2));
		KerArg1->prod2 = (int * __restrict__) (L1_Memory+25512+400*((T1Ind_Total)%2));
		AT_FORK(gap_ncore(), (void *) KerProd16, (void *) KerArg1);
		__CALL(KerProd16, KerArg1);
		KerArg2->Z = (short int * __restrict__) (L1_Memory+24312+400*((T1Ind_Total)%2));
		KerArg2->In = (short int * __restrict__) (L1_Memory+0+56*((T1Ind_Total)%2));
		KerArg2->Iterazione = (unsigned int) (Iterazione);
		KerArg2->H_0 = (short int * __restrict__) (L1_Memory+112+200*((T1Ind_Total)%3));
		KerArg2->Kernel = (short int * __restrict__) (L1_Memory+3112+200*((T1Ind_Total)%2));
		KerArg2->W_Rec_Kernel = (unsigned int) (100);
		KerArg2->Bias = (int * __restrict__) (L1_Memory+23512+400*((T1Ind_Total)%2));
		KerArg2->prod1 = (short int * __restrict__) (L1_Memory+25112+200*((T1Ind_Total)%2));
		KerArg2->prod2 = (int * __restrict__) (L1_Memory+25512+400*((T1Ind_Total)%2));
		KerArg2->OutFirstCol = (unsigned int) ((0)*100);
		AT_FORK(gap_ncore(), (void *) KerGRUEnclayer16, (void *) KerArg2);
		__CALL(KerGRUEnclayer16, KerArg2);
		}
		/*================================= Write Tiles =====================================*/
		if (_SP_H_0) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+200*((T1Ind_Total)%3)),
				_SC_H_0, 1, &DmaW_Evt1);
		if (_SP_Z) AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+24312+400*((T1Ind_Total)%2)),
				_SC_Z, 1, &DmaW_Evt2);
		if (_SP_prod1) AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write prod1 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod1+_C_prod1), ((AT_L2_INT_ADDR_TYPE) L1_Memory+25112+200*((T1Ind_Total)%2)),
				_SC_prod1, 1, &DmaW_Evt3);
		if (_SP_prod2) AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write prod2 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod2+_C_prod2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+25512+400*((T1Ind_Total)%2)),
				_SC_prod2, 1, &DmaW_Evt4);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		
		_SP_H_0 = _SC_H_0;
		
		
		
		
		_SP_Z = _SC_Z;
		_SP_prod1 = _SC_prod1;
		_SP_prod2 = _SC_prod2;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_H_0 = 0;
		
		_SC_Z = 0;
		
		_SC_prod1 = 0;
		
		_SC_prod2 = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		T1Ind_Total++;
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
	AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write Z */
	AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write prod1 */
	AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write prod2 */
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
	/* Shared L1: 47448 bytes, L2 buffer: 0 bytes */
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
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_H_0, _N_H_0;
	unsigned int _SP_H_0, _SC_H_0, _SN_H_0;
	unsigned int _N_Rec_Kernel;
	unsigned int _SN_Rec_Kernel;
	unsigned int _LN_Rec_Kernel;
	unsigned int _N_Bias;
	unsigned int _SN_Bias;
	unsigned int _N_Bias2;
	unsigned int _SN_Bias2;
	unsigned int _N_Dense_Kernel;
	unsigned int _SN_Dense_Kernel;
	unsigned int _N_Dense_Bias;
	unsigned int _SN_Dense_Bias;
	unsigned int _C_Z;
	unsigned int _SP_Z, _SC_Z;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _C_prod1;
	unsigned int _SP_prod1, _SC_prod1;
	unsigned int _C_prod2;
	unsigned int _SP_prod2, _SC_prod2;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 1][Tile0 Dim: 4]
	Ker Arg: H_0, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 200 [Tile1, 1:[100x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 2]
		Tile0: [0, 200, 200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 40000 [Tile0, 4:[100x55, 2:100x55, 100x35], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[100x55, 2:100x55, 100x35], 2]
		Tile0: [0, 11000, 110], Tile1: [110, 11000, 110], Tile2; [220, 11000, 110]
		T0: [Tile0: 0], T1: [Tile0: 1], T2: [Tile0: 0 +1/10]
	Ker Arg: Bias, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 800 [Tile1, 1:[200x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[200x1], 4]
		Tile0: [0, 800, 800], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Rec_Kernel2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 20000 [Tile1, 1:[100x100], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x100], 2]
		Tile0: [0, 20000, 20000], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Bias2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile1, 1:[100x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 4]
		Tile0: [0, 400, 400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Dense_Kernel, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 200 [Tile1, 1:[100x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 2]
		Tile0: [0, 200, 200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Dense_Bias, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4 [Tile1, 1:[1x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1x1], 4]
		Tile0: [0, 4, 4], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Z, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile1, 1:[200x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[200x1], 2]
		Tile0: [0, 400, 400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 18 [Tile1, 1:[9x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[9x1], 2]
		Tile0: [0, 18, 18], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: prod1, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 200 [Tile1, 1:[100x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 2]
		Tile0: [0, 200, 200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: prod2, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile1, 1:[100x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 4]
		Tile0: [0, 400, 400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_H = (unsigned int) (100);
	KerArg0->Norm = (unsigned int) (Norm);
	KerArg1->W_H = (unsigned int) (100);
	KerArg1->Norm = (unsigned int) (Norm);
	KerArg2->W_H = (unsigned int) (100);
	KerArg2->Rec_Kernel = (short int * __restrict__) (L1_Memory+2200);
	KerArg2->Norm = (unsigned int) (Norm);
	KerArg3->InSize = (unsigned int) (100);
	KerArg3->Norm = (unsigned int) (Norm);

	/*================================= Read Tiles Prolog ===============================*/
	_C_H_0=0; _SC_H_0=200;
	_SP_H_0=0;
	_N_H_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+0), 200, 0, &DmaR_Evt1);
	_N_Rec_Kernel=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+25448+0), 11000, 400, 110, 0, &DmaR_Evt2);
	_N_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+600+0), 800, 0, &DmaR_Evt3);
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2200), 20000, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Rec_Kernel2 */
	_N_Bias2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22200+0), 400, 0, &DmaR_Evt5);
	_N_Dense_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+23000+0), 200, 0, &DmaR_Evt6);
	_N_Dense_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+23400+0), 4, 0, &DmaR_Evt7);
	_C_Z=0; _SC_Z=400;
	_SP_Z=0;
	_C_Out=0; _SC_Out=18;
	_SP_Out=0;
	_C_prod1=0; _SC_prod1=200;
	_SP_prod1=0;
	_C_prod2=0; _SC_prod2=400;
	_SP_prod2=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile1 */
		int T1Ind_Last = 1, T1Ind_NextLast = 1;
		/*================================= Prepare Tiles ===================================*/
		_SN_H_0 = 0;
		
		_SN_Bias = 0;
		
		_SN_Bias2 = 0;
		
		_SN_Dense_Kernel = 0;
		
		_SN_Dense_Bias = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read H_0 */
		if (_SN_H_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_N_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+200*((T1Ind_Total+1)%3)),
					_SN_H_0, 0, &DmaR_Evt1);
		}
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+600+800*((T1Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt3);
		}
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Bias2 */
		if (_SN_Bias2) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+_N_Bias2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+22200+400*((T1Ind_Total+1)%2)),
					_SN_Bias2, 0, &DmaR_Evt5);
		}
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Dense_Kernel */
		if (_SN_Dense_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Kernel+_N_Dense_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+23000+200*((T1Ind_Total+1)%2)),
					_SN_Dense_Kernel, 0, &DmaR_Evt6);
		}
		AT_L2_WAIT(0, &DmaR_Evt7); /* Wait previous DMA read Dense_Bias */
		if (_SN_Dense_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Bias+_N_Dense_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+23400+4*((T1Ind_Total+1)%2)),
					_SN_Dense_Bias, 0, &DmaR_Evt7);
		}
		/*============================= End Read Tiles ======================================*/
		for(Iterazione=0;Iterazione<9;Iterazione++){
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3);
			/*================================= Prepare Tiles ===================================*/
			_SN_Rec_Kernel = 0;
			if (!(T0Ind_Last)) {
				_N_Rec_Kernel = _N_Rec_Kernel + (110); _LN_Rec_Kernel = ((T0Ind_NextLast)?70:110); _SN_Rec_Kernel = (100*_LN_Rec_Kernel); 
			} else {
				_N_Rec_Kernel = _N_Rec_Kernel + (-330); _LN_Rec_Kernel = (110); _SN_Rec_Kernel = (100*_LN_Rec_Kernel); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Rec_Kernel */
			if (_SN_Rec_Kernel) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+_N_Rec_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+25448+11000*((T0Ind_Total+1)%2)),
						_SN_Rec_Kernel, 400, _LN_Rec_Kernel, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->H_0 = (short int * __restrict__) (L1_Memory+0+200*((T1Ind_Total)%3));
			KerArg0->Rec_Kernel = (short int * __restrict__) (L1_Memory+25448+11000*((T0Ind_Total)%2));
			KerArg0->W_Rec_Kernel = (unsigned int) ((T0Ind_Last)?35:55);
			KerArg0->Bias = (int * __restrict__) (L1_Memory+600+800*((T1Ind_Total)%2));
			KerArg0->Z = (short int * __restrict__) (L1_Memory+23408+400*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned int) ((T0Ind)*55);
			AT_FORK(gap_ncore(), (void *) KerZDec16, (void *) KerArg0);
			__CALL(KerZDec16, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg1->Z = (short int * __restrict__) (L1_Memory+23408+400*((T1Ind_Total)%2));
		KerArg1->H_0 = (short int * __restrict__) (L1_Memory+0+200*((T1Ind_Total)%3));
		KerArg1->prod1 = (short int * __restrict__) (L1_Memory+24248+200*((T1Ind_Total)%2));
		KerArg1->prod2 = (int * __restrict__) (L1_Memory+24648+400*((T1Ind_Total)%2));
		AT_FORK(gap_ncore(), (void *) KerProd16, (void *) KerArg1);
		__CALL(KerProd16, KerArg1);
		KerArg2->Z = (short int * __restrict__) (L1_Memory+23408+400*((T1Ind_Total)%2));
		KerArg2->H_0 = (short int * __restrict__) (L1_Memory+0+200*((T1Ind_Total)%3));
		KerArg2->W_Rec_Kernel = (unsigned int) (100);
		KerArg2->Bias = (int * __restrict__) (L1_Memory+22200+400*((T1Ind_Total)%2));
		KerArg2->prod1 = (short int * __restrict__) (L1_Memory+24248+200*((T1Ind_Total)%2));
		KerArg2->prod2 = (int * __restrict__) (L1_Memory+24648+400*((T1Ind_Total)%2));
		KerArg2->OutFirstCol = (unsigned int) ((0)*100);
		AT_FORK(gap_ncore(), (void *) KerGRUDeclayer16, (void *) KerArg2);
		__CALL(KerGRUDeclayer16, KerArg2);
		KerArg3->In = (short int * __restrict__) (L1_Memory+0+200*((T1Ind_Total)%3));
		KerArg3->Iterazione = (unsigned int) (Iterazione);
		KerArg3->Filter = (short int * __restrict__) (L1_Memory+23000+200*((T1Ind_Total)%2));
		KerArg3->Bias = (int * __restrict__) (L1_Memory+23400+4*((T1Ind_Total)%2));
		KerArg3->Out = (short int * __restrict__) (L1_Memory+24208+20*((T1Ind_Total)%2));
		AT_FORK(gap_ncore(), (void *) KerDENSElayer16, (void *) KerArg3);
		__CALL(KerDENSElayer16, KerArg3);
		}
		/*================================= Write Tiles =====================================*/
		if (_SP_H_0) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+200*((T1Ind_Total)%3)),
				_SC_H_0, 1, &DmaW_Evt1);
		if (_SP_Z) AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+23408+400*((T1Ind_Total)%2)),
				_SC_Z, 1, &DmaW_Evt2);
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) L1_Memory+24208+20*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt3);
		if (_SP_prod1) AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write prod1 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod1+_C_prod1), ((AT_L2_INT_ADDR_TYPE) L1_Memory+24248+200*((T1Ind_Total)%2)),
				_SC_prod1, 1, &DmaW_Evt4);
		if (_SP_prod2) AT_L2_WAIT(0, &DmaW_Evt5); /* Wait previous DMA write prod2 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod2+_C_prod2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+24648+400*((T1Ind_Total)%2)),
				_SC_prod2, 1, &DmaW_Evt5);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_H_0 = _SC_H_0;
		
		
		
		
		_SP_Z = _SC_Z;
		_SP_Out = _SC_Out;
		_SP_prod1 = _SC_prod1;
		_SP_prod2 = _SC_prod2;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_H_0 = 0;
		
		_SC_Z = 0;
		
		_SC_Out = 0;
		
		_SC_prod1 = 0;
		
		_SC_prod2 = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		T1Ind_Total++;
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
	AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write Z */
	AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Out */
	AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write prod1 */
	AT_L2_WAIT(0, &DmaW_Evt5); /* Wait previous DMA write prod2 */
	/*============================ End Write Tiles Epilog ===============================*/
}
