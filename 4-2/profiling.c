#include <stdio.h>
#include <time.h>

// GCD 함수 (my_math.c 내용)
long long get_gcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    long long fib[50];
    fib[0] = 0; fib[1] = 1;
    
    // 피보나치 수열 생성
    for (int i = 2; i <= 45; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    printf("n\tF(n)\t\tTime(clocks)\n");
    printf("------------------------------------\n");

    for (int n = 5; n <= 45; n++) {
        clock_t start = clock();
        
        // 정밀한 측정을 위해 동일 연산을 반복 수행 (반복 횟수 조절 가능)
        for(int i=0; i<1000000; i++) {
            get_gcd(fib[n], fib[n-1]);
        }
        
        clock_t end = clock();
        double cpu_time_used = ((double) (end - start));
        
        printf("%d\t%lld\t%.0f\n", n, fib[n], cpu_time_used);
    }
    
    return 0;
}
