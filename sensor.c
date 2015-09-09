#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"


int lpf[3];
int hpf[2];
int xsamples[13];
int lptemp[33];

int i;
void handle_line(int line) 
{
  for (i = 0; i < 12; ++i)
  {
      xsamples[i] = xsamples[i+1];
  }
  xsamples[12] = line;
  lowPassFilter();
}

int getNextData()
{


      FILE *samples = fopen("ECG.txt", "r");
      int buffer;
      while(fscanf(samples,"%i",&buffer) != EOF)
      {
      handle_line(buffer);
      }

	return 0;
}

void lowPassFilter()
{
  lpf[3-1]=2 * lpf[3-2]-lpf[3-3]+(((xsamples[12]-(2 * xsamples[12-6])+xsamples[12-12]))/32);
  for (i = 0; i < 2; ++i)
  {
      lpf[i] = lpf[i+1];
  }
  highPassFilter(lpf[2]);
}

void highPassFilter(int pos)
{
  for (i = 0; i < 32; ++i)
  {
      lptemp[i] = lptemp[i+1];
  }
  lptemp[32] = pos;

  hpf[1] = hpf[1-1] - lptemp[32]/32+lptemp[32-16]-lptemp[32-17] + lptemp[32-32] / 32;
  hpf[0] = hpf[1];
  printf("%i\n", hpf[1]);
}

int main()
{
	getNextData();
 
	return 0;
}
