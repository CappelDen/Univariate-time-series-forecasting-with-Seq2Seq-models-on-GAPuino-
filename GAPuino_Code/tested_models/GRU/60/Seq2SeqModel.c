/*
 * Copyright (C) 2017 GreenWaves Technologies
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 *
 */

#include <stdint.h>
#include <stdio.h>
#include "AutoTilerLib.h"
#include "EncDecGenerator.h"

void Model(unsigned int L1Memory, unsigned int L2Memory, unsigned int L3Memory)

{
    SetSymbolDynamics();

    SetUsedFilesNames(0, 1, "EncDecKernel.h");
    SetGeneratedFilesNames("EncDecLayer.c", "EncDecLayer.h");
	SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);

    SetMemoryDeviceInfos(4,
		AT_MEM_L1, L1Memory, "L1_Memory", 0, 0,
		AT_MEM_L2, L2Memory, "L2_Memory", 0, 0,
		AT_MEM_L3_HRAM, L3Memory, "L3_Memory", 0, 0,
		AT_MEM_L3_HFLASH, 20*1024*1024, "0", "L3_Flash_Const.dat", 0
	);

	LoadEncoderDecoderLibrary();
	
	//EncoderZGenerator("EncZGRUlayer",100,27);
	EncoderGRUGenerator("EncGRUlayer",60,27); //Short int
	//DecoderZGenerator("DecZGRUlayer",100,9);
	DecoderGRUGenerator("DecGRUlayer",60,9);

}


int main(int argc, char **argv)

{
        if (TilerParseOptions(argc, argv)) GenTilingError("Failed to initialize or incorrect output arguments directory.\n");
        Model(45000, 360*1024, 8*1024*1024);
        GenerateTilingCode();
        return 0;
}
