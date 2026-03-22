#ifndef MY_FRACTION_H
#define MY_FRACTION_H

#include <stdio.h>

typedef struct {
    int num;  /* numerator */
    int den;  /* denominator (must not be 0) */
} Fraction;

/* Make a fraction and reduce it (den must not be 0) */
Fraction fraction_make(int num, int den);

/* Reduce to irreducible form, and normalize sign so den > 0 */
Fraction fraction_reduce(Fraction f);

/* Arithmetic operations (all return reduced fractions) */
Fraction fraction_add(Fraction a, Fraction b);
Fraction fraction_sub(Fraction a, Fraction b);
Fraction fraction_mul(Fraction a, Fraction b);
Fraction fraction_div(Fraction a, Fraction b); /* b.num must not be 0 */

/* Convert "A/B" string to Fraction (returns 1 on success, 0 on failure) */
int fraction_from_string(const char *s, Fraction *out);

/* Print as A/B */
void fraction_print(Fraction f);

#endif