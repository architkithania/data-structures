#include <stdio.h>
#include <stdlib.h>

#define EMPTY_RETURN 0

typedef int T;

typedef struct node_t {
	T val;
	struct node_t *prev;
}	Node;

typedef struct {
	Node *head;
	Node *tail;
}	Queue;

Node *newNode(T val) {
	Node *node = malloc(sizeof(Node));
	node->val = val;
	node->prev = NULL;
	return node;
}

Queue *newQueue() {
	Queue *q = malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;
	return q;
}

void enqueue(Queue *q, T element) {
	if (q->tail == NULL) {
		q->tail = newNode(element);
		q->head = q->tail;
	}
	else {
		q->tail->prev = newNode(element);
		q->tail = q->tail->prev;
	}
}

T dequeue(Queue *q) {
	if (q->head == NULL) {
		printf("Queue Underflow\n");
		return EMPTY_RETURN;
	}
	Node *temp = q->head;
	q->head = q->head->prev;
	if (q->head == NULL) {
		q->tail = NULL;
	}
	T val = temp->val;
	free(temp);
	return val;
}

void printQueue(Queue *q) {
	Node *head = q->head;
	printf("[");
	while (head != NULL) {
		if (head->prev == NULL) {
			printf("%d", head->val);
		}
		else {
			printf("%d,", head->val);
		}
		head = head->prev;
	}
	printf("]\n");
}

int main(void) {
	Queue *q = newQueue();
	return 0;
}
