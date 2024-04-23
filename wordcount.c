//2. Příklad - wordcount.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "htab.h"

#define HASH_TABLE_SIZE 325001 // Czech has roughly 250k word, ideal hash table size should be 1.3x that and it should also be a prime number
#define MAX_WORD_LENGTH 256 //255+1 for \0

void print_count(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
}

int main(){
    htab_t *t = htab_init(HASH_TABLE_SIZE);
    char *word = malloc(sizeof(char) * MAX_WORD_LENGTH);
    if(word == NULL){
        fprintf(stderr, "Failed to allocate memory!\n");
        exit(1);
    }
    while (read_word(word, MAX_WORD_LENGTH, stdin)!=EOF)
    {
        if(word[0] == '\0') {
            continue;           //Empty line is not a word
        }
        htab_lookup_add(t, word);
        memset(word, 0, sizeof(char) * MAX_WORD_LENGTH);
    }
    htab_for_each(t, &print_count);
    htab_free(t);
    free(word);

    return 0;
}