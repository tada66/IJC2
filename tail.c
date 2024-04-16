#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct { char c[2048]; } LINE;

typedef struct{
LINE* buffer;
int writeIndex;
int readIndex;
int bufferSize;
} cbuf;

/*
int cbuf_get (int * value) 
{
  if (readIndex == writeIndex)
  {
     // buffer is empty
     return 0;
  }

  *value = buffer[readIndex];
  readIndex = (readIndex + 1) % N;
  return 1;
}
*/
cbuf* cbuf_create(int n){
    cbuf* cbuf = malloc(sizeof(cbuf));
    cbuf->bufferSize=n;
    cbuf->readIndex=0;
    cbuf->writeIndex=0;
    cbuf->buffer = malloc(sizeof(LINE)*n);
    return cbuf;
}

void cbuf_put (cbuf* cbuffer, char* line) 
{
    
}

int main (int argc, char** argv)
{
    int lines = 10;
    FILE *file;
    if(strcmp(argv[1], "-n") == 0){
        if(!isdigit(argv[2])){
            fprintf(stderr, "number of lines: '%s'", argv[2]);
            exit(1);
        }
        lines = atoi(argv[2]);
        if(lines == 0){
            exit(0);
        }
    }
    printf("%d\n", lines);
    cbuf* cbuffer = cbuf_create(2);
    for(int i=0; i<2; i++){
        cbuffer->buffer[i].c[0] = 'b';
        printf("%s\n", cbuffer->buffer[i].c);
    }
    int value = 1001;
    /*while (put (value ++));
    while (get (& value))
        printf ("read %d\n", value);*/
    return 0;
}