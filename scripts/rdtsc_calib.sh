#!/bin/bash

CMD="../bin/measure_gcc_NOOPT"
FREQ="2.4GHz"
SIZE=300
WARMUPS=18

sudo cpupower -c 1 frequency-set -f $FREQ

for i in {1..25}; do
	sudo taskset -c 1 "$CMD" $SIZE $WARMUPS "$i" | grep -E "MIN|MED|STABILITY" | tee -a ../calibration_data/rdtsc_calibration_results.txt
done
