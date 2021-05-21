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
	/* Shared L1: 44112 bytes, L2 buffer: 0 bytes */
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
		[Tile1 Dim: 1][Tile0 Dim: 23]
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
			Total Size: 400 [Tile1, 1:[200x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[200x1], 2]
		Tile0: [0, 400, 400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: C_0, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile1, 1:[200x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[200x1], 2]
		Tile0: [0, 400, 400], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Kernel, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1600 [Tile1, 1:[800x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[800x1], 2]
		Tile0: [0, 1600, 1600], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 23 logical tiles, 23 physical tiles
			Total Size: 320000 [Tile0, 23:[200x36, 21:200x36, 200x8], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 23:[200x36, 21:200x36, 200x8], 2]
		Tile0: [0, 14400, 72], Tile1: [72, 14400, 72], Tile2; [144, 14400, 72]
		T0: [Tile0: 0], T1: [Tile0: 1], T2: [Tile0: 2]
	Ker Arg: Bias, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [Tile1, 1:[800x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[800x1], 4]
		Tile0: [0, 3200, 3200], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Z, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1600 [Tile1, 1:[800x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[800x1], 2]
		Tile0: [0, 1600, 1600], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Iterazione = (unsigned int) (Iterazione);
	KerArg0->W_H = (unsigned int) (200);
	KerArg0->Norm = (unsigned int) (Norm);
	KerArg1->W_C = (unsigned int) (200);
	KerArg1->Norm = (unsigned int) (Norm);
	/*================================= Read Tiles Prolog ===============================*/
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+0), 54, 0, &DmaR_Evt1);
	_C_H_0=0; _SC_H_0=400;
	_SP_H_0=0;
	_N_H_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+0), 400, 0, &DmaR_Evt2);
	_C_C_0=0; _SC_C_0=400;
	_SP_C_0=0;
	_N_C_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1312+0), 400, 0, &DmaR_Evt3);
	_N_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2512+0), 1600, 0, &DmaR_Evt4);
	_N_Rec_Kernel=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+15312+0), 14400, 1600, 72, 0, &DmaR_Evt5);
	_N_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+5712+0), 3200, 0, &DmaR_Evt6);
	_C_Z=0; _SC_Z=1600;
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
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+56*((T1Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read H_0 */
		if (_SN_H_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_N_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+400*((T1Ind_Total+1)%3)),
					_SN_H_0, 0, &DmaR_Evt2);
		}
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read C_0 */
		if (_SN_C_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_N_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1312+400*((T1Ind_Total+1)%3)),
					_SN_C_0, 0, &DmaR_Evt3);
		}
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Kernel */
		if (_SN_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+_N_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2512+1600*((T1Ind_Total+1)%2)),
					_SN_Kernel, 0, &DmaR_Evt4);
		}
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+5712+3200*((T1Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt6);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<23; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==22), T0Ind_NextLast = ((T0Ind+1)==22);
			/*================================= Prepare Tiles ===================================*/
			_SN_Rec_Kernel = 0;
			if (!(T0Ind_Last)) {
				_N_Rec_Kernel = _N_Rec_Kernel + (72); _LN_Rec_Kernel = ((T0Ind_NextLast)?16:72); _SN_Rec_Kernel = (200*_LN_Rec_Kernel); 
			} else if (!(1)) {
				_N_Rec_Kernel = _N_Rec_Kernel + (-1584); _LN_Rec_Kernel = (72); _SN_Rec_Kernel = (200*_LN_Rec_Kernel); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Rec_Kernel */
			if (_SN_Rec_Kernel) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+_N_Rec_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+15312+14400*((T0Ind_Total+1)%2)),
						_SN_Rec_Kernel, 1600, _LN_Rec_Kernel, 0, &DmaR_Evt5);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (short int * __restrict__) (L1_Memory+0+56*((T1Ind_Total)%2));
			KerArg0->H_0 = (short int * __restrict__) (L1_Memory+112+400*((T1Ind_Total)%3));
			KerArg0->Kernel = (short int * __restrict__) (L1_Memory+2512+1600*((T1Ind_Total)%2));
			KerArg0->Rec_Kernel = (short int * __restrict__) (L1_Memory+15312+14400*((T0Ind_Total)%2));
			KerArg0->W_Rec_Kernel = (unsigned int) ((T0Ind_Last)?8:36);
			KerArg0->Bias = (int * __restrict__) (L1_Memory+5712+3200*((T1Ind_Total)%2));
			KerArg0->Z = (short int * __restrict__) (L1_Memory+12112+1600*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned int) ((T0Ind)*36);
			AT_FORK(gap_ncore(), (void *) KerZComputation16, (void *) KerArg0);
			__CALL(KerZComputation16, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg1->Z = (short int * __restrict__) (L1_Memory+12112+1600*((T1Ind_Total)%2));
		KerArg1->C_0 = (short int * __restrict__) (L1_Memory+1312+400*((T1Ind_Total)%3));
		KerArg1->H_0 = (short int * __restrict__) (L1_Memory+112+400*((T1Ind_Total)%3));
		AT_FORK(gap_ncore(), (void *) KerLSTMlayer16, (void *) KerArg1);
		__CALL(KerLSTMlayer16, KerArg1);
		/*================================= Write Tiles =====================================*/
		if (_SP_H_0) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+400*((T1Ind_Total)%3)),
				_SC_H_0, 1, &DmaW_Evt1);
		if (_SP_C_0) AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write C_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_C_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1312+400*((T1Ind_Total)%3)),
				_SC_C_0, 1, &DmaW_Evt2);
		if (_SP_Z) AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+12112+1600*((T1Ind_Total)%2)),
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
