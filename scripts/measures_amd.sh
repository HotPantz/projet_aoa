#!/bin/bash

# Runs all the standard measure binaries in the /bin/ folder AND the AOCC specific ones

warmups=18
reps=15
size=300
RESULTS_DIR="../results/no_opt"
FREQ="2.4GHz"

commands=("measure_gcc_NOOPT" "measure_O3_gcc_NOOPT" "measure_OFast_gcc_NOOPT" "measure_O3NATIVE_gcc_NOOPT" "measure_AVX2_gcc_NOOPT" "measure_OCUSTOM_gcc_NOOPT" "measure_AOCC_NOOPT" "measure_O3_AOCC_NOOPT)

sudo cpupower -c 1 frequency-set -f $FREQ

for cmd in "${commands[@]}"; do
    echo "Running $cmd with size $size" > $RESULTS_DIR/$cmd.txt
    sudo taskset -c 1 ../bin/$cmd $size $warmups $reps | tee -a $RESULTS_DIR/$cmd.txt
done