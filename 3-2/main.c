#include <stdio.h>
#include "my_math.h"

int main(void) {
    int a, b;

    if (scanf("%d %d", &a, &b) != 2) {
        return 1;
    }

    printf("GCD: %d, LCM: %lld\n", my_gcd(a, b), my_lcm(a, b));
    return 0;
}
