#include "sensor.h"
#include <time.h>

int xsamples[13];
int *samp = xsamples;

int main()
{
	clock_t begin, end;
	double time_spent;
	begin = clock();
	getNextData(samp);
    end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
 	return 0;
}
