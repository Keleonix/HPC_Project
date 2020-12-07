# -------------- #
# -- Makefile -- #
# -------------- #

# Copyright (c) 2000-2007 Lionel Lacassagne
# with a little help of Stephane Piskorski and Joel Falcou
# Modified by Axel Boujon and Younes Chefou

# -- File list ----------
FILE = nrutil.c vnrutil.c mutil.c my_vnrutil.c main.c mouvement.c \
 test_mouvement.c test_mouvement_SIMD.c test_mouvement_optim.c \
 test_morpho_SIMD.c morpho_SIMD.c test_morpho.c mouvement_SIMD.c \
 morpho.c dtime.c mouvement_optim.c morpho_optim.c test_morpho_optim.c\
 bench_mouvement.c bench_morpho.c bench_chaine.c my_nrutil.c

# -- Paths ----------
SRC_PATH = src
OBJ_PATH = obj
EXE_PATH = exe
INC_PATH = include

# -- OS ----------
#OS = MACH_OSX

# -- Config ----------
# if CONFIG = CLI  (Command Line Interface, no Apple Framework)
CONFIG = CLI

# -- Macros ----------
CC = gcc
AR = ar -rc
LIB = -lm -fopenmp

# -- Flags ----------
C_DEBUG_FLAGS = -O0
C_CC_FLAGS = -std=c99 -DNOALIAS -DALIGNED -DmySSE -DTIMER_UNIX -g
C_OPTIMISATION_FLAGS = -O3 -fstrict-aliasing
C_ARCH_FLAGS = -msse4.2

C_OS_FLAGS =
C_CONFIG_FLAGS = -D$(CONFIG)
C_INC_FLAGS = -I$(INC_PATH)

CFLAGS =  $(C_CC_FLAGS) $(C_DEBUG_FLAGS)        $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH)
CFLAGS = $(C_CC_FLAGS) $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH)
LDFLAGS = $(C_CC_FLAGS) $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_LIB_PATH)

# -- Final product ----------
PRODUCT   = main.exe

# -- src and obj List ----------
#SRC = $(addprefix ${SRC_PATH}/, $(FILE))
SRC = $(addprefix ${SRC_PATH}/, $(FILE))
OBJ = $(addprefix ${OBJ_PATH}/, $(addsuffix .o, $(basename $(FILE))))
# SRC = $(wildcard $(SRC_PATH)/*.c)
# OBJ = $(wildcard $(OBJ_PATH)/*.o)
# -- Base rules ----------
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#-----Main rule ----------

$(EXE_PATH)/$(PRODUCT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(OPTFLAGS) $(CFG) $(INC) $(LIB)

# -- Other stuff ----------
depend:
	makedepend $(CFLAGS) -Y $(SRC)

clean:
	rm -f $(OBJ)
	rm -f ${EXE_PATH}/${PRODUCT}
	rm -f images_OPTIM/*.pgm
	rm -f images_SIMD/*.pgm
	rm -f images_scalaire/*.pgm

tar:
	tar -cvf deriche_SSE.tar Makefile src include
	gzip -9 deriche_SSE.tar
