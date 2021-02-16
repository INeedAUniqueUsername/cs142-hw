#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
using namespace std;

int th = 1;

int reduce(int* A, int n) {
	if (n <= th) {
		int ret = 0;
		for (int i = 0; i < n; i++) {
			ret += A[i];
		}
		return ret;
	}
	int L, R;
	L = cilk_spawn reduce(A, n/2);
	R = reduce(A+n/2, n-n/2);
	cilk_sync;
	return L+R;
}