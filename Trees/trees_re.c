#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct node_t {
	T val;
	struct node_t *left;
	struct node_t *right;
}	Node;

Node *newNode(T val) {
	Node *node = malloc(sizeof(Node));
	node->val = val;
	node->left = node->right = NULL;
	return node;
}

Node *insert(Node *node, T val) {
	if (node == NULL) {
		return newNode(val);
	}
	if (node->val > val) {
		node->left = insert(node->left, val);
	}
	else {
		node->right = insert(node->right, val);
	}
	return node;
}

Node *findMin(Node *root) {
	Node *parent = NULL;
	Node *current = root;
	while (current != NULL) {
		parent = current;
		current = current->left;
	}
	return parent;
}

Node *delete(Node *node, T val) {
	if (node == NULL) {
		printf("Tree is Empty\n");
		return node;
	}
	if (node->val > val) {
		node->left = delete(node->left, val);
	}
	else if (node->val < val) {
		node->right = delete(node->right, val);
	}
	else {
		if (node->left != NULL && node->right != NULL) {
			Node *min = findMin(node->right);
			T temp = min->val;
			node->right = delete(node->right, min->val);
			node->val = temp;
		}
		else {
			Node *temp = node;
			if (node->right == NULL) {
				node = node->left;
			}
			else {
				node = node->right;
			}
			free(temp);
		}
	}
	return node;
}

void printTree(Node *node) {
	if (node == NULL) {
		return;
	}
	printTree(node->left);
	printf("%d\n", node->val);
	printTree(node->right);
}

int main(void) {
	Node *node = newNode(10);
	node = insert(node, 12);
	node = insert(node, 5);
	node = insert(node, 11);
	node = insert(node, 15);
	delete(node, 12);
	printTree(node);
	return 0;
}
