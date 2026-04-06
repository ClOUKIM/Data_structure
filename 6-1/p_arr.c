#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int N, sum = 0, max, min;
    printf("N을 입력하세요: ");
    scanf("%d", &N);

    // 동적 할당
    int *arr = (int *)malloc(sizeof(int) * N);
    srand(time(NULL));

    // 배열 채우기 및 초기화
    for (int i = 0; i < N; i++) {
        *(arr + i) = rand() % (N + 1);
    }

    // 처음부터 출력
    printf("정방향: ");
    for (int i = 0; i < N; i++) printf("%d ", *(arr + i));
    
    // 역방향 출력
    printf("\n역방향: ");
    for (int i = N - 1; i >= 0; i--) printf("%d ", *(arr + i));

    // 총합, 최대, 최소 계산
    max = min = *arr;
    for (int i = 0; i < N; i++) {
        int val = *(arr + i);
        sum += val;
        if (val > max) max = val;
        if (val < min) min = val;
    }

    printf("\n총합: %d, 최대값: %d, 최소값: %d\n", sum, max, min);

    free(arr);
    return 0;
}