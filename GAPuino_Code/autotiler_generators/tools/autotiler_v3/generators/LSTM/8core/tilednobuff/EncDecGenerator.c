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
#include "Gap.h"

#define D0      KER_ITER_D0
#define D1      KER_ITER_D1
#define D2      KER_ITER_D2
#define D3      KER_ITER_D3
#define T0      KER_ITER_TILE0
#define T1      KER_ITER_TILE1
#define T2      KER_ITER_TILE2

void LoadEncoderDecoderLibrary()
{
    LibKernel("KerZComputation16",CALL_PARALLEL,
        CArgs(11,
            TCArg("short int * __restrict__", "In"),
            TCArg("unsigned int","Iterazione"),
            TCArg("short int * __restrict__", "H_0"),
            TCArg("unsigned int", "W_H"),
            TCArg("short int * __restrict__", "Kernel"),
            TCArg("short int * __restrict__", "Rec_Kernel"),
            TCArg("unsigned int", "W_Rec_Kernel"),
            TCArg("int * __restrict__", "Bias"),
            TCArg("short int * __restrict__", "Z"),
            TCArg("unsigned int", "OutFirstCol"),
            TCArg("unsigned int", "Norm")
        ),
        "KerZComputation16_ArgT",0
    );

    LibKernel("KerZComputationDec16",CALL_PARALLEL,
        CArgs(9,
            TCArg("short int * __restrict__", "H_0"),
            TCArg("unsigned int", "W_H"),
            TCArg("short int * __restrict__", "Kernel"),
            TCArg("short int * __restrict__", "Rec_Kernel"),
            TCArg("unsigned int", "W_Rec_Kernel"),
            TCArg("int * __restrict__", "Bias"),
            TCArg("short int * __restrict__", "Z"),
            TCArg("unsigned int", "OutFirstCol"),
            TCArg("unsigned int", "Norm")
        ),
        "KerZComputationDec16_ArgT",0
    );    

    LibKernel("KerLSTMlayer16",CALL_PARALLEL,
        CArgs(5,
            TCArg("short int * __restrict__", "Z"),
            TCArg("short int * __restrict__", "C_0"),
            TCArg("unsigned int","W_C"),
            TCArg("short int * __restrict__", "H_0"),
            TCArg("unsigned int", "Norm")
        ),
        "KerLSTMlayer16_ArgT",0
    );

    LibKernel("KerDENSElayer16",CALL_PARALLEL,
        CArgs(7,
            TCArg("short int * __restrict__", "In"),
            TCArg("unsigned int", "InSize"),
            TCArg("short int * __restrict__","Filter"),
            TCArg("int * __restrict__", "Bias"),
            TCArg("unsigned int", "Norm"),
            TCArg("short int * __restrict__", "Out"),
            TCArg("unsigned int", "Iterazione")            
        ),
        "KerDENSElayer16_ArgT",0
    );

}


void EncoderGenerator(char *Name, unsigned int Neuroni, unsigned int in_step)

{
    unsigned int W= 4*Neuroni;
    char *DataType = 0;
    char *NameExt = 0;
    char *MatKer = 0;
    int DataSize = 0;
    int NeedNorm = 0;
    DataType = "short int * __restrict__";
    //DataType2 = "int * __restrict__";
    DataSize = 2;
    NameExt = "fixedp16";
    NeedNorm = 1;

    UserKernel(Name,
        KernelIterSpace(2, IterTiledSpace(T1), IterTiledSpace(T0)),
                TILE_HOR,
                CArgs(10,
                        TCArg(DataType, "In"),
            		    TCArg("unsigned int","step_in"),
                        TCArg("unsigned int", "Iterazione"),
                        TCArg(DataType, "H_0"),
                        TCArg(DataType, "C_0"),                        
                        TCArg(DataType, "Kernel"),
                        TCArg(DataType, "Rec_Kernel"),
                        TCArg("int * __restrict__", "Bias"),
                        TCArg(DataType, "Z"),
                        TCArg("unsigned int", "Norm")
                ),
        Calls(2,
            Call("KerZComputation16", LOC_INNER_LOOP,
                Bindings(11,
                    K_Arg("In", KER_ARG_TILE),
                    C_Arg("Iterazione") ,
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("Kernel",  KER_ARG_TILE), 
                    K_Arg("Rec_Kernel",  KER_ARG_TILE), K_Arg("Rec_Kernel",  KER_ARG_TILE_W),
                    K_Arg("Bias", KER_ARG_TILE), K_Arg("Z", KER_ARG_TILE),
                    K_Arg("Rec_Kernel",  KER_ARG_TILE_BASE),
                    C_Arg("Norm")
                )
            ),
            Call("KerLSTMlayer16", LOC_INNER_LOOP_EPILOG,
                Bindings(5,
                    K_Arg("Z", KER_ARG_TILE),
                    K_Arg("C_0", KER_ARG_TILE),
                    K_Arg("C_0", KER_ARG_TILE_W),
                    K_Arg("H_0", KER_ARG_TILE),
                    C_Arg("Norm")
                )
            )
        ),
        KerArgs(7,
            KerArg("In",KerArgSpace(1,T1), O_IN,  in_step, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "In"),
            KerArg("H_0", KerArgSpace(1, T1),  O_IN|O_OUT,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "H_0"),
            KerArg("C_0", KerArgSpace(1, T1),  O_IN|O_OUT,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "C_0"),
            KerArg("Kernel", KerArgSpace(1, T1),  O_IN,  W, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Kernel"),
            KerArg("Rec_Kernel", KerArgSpace(1, T0),  O_IN|O_DB, W, Neuroni, DataSize, 0, OBJ_CONSTRAINTS_TILE_VER|OBJ_CONSTRAINTS_PAD_REM, 0, "Rec_Kernel"),
            KerArg("Bias", KerArgSpace(1, T1),  O_IN,  W, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Bias"),
            KerArg("Z",KerArgSpace(1, T1),  O_OUT, W,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Z")
        )
    );
}

void DecoderGenerator(char *Name, unsigned int Neuroni, unsigned int out_step)
{
    unsigned int W= 4*Neuroni;
    char *DataType = 0;
    char *NameExt = 0;

    int DataSize = 0;

    DataType = "short int * __restrict__";
    //DataType2 = "int * __restrict__";
    DataSize = 2;
    NameExt = "fixedp16";


    UserKernel(Name,
        KernelIterSpace(2, IterTiledSpace(T1), IterTiledSpace(T0)),
                TILE_HOR,
                CArgs(12,
            		    TCArg("unsigned int","step_out"),
             		    TCArg("unsigned int","Iterazione"),                       
                        TCArg(DataType, "H_0"),
                        TCArg(DataType, "C_0"),                        
                        TCArg(DataType, "Kernel"),
                        TCArg(DataType, "Rec_Kernel"),
                        TCArg("int * __restrict__", "Bias"),
                        TCArg(DataType, "Dense_Kernel"),
                        TCArg("int * __restrict__", "Dense_Bias"),
                        TCArg(DataType, "Out"),
                        TCArg(DataType, "Z"),
                        TCArg("unsigned int", "Norm")
                ),
        Calls(3,
            Call("KerZComputationDec16", LOC_INNER_LOOP,
                Bindings(9,
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("Kernel",  KER_ARG_TILE), 
                    K_Arg("Rec_Kernel",  KER_ARG_TILE), K_Arg("Rec_Kernel",  KER_ARG_TILE_W),
                    K_Arg("Bias", KER_ARG_TILE), K_Arg("Z", KER_ARG_TILE),
                    K_Arg("Rec_Kernel",  KER_ARG_TILE_BASE),
                    C_Arg("Norm")
                )
            ),
            Call("KerLSTMlayer16", LOC_INNER_LOOP_EPILOG,
                Bindings(5,
                    K_Arg("Z", KER_ARG_TILE),
                    K_Arg("C_0", KER_ARG_TILE),
                    K_Arg("C_0", KER_ARG_TILE_W),
                    K_Arg("H_0", KER_ARG_TILE),
                    C_Arg("Norm")
                )
            ),
            Call("KerDENSElayer16", LOC_INNER_LOOP_EPILOG,
                Bindings(7,
                    K_Arg("H_0", KER_ARG_TILE), K_Arg("H_0", KER_ARG_TILE_W),
                    K_Arg("Dense_Kernel", KER_ARG_TILE),
                    K_Arg("Dense_Bias", KER_ARG_TILE),
                    C_Arg("Norm"),                    
                    K_Arg("Out", KER_ARG_TILE),
                    C_Arg("Iterazione")
                )
            )            
        ),
        KerArgs(9,
            KerArg("H_0", KerArgSpace(1, T1),  O_IN|O_OUT,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "H_0"),
            KerArg("C_0", KerArgSpace(1, T1),  O_IN|O_OUT,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "C_0"),
            KerArg("Kernel", KerArgSpace(1, T1),  O_IN,  W, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Kernel"),
            KerArg("Rec_Kernel", KerArgSpace(1, T0),  O_IN|O_DB, W, Neuroni, DataSize, 0, OBJ_CONSTRAINTS_TILE_VER|OBJ_CONSTRAINTS_PAD_REM, 0, "Rec_Kernel"),
            KerArg("Bias", KerArgSpace(1, T1),  O_IN,  W, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Bias"),
            KerArg("Dense_Kernel", KerArgSpace(1, T1),  O_IN,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Dense_Kernel"),
            KerArg("Dense_Bias", KerArgSpace(1, T1),  O_IN,  1, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Dense_Bias"),
            KerArg("Z",KerArgSpace(1, T1),  O_OUT, W,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Z"),
            KerArg("Out",KerArgSpace(1, T1),  O_OUT, out_step,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Out")        
        )
    );

}
