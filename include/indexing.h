#ifndef _INDEXING_H_
#define _INDEXING_H_

#include <stdio.h>
#include "parser.h"

typedef struct num_index_entry_s {
    unsigned long long key;
    long address;
} NumericIndexEntry;

typedef struct str_index_entry_s {
    char key[EVENT_USER_SESSION_SIZE];
    long address;
    unsigned long long offset;
} StringIndexEntry;


void create_product_index(void);
void create_category_index(void);
void create_session_index(void);

#endif