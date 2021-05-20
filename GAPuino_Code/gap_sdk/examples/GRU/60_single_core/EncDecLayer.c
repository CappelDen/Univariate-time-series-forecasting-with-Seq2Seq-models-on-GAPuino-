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
	/* Shared L1: 38392 bytes, L2 buffer: 0 bytes */
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

	/* Iteration space related variables */
	int T2Ind, T2Ind_Total=0, T2Ind_Last, T2Ind_NextLast;
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Z;
	unsigned int _SP_Z, _SC_Z;
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
	unsigned int _N_Rec_Kernel2;
	unsigned int _SN_Rec_Kernel2;
	unsigned int _LN_Rec_Kernel2;
	unsigned int _N_Bias2;
	unsigned int _SN_Bias2;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _C_prod1;
	unsigned int _SP_prod1, _SC_prod1;
	unsigned int _C_prod2;
	unsigned int _SP_prod2, _SC_prod2;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile2 Dim: 1][Tile1 Dim: 1][Tile0 Dim: 2]
	Ker Arg: Z, Tiled Space: Tile2
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile2, 1:[120x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[120x1], 2]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: H_0, Tiled Space: Tile2
		Min Pipe Depth: -1, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile2, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: Kernel, Tiled Space: Tile2
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile2, 1:[120x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[120x1], 2]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 14400 [Tile0, 2:[60x84, 60x36], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[60x84, 60x36], 2]
		Tile0: [0, 10080, 168], Tile1: [168, 4320, 72], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0 +1/24], T2: [Tile0: 0]
	Ker Arg: Bias, Tiled Space: Tile2
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 480 [Tile2, 1:[120x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[120x1], 4]
		Tile0: [0, 480, 480], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: Kernel2, Tiled Space: Tile2
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile2, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: Rec_Kernel2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 7200 [Tile1, 1:[60x60], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[60x60], 2]
		Tile0: [0, 7200, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Bias2, Tiled Space: Tile2
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile2, 1:[60x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 4]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: In, Tiled Space: Tile2
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 54 [Tile2, 1:[27x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[27x1], 2]
		Tile0: [0, 54, 54], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: prod1, Tiled Space: Tile2
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile2, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: prod2, Tiled Space: Tile2
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile2, 1:[60x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 4]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*================================= Read Tiles Prolog ===============================*/
	_C_Z=0; _SC_Z=240;
	_SP_Z=0;
	_C_H_0=0; _SC_H_0=120;
	_SP_H_0=0;
	_N_H_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+0), 120, 0, &DmaR_Evt1);
	_N_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+472+0), 240, 0, &DmaR_Evt2);
	_N_Rec_Kernel=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+18232+0), 10080, 240, 168, 0, &DmaR_Evt3);
	_N_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+952+0), 480, 0, &DmaR_Evt4);
	_N_Kernel2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1912+0), 120, 0, &DmaR_Evt5);
	_N_Rec_Kernel2=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3832+0), 7200, 120, 120, 0, &DmaR_Evt6);
	_N_Bias2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2152+0), 240, 0, &DmaR_Evt7);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+0), 54, 0, &DmaR_Evt8);
	_C_prod1=0; _SC_prod1=120;
	_SP_prod1=0;
	_C_prod2=0; _SC_prod2=240;
	_SP_prod2=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile2 */
		int T2Ind_Last = 1, T2Ind_NextLast = 1;
		/*================================= Prepare Tiles ===================================*/
		_SN_H_0 = 0;
		
		_SN_Kernel = 0;
		
		_SN_Bias = 0;
		
		_SN_Kernel2 = 0;
		
		_SN_Bias2 = 0;
		
		_SN_In = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read H_0 */
		if (_SN_H_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_N_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+120*((T2Ind_Total+1)%3)),
					_SN_H_0, 0, &DmaR_Evt1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Kernel */
		if (_SN_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel+_N_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+472+240*((T2Ind_Total+1)%2)),
					_SN_Kernel, 0, &DmaR_Evt2);
		}
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+952+480*((T2Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt4);
		}
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Kernel2 */
		if (_SN_Kernel2) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Kernel2+_N_Kernel2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1912+120*((T2Ind_Total+1)%2)),
					_SN_Kernel2, 0, &DmaR_Evt5);
		}
		AT_L2_WAIT(0, &DmaR_Evt7); /* Wait previous DMA read Bias2 */
		if (_SN_Bias2) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+_N_Bias2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2152+240*((T2Ind_Total+1)%2)),
					_SN_Bias2, 0, &DmaR_Evt7);
		}
		AT_L2_WAIT(0, &DmaR_Evt8); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+56*((T2Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt8);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile1 */
			int T1Ind_Last = 1, T1Ind_NextLast = 1;
			/*================================= Prepare Tiles ===================================*/
			_SN_Rec_Kernel2 = 0;
			if (!(1)) {
				_N_Rec_Kernel2 = _N_Rec_Kernel2 + 0; _LN_Rec_Kernel2 = (120); _SN_Rec_Kernel2 = (60*_LN_Rec_Kernel2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Rec_Kernel2 */
			if (_SN_Rec_Kernel2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel2+_N_Rec_Kernel2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3832+7200*((T1Ind_Total+1)%2)),
						_SN_Rec_Kernel2, 120, _LN_Rec_Kernel2, 0, &DmaR_Evt6);
			}
			/*============================= End Read Tiles ======================================*/
			for(Iterazione=0;Iterazione<27;Iterazione++){
			for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
				int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_Rec_Kernel = 0;
				if (!(T0Ind_Last)) {
					_N_Rec_Kernel = _N_Rec_Kernel + (168); _LN_Rec_Kernel = ((T0Ind_NextLast)?72:168); _SN_Rec_Kernel = (60*_LN_Rec_Kernel); 
				} else  {
					_N_Rec_Kernel = _N_Rec_Kernel + (-168); _LN_Rec_Kernel = (168); _SN_Rec_Kernel = (60*_LN_Rec_Kernel); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Rec_Kernel */
				if (_SN_Rec_Kernel) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+_N_Rec_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+18232+10080*((T0Ind_Total+1)%2)),
							_SN_Rec_Kernel, 240, _LN_Rec_Kernel, 0, &DmaR_Evt3);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_LOOP =========================*/
				KerZEnc16(
					(short int * __restrict__) (L1_Memory+0+56*((T2Ind_Total)%2)),
					(unsigned int) (Iterazione),
					(short int * __restrict__) (L1_Memory+112+120*((T2Ind_Total)%3)),
					(unsigned int) (60),
					(short int * __restrict__) (L1_Memory+472+240*((T2Ind_Total)%2)),
					(short int * __restrict__) (L1_Memory+18232+10080*((T0Ind_Total)%2)),
					(unsigned int) ((T0Ind_Last)?36:84),
					(int * __restrict__) (L1_Memory+952+480*((T2Ind_Total)%2)),
					(short int * __restrict__) (L1_Memory+2632+240*((T2Ind_Total)%2)),
					(unsigned int) ((T0Ind)*84),
					(unsigned int) (Norm)
				);
				/*================================= Update Arg Pipeline =============================*/
				
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on Tile0 */
			/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
			KerProd16(
				(short int * __restrict__) (L1_Memory+2632+240*((T2Ind_Total)%2)),
				(short int * __restrict__) (L1_Memory+112+120*((T2Ind_Total)%3)),
				(unsigned int) (60),
				(short int * __restrict__) (L1_Memory+3112+120*((T2Ind_Total)%2)),
				(int * __restrict__) (L1_Memory+3352+240*((T2Ind_Total)%2)),
				(unsigned int) (Norm)
			);
			KerGRUEnclayer16(
				(short int * __restrict__) (L1_Memory+2632+240*((T2Ind_Total)%2)),
				(short int * __restrict__) (L1_Memory+0+56*((T2Ind_Total)%2)),
				(unsigned int) (Iterazione),
				(short int * __restrict__) (L1_Memory+112+120*((T2Ind_Total)%3)),
				(unsigned int) (60),
				(short int * __restrict__) (L1_Memory+1912+120*((T2Ind_Total)%2)),
				(short int * __restrict__) (L1_Memory+3832+7200*((T1Ind_Total)%2)),
				(unsigned int) (60),
				(int * __restrict__) (L1_Memory+2152+240*((T2Ind_Total)%2)),
				(short int * __restrict__) (L1_Memory+3112+120*((T2Ind_Total)%2)),
				(int * __restrict__) (L1_Memory+3352+240*((T2Ind_Total)%2)),
				(unsigned int) ((0)*60),
				(unsigned int) (Norm)
			);
			}
			/*================================= Update Arg Pipeline =============================*/
			
			/*============================= End Update Arg Pipeline =============================*/
			T1Ind_Total++;
		} /* End iteration on Tile1 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Z) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2632+240*((T2Ind_Total)%2)),
				_SC_Z, 1, &DmaW_Evt1);
		if (_SP_H_0) AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+112+120*((T2Ind_Total)%3)),
				_SC_H_0, 1, &DmaW_Evt2);
		if (_SP_prod1) AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write prod1 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod1+_C_prod1), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3112+120*((T2Ind_Total)%2)),
				_SC_prod1, 1, &DmaW_Evt3);
		if (_SP_prod2) AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write prod2 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod2+_C_prod2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3352+240*((T2Ind_Total)%2)),
				_SC_prod2, 1, &DmaW_Evt4);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_Z = _SC_Z;
		_SP_H_0 = _SC_H_0;
		
		
		
		
		
		_SP_prod1 = _SC_prod1;
		_SP_prod2 = _SC_prod2;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Z = 0;
		
		_SC_H_0 = 0;
		
		_SC_prod1 = 0;
		
		_SC_prod2 = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		T2Ind_Total++;
	} /* End iteration on Tile2 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Z */
	AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write H_0 */
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
	/* Shared L1: 38088 bytes, L2 buffer: 0 bytes */
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

	/* Iteration space related variables */
	int T2Ind, T2Ind_Total=0, T2Ind_Last, T2Ind_NextLast;
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Z;
	unsigned int _SP_Z, _SC_Z;
	unsigned int _N_Rec_Kernel;
	unsigned int _SN_Rec_Kernel;
	unsigned int _LN_Rec_Kernel;
	unsigned int _N_Bias;
	unsigned int _SN_Bias;
	unsigned int _N_Rec_Kernel2;
	unsigned int _SN_Rec_Kernel2;
	unsigned int _LN_Rec_Kernel2;
	unsigned int _N_Bias2;
	unsigned int _SN_Bias2;
	unsigned int _N_Dense_Kernel;
	unsigned int _SN_Dense_Kernel;
	unsigned int _N_Dense_Bias;
	unsigned int _SN_Dense_Bias;
	unsigned int _C_H_0, _N_H_0;
	unsigned int _SP_H_0, _SC_H_0, _SN_H_0;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _C_prod1;
	unsigned int _SP_prod1, _SC_prod1;
	unsigned int _C_prod2;
	unsigned int _SP_prod2, _SC_prod2;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile2 Dim: 1][Tile1 Dim: 1][Tile0 Dim: 2]
	Ker Arg: Z, Tiled Space: Tile2
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile2, 1:[120x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[120x1], 2]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: Rec_Kernel, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 14400 [Tile0, 2:[60x85, 60x35], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 2:[60x85, 60x35], 2]
		Tile0: [0, 10200, 170], Tile1: [170, 4200, 70], Tile2; [0, 0, 0]
		T0: [Tile0: 0], T1: [Tile0: 0 +1/25], T2: [Tile0: 0]
	Ker Arg: Bias, Tiled Space: Tile2
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 480 [Tile2, 1:[120x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[120x1], 4]
		Tile0: [0, 480, 480], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: Rec_Kernel2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 7200 [Tile1, 1:[60x60], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[60x60], 2]
		Tile0: [0, 7200, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile1: 0], T1: [Tile1: 0], T2: [Tile1: 0]
	Ker Arg: Bias2, Tiled Space: Tile2
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile2, 1:[60x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 4]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: Dense_Kernel, Tiled Space: Tile2
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile2, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: Dense_Bias, Tiled Space: Tile2
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4 [Tile2, 1:[1x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[1x1], 4]
		Tile0: [0, 4, 4], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: H_0, Tiled Space: Tile2
		Min Pipe Depth: -1, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile2, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: Out, Tiled Space: Tile2
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 18 [Tile2, 1:[9x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[9x1], 2]
		Tile0: [0, 18, 18], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: prod1, Tiled Space: Tile2
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 120 [Tile2, 1:[60x1], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 2]
		Tile0: [0, 120, 120], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	Ker Arg: prod2, Tiled Space: Tile2
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 240 [Tile2, 1:[60x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile2, 1:[60x1], 4]
		Tile0: [0, 240, 240], Tile1: [0, 0, 0], Tile2; [0, 0, 0]
		T0: [Tile2: 0], T1: [Tile2: 0], T2: [Tile2: 0]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*================================= Read Tiles Prolog ===============================*/
	_C_Z=0; _SC_Z=240;
	_SP_Z=0;
	_N_Rec_Kernel=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+17688+0), 10200, 240, 170, 0, &DmaR_Evt1);
	_N_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+360+0), 480, 0, &DmaR_Evt2);
	_N_Rec_Kernel2=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3288+0), 7200, 120, 120, 0, &DmaR_Evt3);
	_N_Bias2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1320+0), 240, 0, &DmaR_Evt4);
	_N_Dense_Kernel=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Kernel+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1800+0), 120, 0, &DmaR_Evt5);
	_N_Dense_Bias=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Bias+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2040+0), 4, 0, &DmaR_Evt6);
	_C_H_0=0; _SC_H_0=120;
	_SP_H_0=0;
	_N_H_0=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+0), 120, 0, &DmaR_Evt7);
	_C_Out=0; _SC_Out=18;
	_SP_Out=0;
	_C_prod1=0; _SC_prod1=120;
	_SP_prod1=0;
	_C_prod2=0; _SC_prod2=240;
	_SP_prod2=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile2 */
		int T2Ind_Last = 1, T2Ind_NextLast = 1;
		/*================================= Prepare Tiles ===================================*/
		_SN_Bias = 0;
		
		_SN_Bias2 = 0;
		
		_SN_Dense_Kernel = 0;
		
		_SN_Dense_Bias = 0;
		
		_SN_H_0 = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+360+480*((T2Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt2);
		}
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Bias2 */
		if (_SN_Bias2) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias2+_N_Bias2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1320+240*((T2Ind_Total+1)%2)),
					_SN_Bias2, 0, &DmaR_Evt4);
		}
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Dense_Kernel */
		if (_SN_Dense_Kernel) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Kernel+_N_Dense_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+1800+120*((T2Ind_Total+1)%2)),
					_SN_Dense_Kernel, 0, &DmaR_Evt5);
		}
		AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Dense_Bias */
		if (_SN_Dense_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Dense_Bias+_N_Dense_Bias), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2040+4*((T2Ind_Total+1)%2)),
					_SN_Dense_Bias, 0, &DmaR_Evt6);
		}
		AT_L2_WAIT(0, &DmaR_Evt7); /* Wait previous DMA read H_0 */
		if (_SN_H_0) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_N_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+120*((T2Ind_Total+1)%3)),
					_SN_H_0, 0, &DmaR_Evt7);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile1 */
			int T1Ind_Last = 1, T1Ind_NextLast = 1;
			/*================================= Prepare Tiles ===================================*/
			_SN_Rec_Kernel2 = 0;
			if (!(1)) {
				_N_Rec_Kernel2 = _N_Rec_Kernel2 + 0; _LN_Rec_Kernel2 = (120); _SN_Rec_Kernel2 = (60*_LN_Rec_Kernel2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Rec_Kernel2 */
			if (_SN_Rec_Kernel2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel2+_N_Rec_Kernel2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+3288+7200*((T1Ind_Total+1)%2)),
						_SN_Rec_Kernel2, 120, _LN_Rec_Kernel2, 0, &DmaR_Evt3);
			}
			/*============================= End Read Tiles ======================================*/
			for(Iterazione=0;Iterazione<9;Iterazione++){			
			for (T0Ind=0; T0Ind<2; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
				int T0Ind_Last = (T0Ind==1), T0Ind_NextLast = ((T0Ind+1)==1);
				/*================================= Prepare Tiles ===================================*/
				_SN_Rec_Kernel = 0;
				if (!(T0Ind_Last)) {
					_N_Rec_Kernel = _N_Rec_Kernel + (170); _LN_Rec_Kernel = ((T0Ind_NextLast)?70:170); _SN_Rec_Kernel = (60*_LN_Rec_Kernel); 
				} else {
					_N_Rec_Kernel = _N_Rec_Kernel + (-170); _LN_Rec_Kernel = (170); _SN_Rec_Kernel = (60*_LN_Rec_Kernel); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Rec_Kernel */
				if (_SN_Rec_Kernel) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Rec_Kernel+_N_Rec_Kernel), ((AT_L2_INT_ADDR_TYPE) L1_Memory+17688+10200*((T0Ind_Total+1)%2)),
							_SN_Rec_Kernel, 240, _LN_Rec_Kernel, 0, &DmaR_Evt1);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_LOOP =========================*/
				KerZDec16(
					(short int * __restrict__) (L1_Memory+0+120*((T2Ind_Total)%3)),
					(unsigned int) (60),
					(short int * __restrict__) (L1_Memory+17688+10200*((T0Ind_Total)%2)),
					(unsigned int) ((T0Ind_Last)?35:85),
					(int * __restrict__) (L1_Memory+360+480*((T2Ind_Total)%2)),
					(short int * __restrict__) (L1_Memory+2048+240*((T2Ind_Total)%2)),
					(unsigned int) ((T0Ind)*85),
					(unsigned int) (Norm)
				);
				/*================================= Update Arg Pipeline =============================*/
				
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on Tile0 */
			/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
			KerProd16(
				(short int * __restrict__) (L1_Memory+2048+240*((T2Ind_Total)%2)),
				(short int * __restrict__) (L1_Memory+0+120*((T2Ind_Total)%3)),
				(unsigned int) (60),
				(short int * __restrict__) (L1_Memory+2568+120*((T2Ind_Total)%2)),
				(int * __restrict__) (L1_Memory+2808+240*((T2Ind_Total)%2)),
				(unsigned int) (Norm)
			);
			KerGRUDeclayer16(
				(short int * __restrict__) (L1_Memory+2048+240*((T2Ind_Total)%2)),
				(short int * __restrict__) (L1_Memory+0+120*((T2Ind_Total)%3)),
				(unsigned int) (60),
				(short int * __restrict__) (L1_Memory+3288+7200*((T1Ind_Total)%2)),
				(unsigned int) (60),
				(int * __restrict__) (L1_Memory+1320+240*((T2Ind_Total)%2)),
				(short int * __restrict__) (L1_Memory+2568+120*((T2Ind_Total)%2)),
				(int * __restrict__) (L1_Memory+2808+240*((T2Ind_Total)%2)),
				(unsigned int) ((0)*60),
				(unsigned int) (Norm)
			);
			KerDENSElayer16(
				(short int * __restrict__) (L1_Memory+0+120*((T2Ind_Total)%3)),
				(unsigned int) (60),
				(short int * __restrict__) (L1_Memory+1800+120*((T2Ind_Total)%2)),
				(int * __restrict__) (L1_Memory+2040+4*((T2Ind_Total)%2)),
				(unsigned int) (Norm),
				(short int * __restrict__) (L1_Memory+2528+20*((T2Ind_Total)%2)),
				(unsigned int) (Iterazione)
			);
			}
			/*================================= Update Arg Pipeline =============================*/
			
			/*============================= End Update Arg Pipeline =============================*/
			T1Ind_Total++;
		} /* End iteration on Tile1 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Z) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Z */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Z+_C_Z), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2048+240*((T2Ind_Total)%2)),
				_SC_Z, 1, &DmaW_Evt1);
		if (_SP_H_0) AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write H_0 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) H_0+_C_H_0), ((AT_L2_INT_ADDR_TYPE) L1_Memory+0+120*((T2Ind_Total)%3)),
				_SC_H_0, 1, &DmaW_Evt2);
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2528+20*((T2Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt3);
		if (_SP_prod1) AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write prod1 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod1+_C_prod1), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2568+120*((T2Ind_Total)%2)),
				_SC_prod1, 1, &DmaW_Evt4);
		if (_SP_prod2) AT_L2_WAIT(0, &DmaW_Evt5); /* Wait previous DMA write prod2 */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) prod2+_C_prod2), ((AT_L2_INT_ADDR_TYPE) L1_Memory+2808+240*((T2Ind_Total)%2)),
				_SC_prod2, 1, &DmaW_Evt5);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_Z = _SC_Z;
		
		
		
		
		_SP_H_0 = _SC_H_0;
		_SP_Out = _SC_Out;
		_SP_prod1 = _SC_prod1;
		_SP_prod2 = _SC_prod2;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Z = 0;
		
		_SC_H_0 = 0;
		
		_SC_Out = 0;
		
		_SC_prod1 = 0;
		
		_SC_prod2 = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		T2Ind_Total++;
	} /* End iteration on Tile2 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Z */
	AT_L2_WAIT(0, &DmaW_Evt2); /* Wait previous DMA write H_0 */
	AT_L2_WAIT(0, &DmaW_Evt3); /* Wait previous DMA write Out */
	AT_L2_WAIT(0, &DmaW_Evt4); /* Wait previous DMA write prod1 */
	AT_L2_WAIT(0, &DmaW_Evt5); /* Wait previous DMA write prod2 */
	/*============================ End Write Tiles Epilog ===============================*/
}
