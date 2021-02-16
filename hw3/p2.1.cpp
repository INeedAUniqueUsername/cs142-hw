#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

#include<iostream>
#include "get_time.h"
using namespace std;

#define FOR(VAR, COUNT) for(int VAR = 0; VAR < COUNT; ++VAR)
#define PFOR(VAR, COUNT) cilk_for(int VAR = 0; VAR < COUNT; ++VAR)

#define COMPUTE c[i][j] += a[i][k] * b[k][j];
#define MULTIPLY(VAR1, VAR2, VAR3)			\
FOR(VAR1, n) {								\
	FOR(VAR2, n) {							\
		FOR(VAR3, n) {						\
			COMPUTE							\
		}									\
	}										\
}

#define INIT								\
FOR(i, n) {									\
	FOR(j, n) {								\
		a[i][j] = i + j;					\
		b[i][j] = i + 2 * j;				\
		c[i][j] = 0;						\
	}										\
}

#define TIME(CODE, NAME) {					\
	timer t;								\
	t.start();								\
	CODE;									\
	t.stop();								\
	cout << NAME << " time: " << t.get_total() << endl; \
}


const unsigned n = 1024;
int a[n][n];
int b[n][n];
int c[n][n];

void p1() {
	INIT
		TIME(MULTIPLY(i, j, k), "ijk")
		INIT
		TIME(MULTIPLY(i, k, j), "ikj")
		INIT
		TIME(MULTIPLY(j, i, k), "jik")
		INIT
		TIME(MULTIPLY(j, k, i), "jki")
		INIT
		TIME(MULTIPLY(k, i, j), "kij")
		INIT
		TIME(MULTIPLY(k, j, i), "kji")
		cout << "c[10][20] = " << c[10][20] << endl;
}
void p2a() {
	PFOR(i, n) {
		FOR(k, n) {
			PFOR(j, n) {
				COMPUTE
			}
		}
	}
}
void p2b() {
	PFOR(i, n) {
		FOR(k, n) {
			FOR(j, n) {
				COMPUTE
			}
		}
	}
}
void p2c() {
	FOR(i, n) {
		FOR(k, n) {
			PFOR(j, n) {
				COMPUTE
			}
		}
	}
}
void p2() {
	INIT
	TIME(p2a(), "Parallel ij")
	INIT
	TIME(p2b(), "Parallel i")
	INIT
	TIME(p2c(), "Parallel j")

		cout << "c[10][20] = " << c[10][20] << endl;
}

static unsigned A[n * n];
static unsigned B[n * n];
static unsigned C[n * n];

#define INIT2 									\
for (unsigned i = 0; i < n * n; i++) {			\
	unsigned row = i/n;							\
	unsigned col = i%n;							\
	A[i] = row + col;								\
	B[i] = row + 2*col;								\
	C[i] = 0;									\
}

void tiled(unsigned s) {
	cilk_for(int i1 = 0; i1 < n; i1 += s) {
		cilk_for(int j1 = 0; j1 < n; j1 += s) {
			for (int k1 = 0; k1 < n; k1 += s) {
				for(int i = i1; i < min(i1 + s, n); i++) {
					for(int j = j1; j < min(j1 + s, n); j++) {
						for (int k = k1; k < k1 + s && k < n; k++) {
							C[i * n + j] += A[i * n + k] * B[k * n + j];
						}
					}
				}
			}
		}
	}
}



void p3() {
		INIT2
		TIME(tiled(4), "s=4")
	cout << "c[10][20] = " << C[10*n + 20] << endl;
		INIT2
		TIME(tiled(8), "s=8")
		INIT2
		TIME(tiled(16), "s=16")
		INIT2
		TIME(tiled(32), "s=32")
		INIT2
		TIME(tiled(64), "s=64")
		INIT2
		TIME(tiled(128), "s=128")
		INIT2
		TIME(tiled(256), "s=256")
		INIT2
		TIME(tiled(512), "s=512")
		INIT2
		TIME(tiled(1024), "s=1024")
		INIT2
		TIME(tiled(2048), "s=2048")
		INIT2
		TIME(tiled(2048), "s=4096")
		INIT2
		TIME(tiled(2048), "s=8192")
}
void p4() {
		INIT2
		TIME(tiled(4), "s=4")
		INIT2
		TIME(tiled(8), "s=8")
		INIT2
		TIME(tiled(16), "s=16")
		INIT2
		TIME(tiled(32), "s=32")
		INIT2
		TIME(tiled(64), "s=64")
		INIT2
		TIME(tiled(128), "s=128")
		INIT2
		TIME(tiled(256), "s=256")
}



// Assume that n is an exact power of 2.
void Rec_Mult(unsigned *C, unsigned *A, unsigned *B,
unsigned n, unsigned rowsize) {
	
	if(n == 1) {
		C[0] += A[0] * B[0];
	} else if (n <= 32) {
		FOR(i, n) {
			FOR(k, n) {
				FOR(j, n) {
					C[i*1024 + j] += A[i*1024 + k] * B[k*1024 + j];
				}
			}
		}
		
		return;
		
		unsigned d11 = 0;
		unsigned d12 = n/2;
		unsigned d21 = (n/2) * rowsize;
		unsigned d22 = (n/2) * (rowsize+1);
		Rec_Mult(C+d11, A+d11, B+d11, n/2, rowsize);
		Rec_Mult(C+d21, A+d22, B+d21, n/2, rowsize);
		Rec_Mult(C+d12, A+d11, B+d12, n/2, rowsize);
		Rec_Mult(C+d22, A+d22, B+d22, n/2, rowsize);
		
		Rec_Mult(C+d11, A+d12, B+d21, n/2, rowsize);
		Rec_Mult(C+d21, A+d21, B+d11, n/2, rowsize);
		Rec_Mult(C+d12, A+d12, B+d22, n/2, rowsize);
		Rec_Mult(C+d22, A+d21, B+d12, n/2, rowsize);
		
		
	} else {
		unsigned d11 = 0;
		unsigned d12 = n/2;
		unsigned d21 = (n/2) * rowsize;
		unsigned d22 = (n/2) * (rowsize+1);
		cilk_spawn Rec_Mult(C+d11, A+d11, B+d11, n/2, rowsize);
		cilk_spawn Rec_Mult(C+d21, A+d22, B+d21, n/2, rowsize);
		cilk_spawn Rec_Mult(C+d12, A+d11, B+d12, n/2, rowsize);
		Rec_Mult(C+d22, A+d22, B+d22, n/2, rowsize);
		cilk_sync;
		cilk_spawn Rec_Mult(C+d11, A+d12, B+d21, n/2, rowsize);
		cilk_spawn Rec_Mult(C+d21, A+d21, B+d11, n/2, rowsize);
		cilk_spawn Rec_Mult(C+d12, A+d12, B+d22, n/2, rowsize);
		Rec_Mult(C+d22, A+d21, B+d12, n/2, rowsize);
		cilk_sync;
	}
}
void p5a() {
	Rec_Mult(C, A, B, n, n);
}
void p5() {
	INIT2
	TIME(p5a(), "")
	cout << "c[10][20] = " << C[10*n + 20] << endl;
}
int main() {
	p5();
}