#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int T;

typedef struct node_t {
	T val;
	struct node_t *left;
	struct node_t *right;
}	Node;

typedef struct {
	Node *root;
}	Tree;

Tree *newTree(Node *root) {
	Tree *tree = malloc(sizeof(Tree));
	tree->root = root;
	return tree;
}

Node *newNode(T val) {
	Node *node = malloc(sizeof(Node));
	node->val = val;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void insert(Tree *tree, Node *node) {
	if (tree->root == NULL) {
		tree->root = node;
		return;
	}
	Node *parent = NULL;
	Node *current = tree->root;
	while (current != NULL) {
		parent = current;
		if (current->val > node->val) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	if (parent->val > node->val) {
		parent->left = node;
	}
	else {
		parent->right = node;
	}
}

Node *find(Node *node, T val) {
	if (node == NULL) {
		return NULL;
	}
	if (val < node->val) {
		node = node->left;
		return find(node, val);
	}
	else if (val > node->val) {
		node = node->right;
		return find(node, val);
	}
	else {
		return node;
	}
}

Node *findParent(Node *node, T val) {
	Node *parent = NULL;
	Node *current = node;
	while (current->val != val) {
		parent = current;
		if (current->val > val) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return parent;
}

Node *findMin(Tree *tree) {
	Node *current = tree->root;
	Node *parent = NULL;
	while (current != NULL) {
		parent = current;
		current = current->left;
	}
	return parent;
}

Node *findMax(Tree *tree) {
	Node *current = tree->root;
	Node *parent = NULL;
	while (current != NULL) {
		parent = current;
		current = current->right;
	}
	return parent;
}

Node *delete(Node *node, T val) {
	if (node == NULL) {
		printf("No such node");
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
			Node *min = findMin(newTree(node->right));
			node->val = min->val;
			node->right = delete(node->right, node->val);
		}
		else {
			Node *temp = node;
			if (node->right == NULL) {
				node = node->left;
			}
			else node = node->right;
			free(temp);
		}
	}
	return node;
}

int main(void) {
	Tree *tree = newTree(NULL);
	insert(tree, newNode(5));
	insert(tree, newNode(3));
	insert(tree, newNode(11));
	insert(tree, newNode(12));
	insert(tree, newNode(10));
	tree->root = delete(tree->root, 24);
	tree->root = delete(tree->root, 11);
	return 0;
}
