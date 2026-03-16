#include <stdio.h>

int main() {
    char str[1000];

    printf("입력값: ");
    fgets(str, sizeof(str), stdin);

    printf("출력값: ");
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            printf("%c", str[i] + 32);   // 대문자 -> 소문자
        }
        else if (str[i] >= 'a' && str[i] <= 'z') {
            printf("%c", str[i] - 32);   // 소문자 -> 대문자
        }
        else {
            printf("%c", str[i]);        // 그 외 문자는 그대로 출력
        }
    }

    return 0;
}
