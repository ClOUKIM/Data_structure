#include <stdio.h>
#include <stdlib.h>
#include "my_fraction.h"

int main(void) {
    char s1[64], s2[64];
    char op;
    Fraction a, b, r;

    /* example input: 2/5 + 2/4 */
    if (scanf("%63s %c %63s", s1, &op, s2) != 3) {
        fprintf(stderr, "Input format error. Use: A/B op C/D\n");
        return 1;
    }

    if (!fraction_from_string(s1, &a) || !fraction_from_string(s2, &b)) {
        fprintf(stderr, "Fraction parse error. Use: A/B where B != 0\n");
        return 1;
    }

    switch (op) {
        case '+': r = fraction_add(a, b); break;
        case '-': r = fraction_sub(a, b); break;
        case '*': r = fraction_mul(a, b); break;
        case '/': r = fraction_div(a, b); break;
        default:
            fprintf(stderr, "Unknown operator: %c\n", op);
            return 1;
    }

    fraction_print(r);
    printf("\n");
    return 0;
}
