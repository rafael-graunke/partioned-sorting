#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "partitioning.h"
#include "intercalation.h"
#include "indexing.h"
#include "searching.h"
#include "show.h"

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

int cmp_numeric_index(const void *id, const void *index)
{
    return *((int *)id) - ((NumericIndexEntry *)index)->key;
}

int cmp_string_index(const void *id, const void *index)
{
    return strncmp((char *)id, ((StringIndexEntry *)index)->key, EVENT_USER_SESSION_SIZE - 1);
}

int cmp_product_id(const void *id, const void *product)
{
    return *((int *)id) - ((ProductEntry *)product)->product_id;
}

int cmp_category_id(const void *id, const void *category)
{
    return *((int *)id) - ((CategoryEntry *)category)->category_id;
}

int cmp_user_session(const void *id, const void *session)
{
    return strncmp((char *)id, ((SessionEntry *)session)->user_session, EVENT_USER_SESSION_SIZE - 1);
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

    char buffer[256];
    sprintf(buffer, "output/partitions/partition_%d.bin", last_product_partition);
    rename(buffer, "output/final_products.bin");

    delete_partition(last_product_partition - 1);
    fclose(source);

    printf("Done.\n");

    // //Categories
    printf("Sorting categories table...\n");

    source = fopen("output/categories.bin", "rb");
    int num_category_partitions = partition(source, sizeof(CategoryEntry), cmp_categories);
    int last_category_partition = merge_category_files(num_category_partitions);

    sprintf(buffer, "output/partitions/partition_%d.bin", last_category_partition);
    rename(buffer, "output/final_categories.bin");

    delete_partition(last_category_partition - 1);
    fclose(source);

    printf("Done.\n");

    // Sessions
    printf("Sorting sessions table...\n");

    source = fopen("output/sessions.bin", "rb");
    int num_session_partitions = partition(source, sizeof(SessionEntry), cmp_session);
    int last_session_partition = merge_session_files(num_session_partitions);

    sprintf(buffer, "output/partitions/partition_%d.bin", last_session_partition);
    rename(buffer, "output/final_sessions.bin");

    delete_partition(last_session_partition - 1);
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

void menu_insertion(void)
{
    int option = -1;

    printf("1 - Inserir em Produtos \n");
    printf("2 - Inserir em Categorias\n");
    printf("3 - Inserir em Sessões\n");
    printf("4 - Retornar\n");
    printf("Escolha uma opcao:\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        // TODO: Insert products
        break;

    case 2:
        // TODO: Insert products
        break;

    case 3:
        // TODO: Insert products
        break;

    case 4:
        return;

    default:
        printf("Invalid option.\n");
        break;
    }
}

void menu_exclude(void)
{
    int option = -1;

    printf("1 - Excluir em Produtos \n");
    printf("2 - Excluir em Categorias\n");
    printf("3 - Excluir em Sessões\n");
    printf("4 - Retornar\n");
    printf("Escolha uma opcao:\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        // TODO: Exclude products
        break;

    case 2:
        // TODO: Exclude products
        break;

    case 3:
        // TODO: Exclude products
        break;

    case 4:
        return;

    default:
        printf("Invalid option.\n");
        break;
    }
}

void menu_search(void)
{
    int option = -1;

    printf("1 - Search em Produtos \n");
    printf("2 - Search em Categorias\n");
    printf("3 - Search em Sessões\n");
    printf("4 - Retornar\n");
    printf("Escolha uma opcao:\n");
    scanf("%d", &option);

    int end;
    int start;
    long record_address;
    int pos_index;
    FILE *f;
    NumericIndexEntry index1, index2;
    long address;

    switch (option)
    {
    case 1:
        long product_id;
        printf("Digite o 'product_id':\n");
        scanf("%ld", &product_id);

        printf("Searching for index...\n");

        f = fopen("output/index_products.bin", "rb");
        fseek(f, 0, SEEK_END);
        end = (ftell(f) / sizeof(NumericIndexEntry)) - 1;
        fseek(f, 0, SEEK_SET);

        address = binsearch_in_file(f, sizeof(NumericIndexEntry), 0, end, &product_id, &pos_index, cmp_numeric_index);
        if (address != -1)
        {
            printf("Record found!\n");
            show_product(address);
            break;
        }

        printf("Searching for record based on index...\n");

        printf("POS INDEX %d\n", pos_index);
        fseek(f, (sizeof(NumericIndexEntry) * pos_index) - sizeof(NumericIndexEntry), SEEK_SET);
        // fseek(f, (sizeof(NumericIndexEntry) * pos_index) - sizeof(NumericIndexEntry), SEEK_SET);

        fread(&index1, sizeof(NumericIndexEntry), 1, f);
        fread(&index2, sizeof(NumericIndexEntry), 1, f);

        printf("key: %lld and addr: %ld\n", index1.key, index1.address);
        printf("key: %lld and addr: %ld\n", index2.key, index2.address);

        FILE *final_products = fopen("output/final_products.bin", "rb");
        start = index1.address / sizeof(ProductEntry);
        end = index2.address / sizeof(ProductEntry);

        record_address = binsearch_in_file(final_products, sizeof(ProductEntry), start, end, &product_id, &pos_index, cmp_product_id);

        if (record_address != -1)
        {
            printf("Record found!\n");
            show_product(record_address);
        }
        else
        {
            printf("Not found.\n");
        }

        printf("Done.\n");

        break;

    case 2:
        long category_id;
        printf("Digite o 'category_id':\n");
        scanf("%ld", &category_id);

        printf("Searching for index...\n");

        f = fopen("output/index_categories.bin", "rb");
        fseek(f, 0, SEEK_END);
        end = (ftell(f) / sizeof(NumericIndexEntry)) - 1;
        fseek(f, 0, SEEK_SET);

        address = binsearch_in_file(f, sizeof(NumericIndexEntry), 0, end, &category_id, &pos_index, cmp_numeric_index);
        if (address != -1)
        {
            printf("Record found!\n");
            show_category(address);
            break;
        }

        printf("Searching for record based on index...\n");

        printf("POS INDEX %d\n", pos_index);
        fseek(f, (sizeof(NumericIndexEntry) * pos_index) - sizeof(NumericIndexEntry), SEEK_SET);
        // fseek(f, (sizeof(NumericIndexEntry) * pos_index) - sizeof(NumericIndexEntry), SEEK_SET);

        fread(&index1, sizeof(NumericIndexEntry), 1, f);
        fread(&index2, sizeof(NumericIndexEntry), 1, f);

        printf("key: %lld and addr: %ld\n", index1.key, index1.address);
        printf("key: %lld and addr: %ld\n", index2.key, index2.address);

        FILE *final_categories = fopen("output/final_categories.bin", "rb");
        start = index1.address / sizeof(CategoryEntry);
        end = index2.address / sizeof(CategoryEntry);

        record_address = binsearch_in_file(final_categories, sizeof(CategoryEntry), start, end, &category_id, &pos_index, cmp_category_id);

        if (record_address != -1)
        {
            printf("Record found!\n");
            show_category(record_address);
        }
        else
        {
            printf("Not found.\n");
        }

        printf("Done.\n");
        break;

    case 3:
        char session_id[EVENT_USER_SESSION_SIZE];
        printf("Digite o 'session_id':\n");
        scanf("%s", session_id);

        printf("Searching for index...\n");

        f = fopen("output/index_sessions.bin", "rb");
        fseek(f, 0, SEEK_END);
        end = (ftell(f) / sizeof(StringIndexEntry)) - 1;
        fseek(f, 0, SEEK_SET);

        address = binsearch_in_file(f, sizeof(StringIndexEntry), 0, end, &session_id, &pos_index, cmp_string_index);
        if (address != -1)
        {
            printf("Record found!\n");
            show_session(address);
            break;
        }

        printf("Searching for record based on index...\n");

        StringIndexEntry sindex1, sindex2;
        printf("POS INDEX %d\n", pos_index);
        fseek(f, (sizeof(StringIndexEntry) * pos_index) - sizeof(StringIndexEntry), SEEK_SET);
        // fseek(f, (sizeof(StringIndexEntry) * pos_index) - sizeof(StringIndexEntry), SEEK_SET);

        fread(&sindex1, sizeof(StringIndexEntry), 1, f);
        fread(&sindex2, sizeof(StringIndexEntry), 1, f);

        // printf("key: %lld and addr: %ld\n", sindex1.key, sindex1.address);
        // printf("key: %lld and addr: %ld\n", sindex2.key, sindex2.address);

        FILE *final_sessions = fopen("output/final_sessions.bin", "rb");
        start = sindex1.address / sizeof(SessionEntry);
        end = sindex2.address / sizeof(SessionEntry);

        record_address = binsearch_in_file(final_sessions, sizeof(SessionEntry), start, end, &category_id, &pos_index, cmp_user_session);

        if (record_address != -1)
        {
            printf("Record found!\n");
            show_session(record_address);
        }
        else
        {
            printf("Not found.\n");
        }

        printf("Done.\n");

        break;
    case 4:
        return;

    default:
        printf("Invalid option.\n");
        break;
    }
}

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

        case 5:
            FILE *in = fopen("output/final_products.bin", "rb");
            fseek(in, 0, SEEK_END);
            int count = ftell(in) / sizeof(ProductEntry);
            rewind(in);
            ProductEntry buffer;
            for (int i = 0; i < count; i++)
            {
                fread(&buffer, sizeof(ProductEntry), 1, in);
                printf("Product ID: %ld\n", buffer.product_id);
            }
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
