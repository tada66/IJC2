//2. Příklad - io.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include <stdio.h>
#include <ctype.h> //isspace()
#include <stdio.h>
#include <stdbool.h>

bool displayederror = false;    //Sets to true after error is shown the first time 

int read_word(char *s, int max, FILE *f){
    int c = 0; //loaded char from file
    int i = 0;
    bool overflow = 0;
    while((c = fgetc(f)) != EOF){
        if(!isspace(c)){
            if(i<max-1){
                s[i] = c;   //Load until we fill up the buffer
                i++;
            }
            else
                overflow = 1;   //If there still hasn't been a space => word is longer than max and we should display error
        }
        else{
            if(i!=0)
                break;  //Ignore leading spaces
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