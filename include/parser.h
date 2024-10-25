#ifndef _PARSER_H_
#define _PARSER_H_

#define EVENT_TIME_SIZE 24
#define EVENT_TYPE_SIZE 17
#define EVENT_USER_SESSION_SIZE 37
#define PRODUCT_BRAND_SIZE 16
#define CATEGORY_CODE_SIZE 50

#include <stdbool.h>

typedef struct category_entry_s
{
    unsigned long long category_id;
    char category_code[CATEGORY_CODE_SIZE];
    long next;
    bool deleted;
} CategoryEntry;
// Total = 58 bytes

typedef struct product_entry_s
{
    long product_id;
    char brand[PRODUCT_BRAND_SIZE];
    float price;
    long next;
    bool deleted;
} ProductEntry;
// Total = 45 bytes

typedef struct session_entry_s
{
    char event_time[EVENT_TIME_SIZE];
    char event_type[EVENT_TYPE_SIZE];
    char user_session[EVENT_USER_SESSION_SIZE];
    unsigned int user_id;
    long next;
    bool deleted;

} SessionEntry;
// Total = 82 bytes

int generate_tables(FILE *source);

#endif