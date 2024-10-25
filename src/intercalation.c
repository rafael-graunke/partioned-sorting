#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

FILE *get_merged_file(int num_partition, char *mode)
{
    char buffer[35];
    sprintf(buffer, "output/partitions/merged_%d.bin", num_partition);
    return fopen(buffer, mode);
}

void delete_partition(int last_partition)
{
    char buffer[35];
    for (int i = 1; i <= last_partition; i++)
    {
        sprintf(buffer, "output/partitions/partition_%d.bin", i);
        remove(buffer);
    }
}

// MERGING PRODUCT PARTITIONS
int min_products(ProductEntry *products, FILE **files, int n)
{
    int index = -1;
    ProductEntry min;
    for (int i = 0; i < n; i++)
        if (files[i] != NULL)
        {
            min = ((ProductEntry *)products)[i];
            index = i;
            break;
        }

    for (int i = 0; i < n; i++)
    {
        if (files[i] != NULL && ((ProductEntry *)products)[i].product_id < min.product_id)
        {
            index = i;
            min = ((ProductEntry *)products)[i];
        }
    }

    return index;
}

int merge_product_files(int num_partitions)
{
    int first_partition = 0;
    int last_partition = num_partitions;
    FILE **files = (FILE **)malloc(sizeof(FILE *) * MAX_FILES);
    ProductEntry *top_records = (ProductEntry *)malloc(sizeof(ProductEntry) * MAX_FILES);

    ProductEntry last_written;
    bool first_write = true;

    while (first_partition < last_partition)
    {
        FILE *output = get_partition_file(++last_partition, "wb");

        for (int i = first_partition; i < MAX_FILES + first_partition && i < last_partition; i++)
        {
            int idx = i - first_partition;
            files[idx] = get_partition_file(i + 1, "rb");
            if (files[idx] == NULL)
            {
                continue;
            }
            fread(&(top_records[idx]), sizeof(ProductEntry), 1, files[idx]);
        }

        int index;
        while ((index = min_products(top_records, files, MAX_FILES)) != -1)
        {
            if (first_write || top_records[index].product_id != last_written.product_id)
            {
                fwrite(&(top_records[index]), sizeof(ProductEntry), 1, output);
                last_written = top_records[index];
                first_write = false;
            }

            int count = fread(&(top_records[index]), sizeof(ProductEntry), 1, files[index]);
            if (count == 0)
            {
                fclose(files[index]);
                files[index] = NULL;
            }
        }

        fclose(output);
        first_partition += MAX_FILES;
    }

    free(files);
    free(top_records);

    return last_partition;
}

// MERGING CATEGORIES PARTITIONS

int min_categories(CategoryEntry *categories, FILE **files, int n)
{
    int index = -1;
    CategoryEntry min;
    for (int i = 0; i < n; i++)
        if (files[i] != NULL)
        {
            min = ((CategoryEntry *)categories)[i];
            index = i;
            break;
        }

    for (int i = 0; i < n; i++)
    {
        if (files[i] != NULL && ((CategoryEntry *)categories)[i].category_id < min.category_id)
        {
            index = i;
            min = ((CategoryEntry *)categories)[i];
        }
    }

    return index;
}

int merge_category_files(int num_partitions)
{
    int first_partition = 0;
    int last_partition = num_partitions;
    FILE **files = (FILE **)malloc(sizeof(FILE *) * MAX_FILES);
    CategoryEntry *top_records = (CategoryEntry *)malloc(sizeof(CategoryEntry) * MAX_FILES);

    CategoryEntry last_written;
    bool first_write = true;

    while (first_partition < last_partition)
    {
        FILE *output = get_partition_file(++last_partition, "wb");

        for (int i = first_partition; i < MAX_FILES + first_partition && i < last_partition; i++)
        {
            int idx = i - first_partition;
            files[idx] = get_partition_file(i + 1, "rb");
            if (files[idx] == NULL)
            {
                continue;
            }
            fread(&(top_records[idx]), sizeof(CategoryEntry), 1, files[idx]);
        }

        int index;
        while ((index = min_categories(top_records, files, MAX_FILES)) != -1)
        {
            if (first_write || top_records[index].category_id != last_written.category_id)
            {
                fwrite(&(top_records[index]), sizeof(CategoryEntry), 1, output);
                last_written = top_records[index];
                first_write = false;
            }

            int count = fread(&(top_records[index]), sizeof(CategoryEntry), 1, files[index]);
            if (count == 0)
            {
                fclose(files[index]);
                files[index] = NULL;
            }
        }

        fclose(output);
        first_partition += MAX_FILES;
    }

    free(files);
    free(top_records);

    return last_partition;
}


// MERGING SESSION PARTITIONS
int min_session(SessionEntry *sessions, FILE **files, int n)
{
    int index = -1;
    SessionEntry min;
    for (int i = 0; i < n; i++)
        if (files[i] != NULL)
        {
            min = sessions[i];
            index = i;
            break;
        }

    for (int i = 0; i < n; i++)
    {
    
        if (files[i] != NULL && strcmp(sessions[i].user_session, min.user_session) < 0 )
        {
            index = i;
            min = sessions[i];
        }
    }

    return index;
    
}

int merge_session_files(int num_partitions)
{
    int first_partition = 0;
    int last_partition = num_partitions;
    FILE **files = (FILE **)malloc(sizeof(FILE *) * MAX_FILES);
    SessionEntry *top_records = (SessionEntry *)malloc(sizeof(SessionEntry) * MAX_FILES);

    SessionEntry last_written;
    bool first_write = true;

    while (first_partition < last_partition)
    {
        FILE *output = get_partition_file(++last_partition, "wb");

        for (int i = first_partition; i < MAX_FILES + first_partition && i < last_partition; i++)
        {
            int idx = i - first_partition;
            files[idx] = get_partition_file(i + 1, "rb");
            if (files[idx] == NULL)
            {
                continue;
            }
            fread(&(top_records[idx]), sizeof(SessionEntry), 1, files[idx]);
        }

        int index;
        while ((index = min_session(top_records, files, MAX_FILES)) != -1)
        {
            if (first_write || !(strcmp(top_records[index].user_session, last_written.user_session) == 0))
            {
                fwrite(&(top_records[index]), sizeof(SessionEntry), 1, output);
                last_written = top_records[index];
                first_write = false;
            }

            int count = fread(&(top_records[index]), sizeof(SessionEntry), 1, files[index]);
            if (count == 0)
            {
                fclose(files[index]);
                files[index] = NULL;
            }
        }

        fclose(output);
        first_partition += MAX_FILES;
    }

    free(files);
    free(top_records);

    return last_partition;
}