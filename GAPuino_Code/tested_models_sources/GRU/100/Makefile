# Copyright (C) 2017 GreenWaves Technologies
# All rights reserved.

# This software may be modified and distributed under the terms
# of the BSD license.  See the LICENSE file for details.

APP = Seq2Seq

GRU_GEN_PATH = $(TILER_GENERATOR_PATH)/GRU/8core/RecKer2notile/
GRU_KER_PATH = $(TILER_GENERATOR_PATH)/GRU/8core/RecKer2notile/

APP_SRCS += Seq2SeqPerf.c
APP_SRCS +=  EncDecLayer.c  $(GRU_KER_PATH)/EncDecKernel.c $(GRU_KER_PATH)/UtilityFunc16_12.c

APP_INC += . $(TILER_INC) $(GRU_KER_PATH)

APP_CFLAGS += -O3 -mno-memcpy -fno-tree-loop-distribute-patterns
APP_CFLAGS += -Wall -Werror -Wno-maybe-uninitialized -Wno-unused-but-set-variable

MODEL_SRC = Seq2SeqModel.c
MODEL_GEN = EncDecLayer
MODEL_GEN_C = $(addsuffix .c, $(MODEL_GEN))
MODEL_GEN_CLEAN = $(MODEL_GEN_C) $(addsuffix .h, $(MODEL_GEN))

RM=rm -f

all:: model

# Build the code generator
GenTile:
	gcc -o GenTile -I$(TILER_INC) -I$(GRU_GEN_PATH) $(MODEL_SRC) $(GRU_GEN_PATH)/EncDecGenerator.c $(TILER_LIB)

# Run the code generator
$(MODEL_GEN_C): GenTile
	./GenTile

model: $(MODEL_GEN_C)

clean::
	$(RM) GenTile $(MODEL_GEN_CLEAN)

.PHONY: model clean

include $(GAP_SDK_HOME)/tools/rules/pmsis_rules.mk
