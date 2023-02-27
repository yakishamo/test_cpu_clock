#include <stdio.h>
#include "rdtsc.h"

int main(void) {
	printf("%u\n", read_clock());
	return 0;
}
