#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY_RETURN 0

typedef int T;

typedef struct {
	int size;
	int head;
	int tail;
	T *elements;
}	Queue;

Queue *newQueue(int size) {
	Queue *q = malloc(sizeof(Queue));
	q->size = size;
	q->head = 0;
	q->tail = 0;
	q->elements = malloc(sizeof(T) * (size + 1));
	return q;
}

bool isFull(Queue *q) {
	if (q->head == ((q->tail + 1) % (q->size + 1)))
		return true;
	return false;
}

bool isEmpty(Queue *q) {
	if (q->head == q->tail)
		return true;
	return false;
}

void enqueue(Queue *q, T element) {
	if (isFull(q)) {
		printf("Queue Overflow");
		return;
	}
	q->elements[q->tail] = element;
	if (q->tail == q->size) {
		q->tail = 0;
	}
	else {
		q->tail++;
	}
}

T dequeue(Queue *q) {
	if (isEmpty(q)) {
		printf("Queue Underflow");
		return EMPTY_RETURN;
	}
	T temp = q->elements[q->head];
	if (q->head == q->size) {
		q->head = 0;
	}
	else {
		q->head = q->head + 1;
	}
	return temp;
}

void printQueue(Queue *q) {
	int printed = 0;
	printf("[");
	int head = q->head;
	int tail = q->tail;
	int elements = (tail < head ? tail + q->size + 1 - head: tail - head);
	while (head != tail) {
		if (printed != elements - 1) {
			printf("%d,", q->elements[head]);
			printed++;
			if (head == q->size) {
				head = 0;
			}
			else {
				head++;
			}
		}
		else {
			printf("%d", q->elements[head]);
			break;
		}
	}
	printf("]\n");
}

int main(void) {
	Queue *q = newQueue(5);
	for (int i = 0; i < 5; i++) {
		enqueue(q, i);
	}
	printQueue(q);
	for (int i = 0; i < 3; i++) {
		dequeue(q);
		printQueue(q);
	}
	enqueue(q, 11);
	printQueue(q);
	return 0;
}
