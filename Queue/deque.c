#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY_RETURN 0

typedef int T;

typedef struct {
	int size;
	int left;
	int right;
	int numOfElements;
	T *elements;
}	Deque;

Deque *newDeque(int size) {
	Deque deque = malloc(sizeof(Deque));
	deque->size = size + 1;
	deque->left = 0;
	deque->right = 0;
	deque->numOfElements = 0;
	deque->elements = malloc(sizeof(T) * (deque->size + 1));
	return deque;
}

bool isFull(Deque *deq) {
	if (deq->numOfElements == deq->size - 1) {
		return true;
	}
	return false;
}

void appendLeft(Deque *deq, T element) {
	if (isFull(deq)) {
		printf("Deque Overflow\n");
		return;
	}
	if (deq->numOfElements == 0) {
		deq->elements[0] = element;
		deq->left = deq->size;
		deq->right = 1;
		return;
	}
	deq->elements[deq->left] = element;
	if (deq->left == 0) {
		deq->left == size;
	}
	else {
		deq->left--;
	}
}
