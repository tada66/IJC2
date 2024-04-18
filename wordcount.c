#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "htab.h"
#include "htab_t.h"
#include "htab_init.c"


int main(){
    htab_t *t = htab_init(16);

    return 0;
}