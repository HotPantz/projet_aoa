#GCC
CC=gcc

#==============================================================================
#							OPTIMISATION FLAGS
#==============================================================================
#The driver (main, "measure" executable) is compiled with O2
CFLAGS=-O2 -g -Wall

#General flags (for all CPUs)
OPTFLAGS=-O2 -g -Wall #Default "measure" : -O2
OPTFLAGS_O3=-O3 
OPTFLAGS_O3NATIVE=-O3 -march=native
OPTFLAGS_OFAST=-Ofast
OPTFLAGS_AVX2=-O3 -mavx2 #YMM vectorization
OPT_OCUSTOM=-O3 -ffinite-math-only -freciprocal-math -fno-math-errno -funsafe-math-optimizations -ffloat-store

#Specific macros & flags for ICC & Intel CPUs

#Specific macros & flags for AOCC & AMD CPUs
AOCC=/home/euro/aocc-compiler-4.2.0/bin/clang
#==============================================================================

OBJS_COMMON=kernel.o rdtsc.o
OBJS_CUSTOM=kernel_O3.o kernel_OFAST.o kernel_O3NATIVE.o kernel_AVX2.o kernel_OCUSTOM.o kernel_AOCC_O2.o
BIN_PATH=../bin/

#==============================================================================
#							MAIN TARGETS
#==============================================================================
#Default target : everything but AOCC
all:	check calibrate measure measure_O3 measure_OFast measure_O3NATIVE measure_AVX2 measure_OCUSTOM 
#Intel Compiler target
#icc: #TODO: mettez ici les cibles pour les versions Intel ICC
#Custom AOCC target (specific install location)
fred: measure_AOCC
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
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^

measure_OFast: kernel_OFAST.o rdtsc.o driver.o
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^

measure_O3NATIVE: kernel_O3NATIVE.o rdtsc.o driver.o
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^

measure_AVX2: kernel_AVX2.o rdtsc.o driver.o
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^

measure_OCUSTOM: kernel_OCUSTOM.o rdtsc.o driver.o
	$(CC) -o $(BIN_PATH)$@_$(CC)_$(OPT) $^

measure_AOCC: kernel_AOCC_O2.o rdtsc.o driver.o
	$(AOCC) -o $(BIN_PATH)$@_$(OPT) $^

measure_AOCC_O3: kernel_AOCC_O3.o rdtsc.o driver.o
	$(AOCC) -o $(BIN_PATH)$@_$(OPT) $^
#==============================================================================

#==============================================================================
#						COMMON OBJECTS
#==============================================================================
driver_check.o: driver_check.c
	$(CC) $(CFLAGS) -D CHECK -c $< -o $@
driver_calib.o: driver_calib.c
	$(CC) $(CFLAGS) -D CALIB -c $< -o $@
driver.o: driver.c
	$(CC) $(CFLAGS) -c $<
#==============================================================================

#==============================================================================
# 						DIFFERENT KERNELS
#==============================================================================
kernel.o: kernel.c
	$(CC) $(OPTFLAGS) -D $(OPT) -c $< -o $@

kernel_O3.o: kernel.c
	$(CC) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@

kernel_OFAST.o: kernel.c
	$(CC) $(OPTFLAGS_OFAST) -D $(OPT) -c $< -o $@

kernel_O3NATIVE.o: kernel.c
	$(CC) $(OPTFLAGS_O3NATIVE) -D $(OPT) -c $< -o $@

kernel_AVX2.o: kernel.c
	$(CC) $(OPTFLAGS_AVX2) -D $(OPT) -c $< -o $@

kernel_OCUSTOM.o: kernel.c
	$(CC) $(OPT_OCUSTOM) -D $(OPT) -c $< -o $@

kernel_AOCC_O2.o: kernel.c
	$(AOCC) $(OPTFLAGS) -D $(OPT) -c $< -o $@

kernel_AOCC_O3.o: kernel.c
	$(AOCC) $(OPTFLAGS_O3) -D $(OPT) -c $< -o $@
#==============================================================================

clean:
	rm -rf $(OBJS_COMMON) $(OBJS_CUSTOM) driver_check.o driver_calib.o driver.o check calibrate measure 
