CC = g++
CFLAGS = -O2 -mcx16 -march=native -DCILK -fcilkplus -std=c++11

all:	reduce scan qsort

reduce:	reduce.cpp reduce.h
	$(CC) $(CFLAGS) -DNDEBUG reduce.cpp -o reduce
	
scan:	scan.cpp scan.h
	$(CC) $(CFLAGS) -DNDEBUG scan.cpp -o scan
	
pscan:	pscan.cpp pscan.h
	$(CC) $(CFLAGS) -DNDEBUG pscan.cpp -o pscan

qsort:	quicksort.cpp qsort.h
	$(CC) $(CFLAGS) -DNDEBUG quicksort.cpp -o qsort

	
clean:
	rm -f reduce scan qsort
