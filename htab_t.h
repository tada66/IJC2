//2. Příklad - htab_t.h
//Tadeáš Horák xhorakt00
//VUT FIT
//20.04.2024

#include "htab.h"
#include "htab_itm_t.h"
#include <stdlib.h>

#ifndef __HTAB_T__
#define __HTAB_T__

typedef struct htab {
    size_t size;
    size_t arr_size;
    struct htab_itm **arr_ptr;
} htab_t;

#endif //__HTAB_T__