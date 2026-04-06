#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    printf("홀수 N을 입력하세요: ");
    scanf("%d", &N);

    // 2차원 배열 동적 할당 (더블 포인터)
    int **magic = (int **)malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++) {
        *(magic + i) = (int *)calloc(N, sizeof(int)); // 0으로 초기화
    }

    int row = 0, col = N / 2; // 시작 위치 (첫 줄 가운데)
    for (int k = 1; k <= N * N; k++) {
        *(*(magic + row) + col) = k;
        
        int next_r = (row - 1 + N) % N;
        int next_c = (col + 1) % N;

        // 이동할 자리에 이미 숫자가 있으면 아래로 한 칸 이동
        if (*(*(magic + next_r) + next_c) != 0) {
            row = (row + 1) % N;
        } else {
            row = next_r;
            col = next_c;
        }
    }

    // 마방진 출력
    printf("\n--- 마방진 결과 ---\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", *(*(magic + i) + j));
        }
        printf("\n");
    }

    // 검증 (합계 출력)
    printf("\n--- 합계 검증 ---\n");
    int d1 = 0, d2 = 0; // 대각선 합
    for (int i = 0; i < N; i++) {
        int r_sum = 0, c_sum = 0;
        for (int j = 0; j < N; j++) {
            r_sum += *(*(magic + i) + j); // 가로 합
            c_sum += *(*(magic + j) + i); // 세로 합
        }
        printf("가로 %d행 합: %d | 세로 %d열 합: %d\n", i + 1, r_sum, i + 1, c_sum);
        d1 += *(*(magic + i) + i);         // 주대각선 \
        d2 += *(*(magic + i) + (N - 1 - i)); // 부대각선 /
    }
    printf("대각선1 합: %d | 대각선2 합: %d\n", d1, d2);

    // 메모리 해제
    for (int i = 0; i < N; i++) free(*(magic + i));
    free(magic);

    return 0;
}