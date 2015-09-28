#include "sensor.h"
#include "filter.h"

int xsamples[13];
int *samp = xsamples;

int main()
{
	getNextData(samp);
 	return 0;
}
