#include <stdio.h>
#include <string.h>

#define MAX_DEGREE 101 // 최대 차수 설정

// 다항식 구조체 정의
typedef struct {
    int degree;                // 다항식의 최고 차수
    float coef[MAX_DEGREE];    // 각 항의 계수 (인덱스가 곧 지수)
} Polynomial;

// 다항식 초기화 함수
Polynomial zeroP() {
    Polynomial p;
    p.degree = 0;
    for (int i = 0; i < MAX_DEGREE; i++) p.coef[i] = 0;
    return p;
}

// 다항식 입력 처리 (형식: 3X^2+2X^1+1X^0)
Polynomial readP() {
    Polynomial p = zeroP();
    int c, e;
    char dummy[10];

    printf("다항식 입력 (예: 3X^2+2X^1+1X^0): ");
    
    // scanf의 반환값을 이용해 입력이 끝날 때까지 계수(c)와 지수(e)를 읽음
    while (scanf("%dX^%d", &c, &e) == 2) {
        p.coef[e] = (float)c;
        if (e > p.degree) p.degree = e;
        
        // '+' 기호를 소비하거나 입력 종료 확인
        if (getchar() != '+') break; 
    }
    return p;
}

// 다항식 출력 함수
void printP(Polynomial p) {
    for (int i = p.degree; i >= 0; i--) {
        if (p.coef[i] != 0) {
            printf("%.0fX^%d", p.coef[i], i);
            if (i > 0 && p.coef[i-1] >= 0) printf("+");
        }
    }
    printf("\n");
}

// 다항식 곱셈 함수
Polynomial multiplyP(Polynomial A, Polynomial B) {
    Polynomial C = zeroP();
    C.degree = A.degree + B.degree;

    for (int i = 0; i <= A.degree; i++) {           // A의 각 항에 대해
        for (int j = 0; j <= B.degree; j++) {       // B의 각 항을 곱함
            C.coef[i + j] += A.coef[i] * B.coef[j]; // 지수는 더하고 계수는 곱함
        }
    }
    return C;
}

int main() {
    printf("--- 첫 번째 다항식 ---\n");
    Polynomial a = readP();
    
    // 입력 버퍼 비우기
    while (getchar() != '\n');

    printf("--- 두 번째 다항식 ---\n");
    Polynomial b = readP();

    Polynomial result = multiplyP(a, b);

    printf("\n결과 (A * B): ");
    printP(result);

    return 0;
}