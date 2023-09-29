#include <stdio.h>
#include <inttypes.h>

extern uint64_t R;
uint64_t A = 2;
uint64_t B = 3;
uint64_t C = 4;
uint64_t D = 5;
extern int calculate();
int main() {
	calculate();
	printf("%d", R);
	return 0;
}
