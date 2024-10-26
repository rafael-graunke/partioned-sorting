#include "insert.h"

#define MAX_EXTENSION_AREA_SIZE 1000

void insert_product(ProductEntry new_record, __compar_fn_t __compare)
{
    FILE *data_file = fopen("output/final_products.bin", "rb");
    FILE *extension_file = fopen("output/extension_products.bin", "ab");

    // long insert_pos = binsearch_in_file(data_file, sizeof(ProductEntry), &new_record.product_id, __compare);

    fseek(extension_file, 0, SEEK_END);
    // fwrite(new_record, sizeof(ProductEntry), 1, extension_file);

    // fwrite(&new_record, sizeof(ProductEntry), 1, data_file);

    // if(extension_offset >= MAX_EXTENSION_AREA_SIZE){
    //     // reorganize_data_file(data_file);
    // }
}

// void reorganize_product_file(){

//     FILE *data_file = ("output/final_products.bin", "rb");
//     FILE *temp_file = ("output/temp_data_file.bin", "wb");

//     ProductEntry buffer;
//     fseek(data_file, 0, SEEK_SET);

//     while( fread(&buffer, sizeof(ProductEntry), 1, data_file)){
//         if(!buffer.deleted){
//             fwrite(&buffer, sizeof(ProductEntry), 1, temp_file);
//         }
//     }

//     fclose(data_file);
//     fclose(temp_file);

//     remove("output/final_products.bin");
//     rename("output/temp_data_file.bin", "output/final_products.bin");
// }