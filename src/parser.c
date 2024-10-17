#include <stdlib.h>
#include <string.h>
#include "parser.h"

int generate_tables(FILE *source)
{
    FILE *categories = fopen("output/categories.bin", "wb");
    FILE *products = fopen("output/products.bin", "wb");
    FILE *sessions = fopen("output/sessions.bin", "wb");

    // breaks the openin of files if it fails
    if (categories == NULL || products == NULL || sessions == NULL)
        return EXIT_FAILURE;

    CategoryEntry category_buffer;
    ProductEntry product_buffer;
    SessionEntry session_buffer;
    char line_buffer[512];
    fgets(line_buffer, 512, source); // skip first line

    while (fgets(line_buffer, 512, source) != NULL)
    {
        sscanf(line_buffer, "%[^,],%[^,],%d,%lld,%[^,],%[^,], %f, %d, %[^,]",
               session_buffer.event_time,
               session_buffer.event_type,
               &product_buffer.product_id,
               &category_buffer.category_id,
               category_buffer.category_code,
               product_buffer.brand,
               &product_buffer.price,
               &session_buffer.user_id,
               session_buffer.user_session);

        fwrite(&category_buffer, sizeof(CategoryEntry), 1, categories);
        fwrite(&product_buffer, sizeof(ProductEntry), 1, products);
        fwrite(&session_buffer, sizeof(SessionEntry), 1, sessions);

        //Reset the buffer to avoid overwrite
        memset(&category_buffer, 0, sizeof(category_buffer));
        memset(&product_buffer, 0, sizeof(product_buffer));
        memset(&session_buffer, 0, sizeof(session_buffer));
    }

    fclose(categories);
    fclose(products);
    fclose(sessions);
}


