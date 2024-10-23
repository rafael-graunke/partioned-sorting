#ifndef _INTERCALATION_H_
#define _INTERCALATION_H_

typedef struct
{
    int key;
    long offset;
} IndexEntry;

// Product
void generate_product_id_index(FILE *source_file);
void generate_product_price_index(FILE *source_file);

// Category
void generate_category_id_index(FILE *source_file);
void generate_category_code_index(FILE *source_file);

// Session
void generate_session_user_id_index(FILE *source_file);
void generate_session_user_session_index(FILE *source_file);

#endif