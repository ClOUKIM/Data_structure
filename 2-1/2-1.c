#include <stdio.h>

int main() {
    union {
        float f;
        unsigned int i;
    } data;

    printf("입력값: ");
    scanf("%f", &data.f);

    printf("출력값: ");
    printf("%u/", (data.i >> 31) & 1);

    for (int i = 30; i >= 23; i--) {
        printf("%u", (data.i >> i) & 1);
        if (i == 27) printf(" ");
    }
    printf("/");

    for (int i = 22; i >= 0; i--) {
        printf("%u", (data.i >> i) & 1);
        if (i == 19 || i == 15 || i == 11 || i == 7 || i == 3)
            printf(" ");
    }

    printf("\n");
    return 0;
}
