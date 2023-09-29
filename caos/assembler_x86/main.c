#include <stdio.h>
#include <inttypes.h>

extern float dot_product(size_t N, const float* A, const float* B);

int main() {
        float A[10] = {1,2,3,4,5,6,7,8,9,10};
	float B[10] = {1,2,3,4,5,6,7,8,9,10};
	float res = dot_product(10, A, B);
	printf("\n%f\n", res);
	return 0;
}
