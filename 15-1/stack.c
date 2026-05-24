#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LEN 100

// 스택의 노드 구조체 정의
typedef struct Node {
    char url[MAX_URL_LEN];
    struct Node* next;
} Node;

// 연결리스트 기반 스택 구조체 정의
typedef struct {
    Node* top;
} LinkedStack;

// ADT 1. 스택 생성 (초기화)
void create(LinkedStack* stack) {
    stack->top = NULL;
}

// ADT 5. 스택이 비어있는지 확인 (비었으면 1, 아니면 0)
int empty(LinkedStack* stack) {
    return (stack->top == NULL);
}

// ADT 6. 스택이 가득 찼는지 확인 (연결리스트는 메모리가 허용하는 한 가득 차지 않으므로 항상 0)
int full(LinkedStack* stack) {
    return 0;
}

// ADT 3. 데이터 추가 (Push)
void push(LinkedStack* stack, char* url) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("메모리 할당 실패!\n");
        return;
    }
    
    strcpy(newNode->url, url); // 문자열 복사
    newNode->next = stack->top; // 새 노드가 기존의 top을 가리키게 함
    stack->top = newNode;       // top을 새 노드로 갱신
}

// ADT 4. 데이터 제거 및 반환 (Pop)
// 이탈된 URL을 출력해야 하므로 문자열을 복사해올 buffer를 매개변수
void pop(LinkedStack* stack, char* buffer) {
    if (empty(stack)) {
        strcpy(buffer, "");
        return;
    }
    
    Node* temp = stack->top;
    strcpy(buffer, temp->url); // 제거할 노드의 URL을 버퍼에 저장
    
    stack->top = temp->next;   // top을 다음 노드로 이동
    free(temp);                // 노드 메모리 해제
}

// ADT 8. 스택의 맨 위 데이터 확인 (Peek)
void peek(LinkedStack* stack, char* buffer) {
    if (empty(stack)) {
        strcpy(buffer, "없음");
        return;
    }
    strcpy(buffer, stack->top->url);
}

// ADT 7. 스택 전체 출력 (현재 창 및 이전 히스토리 확인용)
void print(LinkedStack* stack) {
    if (empty(stack)) {
        printf("현재 창: 없음\n");
        return;
    }
    
    // 가장 위에 있는 현재 창 출력 
    printf("현재 창: %s\n", stack->top->url);
}

// ADT 2. 스택 파괴 (전체 메모리 해제)
void destroy(LinkedStack* stack) {
    Node* current = stack->top;
    Node* nextNode = NULL;
    
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    stack->top = NULL;
}

int main() {
    LinkedStack browserStack;
    create(&browserStack); // 스택 생성 및 초기화
    
    int menu = -1;
    char inputUrl[MAX_URL_LEN];
    char outputUrl[MAX_URL_LEN];
    
    while (1) {
        printf("\n[메뉴] 1.URL 추가 | 2.URL 제거 | 3.스택 확인 (종료는 모든 데이터 제거시 자동 종료)\n");
        printf("입력 ");
        if (scanf("%d", &menu) != 1) break;
        
        // 입력 버퍼 비우기 (문자열 입력을 받기 전 필수 작업)
        while (getchar() != '\n'); 
        
        if (menu == 1) {
            printf("URL 입력:\n입력 ");
            // 공백을 포함할 수도 있으므로 fgets 사용 후 개행문자 제거
            fgets(inputUrl, sizeof(inputUrl), stdin);
            inputUrl[strcspn(inputUrl, "\n")] = '\0'; 
            
            push(&browserStack, inputUrl);
            print(&browserStack);
            
        } else if (menu == 2) {
            if (empty(&browserStack)) {
                printf("제거할 URL이 없습니다.\n");
                continue;
            }
            
            pop(&browserStack, outputUrl);
            printf("이탈: %s\n", outputUrl);
            
            // 데이터가 모두 제거되었는지 확인
            if (empty(&browserStack)) {
                destroy(&browserStack); // 모든 메모리 해제
                printf("브라우저가 종료되었습니다.\n");
                break; // 프로그램 완전히 종료
            } else {
                print(&browserStack);
            }
            
        } else if (menu == 3) {
            peek(&browserStack, outputUrl);
            printf("현재 창: %s\n", outputUrl);
            
        } else {
            printf("잘못된 메뉴 선택입니다.\n");
        }
    }
    
    return 0;
}