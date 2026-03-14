#include <stdio.h>

int main() {
    int x = 1;

    // 1의 보수이면 ~x == -x
    // 2의 보수이면 ~x == -x - 1
    if (~x == -x) {
        printf("1의 보수입니다.\n");
    } else {
        printf("2의 보수입니다.\n");
    }

    return 0;
}

