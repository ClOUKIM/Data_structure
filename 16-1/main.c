#include "calculator.h"
#include <stdio.h>

int main() {

    char sample[] = "3 + 4 * (5 + 6) * 7"; 
    char postfix[100];

    printf("입력:\n%s\n\n", sample);

    infixToPostfix(sample, postfix);
    
    evalPostfix(postfix);

    return 0;
}