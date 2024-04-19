#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
#include "htab.h"

#include <time.h>
#include "htab_t.h"
#include "htab_init.c"
#include "htab_find.c"
#include "htab_size.c"
#include "htab_erase.c"
#include "htab_bucket_count.c"
#include "htab_lookup_add.c"
#include "htab_hash_function.c"
#include "htab_clear.c"
#include "htab_free.c"
#include "htab_statistics.c"

#define HASH_TABLE_SIZE 16

char* generateRandomString(int length) {
    char* random_string = (char*)malloc((length + 1) * sizeof(char)); // Allocate memory for the string
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // Define the characters you want to include

    for (int i = 0; i < length; i++) {
        random_string[i] = charset[rand() % (sizeof(charset) - 1)];
    }

    random_string[length] = '\0'; // Null-terminate the string

    return random_string;
}

int main(){
    htab_t *t = htab_init(HASH_TABLE_SIZE);
    printf("Size: %ld, Arr size: %ld\n", htab_size(t), htab_bucket_count(t));
    htab_pair_t *p = htab_lookup_add(t, "bing bong");
    printf("htab added key: %s\n", p->key);
    printf("Size: %ld, Arr size: %ld\n", htab_size(t), htab_bucket_count(t));
    for(int i=0; i<255; i++){
        char *key = generateRandomString(4);
        htab_lookup_add(t, key);
        free(key);
    }
    htab_statistics(t);
    if(htab_erase(t, "bing bong"));
        printf("successful erase of bing bong\n");
    printf("Size: %ld, Arr size: %ld\n", htab_size(t), htab_bucket_count(t));
    htab_free(t);

    return 0;
}