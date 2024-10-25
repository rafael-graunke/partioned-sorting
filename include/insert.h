#ifndef _INSERT_H_
#define _INSERT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "searching.h"


void insert_product(ProductEntry new_record, __compar_fn_t __compare);
void insert_cateogy(CategoryEntry new_record, __compar_fn_t __compare);
// void insert_session(SessionEntry new_record);   n sei se faz muito sentido


#endif