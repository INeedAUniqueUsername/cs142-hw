#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <ctime>
#include <iostream>
#include "get_time.h"
#include<cmath>

long double reduce(long double* A, int n) {
  if (n == 1) {
    return A[0];
  }
  long double L, R;
  L = cilk_spawn reduce(A, n / 2);
  R = reduce(A + n / 2, n - n / 2);
  cilk_sync;
  return L + R;
}

//Parallel 2
void integral() {
	long double segs = pow(10, 8);
	long double sum = 0;
	for(int l = 0; l < 10000; l++) {
		long start = (long)l*segs / 10000;
		long end = (long)(l+1)*segs/10000;
		
		long count = end - start;
		
		long double pieces[count];
		cilk_for(int i = start; i < end; i++) {
			pieces[i - start] = (sin(1+i/segs) * log(1+i/segs) + sin(1+(i+1)/segs) * log(1+(i+1)/segs)) / segs / 2;
		}
		
		sum += reduce(pieces, count);
	}
	printf("%.10Lf\n", sum);
}

/*
//Sequential 2
void integral() {
	long double segs = pow(10, 8);
	long double sum = 0;
	for(int l = 0; l < 10000; l++) {
		long start = (long)l*segs / 10000;
		long end = (long)(l+1)*segs/10000;
		
		
		for(int i = start; i < end; i++) {
			sum += (sin(1+i/segs) * log(1+i/segs) + sin(1+(i+1)/segs) * log(1+(i+1)/segs)) / segs / 2;
		}
		
	}
	printf("%.10Lf\n", sum);
}
*/
/*
//Parallel 1
void integral(){
	double segs = pow(10, 8);
	int isegs = (int)segs;
	long double sum = 0;

	int ipieces = pow(2, 16);
	long double pieces[ipieces];
	
	cilk_for(int i = 0; i < ipieces; i++) {
		pieces[i] = 0;
	}

	cilk_for (int i=0; i<isegs; i++) {
		pieces[i % ipieces] += (sin(1+i/segs) * log(1+i/segs) + sin(1+(i+1)/segs) * log(1+(i+1)/segs)) / segs / 2;
	}
	
	sum = reduce(pieces, ipieces);
	
	printf("%.10Lf", sum);
	printf("\n");
}
*/
/*
//Sequential 1
void integral(){
	double segs = pow(10, 8);
	int isegs = (int)segs;
	long double sum = 0;

	for (int i=0; i<isegs; i++) {
		sum += (sin(1+i/segs) * log(1+i/segs) + sin(1+(i+1)/segs) * log(1+(i+1)/segs)) / segs / 2;
	}
	printf("%.10Lf", sum);
	printf("\n");
}
*/
int main() {
	timer t;
	integral();
	t.stop();
	std::cout << "elapsed time: " << t.get_total() << std::endl;
	return 0;
}

