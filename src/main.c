#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "partitioning.h"
#include "intercalation.h"
#include "indexing.h"

int cmp_categories(const void *arg1, const void *arg2)
{
    return ((CategoryEntry *)arg1)->category_id - ((CategoryEntry *)arg2)->category_id;
}

int cmp_products(const void *arg1, const void *arg2)
{
    return ((ProductEntry *)arg1)->product_id - ((ProductEntry *)arg2)->product_id;
}

int cmp_session(const void *arg1, const void *arg2)
{
    return strcmp(((SessionEntry *)arg1)->user_session, ((SessionEntry *)arg2)->user_session);
}

void generate_docs(void)
{

    // 1 - Convert the CSV File for smaller binary files
    FILE *file = fopen("input/dataset.csv", "r");
    generate_tables(file);

    // 2 - Generate Partitions and Merge Files

    // Products
    printf("Sorting products table...\n");

    FILE *source = fopen("output/products.bin", "rb");
    int num_product_partitions = partition(source, sizeof(ProductEntry), cmp_products);
    int last_product_partition = merge_product_files(num_product_partitions);

    merge_product_final_files(num_product_partitions, last_product_partition);
    delete_partition(last_product_partition);
    fclose(source);

    printf("Done.\n");

    // //Categories
    printf("Sorting categories table...\n");

    source = fopen("output/categories.bin", "rb");
    int num_category_partitions = partition(source, sizeof(CategoryEntry), cmp_categories);
    int last_category_partition = merge_category_files(num_category_partitions);

    merge_category_final_files(num_category_partitions, last_category_partition);
    delete_partition(last_category_partition);
    fclose(source);

    printf("Done.\n");

    // Sessions
    printf("Sorting sessions table...\n");

    source = fopen("output/sessions.bin", "rb");
    int num_session_partitions = partition(source, sizeof(SessionEntry), cmp_session);
    int last_session_partition = merge_session_files(num_session_partitions);

    merge_session_final_files(num_session_partitions, last_session_partition);
    delete_partition(last_session_partition);
    fclose(source);

    printf("Done.\n");
}

void generate_indexes(void)
{
    printf("Creating indexes...\n");

    create_product_index();  // Product
    create_category_index(); // Category
    create_session_index();  // Session

    printf("Done.\n");
}

void menu_insertion(void) {}
void menu_exclude(void) {}
void menu_search(void) {}

int menu(void)
{
    int option = -1;

    while (option != 0)
    {
        printf("1 - Gerar tabelas e ordenar\n");
        printf("2 - Inserir dados\n");
        printf("3 - Remover dados\n");
        printf("4 - Procurar dados\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao:\n");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            generate_docs();
            break;

        case 2:
            menu_insertion();
            break;

        case 3:
            menu_exclude();
            break;

        case 4:
            menu_search();
            break;

        case 0:
            generate_indexes();
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid option.\n");
            break;
        }
    }
}

int main(void)
{
    menu();
    return EXIT_SUCCESS;
}
