#include "htab.h"
#include "htab_t.h"

#include <stdio.h>

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key){
    htab_pair_t *pair = htab_find(t, key);
    if(pair!=NULL)
        return pair;
    else{
        size_t hash = htab_hash_function(key);
        int index = hash % t->arr_size;
        htab_itm_t *itm = t->arr_ptr[index];
        while(itm->next!=NULL){
            itm=itm->next;
        }
        htab_itm_t *newitm = malloc(sizeof(htab_itm_t));
        if(newitm==NULL){
            fprintf(stderr, "Memory allocation failed!\n");
            exit(1);
        }
        itm->next=newitm;
        newitm->next=NULL;
        newitm->pair.key=key;
        newitm->pair.value=0;
        return newitm;
    }
}