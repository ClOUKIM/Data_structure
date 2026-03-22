#include <stdio.h>
#include <stdlib.h>
#include "my_fraction.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width A/B> <height C/D>\n", argv[0]);
        return 1;
    }

    Fraction w, h;

    if (!fraction_from_string(argv[1], &w)) {
        fprintf(stderr, "Invalid width fraction: %s\n", argv[1]);
        return 1;
    }
    if (!fraction_from_string(argv[2], &h)) {
        fprintf(stderr, "Invalid height fraction: %s\n", argv[2]);
        return 1;
    }

    /* perimeter = 2 * (w + h) */
    Fraction two = fraction_make(2, 1);
    Fraction perimeter = fraction_mul(two, fraction_add(w, h));

    /* area = w * h */
    Fraction area = fraction_mul(w, h);

    printf("Perimeter: ");
    fraction_print(perimeter);
    printf(", Area: ");
    fraction_print(area);
    printf("\n");

    return 0;
}

