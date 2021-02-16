#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"
#include "reduce.h"
using namespace std;

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Usage: ./reduce [num_elements] [threshold=1]" << endl;
		return 0;
	}
	int n = atoi(argv[1]);
	if (argc == 3) {
		th = atoi(argv[2]);}
	int* A = new int[n];
	cilk_for (int i = 0; i < n; i++) A[i] = i;
	timer t0; t0.start();
	int ans = 0;
	for (int i = 0; i < n; i++) ans += A[i];
	t0.stop();
	//cout << ans << ". sequential running time = " << t0.get_total() << endl;
	timer t; t.start();
	int x = reduce(A, n);
	t.stop();
	cout << t.get_total() << " seconds (" << 6.37661 / t.get_total() << "x speedup)" << endl;
	//cout << x << endl;

  delete []A;
	
	return 0;
}
