/*
 * Copyright (C) 2017 GreenWaves Technologies
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 *
 */

#ifndef __ENCDECGEN_H__
#define __ENCDECGEN_H__
extern void LoadEncoderDecoderLibrary();
extern void EncoderGenerator(char *Name, unsigned int Neuroni,unsigned int in_step);
extern void DecoderGenerator(char *Name, unsigned int Neuroni,unsigned int out_step);
#endif
