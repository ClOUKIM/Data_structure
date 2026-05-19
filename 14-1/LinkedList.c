#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 이중 원형 연결리스트 구조체 정의
typedef struct {
    Node* head;
    int size;
} DoublyCircularLinkedList;

// 리스트 초기화 함수
void initList(DoublyCircularLinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

// 새로운 노드 생성하
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// 1. 맨 앞에 추가
void insertFront(DoublyCircularLinkedList* list, int data) {
    Node* newNode = createNode(data);
    
    if (list->head == NULL) { // 리스트가 비어있을 때
        list->head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else { // 리스트에 노드가 이미 있을 때
        Node* tail = list->head->prev; // 원형이므로 head의 이전 노드가 tail
        
        newNode->next = list->head;
        newNode->prev = tail;
        tail->next = newNode;
        list->head->prev = newNode;
        
        list->head = newNode; 
    }
    list->size++;
}

// 2. 맨 뒤에 추가
void insertBack(DoublyCircularLinkedList* list, int data) {
    Node* newNode = createNode(data);
    
    if (list->head == NULL) {
        list->head = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        Node* tail = list->head->prev;
        
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = list->head;
        list->head->prev = newNode;
    }
    list->size++;
}

// 3. 특정 위치에 추가 
void insertAt(DoublyCircularLinkedList* list, int index, int data) {
    if (index < 0 || index > list->size) {
        printf("잘못된 위치입니다.\n");
        return;
    }
    
    if (index == 0) {
        insertFront(list, data);
        return;
    }
    if (index == list->size) {
        insertBack(list, data);
        return;
    }
    
    Node* newNode = createNode(data);
    Node* current = list->head; 

    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    Node* previous = current->prev;
    
    previous->next = newNode;
    newNode->prev = previous;
    newNode->next = current;
    current->prev = newNode;
    
    list->size++;
}

// 4. 특정 위치 삭제 및 값 출력
void deleteAt(DoublyCircularLinkedList* list, int index) {
    if (list->head == NULL) {
        printf("리스트가 비어있습니다.\n");
        return;
    }
    if (index < 0 || index >= list->size) {
        printf("잘못된 위치입니다.\n");
        return;
    }
    
    Node* target = list->head;
    
    // 삭제할 노드 위치로 이동
    for (int i = 0; i < index; i++) {
        target = target->next;
    }
    
    int deletedData = target->data;
    
    if (list->size == 1) { 
        list->head = NULL;
    } else {
        Node* previous = target->prev;
        Node* following = target->next;
        
        previous->next = following;
        following->prev = previous;
        
        if (target == list->head) { 
            list->head = following;
        }
    }
    
    free(target);
    list->size--;
    printf("삭제된 값: %d\n", deletedData);
}

// 5. 전체 목록 출력
void printList(DoublyCircularLinkedList* list) {
    if (list->head == NULL) {
        printf("리스트가 비어있습니다.\n");
        return;
    }
    
    Node* current = list->head;
    printf("리스트 목록: ");
    
    // 원형 연결리스트이므로 head를 다시 만날 때까지 반복 출력
    for (int i = 0; i < list->size; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 0. 종료 (메모리 해제)
void destroyList(DoublyCircularLinkedList* list) {
    if (list->head == NULL) return;
    
    Node* current = list->head;
    Node* nextNode = NULL;
    
    for (int i = 0; i < list->size; i++) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    
    list->head = NULL;
    list->size = 0;
    printf("모든 메모리가 해제되었습니다.\n");
}

int main() {
    DoublyCircularLinkedList list;
    initList(&list);
    
    int menu = -1;
    int data, index;
    
    while (menu != 0) {
        printf("\n--- 메뉴 ---\n");
        printf("1. 맨 앞에 추가\n");
        printf("2. 맨 뒤에 추가\n");
        printf("3. 특정 위치에 추가\n");
        printf("4. 특정 위치 삭제\n");
        printf("5. 전체 목록 출력\n");
        printf("6. 리스트 크기 확인\n");
        printf("0. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &menu);
        
        switch (menu) {
            case 1:
                printf("추가할 정수 입력: ");
                scanf("%d", &data);
                insertFront(&list, data);
                break;
            case 2:
                printf("추가할 정수 입력: ");
                scanf("%d", &data);
                insertBack(&list, data);
                break;
            case 3:
                printf("위치(index) 입력: ");
                scanf("%d", &index);
                printf("추가할 정수 입력: ");
                scanf("%d", &data);
                insertAt(&list, index, data);
                break;
            case 4:
                printf("삭제할 위치(index) 입력: ");
                scanf("%d", &index);
                deleteAt(&list, index);
                break;
            case 5:
                printList(&list);
                break;
            case 6:
                printf("현재 리스트 크기: %d\n", list.size);
                break;
            case 0:
                destroyList(&list);
                printf("프로그램을 종료합니다.\n");
                break;
            default:
                printf("잘못된 메뉴 선택입니다. 다시 선택하세요.\n");
        }
    }
    
    return 0;
}