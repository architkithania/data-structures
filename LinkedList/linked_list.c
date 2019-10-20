#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct node_t {
	T val;
	struct node_t *next;
}	Node;

Node *newNode(T element) {
	Node *node = malloc(sizeof(Node));
	node->val = element;
	node->next = NULL;
	return node;
}

Node *append(Node *root, T element) {
	Node *current = root;
	if (current == NULL) {
		
		return newNode(element);
	}
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newNode(element);
	return root;
}

Node *insert(Node *root, T element, int i) {
	if (i == 0) {
		Node *newRoot = newNode(element);
		newRoot->next = root;
		return newRoot;
	}
	Node *current = root;
	for (int j = 1; j < i; j++) {
		current = current->next;
	} 
	Node *nodeToInsert = newNode(element);
	Node *headNext = current->next;
	current->next = nodeToInsert;
	nodeToInsert->next = headNext;
	return root;
}

Node *delete(Node *root, int i) {
	if (i == 0) {
		Node *newRoot = root->next;
		free(root);
		return newRoot;
	}
	Node *current = root;
	for (int j = 1; j < i; j++) {
		current = current->next;
	}
	Node *nextInLine = current->next->next;
	free(current->next);
	current->next = nextInLine;
	return root;
}

int size(Node *root) {
	if (root == NULL) {
		return 0;
	}
	Node *current = root;
	int size = 1;
	while (current->next != NULL) {
		current = current->next;
		size++;
	}
	return size;
}

Node *reverseList(Node *root) {
	Node *prev, *next, *head;
	if (root == NULL || root->next == NULL) {
		return root;
	}
	prev = NULL;
	head = root;
	while (head != NULL) {
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}
	return prev;
}

void printList(Node *root) {
	Node *current = root;
	if (root == NULL) {
		printf("[]\n");
	}
	else if (current->next == NULL) {
		printf("[%d]\n", current->val);
	}
	else {
		printf("[");
		while (current->next->next != NULL) {
			printf("%d,", current->val);
			current = current->next;
		}
		printf("%d,%d]\n", current->val, current->next->val);
	}
}

int main(void) {
	Node *root = newNode(0);
	for (int i = 1; i < 10; i++) {
		root = insert(root, i, size(root));
	}
	root = reverseList(root);
	printList(root);
	return 0;
}
