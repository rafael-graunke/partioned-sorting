#include <stdio.h>
#include <stdlib.h>
#include "searching.h"


long binsearch_in_file(FILE *source, size_t __size, int start, int end, void *match, int *pos, __compar_fn_t __compare)
{
    int middle;
    void *cursor = malloc(__size);

    printf("start: %ld\t end: %ld\n", start*__size, end*__size);

    if (start < end)
    {
        middle = (end + start) / 2;
        fseek(source, __size * middle, SEEK_SET);
        fread(cursor, __size, 1, source);

        printf("%lld\n", ((NumericIndexEntry *)cursor)->key);
        *pos = middle;

        int cmp = __compare(match, cursor);

        printf("COMPARE: %d\n", cmp);
        if (cmp == 0)
        {
            printf("ACHOU %.8lx\n", ftell(source) - __size);
            return ftell(source) - __size;
        }

        else if (cmp < 0)
            return binsearch_in_file(source, __size, start, middle - 1, match, pos, __compare);
        else
            return binsearch_in_file(source, __size, middle + 1, end, match, pos, __compare);
    }

    return -1; 
}
