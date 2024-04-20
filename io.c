#include <stdio.h>
#include <ctype.h> //isspace()


int read_word(char *s, int max, FILE *f){
    int c = 0;
    int i = 0;
    while((c = fgetc(f)) != EOF){
        if(!isspace(c) && i<max-1){
            s[i] = c;
            i++;
        }
        else{
            if(i!=0)
                break;
        }
    }
    s[i+1] = '\0';
    if(c==EOF && i==0)
        return EOF;
    else
        return i;
}