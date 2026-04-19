#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int row;
    int col;
    int value;
} element;

typedef struct {
    int* data;
    int size;
    int capacity;
} ArrayList;

typedef struct {
    int rows;
    int cols;
    ArrayList* al;
} SparseMatrix;


void clear_list(ArrayList* L) {
    if (L->data != NULL) free(L->data);
    L->size = 0;
    L->capacity = 2;
    L->data = (int*)malloc(L->capacity * sizeof(element));
    printf("\n[System] 리스트가 초기화되었습니다.\n");
}

void init(ArrayList* L) {
    L->size = 0;
    L->capacity = 2;
    L->data = (int*)malloc(L->capacity * sizeof(element));
}

void check_and_expand(ArrayList* L) {
    if (L->size >= L->capacity) {
        L->capacity *= 2;
        L->data = (int*)realloc(L->data, L->capacity * sizeof(element));
        printf("\n[System] 용량 확장 -> %d\n", L->capacity);
    }
}

void insert(ArrayList* L, int pos, element item) {
    if (item.value <= 0) {
        printf("에러: 양의 정수만 입력 가능합니다.\n");
        return;
    }
    if (pos < 0 || pos > L->size) return;
    check_and_expand(L);
    element* arr = (element*)L->data;
    for (int i = L->size - 1; i >= pos; i--) {
        arr[i + 1] = arr[i];
    }
    arr[pos] = item;
    L->size++;
}

void delete(ArrayList* L, int pos) {
    if (pos < 0 || pos >= L->size) return;
    element* arr = (element*)L->data;
    for (int i = pos; i < L->size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    L->size--;
}

void replace(ArrayList* L, int pos, element item) {
    if (item.value <= 0) {
        printf("에러: 양의 정수만 입력 가능합니다.\n");
        return;
    }
    if (pos >= 0 && pos < L->size) {
        element* arr = (element*)L->data;
        arr[pos] = item;
    }
}

void print_list(ArrayList* L) {
    element* arr = (element*)L->data;
    if (L->size == 0) {
        printf("리스트가 비어 있습니다.\n");
        return;
    }
    for (int i = 0; i < L->size; i++) {
        printf("[%d] (r:%d, c:%d, v:%d) \n", i, arr[i].row, arr[i].col, arr[i].value);
    }
}

void transpose_sparse(SparseMatrix* M) {
    int move_count = 0;
    ArrayList* resultAL = (ArrayList*)malloc(sizeof(ArrayList));
    init(resultAL);
    element* source = (element*)M->al->data;

    for (int c = 0; c < M->cols; c++) {
        for (int i = 0; i < M->al->size; i++) {
            if (source[i].col == c) {
                element b = { source[i].col, source[i].row, source[i].value };
                insert(resultAL, resultAL->size, b);
                move_count++; 
            }
        }
    }
    printf("\n--- 전치 결과 (이동 횟수: %d) ---\n", move_count);
    print_list(resultAL);
    free(resultAL->data);
    free(resultAL);
}

int main() {
    srand(time(NULL));
    SparseMatrix m;
    m.rows = 10; m.cols = 10;
    m.al = (ArrayList*)malloc(sizeof(ArrayList));
    init(m.al);

    for (int i = 0; i < 20; i++) {
        element e = { rand() % 10, rand() % 10, rand() % 100 + 1 };
        insert(m.al, m.al->size, e);
    }

    int choice, p, r, c, v;
    element temp;

    while (1) {
        printf("\n1.추가 2.삭제 3.변경 4.출력 5.초기화 6.전치실행 0.종료: ");
        if(scanf("%d", &choice) != 1) break;

        if (choice == 0) break;
        switch (choice) {
            case 1:
                printf("위치 행 열 값 입력: ");
                scanf("%d %d %d %d", &p, &r, &c, &v);
                temp.row = r; temp.col = c; temp.value = v;
                insert(m.al, p, temp);
                break;
            case 2:
                printf("삭제할 위치: ");
                scanf("%d", &p);
                delete(m.al, p);
                break;
            case 3:
                printf("변경 위치 행 열 값: ");
                scanf("%d %d %d %d", &p, &r, &c, &v);
                temp.row = r; temp.col = c; temp.value = v;
                replace(m.al, p, temp);
                break;
            case 4:
                print_list(m.al);
                break;
            case 5:
                clear_list(m.al); 
                break;
            case 6:
                transpose_sparse(&m);
                break;
        }
    }

    free(m.al->data);
    free(m.al);
    return 0;
}
