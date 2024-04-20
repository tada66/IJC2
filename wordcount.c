#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
#include "io.h"
#include "htab.h"
#include <time.h>

#define HASH_TABLE_SIZE 16
#define MAX_WORD_LENGTH 256 //255+1 for \0


int main(){
    htab_t *t = htab_init(HASH_TABLE_SIZE);
    char *c = malloc(sizeof(char) * MAX_WORD_LENGTH);
    if(c = NULL){
        fprintf(stderr, "Failed to allocate memory!\n");
        exit(1);
    }
    

    return 0;
}