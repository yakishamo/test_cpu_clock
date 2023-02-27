#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "rdtsc.h"

#define CLOCK
//#define TIME
//#define SIZE (1960*1080*4)
#define SIZE (1024)
#define SAMPLE_SIZE (10)

int main(void) {
	unsigned char *data = (unsigned char*)malloc(SIZE);
	unsigned char *dst = (unsigned char*)malloc(SIZE);
	if(data == NULL || dst == NULL) {
		printf("malloc failed.\n");
	}
	srand(time(NULL));
	unsigned int i = 0;
	unsigned int j = 0;
	double time_sum = 0;
	double time_ave = 0;
	unsigned long first, second;
	for(j = 0; j < SAMPLE_SIZE; j++) {
		for(i = 0; i < SIZE; i++) {
			if(i < SIZE)data[i] = rand()%256;
		}
		long t1 = 0, t2 = 0;
		struct timeval myTime;
#ifdef CLOCK
		t1 = read_clock();
#else
		gettimeofday(&myTime, NULL);
		t1 = myTime.tv_usec;
#endif

		memcpy(dst, data, SIZE);

#ifdef CLOCK
		t2 = read_clock();
#else
		gettimeofday(&myTime,NULL);
		t2 = myTime.tv_usec;
#endif
#ifdef TIME
		time_sum += (double)(t2-t1)/CLOCKS_PER_SEC*1000;
		printf("%lf[ms]\n", (double)(t2-t1)/CLOCKS_PER_SEC*1000);
#else
		time_sum = t2-t1;
		printf("%ld[clock]\n", t2-t1);
		if(j==0) first = t2-t1;
		if(j==1) second = t2-t1;
#endif
	}
	time_ave = (double)time_sum/SAMPLE_SIZE;
#ifdef TIME
	printf("average : %lf[ms]\n", time_ave);
#else
	printf("average : %lf[clock]\n", time_ave);
#endif
	printf("(1)/(2) : %lf\n", (double)first/second);
	return 0;
}
