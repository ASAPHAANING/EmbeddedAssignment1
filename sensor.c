#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "filter.h"

int i;

//int xsamples[13];
//int *samp = xsamples;

/**
* [handle_line refer to getNextData]
* @param line [integer datatype as extracted from the .txt file]
*/
void handle_line(int line, int *xsamples)
{
  for (i = 0; i < 12; ++i)
  {
    xsamples[i] = xsamples[i+1];
  }
  xsamples[12] = line;
  lowPassFilter(xsamples);
}

/**
* [getNextData Reads from textfile a data point at a time and passes it on to
* handle_line, a function determining the processing of the data]
* @return [default value for int function ANSI C]
*/
int getNextData(int *xsamples)
{
  FILE *samples = fopen("ECG10800K.txt", "r");
  int buffer;
  while(fscanf(samples,"%i",&buffer) != EOF)
  {
    handle_line(buffer, xsamples);

  }
  return 0;
}
