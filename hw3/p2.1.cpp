#include<iostream>
#include "get_time.h"
using namespace std;

#define FOR(VAR, COUNT) for(int VAR = 0; VAR < COUNT; ++VAR)

#define MULTIPLY(i, j, k)					\
FOR(i, n) {									\
	FOR(j, n) {								\
		FOR(k, n) {							\
			c[i][j] += a[i][k] * b[j][j];	\
		}									\
	}										\
}

#define INIT								\
FOR(i, n) {									\
	FOR(j, n) {								\
		a[i][j] = i + j;					\
		b[i][j] = i + 2 * j;				\
	}										\
}

#define TIME(CODE, NAME) {					\
	timer t;								\
	t.start();								\
	CODE									\
	t.stop();								\
	cout << NAME << " time: " << t.get_total() << endl; \
}


const unsigned n = 1024;
int a[n][n];
int b[n][n];
int c[n][n];

int main() {
	INIT
		TIME(MULTIPLY(i, j, k), "ijk")
		cout << "c[10][20] = " << c[10][20] << endl;
	INIT
	TIME(MULTIPLY(i, k, j), "ikj")
		cout << "c[10][20] = " << c[10][20] << endl;
	INIT
	TIME(MULTIPLY(j, i, k), "jik")
		cout << "c[10][20] = " << c[10][20] << endl;
	INIT
	TIME(MULTIPLY(j, k, i), "jki")
		cout << "c[10][20] = " << c[10][20] << endl;
	INIT
	TIME(MULTIPLY(k, i, j), "kij")
		cout << "c[10][20] = " << c[10][20] << endl;
	INIT
	TIME(MULTIPLY(k, j, i), "kji")
		cout << "c[10][20] = " << c[10][20] << endl;
}