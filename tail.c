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
    FILE *file = stdin;
    if(argc > 2 && strcmp(argv[1], "-n") == 0){
        if(!isdigit(*argv[2])){
            fprintf(stderr, "Invalid value for argument -n\n");
            exit(1);
        }
        lines = atoi(argv[2]);
        if(lines == 0){
            exit(0);
        }
        if(argc == 4)
            file = fopen(argv[3], "r");
    }
    else if (argc == 2)
        file = fopen(argv[1], "r");
        
    if(file==NULL){
        fprintf(stderr, "Failed to open file!\n");
        exit(1);
    }
    printf("cbuffer size=%d\n", lines);
    cbuf* cbuffer = cbuf_create(lines); 
    int value = 1001;
    /*while (put (value ++));
    while (get (& value))
        printf ("read %d\n", value);*/
    return 0;
}