#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "partitioning.h"
#include "intercalation.h"

#define MAX_FILES 5

FILE *get_partition_file(int num_partition, char *mode)
{
    char buffer[35];
    sprintf(buffer, "output/partitions/partition_%d.bin", num_partition);
    return fopen(buffer, mode);
}

bool all_closed(bool *closed)
{
    for (int i = 0; i < MAX_FILES; i++)
        if (closed[i] == false)
            return false;

    return true;
}

int merge_files(int num_partitions, size_t __size, __min_fn_t __min)
{
    int first_partition = 0;
    int last_partition = num_partitions;
    FILE **files = (FILE **)malloc(sizeof(FILE *) * MAX_FILES);
    ProductEntry *top_records = malloc(__size * MAX_FILES);

    while (first_partition < last_partition)
    {
        FILE *output = get_partition_file(++last_partition, "wb");

        for (int i = first_partition; i < MAX_FILES + first_partition; i++)
        {
            files[i] = get_partition_file(i + 1, "rb");
            fread(&(top_records[i]), __size, 1, files[i]);
        }

        int index;
        while ((index = __min(top_records, files, MAX_FILES)) != -1)
        {
            fwrite(&(top_records[index]), __size, 1, output);
            int count = fread(&(top_records[index]), __size, 1, files[index]);
            if (count == 0)
            {
                fclose(files[index]);
                files[index] = NULL;
            }
        }
        fclose(output);
        first_partition += MAX_FILES;
    }

    return EXIT_SUCCESS;
};