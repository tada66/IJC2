#include "htab.h"
#include "htab_t.h"

bool htab_erase(htab_t * t, htab_key_t key){
    size_t hash = htab_hash_function(key);
    int index = hash % t->arr_size;
    htab_itm_t *previtm = NULL;
    htab_itm_t *itm = t->arr_ptr[index];
    while(itm!=NULL){
        if(!strcmp(key, itm->pair.key)){
            if(previtm==NULL)
                t->arr_ptr[index] = itm->next;
            else
                previtm->next = itm->next;
            free((void *)itm->pair.key);
            free(itm);
            t->size--;
            return true;
        }
        previtm=itm;
        itm=itm->next;
    }
    return false;
}