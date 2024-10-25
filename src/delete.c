#include "delete.h"


void delete_product(unsigned long long key_to_delete){
    FILE *products_file = fopen("output/final_products.bin", "rb");
    FILE *index_file = fopen("output/indexes/index_products.bin", "rb");

    // long long offset = binsearch_in_file() //search the addres for the offset

    long long offset; // TODO: exclude this and uncomment the offset with binsearch when it's working
    if(offset != -1){

        fseek(products_file, offset, SEEK_SET);

        ProductEntry buffer;
        fread(&buffer, sizeof(ProductEntry), 1, products_file);

        buffer.deleted = 1; //Mark as delete

        fseek(products_file, offset, SEEK_SET);
        fwrite( &buffer, sizeof(ProductEntry), 1, products_file );
    }
    
    fclose(products_file);
    fclose(index_file);
}


void delete_category(unsigned long long key_to_delete){
    FILE *categories_file = fopen("output/final_categories.bin", "rb");
    FILE *index_file = fopen("output/indexes/index_categories.bin", "rb");

    // long long offset = binsearch_in_file() //search the addres for the offset

    long long offset; // TODO: exclude this and uncomment the offset with binsearch when it's working
    if(offset != -1){

        fseek(categories_file, offset, SEEK_SET);

        CategoryEntry buffer;
        fread(&buffer, sizeof(CategoryEntry), 1, categories_file);

        buffer.deleted = 1; //Mark as delete

        fseek(categories_file, offset, SEEK_SET);
        fwrite( &buffer, sizeof(CategoryEntry), 1, categories_file );
    }
    
    fclose(categories_file);
    fclose(index_file);
}


void delete_session(unsigned long long key_to_delete){
    FILE *sessions_file = fopen("output/final_sessions.bin", "rb");
    FILE *index_file = fopen("output/indexes/index_sessions.bin", "rb");

    // long long offset = binsearch_in_file() //search the addres for the offset

    long long offset; // TODO: exclude this and uncomment the offset with binsearch when it's working
    if(offset != -1){

        fseek(sessions_file, offset, SEEK_SET);

        SessionEntry buffer;
        fread(&buffer, sizeof(SessionEntry), 1, sessions_file);

        buffer.deleted = 1; //Mark as delete
        
        fseek(sessions_file, offset, SEEK_SET);
        fwrite( &buffer, sizeof(SessionEntry), 1, sessions_file );
    }
    
    fclose(sessions_file);
    fclose(index_file);
}



