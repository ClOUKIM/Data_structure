#include <stdio.h>
#include <stdint.h>

int main() {
    double x;
    int16_t fixed;
    uint16_t bits;

    printf("입력값: ");
    scanf("%lf", &x);

    fixed = (int16_t)(x * 256);
    bits = (uint16_t)fixed;

    for (int i = 15; i >= 0; i--) {
        printf("%d", (bits >> i) & 1);

        if (i == 8)
            printf(".");
    }

    printf("\n");

    return 0;
}
