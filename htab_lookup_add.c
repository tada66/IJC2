#include "htab.h"
#include "htab_t.h"

#include <stdio.h>

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key){
    htab_pair_t *pair = htab_find(t, key);
    if(pair!=NULL)
        return pair;
    else{
        size_t hash = htab_hash_function(key);
        size_t index = hash % t->arr_size;
        htab_itm_t *itm = t->arr_ptr[index];
        if(itm!=NULL){
            while(itm->next!=NULL){
                itm=itm->next;
            }
        }
        htab_itm_t *newitm = malloc(sizeof(htab_itm_t));
        if(newitm==NULL){
            fprintf(stderr, "Memory allocation failed!\n");
            exit(1);
        }
        if(itm==NULL)
            t->arr_ptr[index] = newitm;
        else
            itm->next = newitm;

        newitm->next=NULL;
        char *keyString = malloc(sizeof(char) * (strlen(key)+1));
        if(keyString==NULL){
            fprintf(stderr, "Memory allocation failed!\n");
            free(newitm);
            exit(1);
        }
        strcpy(keyString, key);
        newitm->pair.key=keyString;
        newitm->pair.value=1;
        t->size++;
        return &newitm->pair;
    }
}