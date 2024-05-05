#==============================================================================
#								COMPILERS
#==============================================================================
CC=gcc
ICX=icx

AOCC=/home/euro/aocc-compiler-4.2.0/bin/clang
AOCC2=/home/sami/Bureau/aocc-compiler-4.2.0/bin/clang
#==============================================================================


#==============================================================================
#							OPTIMISATION FLAGS
#==============================================================================
#The driver (main, "measure" executable) is compiled with O2
CFLAGS=-O2 -g -Wall

#General flags (for all CPUs)
OPTFLAGS=-O2 -g -Wall #Default "measure" : -O2
OPTFLAGS_O3=-O3 -g
OPTFLAGS_O3NATIVE=-O3 -march=native -g
OPTFLAGS_OFAST=-Ofast -g
OPTFLAGS_AVX2=-O3 -mavx2 -g #YMM vectorization 
OPT_OCUSTOM=-O3 -ffinite-math-only -freciprocal-math -fno-math-errno -funsafe-math-optimizations -ffloat-store -g

#Specific macros & flags for ICC & Intel CPUs


#Specific macros & flags for AOCC & AMD CPUs

#==============================================================================

OBJS_COMMON=kernel.o rdtsc.o
OBJS_CUSTOM=kernel_O3.o kernel_OFAST.o kernel_O3NATIVE.o kernel_AVX2.o kernel_OCUSTOM.o kernel_AOCC_O2.o
OBJS_ICX=kernel_icx_O2.o
BIN_PATH=../bin/

#==============================================================================
#							MAIN TARGETS
#==============================================================================
#Default target : everything but AOCC
all:	check calibrate measure measure_O3 measure_OFast measure_O3NATIVE measure_AVX2 measure_OCUSTOM 
#Intel Compiler target
icx: measure_ICX measure_ICX_O3
#Custom AOCC target (specific install location)
fred: measure_AOCC measure_AOCC_03
sami: measure_AOCC_sami measure_AOCC_O3_sami
phase2: clean measure_phase2
phase2_flags: clean measure_02NATIVE measure_O3 measure_OFast measure_O3NATIVE
#==============================================================================

check:	$(OBJS_COMMON) driver_check.o
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
calibrate: $(OBJS_COMMON) driver_calib.o
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
measure: $(OBJS_COMMON) driver.o
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^

#==============================================================================
#						SPECIFIC TARGETS
#==============================================================================
measure_O3: kernel_O3.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(CC) -lm -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
else
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
endif

measure_02NATIVE : kernel_O2NATIVE.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(CC) -lm -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
else
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
endif

measure_OFast: kernel_OFAST.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(CC) -lm -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
else
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
endif

measure_O3NATIVE: kernel_O3NATIVE.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(CC) -lm -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
else
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
endif

measure_AVX2: kernel_AVX2.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(CC) -lm -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
else
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
endif

measure_OCUSTOM: kernel_OCUSTOM.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(CC) -lm -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
else
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^
endif

measure_AOCC: kernel_AOCC_O2.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(AOCC) -lm -o $(BIN_PATH)$@_$(OPT) $^
else
	$(AOCC) -o $(BIN_PATH)$@_$(OPT) $^
endif

measure_AOCC_O3: kernel_AOCC_O3.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(AOCC) -lm -o $(BIN_PATH)$@_$(OPT) $^
else
	$(AOCC) -o $(BIN_PATH)$@_$(OPT) $^
endif

measure_AOCC_sami: kernel_AOCC_O2_sami.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(AOCC2) -lm -o $(BIN_PATH)$@_$(OPT) $^
else
	$(AOCC2) -o $(BIN_PATH)$@_$(OPT) $^
endif

measure_AOCC_O3_sami: kernel_AOCC_O3_sami.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(AOCC2) -lm -o $(BIN_PATH)$@_$(OPT) $^
else
	$(AOCC2) -o $(BIN_PATH)$@_$(OPT) $^
endif

measure_ICX: kernel_icx_O2.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(ICX) -lm -o $(BIN_PATH)$@_$(OPT) $^
else
	$(ICX) -o $(BIN_PATH)$@_$(OPT) $^
endif

measure_ICX_O3: kernel_icx_O3.o rdtsc.o driver.o
ifeq ($(OPT),TILING)
	$(ICX) -lm -o $(BIN_PATH)$@_$(OPT) $^
else
	$(ICX) -o $(BIN_PATH)$@_$(OPT) $^
endif

measure_phase2: $(OBJS_COMMON) driver.o
ifeq ($(OPT),TILING)
	$(CC) -lm -o $(BIN_PATH)$@_$(OPT) $^
else
	$(CC) -o $(BIN_PATH)$@_$(OPT) $^
endif

#==============================================================================

#==============================================================================
#						COMMON OBJECTS
#==============================================================================
driver_check.o: driver_check.c
	$(CC) $(CFLAGS) -D CHECK -c $< -o $@
driver_calib.o: driver_calib.c
	$(CC) $(CFLAGS) -D CALIB -c $< -o $@
driver.o: driver.c
	$(CC) -D $(OPT) $(CFLAGS) -c $<
#==============================================================================

#==============================================================================
# 						DIFFERENT KERNELS
#==============================================================================
kernel.o: kernel.c
ifeq ($(OPT),TILING)
	$(CC) $(OPTFLAGS) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(CC) $(OPTFLAGS) -D $(OPT) -c $< -o $@ -mavx
else
	$(CC) $(OPTFLAGS) -D $(OPT) -c $< -o $@
endif

kernel_O2NATIVE.o: kernel.c
ifeq ($(OPT),TILING)
	$(CC) $(OPTFLAGS) -march=native -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(CC) $(OPTFLAGS) -march=native -D $(OPT) -c $< -o $@ -mavx
else
	$(CC) $(OPTFLAGS) -march=native -D $(OPT) -c $< -o $@
endif

kernel_O3.o: kernel.c
ifeq ($(OPT),TILING)
	$(CC) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(CC) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@ -mavx
else
	$(CC) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@
endif

kernel_OFAST.o: kernel.c
ifeq ($(OPT),TILING)
	$(CC) $(OPTFLAGS_OFAST) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(CC) $(OPTFLAGS_OFAST) -D $(OPT) -c $< -o $@ -mavx
else
	$(CC) $(OPTFLAGS_OFAST) -D $(OPT) -c $< -o $@
endif

kernel_O3NATIVE.o: kernel.c
ifeq ($(OPT),TILING)
	$(CC) $(OPTFLAGS_O3NATIVE) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(CC) $(OPTFLAGS_O3NATIVE) -D $(OPT) -c $< -o $@ -mavx
else
	$(CC) $(OPTFLAGS_O3NATIVE) -D $(OPT) -c $< -o $@
endif

kernel_AVX2.o: kernel.c
ifeq ($(OPT),TILING)
	$(CC) $(OPTFLAGS_AVX2) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(CC) $(OPTFLAGS_AVX2) -D $(OPT) -c $< -o $@ -mavx
else
	$(CC) $(OPTFLAGS_AVX2) -D $(OPT) -c $< -o $@
endif

kernel_OCUSTOM.o: kernel.c
ifeq ($(OPT),TILING)
	$(CC) $(OPT_OCUSTOM) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(CC) $(OPT_OCUSTOM) -D $(OPT) -c $< -o $@ -mavx
else
	$(CC) $(OPT_OCUSTOM) -D $(OPT) -c $< -o $@
endif

kernel_AOCC_O2.o: kernel.c
ifeq ($(OPT),TILING)
	$(AOCC) $(OPTFLAGS) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(AOCC) $(OPTFLAGS) -D $(OPT) -c $< -o $@ -mavx
else
	$(AOCC) $(OPTFLAGS) -D $(OPT) -c $< -o $@
endif

kernel_AOCC_O3.o: kernel.c
ifeq ($(OPT),TILING)
	$(AOCC) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(AOCC) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@ -mavx
else
	$(AOCC) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@
endif

kernel_AOCC_O2_sami.o: kernel.c
ifeq ($(OPT),TILING)
	$(AOCC2) $(OPTFLAGS) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(AOCC2) $(OPTFLAGS) -D $(OPT) -c $< -o $@ -mavx
else
	$(AOCC2) $(OPTFLAGS) -D $(OPT) -c $< -o $@
endif

kernel_AOCC_O3_sami.o: kernel.c
ifeq ($(OPT),TILING)
	$(AOCC2) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(AOCC2) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@ -mavx
else
	$(AOCC2) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@
endif

kernel_icx_O2.o: kernel.c
ifeq ($(OPT),TILING)
	$(ICX) $(OPTFLAGS) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(ICX) $(OPTFLAGS) -D $(OPT) -c $< -o $@ -mavx
else
	$(ICX) $(OPTFLAGS) -D $(OPT) -c $< -o $@
endif

kernel_icx_O3.o: kernel.c
ifeq ($(OPT),TILING)
	$(ICX) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@ -lm 
else ifeq ($(OPT),OPT_INTRINSICS)
	$(ICX) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@ -mavx
else
	$(ICX) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@
endif

#==============================================================================

clean:
	rm -rf $(OBJS_COMMON) $(OBJS_CUSTOM) $(OBJS_ICX) driver_check.o driver_calib.o driver.o check calibrate measure 

clean_phase2: 
	rm -rf $(OBJS_COMMON) $(OBJS_CUSTOM) $(OBJS_ICX) driver_check.o driver_calib.o driver.o check calibrate measure kernel_O2NATIVE.o measure_O3.o measure_OFast.o measure_O3NATIVE.o
