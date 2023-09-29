#include <stdio.h>

extern double avx_sin(double x);

int main() {
	double res = avx_sin(3.141592653 / 6);
	printf("%f", res);
}
