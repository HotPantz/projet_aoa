#!/bin/bash

CMD="../bin/measure_gcc_NOOPT"

for i in {1..25}; do
	sudo taskset -c 1 "$CMD" 319 18 "$i" | grep -E "MIN|MED|STABILITY" | tee -a ../calibration_data/rdtsc
done
