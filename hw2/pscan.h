#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "reduce.h"

int threshold_scan = 128;
void scan(int* A, int n, int ps) {
	if(n <= threshold_scan) {
		//A[0] += ps;
		
		
		for(int i = 0; i < n; i++) {
			int item = A[i];
			A[i] += ps;
			ps += item;
		}
	} else {
		auto leftSum = cilk_spawn reduce(A, n/2);
		
		cilk_spawn scan(A, n/2, ps);
		scan(A + n/2, n - n/2, ps + leftSum);
		cilk_sync;
	}
}