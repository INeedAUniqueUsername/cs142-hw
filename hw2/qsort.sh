#!/bin/bash
make qsort;
for threshold in 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288
do
	echo "threshold: $threshold"
	./qsort 100000000 $threshold;
done
exit 0