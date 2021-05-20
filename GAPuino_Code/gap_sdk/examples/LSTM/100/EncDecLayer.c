#include "EncDecLayer.h"
L1_CL_MEM AT_L1_POINTER L1_Memory;
L2_MEM AT_L2_POINTER L2_Memory;
void Encoder(
		short int * __restrict__ In,
		unsigned int step_in,
		unsigned int Iterazione,
		short int * __restrict__ H_0,
		short int * __restrict__ C_0,
		short int * __restrict__ Kernel,
		short int * __restrict__ Rec_Kernel,
		int * __restrict__ Bias,
		short int * __restrict__ Z,
		unsigned int Norm)

{
	/* Shared L1: 44512 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_L2_EVENT DmaW_Evt2;
	AT_L2_EVENT DmaW_Evt3;
	KerZComputation16_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;
	KerLSTMlayer16_ArgT S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _C_H_0, _N_H_0;
	unsigned int _SP_H_0, _SC_H_0, _SN_H_0;
	unsigned int _C_C_0, _N_C_0;
	unsigned int _SP_C_0, _SC_C_0, _SN_C_0;
	unsigned int _N_Kernel;
	unsigned int _SN_Kernel;
	unsigned int _N_Rec_Kernel;
	unsigned int _SN_Rec_Kernel;
	unsigned int _LN_Rec_Kernel;
	unsigned int _N_Bias;
	unsigned int _SN_Bias;
	unsigned int _C_Z;
	unsigned int _SP_Z, _SC_Z;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 1][Tile0 Dim: 5]
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
	Ker Arg: C_0, Tiled Space: Tile1
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
			Total Size: 800 [Tile1, 1:[400x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[400x1], 2]
		Tile0: [0, 800, 800], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 80000 [Tile0, 5:[100x92, 3:100x92, 100x32], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[100x92, 3:100x92, 100x32], 2]
		Tile0: [0, 18400, 184], Tile1: [184, 18400, 184], Tile2; [368, 18400, 184]
		T0: [Tile0: 0], T1: [Tile0: 1], T2: [Tile0: 0 +1/84]
	Ker Arg: Bias, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1600 [Tile1, 1:[400x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[400x1], 4]
		Tile0: [0, 1600, 1600], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Z, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 800 [Tile1, 1:[400x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[400x1], 2]
		Tile0: [0, 800, 800], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_H = (unsigned int) (100);
	KerArg1->W_C = (unsigned int) (100);
	/*================================= Read Tiles Prolog ===============================*/
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+36800+0), 54, 0, &DmaR_Evt1);
	_C_H_0=0; _SC_H_0=200;
	_SP_H_0=0;
	_N_H_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+36912+0), 200, 0, &DmaR_Evt2);
	_C_C_0=0; _SC_C_0=200;
	_SP_C_0=0;
	_N_C_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+37512+0), 200, 0, &DmaR_Evt3);
	_N_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+38112+0), 800, 0, &DmaR_Evt4);
	_N_Rec_Kernel=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+0), 18400, 800, 184, 0, &DmaR_Evt5);
	_N_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+39712+0), 1600, 0, &DmaR_Evt6);
	_C_Z=0; _SC_Z=800;
	_SP_Z=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile1 */
		int T1Ind_Last = 1, T1Ind_NextLast = 1;
		/*================================= Prepare Tiles ===================================*/
		_SN_In = 0;
		
		_SN_H_0 = 0;
		
		_SN_C_0 = 0;
		
		_SN_Kernel = 0;
		
		_SN_Bias = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) L1_Memory+36800+56*((T1Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read H_0 */
		if (_SN_H_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_N_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+36912+200*((T1Ind_Total+1)%3)),
					_SN_H_0, 0, &DmaR_Evt2);
		}
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read C_0 */
		if (_SN_C_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_N_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+37512+200*((T1Ind_Total+1)%3)),
					_SN_C_0, 0, &DmaR_Evt3);
		}
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Kernel */
		if (_SN_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+_N_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+38112+800*((T1Ind_Total+1)%2)),
					_SN_Kernel, 0, &DmaR_Evt4);
		}
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+39712+1600*((T1Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt6);
		}
		/*============================= End Read Tiles ======================================*/
		for(Iterazione=0;Iterazione<step_in;Iterazione++){
		for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4);
			/*================================= Prepare Tiles ===================================*/
			_SN_Rec_Kernel = 0;
			if (!(T0Ind_Last)) {
				_N_Rec_Kernel = _N_Rec_Kernel + (184); _LN_Rec_Kernel = ((T0Ind_NextLast)?64:184); _SN_Rec_Kernel = (100*_LN_Rec_Kernel); 
			} else {
				_N_Rec_Kernel = _N_Rec_Kernel + (-736); _LN_Rec_Kernel = (184); _SN_Rec_Kernel = (100*_LN_Rec_Kernel); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Rec_Kernel */
			if (_SN_Rec_Kernel) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+_N_Rec_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+18400*((T0Ind_Total+1)%2)),
						_SN_Rec_Kernel, 800, _LN_Rec_Kernel, 0, &DmaR_Evt5);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (short int * __restrict__) (L1_Memory+36800+56*((T1Ind_Total)%2));
			KerArg0->Iterazione = (unsigned int) (Iterazione);
			KerArg0->H_0 = (short int * __restrict__) (L1_Memory+36912+200*((T1Ind_Total)%3));
			KerArg0->Kernel = (short int * __restrict__) (L1_Memory+38112+800*((T1Ind_Total)%2));
			KerArg0->Rec_Kernel = (short int * __restrict__) (L1_Memory+0+18400*((T0Ind_Total)%2));
			KerArg0->W_Rec_Kernel = (unsigned int) ((T0Ind_Last)?32:92);
			KerArg0->Bias = (int * __restrict__) (L1_Memory+39712+1600*((T1Ind_Total)%2));
			KerArg0->Z = (short int * __restrict__) (L1_Memory+42912+800*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned int) ((T0Ind)*92);
			KerArg0->Norm = (unsigned int) (Norm);
			AT_FORK(gap_ncore(), (void *) KerZComputation16, (void *) KerArg0);
			__CALL(KerZComputation16, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg1->Z = (short int * __restrict__) (L1_Memory+42912+800*((T1Ind_Total)%2));
		KerArg1->C_0 = (short int * __restrict__) (L1_Memory+37512+200*((T1Ind_Total)%3));
		KerArg1->H_0 = (short int * __restrict__) (L1_Memory+36912+200*((T1Ind_Total)%3));
		KerArg1->Norm = (unsigned int) (Norm);
		AT_FORK(gap_ncore(), (void *) KerLSTMlayer16, (void *) KerArg1);
		__CALL(KerLSTMlayer16, KerArg1);}
		/*================================= Write Tiles =====================================*/
		if (_SP_H_0) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+36912+200*((T1Ind_Total)%3)),
				_SC_H_0, 1, &DmaW_Evt1);
		if (_SP_C_0) AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write C_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_C_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+37512+200*((T1Ind_Total)%3)),
				_SC_C_0, 1, &DmaW_Evt2);
		if (_SP_Z) AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+42912+800*((T1Ind_Total)%2)),
				_SC_Z, 1, &DmaW_Evt3);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		
		_SP_H_0 = _SC_H_0;
		_SP_C_0 = _SC_C_0;
		
		
		_SP_Z = _SC_Z;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_H_0 = 0;
		
		_SC_C_0 = 0;
		
		_SC_Z = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		T1Ind_Total++;
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
	AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write C_0 */
	AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Z */
	/*============================ End Write Tiles Epilog ===============================*/
}
void Decoder(
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
		unsigned int Norm)

{
	/* Shared L1: 44448 bytes, L2 buffer: 0 bytes */
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
	KerZComputationDec16_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;
	KerLSTMlayer16_ArgT S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDENSElayer16_ArgT S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_H_0, _N_H_0;
	unsigned int _SP_H_0, _SC_H_0, _SN_H_0;
	unsigned int _C_C_0, _N_C_0;
	unsigned int _SP_C_0, _SC_C_0, _SN_C_0;
	unsigned int _N_Kernel;
	unsigned int _SN_Kernel;
	unsigned int _N_Rec_Kernel;
	unsigned int _SN_Rec_Kernel;
	unsigned int _LN_Rec_Kernel;
	unsigned int _N_Bias;
	unsigned int _SN_Bias;
	unsigned int _N_Dense_Kernel;
	unsigned int _SN_Dense_Kernel;
	unsigned int _N_Dense_Bias;
	unsigned int _SN_Dense_Bias;
	unsigned int _C_Z;
	unsigned int _SP_Z, _SC_Z;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 1][Tile0 Dim: 5]
	Ker Arg: H_0, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 200 [Tile1, 1:[100x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[100x1], 2]
		Tile0: [0, 200, 200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: C_0, Tiled Space: Tile1
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
			Total Size: 800 [Tile1, 1:[400x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[400x1], 2]
		Tile0: [0, 800, 800], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 80000 [Tile0, 5:[100x91, 3:100x91, 100x36], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[100x91, 3:100x91, 100x36], 2]
		Tile0: [0, 18200, 182], Tile1: [182, 18200, 182], Tile2; [364, 18200, 182]
		T0: [Tile0: 0], T1: [Tile0: 1], T2: [Tile0: 0 +1/82]
	Ker Arg: Bias, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1600 [Tile1, 1:[400x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[400x1], 4]
		Tile0: [0, 1600, 1600], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
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
			Total Size: 800 [Tile1, 1:[400x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[400x1], 2]
		Tile0: [0, 800, 800], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 18 [Tile1, 1:[9x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[9x1], 2]
		Tile0: [0, 18, 18], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_H = (unsigned int) (100);
	KerArg1->W_C = (unsigned int) (100);
	KerArg2->InSize = (unsigned int) (100);
	/*================================= Read Tiles Prolog ===============================*/
	_C_H_0=0; _SC_H_0=200;
	_SP_H_0=0;
	_N_H_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+36400+0), 200, 0, &DmaR_Evt1);
	_C_C_0=0; _SC_C_0=200;
	_SP_C_0=0;
	_N_C_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+37000+0), 200, 0, &DmaR_Evt2);
	_N_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+37600+0), 800, 0, &DmaR_Evt3);
	_N_Rec_Kernel=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+0), 18200, 800, 182, 0, &DmaR_Evt4);
	_N_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+39200+0), 1600, 0, &DmaR_Evt5);
	_N_Dense_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+42400+0), 200, 0, &DmaR_Evt6);
	_N_Dense_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+42800+0), 4, 0, &DmaR_Evt7);
	_C_Z=0; _SC_Z=800;
	_SP_Z=0;
	_C_Out=0; _SC_Out=18;
	_SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile1 */
		int T1Ind_Last = 1, T1Ind_NextLast = 1;
		/*================================= Prepare Tiles ===================================*/
		_SN_H_0 = 0;
		
		_SN_C_0 = 0;
		
		_SN_Kernel = 0;
		
		_SN_Bias = 0;
		
		_SN_Dense_Kernel = 0;
		
		_SN_Dense_Bias = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read H_0 */
		if (_SN_H_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_N_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+36400+200*((T1Ind_Total+1)%3)),
					_SN_H_0, 0, &DmaR_Evt1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read C_0 */
		if (_SN_C_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_N_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+37000+200*((T1Ind_Total+1)%3)),
					_SN_C_0, 0, &DmaR_Evt2);
		}
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Kernel */
		if (_SN_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+_N_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+37600+800*((T1Ind_Total+1)%2)),
					_SN_Kernel, 0, &DmaR_Evt3);
		}
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+39200+1600*((T1Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt5);
		}
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Dense_Kernel */
		if (_SN_Dense_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Kernel+_N_Dense_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+42400+200*((T1Ind_Total+1)%2)),
					_SN_Dense_Kernel, 0, &DmaR_Evt6);
		}
		AT_L2_WAIT(0, &DmaR_Evt7); /* Wait previous DMA read Dense_Bias */
		if (_SN_Dense_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Bias+_N_Dense_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+42800+4*((T1Ind_Total+1)%2)),
					_SN_Dense_Bias, 0, &DmaR_Evt7);
		}
		/*============================= End Read Tiles ======================================*/
		for(Iterazione=0;Iterazione<step_out;Iterazione++){
		for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4);
			/*================================= Prepare Tiles ===================================*/
			_SN_Rec_Kernel = 0;
			if (!(T0Ind_Last)) {
				_N_Rec_Kernel = _N_Rec_Kernel + (182); _LN_Rec_Kernel = ((T0Ind_NextLast)?72:182); _SN_Rec_Kernel = (100*_LN_Rec_Kernel); 
			} else {
				_N_Rec_Kernel = _N_Rec_Kernel + (-728); _LN_Rec_Kernel = (182); _SN_Rec_Kernel = (100*_LN_Rec_Kernel); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Rec_Kernel */
			if (_SN_Rec_Kernel) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+_N_Rec_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+18200*((T0Ind_Total+1)%2)),
						_SN_Rec_Kernel, 800, _LN_Rec_Kernel, 0, &DmaR_Evt4);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->H_0 = (short int * __restrict__) (L1_Memory+36400+200*((T1Ind_Total)%3));
			KerArg0->Kernel = (short int * __restrict__) (L1_Memory+37600+800*((T1Ind_Total)%2));
			KerArg0->Rec_Kernel = (short int * __restrict__) (L1_Memory+0+18200*((T0Ind_Total)%2));
			KerArg0->W_Rec_Kernel = (unsigned int) ((T0Ind_Last)?36:91);
			KerArg0->Bias = (int * __restrict__) (L1_Memory+39200+1600*((T1Ind_Total)%2));
			KerArg0->Z = (short int * __restrict__) (L1_Memory+42808+800*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned int) ((T0Ind)*91);
			KerArg0->Norm = (unsigned int) (Norm);
			AT_FORK(gap_ncore(), (void *) KerZComputationDec16, (void *) KerArg0);
			__CALL(KerZComputationDec16, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg1->Z = (short int * __restrict__) (L1_Memory+42808+800*((T1Ind_Total)%2));
		KerArg1->C_0 = (short int * __restrict__) (L1_Memory+37000+200*((T1Ind_Total)%3));
		KerArg1->H_0 = (short int * __restrict__) (L1_Memory+36400+200*((T1Ind_Total)%3));
		KerArg1->Norm = (unsigned int) (Norm);
		AT_FORK(gap_ncore(), (void *) KerLSTMlayer16, (void *) KerArg1);
		__CALL(KerLSTMlayer16, KerArg1);
		KerArg2->In = (short int * __restrict__) (L1_Memory+36400+200*((T1Ind_Total)%3));
		KerArg2->Filter = (short int * __restrict__) (L1_Memory+42400+200*((T1Ind_Total)%2));
		KerArg2->Bias = (int * __restrict__) (L1_Memory+42800+4*((T1Ind_Total)%2));
		KerArg2->Norm = (unsigned int) (Norm);
		KerArg2->Out = (short int * __restrict__) (L1_Memory+44408+20*((T1Ind_Total)%2));
		KerArg2->Iterazione = (unsigned int) (Iterazione);
		AT_FORK(gap_ncore(), (void *) KerDENSElayer16, (void *) KerArg2);
		__CALL(KerDENSElayer16, KerArg2);}
		/*================================= Write Tiles =====================================*/
		if (_SP_H_0) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+36400+200*((T1Ind_Total)%3)),
				_SC_H_0, 1, &DmaW_Evt1);
		if (_SP_C_0) AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write C_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_C_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+37000+200*((T1Ind_Total)%3)),
				_SC_C_0, 1, &DmaW_Evt2);
		if (_SP_Z) AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+42808+800*((T1Ind_Total)%2)),
				_SC_Z, 1, &DmaW_Evt3);
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) L1_Memory+44408+20*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt4);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_H_0 = _SC_H_0;
		_SP_C_0 = _SC_C_0;
		
		
		
		
		_SP_Z = _SC_Z;
		_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_H_0 = 0;
		
		_SC_C_0 = 0;
		
		_SC_Z = 0;
		
		_SC_Out = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		T1Ind_Total++;
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
	AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write C_0 */
	AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Z */
	AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
