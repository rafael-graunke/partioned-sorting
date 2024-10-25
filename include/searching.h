#ifndef _SEARCHING_H_
#define _SEARCHING_H_

#include <stdlib.h>
#include "indexing.h"
#include "parser.h"

long binsearch_in_file(FILE *source, size_t __size, int start, int end, void *match, int *pos, __compar_fn_t __compare);

#endif