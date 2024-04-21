//1. Příklad - tail.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#define  _POSIX_C_SOURCE 200809L    //needed to avoid -Wimplicit-function-declaration from getline
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

//Checks if a string is a number
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
    int i = 0;
    while(line[i]!='\0' && i<MAX_LINE_LENGTH-1){
        cbuffer->buffer[cbuffer->writeIndex].c[i]=line[i];  //write until we reach \0, or max char count-1, to guarantee the last char is \0
        i++;
    }
    for(int j=i; j<MAX_LINE_LENGTH; j++)
        cbuffer->buffer[cbuffer->writeIndex].c[j]='\0';     //if we haven't filled the whole line, set the rest to \0
    cbuffer->writeIndex = (cbuffer->writeIndex + 1) % cbuffer->bufferSize; //increment index by one, if index>size -> index=0
    cbuffer->readIndex = (cbuffer->readIndex + 1) % cbuffer->bufferSize;   //we also move readIndex so that in the end we can start reading from the last changed line
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
    int lines = 10;     //By default return last 10 lines and read from stdin
    FILE *file = stdin;

    if(argc > 4){
        fprintf(stderr, "Too many arguments!\n");   //max 4 arguments (./tail -n number file.txt)
        exit(1);
    }
    if(argc > 2 && strcmp(argv[1], "-n") == 0){
        if(!isnumber(argv[2])){                 //check that number of lines is actually a number, this will filter out negative numbers as well
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
    char *gline = NULL; //Loaded line
    size_t glinecount = 0;  //Amount of characters read
    int truncated = 0;      //Keeps track of whether we have shown the 'line too long' error already
    
    while (getline(&gline, &glinecount, file) != -1) {  //Read lines from file, until we reach the end
        if(glinecount>MAX_LINE_LENGTH){
            if(!truncated){
                if(gline[MAX_LINE_LENGTH-1]!=0 && gline[MAX_LINE_LENGTH-1]!=10 && gline[MAX_LINE_LENGTH-1]!=13){    //If not NUL, LF or CR, we still haven't reached the end of line, truncating
                    truncated=1;
                    fprintf(stderr, "Line longer than 2047 characters detected!\n");
                }
            }
        }
        cbuf_put(cbuffer, gline);  
    }
    free(gline);
    fclose(file);
    
    LINE line;
        
    for(int i=0; i<lines; i++){
        if(i<cbuffer->bufferSize){
            line = cbuf_get(cbuffer);
            if(line.c[0]!='\0'){
                printf("%s", line.c);
                if(strstr(line.c, "\n") == NULL && i!=lines-1)//if \n got cut off due to a line being too long we need to insert it back again
                    printf("\n");                               //Also do NOT print newline on last line
            }
        }
    }
    cbuf_free(cbuffer);
    return 0;
}