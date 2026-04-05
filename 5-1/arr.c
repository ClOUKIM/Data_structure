#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int main() {
    int arr[N];
    int sum = 0, max, min;
    srand(time(NULL)); // 실행할 때마다 다른 랜덤값 생성

    // 배열 채우기 (0 ~ N 사이의 값)
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % (N + 1);
    }

    // 처음부터 끝까지 출력
    printf("정방향: ");
    for (int i = 0; i < N; i++) printf("%d ", arr[i]);
    
    // 뒤에서부터 출력
    printf("\n역방향: ");
    for (int i = N - 1; i >= 0; i--) printf("%d ", arr[i]);

    // 총합, 최대, 최소 계산
    max = min = arr[0];
    for (int i = 0; i < N; i++) {
        sum += arr[i];
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    printf("\n총합: %d, 최대값: %d, 최소값: %d\n", sum, max, min);
    return 0;
}