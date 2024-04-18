#include "htab.h"
#include "htab_t.h"

#include <stdio.h>

htab_t *htab_init(const size_t n){
    htab_t *tab = malloc(sizeof(htab_t));
    if(tab == NULL){
        fprintf(stderr, "Failed to allocate memory!\n");
    }
    tab->size = 0;
    tab->arr_size = n;
    tab->arr_ptr = calloc(n, sizeof(htab_itm_t*));
    if(tab->arr_ptr == NULL){
        fprintf(stderr, "Failed to allocate memory!\n");
    }
    return tab;
}