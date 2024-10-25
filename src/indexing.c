#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "indexing.h"

#define MAX_INDEX_SPAN 1000

void create_product_index(void)
{
    FILE *products_file = fopen("output/final_products.bin", "rb");
    FILE *output = fopen("output/index_products.bin", "wb");

    ProductEntry buffer;
    NumericIndexEntry index_entry;
    int record_count = 0;

    while (fread(&buffer, sizeof(ProductEntry), 1, products_file))
    {
        long long address = ftell(products_file) - sizeof(ProductEntry);

        if (record_count % MAX_INDEX_SPAN == 0)
        {
            index_entry.key = buffer.product_id;
            index_entry.address = address;

            fwrite(&index_entry, sizeof(NumericIndexEntry), 1, output);
        }
        record_count++;
    }

    fclose(products_file);
    fclose(output);
}

void create_category_index(void)
{
    FILE *categories_file = fopen("output/final_categories.bin", "rb");
    FILE *output = fopen("output/index_categories.bin", "wb");

    CategoryEntry buffer;
    NumericIndexEntry index_entry;
    int record_count = 0;

    while (fread(&buffer, sizeof(CategoryEntry), 1, categories_file))
    {
        long long address = ftell(categories_file) - sizeof(CategoryEntry);

        if (record_count % MAX_INDEX_SPAN == 0)
        {
            index_entry.key = buffer.category_id;
            index_entry.address = address;

            fwrite(&index_entry, sizeof(NumericIndexEntry), 1, output);
        }
        record_count++;
    }

    fclose(categories_file);
    fclose(output);
}

void create_session_index(void)
{
    FILE *sessions_file = fopen("output/final_sessions.bin", "rb");
    FILE *output = fopen("output/index_sessions.bin", "wb");

    SessionEntry buffer;
    StringIndexEntry index_entry;
    int record_count = 0;

    while (fread(&buffer, sizeof(SessionEntry), 1, sessions_file))
    {
        long long address = ftell(sessions_file) - sizeof(SessionEntry);

        if (record_count % MAX_INDEX_SPAN == 0)
        {
            strncpy(index_entry.key, buffer.user_session, EVENT_USER_SESSION_SIZE);
            index_entry.address = address;

            fwrite(&index_entry, sizeof(StringIndexEntry), 1, output);
        }
        record_count++;
    }

    fclose(sessions_file);
    fclose(output);
}
