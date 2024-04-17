#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 2048
typedef struct { char c[MAX_LINE_LENGTH]; } LINE;  //Maximum length of a single line 2047 + 1 for \0

typedef struct{
LINE* buffer;
int writeIndex;
int readIndex;
int bufferSize;
} cbuf;

cbuf* cbuf_create(int n){
    cbuf* cbuf = malloc(sizeof(*cbuf));
    if(cbuf==NULL){
        fprintf(stderr, "Failed to allocate memory!\n");
        exit(1);
    }
    cbuf->bufferSize=n;
    cbuf->readIndex=0;
    cbuf->writeIndex=0;
    cbuf->buffer = malloc(sizeof(LINE)*n);
    if(cbuf->buffer==NULL){
        fprintf(stderr, "Failed to allocate memory!\n");
        exit(1);
    }
    for(int i=0; i<n; i++)
        memset(cbuf->buffer[i].c, 0, sizeof(LINE));
    return cbuf;
}

int isnumber(char* arg){
    int i = 0; 
    while (arg[i]!='\0'){
        if(!isdigit(arg[i]))
            return 0;
        i++;
    }
    return 1;
}

void cbuf_put (cbuf* cbuffer, char* line) 
{
    memset(cbuffer->buffer[cbuffer->writeIndex].c, 0, sizeof(LINE));
    int i = 0;
    while(line[i]!='\0' && i<2047){
        cbuffer->buffer[cbuffer->writeIndex].c[i]=line[i];
        i++;
    }
    cbuffer->buffer[cbuffer->writeIndex].c[2047]='\0';
    cbuffer->writeIndex = (cbuffer->writeIndex + 1) % cbuffer->bufferSize;
    cbuffer->readIndex = (cbuffer->readIndex + 1) % cbuffer->bufferSize;
}

LINE cbuf_get(cbuf* cbuffer){
    LINE line = cbuffer->buffer[cbuffer->readIndex];
    cbuffer->readIndex = (cbuffer->readIndex + 1) % cbuffer->bufferSize;
    return line;
}

void cbuf_free(cbuf* cbuffer){
    free(cbuffer->buffer);
    free(cbuffer);
}

int main (int argc, char** argv)
{
    int lines = 10;
    FILE *file = stdin;
    if(argc > 4){
        fprintf(stderr, "Too many arguments!\n");
        exit(1);
    }
    if(argc > 2 && strcmp(argv[1], "-n") == 0){
        if(!isnumber(argv[2])){
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


    cbuf *cbuffer = cbuf_create(lines);
    char *gline = NULL;
    size_t glinecount = 0;
    
    while (getline(&gline, &glinecount, file) != -1) {
        gline[strcspn(gline, "\n")] = '\0';
        if(glinecount>MAX_LINE_LENGTH-1)
            gline[MAX_LINE_LENGTH-1]='\0';
        cbuf_put(cbuffer, gline);
    }
    free(gline);
    fclose(file);

    LINE line;

    for(int i=0; i<lines-1; i++){
        if(i<cbuffer->bufferSize){
            line = cbuf_get(cbuffer);
            if(line.c[0]!='\0')
                printf("%s\n", line.c);
        }
    }
    line = cbuf_get(cbuffer);
        if(line.c[0]!='\0')
            printf("%s", line.c);
    cbuf_free(cbuffer);
    return 0;
}