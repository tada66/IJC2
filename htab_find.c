//2. Příklad - htab_find.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include "htab.h"
#include "htab_t.h"

htab_pair_t *htab_find(const htab_t * t, htab_key_t key){
    size_t hash = htab_hash_function(key);
    int index = hash % t->arr_size;
    htab_itm_t *itm = t->arr_ptr[index];
    while(itm!=NULL){
        if(!strcmp(key, itm->pair.key))
            return &itm->pair;
        itm=itm->next;
    }
    return NULL;
}