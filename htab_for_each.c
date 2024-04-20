//2. Příklad - htab_for_each.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include "htab.h"
#include "htab_t.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)){
    for(size_t i = 0; i < t->arr_size; i++){
        htab_itm_t *itm = t->arr_ptr[i];
        while(itm != NULL) {
            f(&itm->pair);
            itm = itm->next;
        }
    }
}