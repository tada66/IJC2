//2. Příklad - htab_clear.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include "htab.h"
#include "htab_t.h"

//Deletes all entries in hash table
void htab_clear(htab_t * t){
    htab_itm_t *previtm = NULL;
    for(size_t i=0; i<t->arr_size; i++){
        htab_itm_t *itm = t->arr_ptr[i];
        while(itm!=NULL){
            previtm=itm;
            itm=itm->next;
            free((char *)previtm->pair.key);    //is set to const char*, need to cast away constness
            free(previtm);
        }
        t->arr_ptr[i]=NULL;
    }
}