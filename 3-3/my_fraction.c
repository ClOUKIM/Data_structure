#include "my_fraction.h"
#include <stdlib.h>  /* strtol, exit */
#include <limits.h>  /* INT_MIN */
#include <ctype.h>   /* isspace */

/* ----- internal helpers ----- */

static long long llabs_ll(long long x) {
    return (x < 0) ? -x : x;
}

/* gcd for non-negative numbers */
static long long gcd_ll(long long a, long long b) {
    a = llabs_ll(a);
    b = llabs_ll(b);
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return (a == 0) ? 1 : a; /* avoid division by 0 in reduce(0/x) cases */
}

Fraction fraction_reduce(Fraction f) {
    long long num = f.num;
    long long den = f.den;

    if (den == 0) {
        fprintf(stderr, "Error: denominator is zero.\n");
        exit(EXIT_FAILURE);
    }

    /* move sign to numerator */
    if (den < 0) {
        den = -den;
        num = -num;
    }

    if (num == 0) {
        Fraction r;
        r.num = 0;
        r.den = 1;
        return r;
    }

    {
        long long g = gcd_ll(num, den);
        num /= g;
        den /= g;
    }

    Fraction r;
    r.num = (int)num;
    r.den = (int)den;
    return r;
}

Fraction fraction_make(int num, int den) {
    Fraction f;
    f.num = num;
    f.den = den;
    return fraction_reduce(f);
}

Fraction fraction_add(Fraction a, Fraction b) {
    long long num = (long long)a.num * b.den + (long long)b.num * a.den;
    long long den = (long long)a.den * b.den;
    Fraction r;
    r.num = (int)num;
    r.den = (int)den;
    return fraction_reduce(r);
}

Fraction fraction_sub(Fraction a, Fraction b) {
    long long num = (long long)a.num * b.den - (long long)b.num * a.den;
    long long den = (long long)a.den * b.den;
    Fraction r;
    r.num = (int)num;
    r.den = (int)den;
    return fraction_reduce(r);
}

Fraction fraction_mul(Fraction a, Fraction b) {
    long long num = (long long)a.num * b.num;
    long long den = (long long)a.den * b.den;
    Fraction r;
    r.num = (int)num;
    r.den = (int)den;
    return fraction_reduce(r);
}

Fraction fraction_div(Fraction a, Fraction b) {
    if (b.num == 0) {
        fprintf(stderr, "Error: division by zero fraction.\n");
        exit(EXIT_FAILURE);
    }
    long long num = (long long)a.num * b.den;
    long long den = (long long)a.den * b.num;
    Fraction r;
    r.num = (int)num;
    r.den = (int)den;
    return fraction_reduce(r);
}

static const char *skip_spaces(const char *p) {
    while (*p && isspace((unsigned char)*p)) p++;
    return p;
}

/* parse "A/B" */
int fraction_from_string(const char *s, Fraction *out) {
    char *endp;
    long a, b;
    const char *p = s;

    if (!s || !out) return 0;

    p = skip_spaces(p);

    a = strtol(p, &endp, 10);
    if (endp == p) return 0;          /* no number */
    if (*endp != '/') return 0;       /* must have '/' */

    p = endp + 1; /* after '/' */
    b = strtol(p, &endp, 10);
    if (endp == p) return 0;          /* no denom */

    p = skip_spaces(endp);
    if (*p != '\0') return 0;         /* extra garbage */

    if (b == 0) return 0;

    *out = fraction_make((int)a, (int)b);
    return 1;
}

void fraction_print(Fraction f) {
    /* ensure consistent output */
    f = fraction_reduce(f);
    printf("%d/%d", f.num, f.den);
}
