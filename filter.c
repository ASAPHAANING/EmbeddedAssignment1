#include "search.h"

// Fields.
int lpf[3];
int hpf[2];
int derivative;
int mwi;

// Sample arrays used for passing along
int lptemp[33];
int hptemp[5];
int dertemp[30];

// For loop compiler issues
int i;

void highPassFilter(int pos);
void derivativeFilter(int pos);
void squareShit(int result);
void movingWindowIntegration(int pos);
/**
* [lowPassFilter applies a low pass filter to the original signal one data point at a time.
* The formula is set to cut the frequencies at around 20Hz and above]
*/
void lowPassFilter(int *xsamples)
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

  hpf[1]     = hpf[1-1] - lptemp[32]/32+lptemp[32-16]-lptemp[32-17] + lptemp[32-32] / 32;
  hpf[0]     = hpf[1];
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

  hptemp[4]  = pos;

  derivative = (2*hptemp[4]+hptemp[4-1]-hptemp[4-3]-2*hptemp[4-4])/8;
  squareShit(derivative);
//movingWindowIntegration(derivative);
//printf("%i\n", derivative);

}

void squareShit(int result)
{
  int temp = result*result;
  movingWindowIntegration(temp);
}

void movingWindowIntegration(int pos)
{
  mwi = 0;
  for (i = 0; i < 29; ++i)
  {
    dertemp[i] = dertemp[i+1];
  }

  dertemp[29] = pos;

  for (i = 29; i >= 0; --i)
  {
    mwi += dertemp[29-i];

  }
  mwi /= 30;
  findPeak(mwi);
  //printf("%i\n", mwi);
}
