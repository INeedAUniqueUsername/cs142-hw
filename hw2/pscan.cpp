#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include "get_time.h"
#include "pscan.h"
using namespace std;


int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Usage: ./scan [num_elements]" << endl;
		return 0;
	}
	int n = atoi(argv[1]);
	
	if (argc == 3) {
		th = atoi(argv[2]);}
	
	//cout << n << endl;
	int* A = new int[n];
	cilk_for (int i = 0; i < n; i++) A[i] = i;
	
	/*
	for (int i = 0; i < n; i++) cout << A[i] << " ";
	cout << endl;
	*/
	
	timer t; t.start();
	scan(A, n, 0);
	t.stop(); cout << t.get_total() << " seconds (" << 12.9049 / t.get_total() << "x speedup)" << endl;
	
	//for (int i = n - 2; i < n; i++) cout << A[i] << " ";
	//cout << endl;
	
	//cilk_for (int i = 0; i < n; i++) cout << A[i] << " ";
  
  delete []A;
	
	return 0;
}
