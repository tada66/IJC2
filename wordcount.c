#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "htab.h"
#include "htab_t.h"
#include "htab_init.c"

#define HASH_TABLE_SIZE 16


int main(){
    htab_t *t = htab_init(HASH_TABLE_SIZE);

    return 0;
}