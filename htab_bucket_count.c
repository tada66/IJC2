//2. Příklad - htab_bucket_count.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include "htab.h"
#include "htab_t.h"

size_t htab_bucket_count(const htab_t * t){
    return t->arr_size;
}