//2. Příklad - htab_size.c
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include "htab.h"
#include "htab_t.h"

size_t htab_size(const htab_t * t){
    return t->size;
}