#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct { char c[2048]; } LINE;  //Maximum length of a single line 2047 + 1 for \0

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
    int i = 0;
    while(line[i]!='\0' && i<2047){
        cbuffer->buffer[cbuffer->writeIndex].c[i]=line[i];
        i++;
    }
    cbuffer->buffer[cbuffer->writeIndex].c[2047]='\0';
    cbuffer->writeIndex = (cbuffer->writeIndex + 1) % cbuffer->bufferSize;
}

LINE cbuf_get(cbuf* cbuffer){
    LINE line = cbuffer->buffer[cbuffer->readIndex];
    cbuffer->readIndex = (cbuffer->readIndex + 1) % cbuffer->bufferSize;
    return line;
}

int main (int argc, char** argv)
{
    int lines = 10;
    FILE *file;
    if(strcmp(argv[1], "-n") == 0){
        if(!isdigit(*argv[2])){
            fprintf(stderr, "number of lines: '%s'\n", argv[2]);
            exit(1);
        }
        lines = atoi(argv[2]);
        if(lines == 0){
            exit(0);
        }
        if(argc=3)
            file = stdin;
    }
    printf("cbuffer size=%d\n", lines);
    cbuf* cbuffer = cbuf_create(lines);
    cbuf_put(cbuffer, "aaahhh");
    cbuf_put(cbuffer, "aaa");
    cbuf_put(cbuffer, "hhh");
    cbuf_put(cbuffer, "bing bong");
    for(int i=0; i<cbuffer->bufferSize; i++)
        printf("%s\n", cbuf_get(cbuffer).c);
    int value = 1001;
    /*while (put (value ++));
    while (get (& value))
        printf ("read %d\n", value);*/
    return 0;
}