#include <stdio.h>
#include <ctype.h> //isspace()


int read_word(char *s, int max, FILE *f){
    int c = 0;
    int i = 0;
    while((c = fgetc(f)) != EOF){
        if(!isspace(c) && i<max)
            s[i] = c;
        else
            break;
        i++;
    }
    if(c==EOF)
        return EOF;
    else
        return i;
}