#ifndef _PARTITIONING_H_
#define _PARTITIONING_H_

#include "parser.h"

int partition(FILE *source, size_t __size, __compar_fn_t __compare);

#endif