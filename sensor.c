#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

int xsamples[32];
int i;
void handle_line(int *line) {
  for (i = 0; i < sizeof(xsamples); ++i)
  {
      xsamples[i] = xsamples[i+1];
  }
  xsamples[sizeof(xsamples)-1] = line;
  printf("%d\n",xsamples[sizeof(xsamples)-1]);
}

int getNextData()
{


      FILE *samples = fopen("ECG1.txt", "r");
    int *buffer;
    while(fscanf(samples,"%i",&buffer) != EOF)
    {
      handle_line(buffer);
    }

	return 0;
}

int main()
{
	getNextData();
	return 0;
}
