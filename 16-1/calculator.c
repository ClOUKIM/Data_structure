#include "calculator.h"
#include "ArrayStack.h"
#include <stdio.h>
#include <string.h>

extern void printArrayStackLine(ArrayStack* s);

int infixToPostfix(char* infix, char* postfix) {
    int j = 0;
    ArrayStack* opStack = createArrayStack(100, CHARACTER);
    stackElement element;

    printf("Transform:\n");

    for (int i = 0; infix[i] != '\0'; i++) { 
        
        if (infix[i] == ' ' || infix[i] == '\t') continue;

        if (infix[i] >= '0' && infix[i] <= '9') { 
            postfix[j++] = infix[i];
            postfix[j++] = ' ';
        }
        else if (infix[i] == '+' || infix[i] == '-' ||
            infix[i] == '*' || infix[i] == '/') {

            while (!emptyArrayStack(opStack)) {
                stackElement prevOp = peekArrayStack(opStack);

                
                if (precedence(infix[i]) <= precedence(prevOp.operator)) {
                    stackElement popped = popArrayStack(opStack);
                    postfix[j++] = popped.operator;
                    postfix[j++] = ' ';
                }
                else {
                    break;
                }
            }
            element.operator = infix[i];
            pushArrayStack(opStack, element); 
        }
        else if (infix[i] == '(') {
            element.operator = infix[i];
            pushArrayStack(opStack, element);
        }
        else if (infix[i] == ')') {
           
            while (!emptyArrayStack(opStack)) {
                stackElement prevOp = popArrayStack(opStack);
                
                if (prevOp.operator != '(') {
                    postfix[j++] = prevOp.operator;
                    postfix[j++] = ' ';
                }
                else {
                    break; 
                }
            }
        }

        
        postfix[j] = '\0'; 
        printf("- Postfix: %s| Stack: ", postfix);
        printArrayStackLine(opStack);
        printf("\n");
    }

    
    while (!emptyArrayStack(opStack)) {
        stackElement popped = popArrayStack(opStack);
        postfix[j++] = popped.operator;
        postfix[j++] = ' ';
    }

    if (j > 0) postfix[j - 1] = '\0'; 
    else postfix[j] = '\0';

    printf("- Postfix: %s | Stack: \n", postfix);
    printf("\n- Result: %s\n\n", postfix);

    destroyArrayStack(opStack); 
    return 1;
}

int evalPostfix(char* postfix) {
    ArrayStack* valueStack = createArrayStack(100, INTEGER);
    stackElement element;
    int i = 0;

    printf("Eval:\n");
    printf("- Postfix: %s\n", postfix);

    while (postfix[i] != '\0') { 
        if (postfix[i] == ' ') {
            i++;
            continue;
        }

        if (postfix[i] >= '0' && postfix[i] <= '9') {
            element.value = (int)(postfix[i] - '0');
            pushArrayStack(valueStack, element); 

            printf("- Current: %c | Stack: ", postfix[i]);
            printArrayStackLine(valueStack);
            printf("\n");
        }
        else if (postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '+' || postfix[i] == '-') {
            
            stackElement e1 = popArrayStack(valueStack);
            stackElement e2 = popArrayStack(valueStack);
            int i1 = e1.value;
            int i2 = e2.value;
            int result = 0;

            if (postfix[i] == '*') {
                result = i2 * i1;
            }
            else if (postfix[i] == '/') {
                result = i2 / i1; 
            }
            else if (postfix[i] == '+') {
                result = i2 + i1;
            }
            else if (postfix[i] == '-') {
                result = i2 - i1; 
            }

            element.value = result;
            pushArrayStack(valueStack, element);

            printf("- Current: %c | Stack: ", postfix[i]);
            printArrayStackLine(valueStack);
            printf("\n");
        }
        i++;
    }

    stackElement finalElement = popArrayStack(valueStack);
    int finalResult = finalElement.value;
    printf("\n- Result: %d\n", finalResult);

    destroyArrayStack(valueStack); 
    return finalResult;
}

int precedence(char op) {
    switch (op)
    {
    case ')':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
        return 0;
    default:
        return 0;
    }
}