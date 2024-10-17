#include <stdio.h>
#include <stdlib.h>

#include "parser.h"


int main(void) {

    FILE *file = fopen("input/dataset.csv", "r");
    return generate_tables(file);

}
