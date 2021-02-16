#!/bin/bash
for threshold in 1 2 4 8 16 32 64 128
do
	echo "threshold: $threshold"
	for workers in 1 2 4 8 12 24
	do
		echo "    $workers workers:"
		export CILK_NWORKERS=$workers;
		./reduce 100000000 $threshold;
	done
	
done
exit 0