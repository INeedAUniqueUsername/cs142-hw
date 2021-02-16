#!/bin/bash
for workers in 1 2 4 8 12 24
do	
	echo "    $workers workers:"
	export CILK_NWORKERS=$workers;
	./a.out $threshold;
done
exit 0