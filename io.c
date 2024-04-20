//2. Příklad - io.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include <stdio.h>
#include <ctype.h> //isspace()
#include <stdio.h>
#include <stdbool.h>

bool displayederror = false;

int read_word(char *s, int max, FILE *f){
    int c = 0;
    int i = 0;
    bool overflow = 0;
    while((c = fgetc(f)) != EOF){
        if(!isspace(c)){
            if(i<max-1){
                s[i] = c;
                i++;
            }
            else
                overflow = 1;
        }
        else{
            if(i!=0)
                break;
        }
    }
    if(overflow && !displayederror){
        fprintf(stderr, "Detected word longer than max word length, truncating!\n");
        displayederror=true;
    }
    s[i+1] = '\0';
    if(c==EOF && i==0)
        return EOF;
    else
        return i;
}