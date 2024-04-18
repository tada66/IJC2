#include "htab.h"
#ifndef __HTAB_ITM_T__
#define __HTAB_ITM_T__

typedef struct htab_itm {
    htab_pair_t pair;
    struct htab_itm *next;
} htab_itm_t;

#endif //__HTAB_ITM_T__