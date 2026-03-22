#include "my_math.h"

static int my_abs_int(int x) {
    return (x < 0) ? -x : x;
}

int my_gcd(int a, int b) {
    int r;

    a = my_abs_int(a);
    b = my_abs_int(b);

    /* gcd(a,0) = a */
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long my_lcm(int a, int b) {
    int g;

    if (a == 0 || b == 0) return 0;

    g = my_gcd(a, b);

    /* overflow 줄이기: (a/g)*b */
    {
        long long x = (long long)(a / g) * (long long)b;
        if (x < 0) x = -x;
        return x;
    }
}
