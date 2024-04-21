//2. Příklad - htab_erase.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include "htab.h"
#include "htab_t.h"

//Erases one entry in hash table
bool htab_erase(htab_t * t, htab_key_t key){
    size_t hash = htab_hash_function(key);
    int index = hash % t->arr_size;
    htab_itm_t *previtm = NULL;
    htab_itm_t *itm = t->arr_ptr[index];

    while(itm!=NULL){
        if(!strcmp(key, itm->pair.key)){    //Search for the key
            if(previtm==NULL)
                t->arr_ptr[index] = itm->next;
            else
                previtm->next = itm->next;
            free((char *)itm->pair.key);    //is set to const char*, need to cast away constness
            free(itm);
            t->size--;
            return true;
        }
        previtm=itm;
        itm=itm->next;  //Advance to next item in list
    }
    return false;
}