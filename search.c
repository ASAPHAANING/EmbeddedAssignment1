#include <stdio.h>
#include <stdlib.h>

int compare[3];
int peak[],Rpeak[];
int index = 0;
int divideCount = 0;
int rising = 0;
int RpeakCount = 0;
int i, j, RRcount;
int RRaverage1 = 0;
int RRaverage2 = 0;
int RRlow, RRhigh, RRmiss;
int threshold1 = 3000;
int RRvalues[8] = {0,0,0,0,0,0,0,0};

void findPeak(int filtervalue)
{
	RRcount += 1; //Counter til RR interval
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
		//printf("%i %i\n", index, peak[index]);
		findRPeak();
		index++;
	}
}
void findRPeak ()
{
	if (peak[index] > threshold1 && RRcount > 50)
	{
		//printf("%i\n", peak[index]);
		for (i = 0; i < 7; ++i)
		{
			RRvalues[i] = RRvalues[i+1];
		}
		RRvalues[7] = RRcount;
		// Fucker lidt.
		//printf("%i\n",RRcount);
		for (i = 0; i < 8; ++i)
		{
			//printf("%i\n", RRvalues[i]);
			RRaverage2 += RRvalues[i];
			

		}
		divideCount +=1;

		if(divideCount<8)
		{	
			RRaverage2/=divideCount;

		}
		else
		{
		RRaverage2 /= 8;	
		}
		printf("%i\n", peak[index]);
		RRlow = RRaverage2*92/100;
		RRhigh = RRaverage2*116/100;
		RRmiss = RRaverage2*166/100;
		printf("%i\n", peak[index]);

		if (RRcount < RRhigh && RRcount > RRlow){
			Rpeak[RRcount] = peak[index];
			//printf("%i\n", peak[index]);
			//ŔpeakCount += 1;
		}
		RRaverage2 = 0;
		RRcount = 0;
	}

}

