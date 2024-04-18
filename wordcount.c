#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
#include "htab.h"
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

#define HASH_TABLE_SIZE 16


int main(){
    htab_t *t = htab_init(HASH_TABLE_SIZE);
    printf("Size: %ld, Arr size: %ld\n", htab_size(t), htab_bucket_count(t));
    htab_pair_t *p = htab_lookup_add(t, "bing bong");
    printf("htab added key: %s\n", p->key);
    printf("Size: %ld, Arr size: %ld\n", htab_size(t), htab_bucket_count(t));
    if(htab_erase(t, "bing bong"));
        printf("successful erase of bing bong\n");
    printf("Size: %ld, Arr size: %ld\n", htab_size(t), htab_bucket_count(t));
    htab_free(t);

    return 0;
}