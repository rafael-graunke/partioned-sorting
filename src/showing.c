#include "show.h"

void show_product(ProductEntry product){
    printf("Product ID: %d\n", product.product_id);
    printf("Brand: %s\n", product.brand);
    printf("Price: %.2f\n", product.price);
    // printf("Next: %ld\n", product.next);
    // printf("Deleted: %s\n", product.deleted ? "Yes" : "No");
    printf("\n");
}

void show_category(CategoryEntry category){
    printf("Category ID: %llu\n", category.category_id);
    printf("Category Code: %s\n", category.category_code);
    // printf("Next: %ld\n", category.next);
    // printf("Deleted: %s\n", category.deleted ? "Yes" : "No");
    printf("\n");
}

void show_session(SessionEntry session){
    printf("Event Time: %s\n", session.event_time);
    printf("Event Type: %s\n", session.event_type);
    printf("User Session: %s\n", session.user_session);
    printf("User ID: %u\n", session.user_id);
    // printf("Next: %ld\n", session.next);
    // printf("Deleted: %s\n", session.deleted ? "Yes" : "No");
    printf("\n");
}
