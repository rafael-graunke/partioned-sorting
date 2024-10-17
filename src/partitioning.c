#include <stdio.h>
#include <stdlib.h>
#include "partitioning.h"

#define MEM_SIZE 1500000

int partition(FILE *source, size_t __size, __compar_fn_t __compare)
{
    int count, iter = 0;
    void *buffer = malloc(__size * MEM_SIZE);
    char file_name[35];

    while ((count = fread(buffer, __size, MEM_SIZE, source)))
    {
        iter++;
        qsort(buffer, count, __size, __compare);
        sprintf(file_name, "output/partitions/partition_%d.bin", iter);
        FILE *output = fopen(file_name, "wb");
        fwrite(buffer, __size, count, output);
    }
    
    free(buffer);
    return iter;
}
