#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

#include<iostream>
#include "get_time.h"
using namespace std;

#define FOR(VAR, COUNT) for(int VAR = 0; VAR < COUNT; ++VAR)
#define CILK_FOR(VAR, COUNT) cilk_for(int VAR = 0; VAR < COUNT; ++VAR)

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
	CILK_FOR(i, n) {
		FOR(k, n) {
			CILK_FOR(j, n) {
				COMPUTE
			}
		}
	}
}
void p2b() {
	CILK_FOR(i, n) {
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
			CILK_FOR(j, n) {
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

void p3() {
	cilk_for (int i2 = 0; i2 < n / t; i2 += t)
		cilk_for (int j2 = 0; j2 < n / t; j2 += t)
			for (int k2 = 0; k2 < n / t; k2 += t)
				cilk_for (int i1 = i2; i1 < i2 + t && i1 < n; i1 += s)
					cilk_for (int j1 = j2; j1 < j2 + t && j1 < n; j1 += s)
						for (int k1 = k2; k1 < k2 + t && k1 < n; k1 += s)
							cilk_for (int i = i1; i < i1 + s && i < i2 + t && i < n; i++)
								cilk_for (int j = j1; j < j1 + s && j < j2 + t && j < n; j++)
									for (int k = k1; k1 < k1 + s && k < k2 + t && k < n; k++)
										c[i * n + j] += a[i * n + k] * b[k * n + j]
}
int main() {
	p3();
}