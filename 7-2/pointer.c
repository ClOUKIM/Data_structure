#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[50];
    int id;
    int score;
} Student;

int main() {
    int N;
    FILE* fp;
    char names[100][50];
    int name_count = 0;

    fp = fopen("name_list.txt", "r");
    if (fp == NULL) return 1;

    while (fgets(*(names + name_count), 50, fp) != NULL) {
        (*(names + name_count))[strcspn(*(names + name_count), "\r\n")] = 0;
        name_count++;
    }
    fclose(fp);

    printf("N 입력: ");
    scanf("%d", &N);
    Student* students = (Student*)malloc(sizeof(Student) * N);

    srand((unsigned int)time(NULL));

    // 포인터 연산자로 데이터 입력
    for (int i = 0; i < N; i++) {
        strcpy((students + i)->name, *(names + (rand() % name_count)));
        (students + i)->id = i + 1;
        (students + i)->score = (rand() % 100) + 1;
    }

    // 포인터 연산자로 통계 계산
    int min_idx = 0, max_idx = 0;
    double sum = 0;

    for (int i = 0; i < N; i++) {
        if ((students + i)->score < (students + min_idx)->score) min_idx = i;
        if ((students + i)->score > (students + max_idx)->score) max_idx = i;
        sum += (students + i)->score;
    }

    printf("\n--- 결과 (Pointer 연산) ---\n");
    printf("최고점: %s(점수: %d)\n", (students + max_idx)->name, (students + max_idx)->score);
    printf("최저점: %s(점수: %d)\n", (students + min_idx)->name, (students + min_idx)->score);
    printf("평균: %.2f\n", sum / N);

    free(students);
    return 0;
}