#!/bin/bash

make phase2 OPT=NOOPT
make phase2 OPT=PERMUTATION
make phase2 OPT=DOUBLETOSIMPLE
make phase2 OPT=UNROLLING
make phase2 OPT=DIVOPTI
make phase2 OPT=TILING
make phase2 OPT=ALLOPTI
make phase2 OPT=ALLOPTI_UNROLLING
make phase2 OPT=ALLOPTI2_INTRINSICS
make phase2 OPT=OPT_INTRINSICS
