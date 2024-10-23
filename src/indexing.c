#include <stdio.h>
#include <stdlib.h>
#include "indexing.h"
#include "parser.h"

// int create_product_index(const char *file_name, const char *index_name, int by_price)
// {

//     FILE *file = fopen(file_name, "rb");
//     if (file == NULL)
//         return;

//     FILE *index_file = fopen(index_name, "wb");
//     if (index_file == NULL)
//         return;

//     ProductEntry entry;
//     IndexEntry index_entry;
//     long offset = 0;

//     while (fread(&entry, sizeof(ProductEntry), 1, file) == 1)
//     {
//         index_entry.offset = offset;

//         if (by_price)
//         {
//             index_entry.key = (int)entry.price;
//         }
//         else
//         {
//             index_entry.key = entry.product_id;
//         }

//         fwrite(&index_entry, sizeof(IndexEntry), 1, index_file);
//         offset += sizeof(ProductEntry);
//     }

//     fclose(file);
//     fclose(index_file);
// }

void generate_index(FILE *source_file, const char *index_name, int record_size, int (*get_key)(int *))
{
    FILE *index_file = fopen(index_name, "wb");
    if (index_file == NULL)
        return;

    int *record = malloc(record_size);
    if (record == NULL)
        return;

    IndexEntry index_entry;
    long offset = 0;

    while (fread(record, record_size, 1, source_file) == 1)
    {
        index_entry.key = get_key(record);
        index_entry.offset = offset;

        fwrite(&index_entry, sizeof(IndexEntry), 1, index_file);
        offset += record_size;
    }

    free(record);
    fclose(index_file);
}

// Product

void generate_product_id_index(FILE *source_file)
{
    FILE *index_file = fopen("output/indexes/product_id_index.bin", "wb");
    if (index_file == NULL)
        return;

    ProductEntry product;
    IndexEntry index_entry;
    long offset = 0;

    while (fread(&product, sizeof(ProductEntry), 1, source_file) == 1)
    {
        index_entry.key = product.product_id;
        index_entry.offset = offset;
        fwrite(&index_entry, sizeof(IndexEntry), 1, index_file);
        offset += sizeof(ProductEntry);
    }

    fclose(index_file);
}

void generate_product_price_index(FILE *source_file)
{
    FILE *index_file = fopen("output/indexes/product_price_index.bin", "wb");
    if (index_file == NULL)
        return;

    ProductEntry product;
    IndexEntry index_entry;
    long offset = 0;

    while (fread(&product, sizeof(ProductEntry), 1, source_file) == 1)
    {
        index_entry.key = (int)product.price;
        index_entry.offset = offset;
        fwrite(&index_entry, sizeof(IndexEntry), 1, index_file);
        offset += sizeof(ProductEntry);
    }

    fclose(index_file);
}

// Category
void generate_category_id_index(FILE *source_file)
{
    FILE *index_file = fopen("output/indexes/category_id_index.bin", "wb");
    if (index_file == NULL)
        return;

    CategoryEntry category;
    IndexEntry index_entry;
    long offset = 0;

    while (fread(&category, sizeof(CategoryEntry), 1, source_file) == 1)
    {
        index_entry.key = category.category_id;
        index_entry.offset = offset;
        fwrite(&index_entry, sizeof(IndexEntry), 1, index_file);
        offset += sizeof(CategoryEntry);
    }

    fclose(index_file);
}

void generate_category_code_index(FILE *source_file)
{
    FILE *index_file = fopen("output/indexes/category_code_index.bin", "wb");
    if (index_file == NULL)
        return;

    CategoryEntry category;
    IndexEntry index_entry;
    long offset = 0;

    while (fread(&category, sizeof(CategoryEntry), 1, source_file) == 1)
    {
        index_entry.key = atoi(category.category_code);
        index_entry.offset = offset;
        fwrite(&index_entry, sizeof(IndexEntry), 1, index_file);
        offset += sizeof(CategoryEntry);
    }

    fclose(index_file);
}

// Sessions
void generate_session_user_id_index(FILE *source_file)
{
    FILE *index_file = fopen("output/indexes/session_user_id_index.bin", "wb");
    if (index_file == NULL)
        return;

    SessionEntry session;
    IndexEntry index_entry;
    long offset = 0;

    while (fread(&session, sizeof(SessionEntry), 1, source_file) == 1)
    {
        index_entry.key = session.user_id;
        index_entry.offset = offset;
        fwrite(&index_entry, sizeof(IndexEntry), 1, index_file);
        offset += sizeof(SessionEntry);
    }

    fclose(index_file);
}

void generate_session_user_session_index(FILE *source_file)
{
    FILE *index_file = fopen("output/indexes/session_user_session_index.bin", "wb");
    if (index_file == NULL)
        return;

    SessionEntry session;
    IndexEntry index_entry;
    long offset = 0;

    while (fread(&session, sizeof(SessionEntry), 1, source_file) == 1)
    {
        index_entry.key = atoi(session.user_session);
        index_entry.offset = offset;
        fwrite(&index_entry, sizeof(IndexEntry), 1, index_file);
        offset += sizeof(SessionEntry);
    }

    fclose(index_file);
}