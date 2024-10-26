#include "show.h"

void show_product(long address)
{
    FILE *f = fopen("output/final_products.bin", "rb");
    fseek(f, address, SEEK_SET);
    ProductEntry product;
    fread(&product, sizeof(ProductEntry), 1, f);

    printf("\n");
    printf("Product Data\n");
    printf("Product ID: %ld\n", product.product_id);
    printf("Brand: %s\n", product.brand);
    printf("Price: %.2f\n", product.price);
    printf("\n");
    fclose(f);
}

void show_category(long address)
{
    FILE *f = fopen("output/final_categories.bin", "rb");
    fseek(f, address, SEEK_SET);
    CategoryEntry category;
    fread(&category, sizeof(CategoryEntry), 1, f);

    printf("\n");
    printf("Category Data\n");
    printf("Category ID: %lld\n", category.category_id);
    printf("Category Code: %s\n", category.category_code);
    printf("\n");
    fclose(f);
}

void show_session(long address)
{
    FILE *f = fopen("output/final_sessions.bin", "rb");
    fseek(f, address, SEEK_SET);
    SessionEntry session;
    fread(&session, sizeof(SessionEntry), 1, f);

    printf("\n");
    printf("Session Data\n");
    printf("Event Time: %s\n", session.event_time);
    printf("Event Type: %s\n", session.event_type);
    printf("User Session: %s\n", session.user_session);
    printf("User ID: %u\n", session.user_id);
    printf("\n");
    fclose(f);
}
