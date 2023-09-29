#include <stdio.h>

extern double very_important_function(size_t N, const float* A, const float* B, float* R);
int main() {
	float A[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	float B[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	float R[16];
	double res = very_important_function(16, A, B, R);
	for (int i = 0; i < 16; i++) {
		printf("%f ", R[i]);
	}
	printf("%f", res);
}
