#include <stdio.h>
#include <stdlib.h>

int R[];
int compare[3];
int peak[];
int index = 0;
int rising = 0;
int i;

void findPeak(int filtervalue)
{
	for (i = 0; i < 2; ++i)
	{
		compare[i] = compare[i+1];
	}
	compare[2] = filtervalue;

	if(rising == 0 && compare[1] > compare[0])
	{
		rising = 1;
	}


	if(compare[0] <= compare[1] && compare[1] > compare[2] && rising == 1)
	{
		rising = 0;
		peak[index] = compare[1];
		printf("%i %i\n", index, peak[index]);
		index++;
	}
}

