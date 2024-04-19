#include "htab.h"
#include "htab_t.h"

#include <stdio.h>

void htab_clear(htab_t * t){
    htab_itm_t *previtm = NULL;
    for(int i=0; i<t->arr_size; i++){
        htab_itm_t *itm = t->arr_ptr[i];
        while(itm!=NULL){
            previtm=itm;
            itm=itm->next;
            free((void *)previtm->pair.key);
            free(previtm);
        }
    }
}