#include <stdio.h>
#include <stdlib.h>

int compare[3];
static int peak[100],Rpeak[8];
static int index  = 0;
static int indexR = 0;
int divideCount   = 0;
int rising        = 0;
int RpeakCount    = 0;
int i, j;
int RRcount       = 0;
int RRaverage1    = 0;
int RRaverage2    = 0;
int SPKF          = 0;
int NPKF          = 0;
int RRlow         = 0;
int RRhigh        = 300;
int RRmiss;
int threshold1    = 1000;
int threshold2    = 500;
int RRvalues[8]   = {0,0,0,0,0,0,0,0};

void findPeak(int filtervalue)
{

	for (i = 0; i < 2; ++i)
	{
		compare[i] = compare[i+1];
	}
	compare[2] = filtervalue;

	if(rising == 0 && compare[1] > compare[0])// ser om vi stiger i værdi
	{
		rising = 1;
	}


	if(compare[0] <= compare[1] && compare[1] > compare[2] && rising == 1)
	{
		rising      = 0;
		for (i      = 0; i < 100; ++i)
		{
			peak[i] = peak[i+1];
		}
		peak[99]    = compare[1];
		//printf("%i \n", peak[index]);
		findRPeak();

	}
	RRcount += 1; //Counter til RR interval
}
void findRPeak ()
{
	if (peak[99] > threshold1 /*&& RRcount > 50*/)
	{
		if (RRcount < RRhigh && RRcount > RRlow)
		{
			for (i = 0; i < 7; ++i)
			{
				RRvalues[i] = RRvalues[i+1];
			}
			RRvalues[7] = RRcount;

			for (i = 0; i < 8; ++i)
			{
				RRaverage2 += RRvalues[i];
				RRaverage1 += RRvalues[i];
			}
			divideCount +=1;
			if(divideCount<8)
			{
				RRaverage2 /= divideCount;
				RRaverage1 /= divideCount;
			}
			else
			{
				RRaverage2 /= 8;
				RRaverage1 /= 8;
			}

			Rpeak[indexR] = peak[99];
			printf("%i %i %i\n", RRcount, Rpeak[indexR], threshold1 );
			if (++indexR > 7)
			{
				indexR = 0;
			}
			RRlow            = RRaverage2*92/100;
			RRmiss           = RRaverage2*166/100;
			RRhigh           = RRaverage2*116/100;
			SPKF             = 0.125 * peak[99] + 0.875 * SPKF;
			threshold1       = NPKF + 0.25 *(SPKF - NPKF);
			threshold2       = 0.5*threshold1;
			RRaverage2       = 0;
			RRcount          = 0;
		}
		else
		{
			if (RRcount > RRmiss)
			{
				while (peak[index] > threshold2)
				{

					index++;
					RRcount--;
				}
				for (i = 0; i < 7; ++i)
				{
					RRvalues[i] = RRvalues[i+1];
				}
				RRvalues[7] = RRcount;
				for (i = 0; i < 8; ++i)
				{
					RRaverage1 += RRvalues[i];
				}

				Rpeak[indexR] = peak[index];
				RRaverage1    = RRaverage1/8;
				RRlow         = 0.92*RRaverage1;
				RRhigh        = 1.16*RRaverage1;
				RRmiss        = 1.66*RRaverage1;
				threshold1    = NPKF + 0.25 * (SPKF-NPKF);
				threshold2    = 0.5 * threshold1;
				SPKF          = 0.25 * peak[index] + 0.75 * SPKF;
				RRcount = 0;

			}
			RRcount = 0;
		}


	}
	else {
		NPKF       = 0.125*peak[99]+0.875*NPKF;
		threshold1 = NPKF + 0.25 *(SPKF - NPKF);
		threshold2 = 0.5*threshold1;
	}
}

