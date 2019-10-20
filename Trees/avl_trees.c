#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct node_t {
	int height;
	int bf;
	int val;
	struct node_t *left;
	struct node_t *right;
}	Node;

Node *newNode(T val) {
	Node *node = malloc(sizeof(Node));
	node->val = val;
	node->height = 0;
	node->left = NULL;
	node->right = NULL;
	node->bf = 0;
	return node;
}

Node *find(Node *node, T val) {
	if (node == NULL) {
		return NULL;
	}
	if (node->val > val) {
		return find(node->left, val);
	}
	else {
		return find(node->right, val);
	}
}

Node *findMax(Node *node) {
	if (node->right == NULL) {
		return node;
	}
	return findMax(node->right);
}

Node *findMin(Node *node) {
	if (node->left == NULL) {
		return node;
	}
	return findMin(node->left);
}

void update(Node *node) {
	int leftNodeHeight = (node->left == NULL ? -1 : node->left->height);
	int rightNodeHeight = (node->right == NULL ? -1 : node->right->height);
	node->height = 1 + (leftNodeHeight > rightNodeHeight ? leftNodeHeight : rightNodeHeight);
	node->bf = rightNodeHeight - leftNodeHeight;
}

Node *leftRotation(Node *node) {
	Node *newParent = node->right;
	node->right = newParent->left;
	newParent->left = node;
	update(node);
	update(newParent);
	return newParent;
}

Node *rightRotation(Node *node) {
	Node *newParent = node->left;
	node->left = newParent->right;
	newParent->right = node;
	update(node);
	update(newParent);
	return newParent;
	
}

Node *balance(Node *node) {
	if (node->bf == -2) {
		// LL Case
		if (node->left->bf <= 0) {
			return rightRotation(node);
		}
		// LR Case
		else {
			node->left = leftRotation(node->left);
			return rightRotation(node);
		}
	}
	else if (node->bf == 2) {
		// RR Case
		if (node->right->bf >= 0) {
			return leftRotation(node);
		}
		// RL Case
		else {
			node->right = rightRotation(node->right);
			return leftRotation(node);
		}
	}
	return node;
}

Node *insert(Node *node, T val) {
	if (node == NULL) {
		return newNode(val);
	}
	if (node->val > val) {
		node->left = insert(node->left, val);
	}
	else if (node->val < val) {
		node->right = insert(node->right, val);
	}
	update(node);
	return balance(node);
}

Node *delete(Node *node, T val) {
	if (node->val > val) {
		node->left = delete(node->left, val);
	}
	else if (node->val < val) {
		node->right = delete(node->right, val);
	}
	else {
		if (node->left == NULL) {
			Node *temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) {
			Node *temp = node->left;
			free(node);
			return temp;
		}
		else {
			if (node->left->height > node->right->height) {
				Node *max = findMax(node->left);
				node->val = max->val;
				node->left = delete(node->left, max->val);
			}
			else {
				Node *min = findMin(node->right);
				node->val = min->val;
				node->right = delete(node->right, min->val);
			}
		}
	}
	update(node);
	return balance(node);
}

void printTree(Node *node) {
	if (node == NULL) {
		return;
	}
	printTree(node->left);
	printf("%d ", node->val);
	printTree(node->right);
}

int main(void) {
	Node *root = NULL;
	for (int i = 8; i >= 0; i--) {
		root = insert(root, i);
		printTree(root);
		printf("\n");
	}
	for (int i = 0; i <= 8; i++) {
		root = delete(root, i);
		printTree(root);
		printf("\n");
	}
	return 0;
}
