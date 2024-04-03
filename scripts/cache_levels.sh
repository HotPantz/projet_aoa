#!/bin/bash

# Script montrant l'impact des caches sur les performances

cmd="../bin/measure_gcc_NOOPT"
warmups=18
reps=15
RESULTS_DIR="../results"

# Numéro du coeur (a modifier selon CPU)
core=1
FREQ="2.4GHz"

# Tailles du problème (a modifier selon CPU)
arg_values=(10 15 25 50 75 100 150 200 250 300 350 400 500 600 700)

sudo cpupower -c 1 frequency-set -f $FREQ

for arg in "${arg_values[@]}"; do
    echo "MEASURE N = $arg" | tee -a  $RESULTS_DIR/cache_levels_results.txt
    sudo taskset -c 1 $cmd $arg $warmups $reps | tee -a $RESULTS_DIR/cache_levels_results.txt
done