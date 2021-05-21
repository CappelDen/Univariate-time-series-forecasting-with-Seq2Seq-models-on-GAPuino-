#include "EncDecLayer.h"
L1_CL_MEM AT_L1_POINTER L1_Memory;
L2_MEM AT_L2_POINTER L2_Memory;
//AT_HYPERRAM_POINTER L3_Memory;
//static AT_HYPERRAM_T HyperRam;
void Encoder(
		struct pi_device HyperRam,
		short int * __restrict__ In,
		unsigned int step_in,
		unsigned int Iterazione,
		short int * __restrict__ H_0,
		short int * __restrict__ C_0,
		short int * __restrict__ Kernel,
		uint32_t Rec_Kernel,
		int * __restrict__ Bias,
		short int * __restrict__ Z,
		unsigned int Norm)

{
	/* Shared L1: 44112 bytes, L2 buffer: 25000 bytes */
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
	AT_HYPERRAM_CL_EVENT Uchan1;
	KerZComputation16_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;
	KerLSTMlayer16_ArgT S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _C_H_0, _N_H_0;
	unsigned int _SP_H_0, _SC_H_0, _SN_H_0;
	unsigned int _C_C_0, _N_C_0;
	unsigned int _SP_C_0, _SC_C_0, _SN_C_0;
	unsigned int _N_Kernel;
	unsigned int _SN_Kernel;
	unsigned int _NN_Rec_Kernel;
	unsigned int _SN_Rec_Kernel, _SNN_Rec_Kernel;
	unsigned int _LN_Rec_Kernel, _LNN_Rec_Kernel;
	unsigned int _N_Bias;
	unsigned int _SN_Bias;
	unsigned int _C_Z;
	unsigned int _SP_Z, _SC_Z;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 1][Tile0 Dim: 40]
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
			Total Size: 500 [Tile1, 1:[250x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[250x1], 2]
		Tile0: [0, 500, 500], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: C_0, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 500 [Tile1, 1:[250x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[250x1], 2]
		Tile0: [0, 500, 500], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Kernel, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2000 [Tile1, 1:[1000x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1000x1], 2]
		Tile0: [0, 2000, 2000], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 40 logical tiles, 40 physical tiles
			Total Size: 500000 [Tile0, 40:[250x25, 38:250x25, 250x25], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 40:[250x25, 38:250x25, 250x25], 2]
		Tile0: [0, 12500, 50], Tile1: [50, 12500, 50], Tile2; [100, 12500, 50]
		T0: [Tile0: 0], T1: [Tile0: 1], T2: [Tile0: 2]
	Ker Arg: Bias, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4000 [Tile1, 1:[1000x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1000x1], 4]
		Tile0: [0, 4000, 4000], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Z, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2000 [Tile1, 1:[1000x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1000x1], 2]
		Tile0: [0, 2000, 2000], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	
	KerArg0->W_H = (unsigned int) (250);
	KerArg0->W_Rec_Kernel = (unsigned int) (25);
	KerArg0->Norm = (unsigned int) (Norm);
	KerArg1->W_C = (unsigned int) (250);
	KerArg1->Norm = (unsigned int) (Norm);
	/*================================= Read Tiles Prolog ===============================*/
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+0), 54, 0, &DmaR_Evt1);
	_C_H_0=0; _SC_H_0=500;
	_SP_H_0=0;
	_N_H_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+0), 500, 0, &DmaR_Evt2);
	_C_C_0=0; _SC_C_0=500;
	_SP_C_0=0;
	_N_C_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1612+0), 500, 0, &DmaR_Evt3);
	_N_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3112+0), 2000, 0, &DmaR_Evt4);
	_NN_Rec_Kernel=50; _SN_Rec_Kernel=12500;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Rec_Kernel+0), ((AT_HYPERRAM_INT_ADDR_TYPE) L2_Memory+0+0), 12500, 2000, 50, 0, &Uchan1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &Uchan1); /* Wait previous uDMA read Rec_Kernel */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Rec_Kernel+50), ((AT_HYPERRAM_INT_ADDR_TYPE) L2_Memory+0+12500), 12500, 2000, 50, 0, &Uchan1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+19112+0), 12500, 0, &DmaR_Evt5);
	_N_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+7112+0), 4000, 0, &DmaR_Evt6);
	_C_Z=0; _SC_Z=2000;
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
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_N_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+500*((T1Ind_Total+1)%3)),
					_SN_H_0, 0, &DmaR_Evt2);
		}
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read C_0 */
		if (_SN_C_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_N_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1612+500*((T1Ind_Total+1)%3)),
					_SN_C_0, 0, &DmaR_Evt3);
		}
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Kernel */
		if (_SN_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+_N_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3112+2000*((T1Ind_Total+1)%2)),
					_SN_Kernel, 0, &DmaR_Evt4);
		}
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+7112+4000*((T1Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt6);
		}
		/*============================= End Read Tiles ======================================*/
		for(Iterazione=0;Iterazione<step_in;Iterazione++){
		for (T0Ind=0; T0Ind<40; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==39), T0Ind_NextLast = ((T0Ind+1)==39), T0Ind_NextNextLast = ((T0Ind+2)==39);
			/*================================= Prepare Tiles ===================================*/
			_SNN_Rec_Kernel = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_Rec_Kernel = _NN_Rec_Kernel + (50); _LNN_Rec_Kernel = (50); _SNN_Rec_Kernel = (250*_LNN_Rec_Kernel); 
				} else {
					_NN_Rec_Kernel = _NN_Rec_Kernel + (-1950); _LNN_Rec_Kernel = (50); _SNN_Rec_Kernel = (250*_LNN_Rec_Kernel); 
				}
			} else {
				_NN_Rec_Kernel = _NN_Rec_Kernel + (50); _LNN_Rec_Kernel = (50); _SNN_Rec_Kernel = (250*_LNN_Rec_Kernel); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &Uchan1); /* Wait previous uDMA read Rec_Kernel */
			if (_SNN_Rec_Kernel) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Rec_Kernel+_NN_Rec_Kernel), ((AT_HYPERRAM_INT_ADDR_TYPE) L2_Memory+0+12500*((T0Ind_Total)%2)),
						_SNN_Rec_Kernel, 2000, _LNN_Rec_Kernel, 0, &Uchan1);
			}
			AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Rec_Kernel */
			if (_SN_Rec_Kernel) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) L2_Memory+0+12500*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) L1_Memory+19112+12500*((T0Ind_Total+1)%2)),
						_SN_Rec_Kernel, 0, &DmaR_Evt5);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (short int * __restrict__) (L1_Memory+0+56*((T1Ind_Total)%2));
			KerArg0->Iterazione = (unsigned int) (Iterazione);
			KerArg0->H_0 = (short int * __restrict__) (L1_Memory+112+500*((T1Ind_Total)%3));
			KerArg0->Kernel = (short int * __restrict__) (L1_Memory+3112+2000*((T1Ind_Total)%2));
			KerArg0->Rec_Kernel = (short int * __restrict__) (L1_Memory+19112+12500*((T0Ind_Total)%2));
			KerArg0->Bias = (int * __restrict__) (L1_Memory+7112+4000*((T1Ind_Total)%2));
			KerArg0->Z = (short int * __restrict__) (L1_Memory+15112+2000*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned int) ((T0Ind)*25);
			AT_FORK(gap_ncore(), (void *) KerZComputation16, (void *) KerArg0);
			__CALL(KerZComputation16, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			
			_SN_Rec_Kernel = _SNN_Rec_Kernel;_LN_Rec_Kernel = _LNN_Rec_Kernel;
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg1->Z = (short int * __restrict__) (L1_Memory+15112+2000*((T1Ind_Total)%2));
		KerArg1->C_0 = (short int * __restrict__) (L1_Memory+1612+500*((T1Ind_Total)%3));
		KerArg1->H_0 = (short int * __restrict__) (L1_Memory+112+500*((T1Ind_Total)%3));
		AT_FORK(gap_ncore(), (void *) KerLSTMlayer16, (void *) KerArg1);
		__CALL(KerLSTMlayer16, KerArg1);
		}
		/*================================= Write Tiles =====================================*/
		if (_SP_H_0) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+500*((T1Ind_Total)%3)),
				_SC_H_0, 1, &DmaW_Evt1);
		if (_SP_C_0) AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write C_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_C_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1612+500*((T1Ind_Total)%3)),
				_SC_C_0, 1, &DmaW_Evt2);
		if (_SP_Z) AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+15112+2000*((T1Ind_Total)%2)),
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
		struct pi_device HyperRam,
		unsigned int step_out,
		unsigned int Iterazione,
		short int * __restrict__ H_0,
		short int * __restrict__ C_0,
		short int * __restrict__ Kernel,
		uint32_t Rec_Kernel,
		int * __restrict__ Bias,
		short int * __restrict__ Dense_Kernel,
		int * __restrict__ Dense_Bias,
		short int * __restrict__ Out,
		short int * __restrict__ Z,
		unsigned int Norm)

{
	/* Shared L1: 44048 bytes, L2 buffer: 24000 bytes */
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
	AT_HYPERRAM_CL_EVENT Uchan1;
	KerZComputationDec16_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;
	KerLSTMlayer16_ArgT S_KerArg1, *KerArg1 = &S_KerArg1;
	KerDENSElayer16_ArgT S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _C_H_0, _N_H_0;
	unsigned int _SP_H_0, _SC_H_0, _SN_H_0;
	unsigned int _C_C_0, _N_C_0;
	unsigned int _SP_C_0, _SC_C_0, _SN_C_0;
	unsigned int _N_Kernel;
	unsigned int _SN_Kernel;
	unsigned int _NN_Rec_Kernel;
	unsigned int _SN_Rec_Kernel, _SNN_Rec_Kernel;
	unsigned int _LN_Rec_Kernel, _LNN_Rec_Kernel;
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
		[Tile1 Dim: 1][Tile0 Dim: 42]
	Ker Arg: H_0, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 500 [Tile1, 1:[250x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[250x1], 2]
		Tile0: [0, 500, 500], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: C_0, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 500 [Tile1, 1:[250x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[250x1], 2]
		Tile0: [0, 500, 500], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Kernel, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2000 [Tile1, 1:[1000x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1000x1], 2]
		Tile0: [0, 2000, 2000], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 42 logical tiles, 42 physical tiles
			Total Size: 500000 [Tile0, 42:[250x24, 40:250x24, 250x16], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 42:[250x24, 40:250x24, 250x16], 2]
		Tile0: [0, 12000, 48], Tile1: [48, 12000, 48], Tile2; [96, 12000, 48]
		T0: [Tile0: 0], T1: [Tile0: 1], T2: [Tile0: 2]
	Ker Arg: Bias, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4000 [Tile1, 1:[1000x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1000x1], 4]
		Tile0: [0, 4000, 4000], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Dense_Kernel, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 500 [Tile1, 1:[250x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[250x1], 2]
		Tile0: [0, 500, 500], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
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
			Total Size: 2000 [Tile1, 1:[1000x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1000x1], 2]
		Tile0: [0, 2000, 2000], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
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
	KerArg0->W_H = (unsigned int) (250);
	KerArg0->Norm = (unsigned int) (Norm);
	KerArg1->W_C = (unsigned int) (250);
	KerArg1->Norm = (unsigned int) (Norm);
	KerArg2->InSize = (unsigned int) (250);
	KerArg2->Norm = (unsigned int) (Norm);
	
	/*================================= Read Tiles Prolog ===============================*/
	_C_H_0=0; _SC_H_0=500;
	_SP_H_0=0;
	_N_H_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+0), 500, 0, &DmaR_Evt1);
	_C_C_0=0; _SC_C_0=500;
	_SP_C_0=0;
	_N_C_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1500+0), 500, 0, &DmaR_Evt2);
	_N_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3000+0), 2000, 0, &DmaR_Evt3);
	_NN_Rec_Kernel=48; _SN_Rec_Kernel=12000;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Rec_Kernel+0), ((AT_HYPERRAM_INT_ADDR_TYPE) L2_Memory+0+0), 12000, 2000, 48, 0, &Uchan1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &Uchan1); /* Wait previous uDMA read Rec_Kernel */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Rec_Kernel+48), ((AT_HYPERRAM_INT_ADDR_TYPE) L2_Memory+0+12000), 12000, 2000, 48, 0, &Uchan1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) L2_Memory+0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+20048+0), 12000, 0, &DmaR_Evt4);
	_N_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+7000+0), 4000, 0, &DmaR_Evt5);
	_N_Dense_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+15000+0), 500, 0, &DmaR_Evt6);
	_N_Dense_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+16000+0), 4, 0, &DmaR_Evt7);
	_C_Z=0; _SC_Z=2000;
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
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_N_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+500*((T1Ind_Total+1)%3)),
					_SN_H_0, 0, &DmaR_Evt1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read C_0 */
		if (_SN_C_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_N_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1500+500*((T1Ind_Total+1)%3)),
					_SN_C_0, 0, &DmaR_Evt2);
		}
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Kernel */
		if (_SN_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+_N_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3000+2000*((T1Ind_Total+1)%2)),
					_SN_Kernel, 0, &DmaR_Evt3);
		}
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+7000+4000*((T1Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt5);
		}
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Dense_Kernel */
		if (_SN_Dense_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Kernel+_N_Dense_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+15000+500*((T1Ind_Total+1)%2)),
					_SN_Dense_Kernel, 0, &DmaR_Evt6);
		}
		AT_L2_WAIT(0, &DmaR_Evt7); /* Wait previous DMA read Dense_Bias */
		if (_SN_Dense_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Bias+_N_Dense_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+16000+4*((T1Ind_Total+1)%2)),
					_SN_Dense_Bias, 0, &DmaR_Evt7);
		}
		/*============================= End Read Tiles ======================================*/
		for(Iterazione=0;Iterazione<step_out;Iterazione++){
		for (T0Ind=0; T0Ind<42; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==41), T0Ind_NextLast = ((T0Ind+1)==41), T0Ind_NextNextLast = ((T0Ind+2)==41);
			/*================================= Prepare Tiles ===================================*/
			_SNN_Rec_Kernel = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_Rec_Kernel = _NN_Rec_Kernel + (48); _LNN_Rec_Kernel = ((T0Ind_NextNextLast)?32:48); _SNN_Rec_Kernel = (250*_LNN_Rec_Kernel); 
				} else {
					_NN_Rec_Kernel = _NN_Rec_Kernel + (-1968); _LNN_Rec_Kernel = (48); _SNN_Rec_Kernel = (250*_LNN_Rec_Kernel); 
				}
			} else {
				_NN_Rec_Kernel = _NN_Rec_Kernel + (48); _LNN_Rec_Kernel = (48); _SNN_Rec_Kernel = (250*_LNN_Rec_Kernel); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &Uchan1); /* Wait previous uDMA read Rec_Kernel */
			if (_SNN_Rec_Kernel) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Rec_Kernel+_NN_Rec_Kernel), ((AT_HYPERRAM_INT_ADDR_TYPE) L2_Memory+0+12000*((T0Ind_Total)%2)),
						_SNN_Rec_Kernel, 2000, _LNN_Rec_Kernel, 0, &Uchan1);
			}
			AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Rec_Kernel */
			if (_SN_Rec_Kernel) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) L2_Memory+0+12000*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) L1_Memory+20048+12000*((T0Ind_Total+1)%2)),
						_SN_Rec_Kernel, 0, &DmaR_Evt4);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->H_0 = (short int * __restrict__) (L1_Memory+0+500*((T1Ind_Total)%3));
			KerArg0->Kernel = (short int * __restrict__) (L1_Memory+3000+2000*((T1Ind_Total)%2));
			KerArg0->Rec_Kernel = (short int * __restrict__) (L1_Memory+20048+12000*((T0Ind_Total)%2));
			KerArg0->W_Rec_Kernel = (unsigned int) ((T0Ind_Last)?16:24);
			KerArg0->Bias = (int * __restrict__) (L1_Memory+7000+4000*((T1Ind_Total)%2));
			KerArg0->Z = (short int * __restrict__) (L1_Memory+16008+2000*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned int) ((T0Ind)*24);
			AT_FORK(gap_ncore(), (void *) KerZComputationDec16, (void *) KerArg0);
			__CALL(KerZComputationDec16, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			
			_SN_Rec_Kernel = _SNN_Rec_Kernel;_LN_Rec_Kernel = _LNN_Rec_Kernel;
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg1->Z = (short int * __restrict__) (L1_Memory+16008+2000*((T1Ind_Total)%2));
		KerArg1->C_0 = (short int * __restrict__) (L1_Memory+1500+500*((T1Ind_Total)%3));
		KerArg1->H_0 = (short int * __restrict__) (L1_Memory+0+500*((T1Ind_Total)%3));
		AT_FORK(gap_ncore(), (void *) KerLSTMlayer16, (void *) KerArg1);
		__CALL(KerLSTMlayer16, KerArg1);
		KerArg2->In = (short int * __restrict__) (L1_Memory+0+500*((T1Ind_Total)%3));
		KerArg2->Iterazione = (unsigned int) (Iterazione);
		KerArg2->Filter = (short int * __restrict__) (L1_Memory+15000+500*((T1Ind_Total)%2));
		KerArg2->Bias = (int * __restrict__) (L1_Memory+16000+4*((T1Ind_Total)%2));
		KerArg2->Out = (short int * __restrict__) (L1_Memory+20008+20*((T1Ind_Total)%2));
		AT_FORK(gap_ncore(), (void *) KerDENSElayer16, (void *) KerArg2);
		__CALL(KerDENSElayer16, KerArg2);
		}
		/*================================= Write Tiles =====================================*/
		if (_SP_H_0) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+500*((T1Ind_Total)%3)),
				_SC_H_0, 1, &DmaW_Evt1);
		if (_SP_C_0) AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write C_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) C_0+_C_C_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1500+500*((T1Ind_Total)%3)),
				_SC_C_0, 1, &DmaW_Evt2);
		if (_SP_Z) AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+16008+2000*((T1Ind_Total)%2)),
				_SC_Z, 1, &DmaW_Evt3);
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) L1_Memory+20008+20*((T1Ind_Total)%2)),
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
