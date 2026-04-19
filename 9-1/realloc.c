#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;      // 배열
    int size;       // 현재 데이터 개수
    int capacity;   // 전체 칸 수
} ArrayList;

void insert(ArrayList *L, int item) {
    // 포화 상태 체크
    if (L->size == L->capacity) {
        L->capacity *= 2; // 용량을 2배로 늘림
        // realloc으로 메모리 확장
        L->data = (int *)realloc(L->data, L->capacity * sizeof(int));
    }
    // 데이터 삽입
    L->data[L->size++] = item;
}

int main() {
    ArrayList list = { (int*)malloc(sizeof(int) * 2), 0, 2 }; // 초기 용량 2로 시작

    for(int i = 1; i <= 5; i++) insert(&list, i * 10); // 5개 삽입 (중간에 확장 발생)

    for(int i = 0; i < list.size; i++) printf("%d ", list.data[i]);
    
    free(list.data);
    return 0;
}