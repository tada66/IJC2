#include "htab.h"
#include "htab_t.h"

#include <limits.h>
#include <stdio.h>

void htab_statistics(const htab_t * t){
    int min = INT_MAX;
    int max = INT_MIN;

    int count = 0;
    double total = 0.0;
    for(int i=0; i<t->arr_size; i++){
        htab_itm_t *itm = t->arr_ptr[i];
        while(itm!=NULL){
            itm=itm->next;
            count++;
        }
        fprintf(stderr, "Index %d: %d\n", i, count);
        if(count>max)
            max=count;
        if(count<min)
            min=count;
        total += count;
        count=0;
    }
    fprintf(stderr, "Min: %d, Max: %d, Avg: %f\n", min, max, total/t->arr_size);
}