#include <stdio.h>

#define N 3 // 반드시 홀수

int main() {
    int magic[N][N] = {0};
    int r = 0, c = N / 2; // 시작 위치 (첫 행 가운데)

    for (int i = 1; i <= N * N; i++) {
        magic[r][c] = i;
        
        // 다음 위치 계산 (오른쪽 위)
        int next_r = (r - 1 + N) % N;
        int next_c = (c + 1) % N;

        if (magic[next_r][next_c] != 0) { // 이미 숫자가 있으면 아래로
            r = (r + 1) % N;
        } else {
            r = next_r;
            c = next_c;
        }
    }

    // 배열 출력
    printf("--- %d * %d 마방진 ---\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", magic[i][j]);
        printf("\n");
    }

    // 합계 검증 출력
    printf("\n--- 합계 검증 ---\n");
    int row_sum, col_sum, diag1 = 0, diag2 = 0;

    for (int i = 0; i < N; i++) {
        row_sum = col_sum = 0;
        for (int j = 0; j < N; j++) {
            row_sum += magic[i][j];
            col_sum += magic[j][i];
        }
        printf("가로 %d행 합: %d\n", i + 1, row_sum);
        printf("세로 %d열 합: %d\n", i + 1, col_sum);
        diag1 += magic[i][i];         // 주대각선 (\)
        diag2 += magic[i][N - 1 - i]; // 부대각선 (/)
    }
    printf("대각선1 합: %d\n", diag1);
    printf("대각선2 합: %d\n", diag2);

    return 0;
}