#!/bin/bash

CMD="../bin/calibrate_gcc_NOOPT"
FREQ="2.4GHz"
SIZE=300
REPS=25

sudo cpupower -c 1 frequency-set -f $FREQ
sudo taskset -c 1 "$CMD" $SIZE $REPS | tee -a ../calibration_data/warmups_calibrate_results.txt

