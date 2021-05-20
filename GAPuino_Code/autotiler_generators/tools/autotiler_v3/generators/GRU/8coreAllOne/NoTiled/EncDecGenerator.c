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
    LibKernel("KerZEnc16",CALL_PARALLEL,
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
        "KerZEnc16_ArgT",0
    );

    LibKernel("KerZDec16",CALL_PARALLEL,
        CArgs(8,
            TCArg("short int * __restrict__", "H_0"),
            TCArg("unsigned int", "W_H"),
            TCArg("short int * __restrict__", "Rec_Kernel"),
            TCArg("unsigned int", "W_Rec_Kernel"),
            TCArg("int * __restrict__", "Bias"),
            TCArg("short int * __restrict__", "Z"),
            TCArg("unsigned int", "OutFirstCol"),
            TCArg("unsigned int", "Norm")
        ),
        "KerZDec16_ArgT",0
    );    

    LibKernel("KerProd16",CALL_PARALLEL,
        CArgs(6,
            TCArg("short int * __restrict__", "Z"),
            TCArg("short int * __restrict__", "H_0"),
            TCArg("unsigned int","W_H"),
            TCArg("short int * __restrict__", "prod1"),
            TCArg("int * __restrict__", "prod2"),
            TCArg("unsigned int", "Norm")
        ),
        "KerProd16_ArgT",0
    );
    LibKernel("KerGRUEnclayer16",CALL_PARALLEL,
        CArgs(13,
            TCArg("short int * __restrict__", "Z"),
            TCArg("short int * __restrict__", "In"),
            TCArg("unsigned int","Iterazione"),
            TCArg("short int * __restrict__", "H_0"),
            TCArg("unsigned int", "W_H"),
            TCArg("short int * __restrict__", "Kernel"),
            TCArg("short int * __restrict__", "Rec_Kernel"),
            TCArg("unsigned int", "W_Rec_Kernel"),
            TCArg("int * __restrict__", "Bias"),
            TCArg("short int * __restrict__", "prod1"),
            TCArg("int * __restrict__", "prod2"),
            TCArg("unsigned int", "OutFirstCol"),
            TCArg("unsigned int", "Norm")
        ),
        "KerGRUEnclayer16_ArgT",0
    );

    LibKernel("KerGRUDeclayer16",CALL_PARALLEL,
        CArgs(10,
            TCArg("short int * __restrict__", "Z"),
            TCArg("short int * __restrict__", "H_0"),
            TCArg("unsigned int", "W_H"),
            TCArg("short int * __restrict__", "Rec_Kernel"),
            TCArg("unsigned int", "W_Rec_Kernel"),
            TCArg("int * __restrict__", "Bias"),
            TCArg("short int * __restrict__", "prod1"),
            TCArg("int * __restrict__", "prod2"),
            TCArg("unsigned int", "OutFirstCol"),
            TCArg("unsigned int", "Norm")
        ),
        "KerGRUDeclayer16_ArgT",0
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


void EncoderGRUGenerator(char *Name, unsigned int Neuroni, unsigned int in_step)

{
    unsigned int W= 2*Neuroni;
    char *DataType = 0;
    char *DataType2 = 0;
    char *NameExt = 0;
    char *MatKer = 0;
    int DataSize = 0;
    int NeedNorm = 0;
    DataType = "short int * __restrict__";
    DataType2 = "int * __restrict__";
    DataSize = 2;
    NameExt = "fixedp16";
    NeedNorm = 1;

    UserKernel(Name,
        KernelIterSpace(2,IterTiledSpace(T1), IterTiledSpace(T0)),
                TILE_HOR,
                CArgs(13,
                        TCArg(DataType, "In"),
                        TCArg("unsigned int", "Iterazione"),
                        TCArg(DataType, "H_0"),                       
                        TCArg(DataType, "Kernel"),
                        TCArg(DataType, "Rec_Kernel"),
                        TCArg(DataType2, "Bias"),
                        TCArg(DataType, "Kernel2"),
                        TCArg(DataType, "Rec_Kernel2"),
                        TCArg(DataType2, "Bias2"),                                               
                        TCArg(DataType, "Z"),
						TCArg(DataType, "prod1"),
						TCArg(DataType2, "prod2"),	
                        TCArg("unsigned int", "Norm")
                ),
        Calls(3,
            Call("KerZEnc16", LOC_INNER_LOOP,
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
            Call("KerProd16", LOC_INNER_LOOP_EPILOG,
                Bindings(6,
                    K_Arg("Z", KER_ARG_TILE),
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("prod1", KER_ARG_TILE), K_Arg("prod2", KER_ARG_TILE),
                    C_Arg("Norm")
                )
            ),
            Call("KerGRUEnclayer16", LOC_INNER_LOOP_EPILOG,
                Bindings(13,
                    K_Arg("Z", KER_ARG_TILE),
                    K_Arg("In", KER_ARG_TILE),
                    C_Arg("Iterazione"),
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("Kernel2",  KER_ARG_TILE),
                    K_Arg("Rec_Kernel2",  KER_ARG_TILE), K_Arg("Rec_Kernel2",  KER_ARG_TILE_W),
                    K_Arg("Bias2", KER_ARG_TILE), K_Arg("prod1", KER_ARG_TILE),
                    K_Arg("prod2", KER_ARG_TILE),
                    K_Arg("Rec_Kernel2",  KER_ARG_TILE_BASE),
                    C_Arg("Norm")
                )
            )                         
        ),
        KerArgs(11,
            KerArg("In",KerArgSpace(1,T1), O_IN|O_DB,  in_step, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "In"),
            KerArg("H_0", KerArgSpace(1, T1),   O_IN|O_OUT|O_DB,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "H_0"),
            KerArg("Kernel", KerArgSpace(1, T1),  O_IN|O_DB,  W, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Kernel"),
            KerArg("Rec_Kernel", KerArgSpace(1, T0),  O_IN|O_DB, W, Neuroni, DataSize, 0, OBJ_CONSTRAINTS_TILE_VER|OBJ_CONSTRAINTS_PAD_REM, 0, "Rec_Kernel"),
            KerArg("Bias", KerArgSpace(1, T1),  O_IN|O_DB,  W, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Bias"),
            KerArg("Kernel2", KerArgSpace(1, T1),  O_IN|O_DB,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Kernel2"),
            KerArg("Rec_Kernel2", KerArgSpace(1, T1), OBJ_BUFFER_IN_NTILED, Neuroni, Neuroni, DataSize, 0,OBJ_CONSTRAINTS_TILE_VER|OBJ_CONSTRAINTS_PAD_REM, 0, "Rec_Kernel2"),
            KerArg("Bias2", KerArgSpace(1, T1),  O_IN|O_DB,  Neuroni, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Bias2"),            
            KerArg("Z",KerArgSpace(1, T1),  O_OUT|O_DB, W,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Z"),
            KerArg("prod1",KerArgSpace(1, T1),  O_OUT|O_DB, Neuroni,  1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "prod1"),
            KerArg("prod2",KerArgSpace(1, T1),  O_OUT|O_DB, Neuroni,  1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "prod2")			
        )
    );
}


void DecoderGRUGenerator(char *Name, unsigned int Neuroni, unsigned int out_step)

{
    unsigned int W= 2*Neuroni;
    char *DataType = 0;
    char *DataType2 = 0;
    char *NameExt = 0;
    char *MatKer = 0;
    int DataSize = 0;
    int NeedNorm = 0;
    DataType = "short int * __restrict__";
    DataType2 = "int * __restrict__";
    DataSize = 2;
    NameExt = "fixedp16";
    NeedNorm = 1;

    UserKernel(Name,
        KernelIterSpace(2,IterTiledSpace(T1), IterTiledSpace(T0)),
                TILE_HOR,
                CArgs(13,
                        TCArg("unsigned int", "Iterazione"),
                        TCArg(DataType, "H_0"),                       
                        TCArg(DataType, "Rec_Kernel"),
                        TCArg(DataType2, "Bias"),
                        TCArg(DataType, "Rec_Kernel2"),
                        TCArg(DataType2, "Bias2"),
                        TCArg(DataType, "Dense_Kernel"),
                        TCArg(DataType2, "Dense_Bias"),
                        TCArg(DataType, "Out"),	                                               
                        TCArg(DataType, "Z"),
						TCArg(DataType, "prod1"),
						TCArg(DataType2, "prod2"),	
                        TCArg("unsigned int", "Norm")
                ),
        Calls(4,
            Call("KerZDec16", LOC_INNER_LOOP,
                Bindings(8,
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("Rec_Kernel",  KER_ARG_TILE), K_Arg("Rec_Kernel",  KER_ARG_TILE_W),
                    K_Arg("Bias", KER_ARG_TILE), K_Arg("Z", KER_ARG_TILE),
                    K_Arg("Rec_Kernel",  KER_ARG_TILE_BASE),
                    C_Arg("Norm")
                )
            ),
            Call("KerProd16", LOC_INNER_LOOP_EPILOG,
                Bindings(6,
                    K_Arg("Z", KER_ARG_TILE),
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("prod1", KER_ARG_TILE), K_Arg("prod2", KER_ARG_TILE),
                    C_Arg("Norm")
                )
            ),
            Call("KerGRUDeclayer16", LOC_INNER_LOOP_EPILOG,
                Bindings(10,
                    K_Arg("Z", KER_ARG_TILE),
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("Rec_Kernel2",  KER_ARG_TILE), K_Arg("Rec_Kernel2",  KER_ARG_TILE_W),
                    K_Arg("Bias2", KER_ARG_TILE), K_Arg("prod1", KER_ARG_TILE),
                    K_Arg("prod2", KER_ARG_TILE),
                    K_Arg("Rec_Kernel2",  KER_ARG_TILE_BASE),
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
        KerArgs(11,
            KerArg("H_0", KerArgSpace(1, T1),   O_IN|O_OUT|O_DB,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "H_0"),
            KerArg("Rec_Kernel", KerArgSpace(1, T0),  O_IN|O_DB, W, Neuroni, DataSize, 0, OBJ_CONSTRAINTS_TILE_VER|OBJ_CONSTRAINTS_PAD_REM, 0, "Rec_Kernel"),
            KerArg("Bias", KerArgSpace(1, T1),  O_IN|O_DB,  W, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Bias"),
            KerArg("Rec_Kernel2", KerArgSpace(1, T1), OBJ_BUFFER_IN_NTILED , Neuroni, Neuroni, DataSize, 0, OBJ_CONSTRAINTS_TILE_VER|OBJ_CONSTRAINTS_PAD_REM, 0, "Rec_Kernel2"),
            KerArg("Bias2", KerArgSpace(1, T1),  O_IN|O_DB,  Neuroni, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Bias2"),            
            KerArg("Dense_Kernel", KerArgSpace(1, T1),  O_IN|O_DB,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Dense_Kernel"),
            KerArg("Dense_Bias", KerArgSpace(1, T1),  O_IN|O_DB,  1, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Dense_Bias"),
            KerArg("Z",KerArgSpace(1, T1),  O_OUT|O_DB, W,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Z"),
            KerArg("Out",KerArgSpace(1, T1),  O_OUT|O_DB, out_step,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Out"),
            KerArg("prod1",KerArgSpace(1, T1),  O_OUT|O_DB, Neuroni,  1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "prod1"),
            KerArg("prod2",KerArgSpace(1, T1),  O_OUT|O_DB, Neuroni,  1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "prod2")			
        )
    );
}




/*


void DecoderGRUGenerator(char *Name, unsigned int Neuroni, unsigned int out_step)

{
    unsigned int W= 2*Neuroni;
    char *DataType = 0;
    char *DataType2 = 0;
    char *NameExt = 0;
    char *MatKer = 0;
    int DataSize = 0;
    int NeedNorm = 0;
    DataType = "short int * __restrict__";
    DataType2 = "int * __restrict__";
    DataSize = 2;
    NameExt = "fixedp16";
    NeedNorm = 1;

    UserKernel(Name,
        KernelIterSpace(2, IterTiledSpace(T1), IterTiledSpace(T0)),
                TILE_HOR,
                CArgs(11,
                        TCArg("unsigned int", "Iterazione"),
                        TCArg(DataType, "H_0"),                       
                        TCArg(DataType, "Rec_Kernel"),
                        TCArg(DataType2, "Bias"),                      
                        TCArg(DataType, "z"),
						TCArg(DataType, "prod1"),
						TCArg(DataType2, "prod2"),
                        TCArg(DataType, "Dense_Kernel"),
                        TCArg(DataType2, "Dense_Bias"),
                        TCArg(DataType, "Out"),	
                        TCArg("unsigned int", "Norm")
                ),
        Calls(2,           
            Call("KerGRUDeclayer16", LOC_INNER_LOOP,
                Bindings(10,
                    K_Arg("z", KER_ARG_TILE),
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("Rec_Kernel",  KER_ARG_TILE), K_Arg("Rec_Kernel",  KER_ARG_TILE_W),
                    K_Arg("Bias", KER_ARG_TILE), K_Arg("prod1", KER_ARG_TILE),
                    K_Arg("prod2", KER_ARG_TILE),
                    K_Arg("Rec_Kernel",  KER_ARG_TILE_BASE),
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
            KerArg("H_0", KerArgSpace(1, T1),  O_IN|O_OUT|O_DB,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "H_0"),
            KerArg("Rec_Kernel", KerArgSpace(1, T0),  O_IN|O_DB, Neuroni, Neuroni, DataSize, 0, OBJ_CONSTRAINTS_TILE_VER|OBJ_CONSTRAINTS_PAD_REM, 0, "Rec_Kernel"),
            KerArg("Bias", KerArgSpace(1, T1),  O_IN|O_DB,  Neuroni, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Bias"),
            KerArg("z",KerArgSpace(1, T1),  O_IN|O_DB, Neuroni,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "z"),
            KerArg("prod1",KerArgSpace(1, T1),  O_IN|O_DB, Neuroni,  1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "prod1"),
            KerArg("prod2",KerArgSpace(1, T1),  O_IN|O_DB, Neuroni,  1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "prod2"),
            KerArg("Dense_Kernel", KerArgSpace(1, T1),  O_IN|O_DB,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Dense_Kernel"),
            KerArg("Dense_Bias", KerArgSpace(1, T1),  O_IN|O_DB,  1, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Dense_Bias"),
            KerArg("Out",KerArgSpace(1, T1),  O_OUT|O_DB, out_step,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Out")		
        )
    );
}


void DecoderGenerator(char *Name, unsigned int Neuroni, unsigned int out_step)
{
    unsigned int W= 2*Neuroni;
    char *DataType = 0;
    char *DataType2 = 0;
    char *NameExt = 0;
    char *MatKer = 0;
    int DataSize = 0;
    int NeedNorm = 0;
    DataType = "short int * __restrict__";
    DataType2 = "int * __restrict__";
    DataSize = 2;
    NameExt = "fixedp16";
    NeedNorm = 1;

    UserKernel(Name,
        KernelIterSpace(2, IterTiledSpace(T1), IterTiledSpace(T0)),
                TILE_HOR,
                CArgs(16,
            		    TCArg("unsigned int","step_out"),
                        TCArg("unsigned int", "Iterazione"),
                        TCArg(DataType, "H_0"),                       
                        TCArg(DataType, "Kernel1"),
                        TCArg(DataType, "Rec_Kernel1"),
                        TCArg(DataType2, "Bias1"),
                        TCArg(DataType, "Kernel2"),
                        TCArg(DataType, "Rec_Kernel2"),
                        TCArg(DataType2, "Bias2"),
                        TCArg(DataType, "Dense_Kernel"),
                        TCArg(DataType2, "Dense_Bias"),
                        TCArg(DataType, "Out"),
                        TCArg(DataType, "Z"),
						TCArg(DataType, "prod1"),
						TCArg(DataType2, "prod2"),	
                        TCArg("unsigned int", "Norm")
                ),
        Calls(4,
            Call("KerZDec16", LOC_INNER_LOOP,
                Bindings(9,
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("Kernel1",  KER_ARG_TILE), 
                    K_Arg("Rec_Kernel1",  KER_ARG_TILE), K_Arg("Rec_Kernel1",  KER_ARG_TILE_W),
                    K_Arg("Bias1", KER_ARG_TILE), K_Arg("Z", KER_ARG_TILE),
                    K_Arg("Rec_Kernel1",  KER_ARG_TILE_BASE),
                    C_Arg("Norm")
                )
            ),
            Call("KerProd16", LOC_INNER_LOOP_EPILOG,
                Bindings(6,
                    K_Arg("Z", KER_ARG_TILE),
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("prod1", KER_ARG_TILE), K_Arg("prod2", KER_ARG_TILE),
                    C_Arg("Norm")
                )
            ),            
            Call("KerGRUDeclayer16", LOC_INNER_LOOP_EPILOG,
                Bindings(11,
                    K_Arg("Z", KER_ARG_TILE),
                    K_Arg("H_0",  KER_ARG_TILE), K_Arg("H_0",  KER_ARG_TILE_W),
                    K_Arg("Kernel2",  KER_ARG_TILE), 
                    K_Arg("Rec_Kernel2",  KER_ARG_TILE), K_Arg("Rec_Kernel2",  KER_ARG_TILE_W),
                    K_Arg("Bias2", KER_ARG_TILE), K_Arg("prod1", KER_ARG_TILE),
                    K_Arg("prod2", KER_ARG_TILE),
                    K_Arg("Rec_Kernel2",  KER_ARG_TILE_BASE),
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
        KerArgs(13,
            KerArg("H_0", KerArgSpace(1, T1),  O_IN|O_OUT|O_DB,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "H_0"),
            KerArg("Kernel1", KerArgSpace(1, T1),  O_IN|O_DB,  W, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Kernel1"),
            KerArg("Rec_Kernel1", KerArgSpace(1, T0),  O_IN|O_DB, W, Neuroni, DataSize, 0, OBJ_CONSTRAINTS_TILE_VER|OBJ_CONSTRAINTS_PAD_REM, 0, "Rec_Kernel1"),
            KerArg("Bias1", KerArgSpace(1, T1),  O_IN|O_DB,  W, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Bias1"),
            KerArg("Kernel2", KerArgSpace(1, T1),  O_IN|O_DB,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Kernel2"),
            KerArg("Rec_Kernel2", KerArgSpace(1, T0),  O_IN|O_DB, Neuroni, Neuroni, DataSize, 0, OBJ_CONSTRAINTS_TILE_VER|OBJ_CONSTRAINTS_PAD_REM, 0, "Rec_Kernel2"),
            KerArg("Bias2", KerArgSpace(1, T1),  O_IN|O_DB, Neuroni, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Bias2"),
            KerArg("Dense_Kernel", KerArgSpace(1, T1),  O_IN|O_DB,  Neuroni, 1, DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Dense_Kernel"),
            KerArg("Dense_Bias", KerArgSpace(1, T1),  O_IN|O_DB,  1, 1, DataSize*2, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Dense_Bias"),
            KerArg("Z",KerArgSpace(1, T1),  O_OUT|O_DB, W,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Z"),
            KerArg("Out",KerArgSpace(1, T1),  O_OUT|O_DB, out_step,  1,  DataSize, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "Out"),
            KerArg("prod1",KerArgSpace(1, T1),  O_OUT|O_DB, W,  1,  Neuroni, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "prod1"),
            KerArg("prod2",KerArgSpace(1, T1),  O_OUT|O_DB, W,  1,  Neuroni, 0, OBJ_CONSTRAINTS_PAD_REM,                          0, "prod2")	        
        )
    );
}
*/
