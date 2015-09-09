#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

void handle_line(char *line) {
  printf("%s", line);
}

int getNextData()
{

    int size = 1024, pos;
    int c;
    char *buffer = (char *)malloc(size);

    FILE *samples = fopen("ECG.txt", "r");
    if(samples) {
      do { // read all lines in file
        pos = 0;
        do{ // read one line
          c = fgetc(samples);
          if(c != EOF) buffer[pos++] = (char)c;
          if(pos >= size - 1) { // increase buffer length - leave room for 0
            size *=2;
            buffer = (char*)realloc(buffer, size);
          }
        }while(c != EOF && c != '\n');
        buffer[pos] = 0;
        // line is now in buffer
        handle_line(buffer);
      } while(c != EOF); 
      fclose(samples);           
    }
    free(buffer);
	return 0;
}

int main()
{
	getNextData();
	return 0;
}
