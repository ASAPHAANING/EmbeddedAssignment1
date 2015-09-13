#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

// Fields.
int lpf[3];
int hpf[2];
int derivative;

// Sample arrays used for passing along
int xsamples[13];
int lptemp[33];
int hptemp[5];

// For loop compiler issues
int i;

/**
 * [handle_line refer to getNextData]
 * @param line [integer datatype as extracted from the .txt file]
 */
void handle_line(int line)
{
  for (i = 0; i < 12; ++i)
  {
      xsamples[i] = xsamples[i+1];
  }
  xsamples[12] = line;
  lowPassFilter();
}

/**
 * [getNextData Reads from textfile a data point at a time and passes it on to
 * handle_line, a function determining the processing of the data]
 * @return [default value for int function ANSI C]
 */
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

/**
 * [lowPassFilter applies a low pass filter to the original signal one data point at a time.
 * The formula is set to cut the frequencies at around 20Hz and above]
 */
void lowPassFilter()
{
  lpf[3-1] =2 * lpf[3-2]-lpf[3-3]+(((xsamples[12]-(2 * xsamples[12-6])+xsamples[12-12]))/32);
  for (i = 0; i < 2; ++i)
  {
      lpf[i] = lpf[i+1];
  }
  highPassFilter(lpf[2]);
}

/**
 * [highPassFilter applies a high pass filter on the signal,
 * removing the low end of the frequency spectrum at around 5Hz]
 * @param pos [Yn value from last filter needed for calculations in the new filter
 * Sets the value of the last position in the shifted array]
 */
void highPassFilter(int pos)
{
  for (i = 0; i < 32; ++i)
  {
      lptemp[i] = lptemp[i+1];
  }

  lptemp[32] = pos;

  hpf[1] = hpf[1-1] - lptemp[32]/32+lptemp[32-16]-lptemp[32-17] + lptemp[32-32] / 32;
  hpf[0] = hpf[1];
  //printf("%i\n", hpf[1]);
  derivativeFilter(hpf[1]);
}

/**
 * [derivativeFilter applies derivative filter to a signal in order to
 * focus on a certain frequency range and amplitude.]
 * @param pos [Yn value from last filter needed for calculations in the new filter.
 * Sets the value of the last position in the shifted array]
 */
void derivativeFilter(int pos)
{
    for (i = 0; i < 4; ++i)
  {
      hptemp[i] = hptemp[i+1];
  }

  hptemp[4] = pos;

  derivative = (2*hptemp[4]+hptemp[4-1]-hptemp[4-3]-2*hptemp[4-4])/8;

  printf("%i\n", derivative);

}

int main()
{
	getNextData();

	return 0;
}
