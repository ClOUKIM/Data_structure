#define _CRT_SECURE_NO_WARNINGS
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
    char names[100][50]; // 최대 100명의 이름을 저장할 공간
    int name_count = 0;

    // 이름 리스트 파일 읽기
    fp = fopen("name_list.txt", "r");
    if (fp == NULL) {
        printf("Fail to open file\n");
        return 1;
    }

    while (fgets(names[name_count], sizeof(names[name_count]), fp) != NULL) {
        // 개행 문자 제거
        names[name_count][strcspn(names[name_count], "\r\n")] = 0;
        name_count++;
    }
    fclose(fp);

    // N 입력 및 동적 할당
    printf("입력할 학생 수 N을 입력하세요: ");
    scanf("%d", &N);
    Student* students = (Student*)malloc(sizeof(Student) * N);

    // 무작위 데이터 생성 (인덱스 연산 사용)
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N; i++) {
        strcpy(students[i].name, names[rand() % name_count]);
        students[i].id = i + 1;
        students[i].score = (rand() % 100) + 1;
    }

    // 통계 계산 (인덱스 연산 사용)
    int min_idx = 0, max_idx = 0;
    double sum = 0;

    for (int i = 0; i < N; i++) {
        if (students[i].score < students[min_idx].score) min_idx = i;
        if (students[i].score > students[max_idx].score) max_idx = i;
        sum += students[i].score;
    }

    // 출력
    printf("\n--- 결과 ---\n");
    printf("최고점: %s(학번: %d, 점수: %d)\n", students[max_idx].name, students[max_idx].id, students[max_idx].score);
    printf("최저점: %s(학번: %d, 점수: %d)\n", students[min_idx].name, students[min_idx].id, students[min_idx].score);
    printf("평균점수: %.2f\n", sum / N);

    free(students);
    return 0;
}