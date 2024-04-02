#!/bin/bash

# Script montrant l'impact des caches sur les performances

cmd="../bin/measure_gcc_NOOPT"

# Tailles du problème (a modifier selon CPU)
arg_values=(10 25 50 75 100 150 200 250 300 350 400 500 600)

for arg in "${arg_values[@]}"; do
    $cmd $arg 18 15
done