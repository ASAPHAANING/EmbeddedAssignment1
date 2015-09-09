#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"


int lpf[3];
int hpf[2];
int xsamples[32];

int i;
void handle_line(int line) 
{
  for (i = 0; i < 32; ++i)
  {
      xsamples[i] = xsamples[i+1];
  }
  xsamples[31] = line;
  lowPassFilter();
}

int getNextData()
{


      FILE *samples = fopen("ECG1.txt", "r");
      int buffer;
      while(fscanf(samples,"%i",&buffer) != EOF)
      {
      handle_line(buffer);
      }

	return 0;
}

void lowPassFilter()
{
  lpf[3-1]=2 * lpf[3-2]-lpf[3-3]+(((xsamples[32-1]-(2 * xsamples[32-7])+xsamples[32-13]))/32);
  for (i = 0; i < 2; ++i)
  {
      lpf[i] = lpf[i+1];
  }
  printf("%i\n",lpf[2]);
}

int main()
{
	getNextData();
 
	return 0;
}
