#!/bin/bash
make pscan;
for threshold in 128 256 512 1024
do
	echo "threshold: $threshold"
	for workers in 1 2 4 8 12 24
	do
		echo "    $workers workers:"
		export CILK_NWORKERS=$workers;
		./pscan 100000000 $threshold;
	done
	
done
exit 0