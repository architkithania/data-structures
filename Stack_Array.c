#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY_RETURN 0

typedef int T;

typedef struct {
    int capacity;
    int top;
    T *elements;
}   Stack;

Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->elements = malloc(sizeof(T) * capacity);
    stack->top = -1;
    return stack;
}

bool isFull(Stack *stack) {
    if (stack->capacity <= stack->top - 1) {
        return true;
    }
    return false;
}

bool isEmpty(Stack *stack) {
    if (stack->top == -1) {
        return true;
    }
    return false;
}

void push(Stack *stack, T element) {
    if (isFull(stack)) {
        printf("Stack is full");
        return;
    }
    else {
        (stack->elements)[stack->top + 1] = element;
        stack->top = stack->top + 1;
    }
}

T pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty");
        return EMPTY_RETURN;
    }
    else {
        T element = (stack->elements)[stack->top];
        stack->top--;
        return element;
    }
}

void printStack(Stack *stack) {
    int i;
    printf("[");
    for (i = 0; i < stack->top + 1; i++) {
        if (i != stack->top) {
            printf("%d, ", stack->elements[i]);
        }
        else {
            printf("%d", stack->elements[i]);
        }
    }
    printf("]\n");
}

int main(void) {
    Stack *stack = createStack(10);
    for (int i = 1 ; i <= 10; i++) {
        push(stack, i);
    }
    printStack(stack);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", pop(stack));
    }
    printStack(stack);
    return 0;
}
