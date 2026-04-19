#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} ArrayList;

// 초기화 함수
void init(ArrayList *L) {
    L->capacity = 2;
    L->size = 0;
    L->data = (int*)malloc(sizeof(int) * L->capacity);
}

// 1. 추가 (원하는 위치에 삽입)
void insert(ArrayList *L, int pos, int item) {
    if (pos < 0 || pos > L->size) return; // 범위 체크
    if (L->size == L->capacity) {
        L->capacity *= 2;
        L->data = (int*)realloc(L->data, L->capacity * sizeof(int));
    }
    for (int i = L->size - 1; i >= pos; i--) L->data[i + 1] = L->data[i];
    L->data[pos] = item;
    L->size++;
}

// 2. 삭제
void delete(ArrayList *L, int pos) {
    if (pos < 0 || pos >= L->size) return;
    for (int i = pos; i < L->size - 1; i++) L->data[i] = L->data[i + 1];
    L->size--;
}

// 3. 변경
void replace(ArrayList *L, int pos, int item) {
    if (pos >= 0 && pos < L->size) L->data[pos] = item;
}

// 4. 출력
void print_list(ArrayList *L) {
    for (int i = 0; i < L->size; i++) printf("[%d]:%d ", i, L->data[i]);
    printf("\n");
}

// 5. 전체 삭제
void clear(ArrayList *L) {
    free(L->data);
    init(L); // 다시 쓸 수 있게 초기화
}