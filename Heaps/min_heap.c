#include <stdio.h>
#include <stdlib.h>

#define EMPTY_RETURN 0

typedef int T;

typedef struct {
	int size;
	int capacity;
	T *elements;
}	Heap;

Heap *newHeap(int capacity) {
	Heap *heap = malloc(sizeof(Heap));
	heap->capacity = capacity;
	heap->size = 0;
	heap->elements = malloc(sizeof(T) * (capacity + 1));
	return heap;
}

int leftNode(int i) {
	return i << 1;
}

int rightNode(int i) {
	return (i << 1) + 1;
}

int parentNode(int i) {
	return i >> 1;
}

void swap(Heap *heap, int ind1, int ind2) {
	T temp = heap->elements[ind1];
	heap->elements[ind1] = heap->elements[ind2];
	heap->elements[ind2] = temp;
}

void minHeapify(Heap *heap, int i) {
	int left = leftNode(i);
	int right = rightNode(i);
	int smallest = i;
	if (left <= heap->size && heap->elements[left] < heap->elements[smallest]) {
		smallest = left;
	}
	if (right <= heap->size && heap->elements[right] < heap->elements[smallest]) {
		smallest = right;
	}
	if (smallest != i) {
		swap(heap, i, smallest);
		minHeapify(heap, smallest);
	}
}

T extractMin(Heap *heap) {
	if (heap->size < 1) {
		printf("Heap Underflow");
		return EMPTY_RETURN;
	}
	T min = heap->elements[1];
	heap->elements[1] = heap->elements[heap->size];
	heap->size--;
	minHeapify(heap, 1);
	return min;
}

void decreaseKey(Heap *heap, int i, T key) {
	heap->elements[i] = key;
	while (i > 1 && heap->elements[i] < heap->elements[parentNode(i)]) {
		swap(heap, i, parentNode(i));
		i = parentNode(i);
	}
}

void insert(Heap *heap, T key) {
	if (heap->size == heap->capacity) {
		printf("Heap Overflow");
		return;
	}
	heap->size++;
	heap->elements[heap->size] = 0;
	decreaseKey(heap, heap->size, key);
}

void delete(Heap *heap, int i) {
	if (heap->size == 0) {
		printf("Heap Underflow\n");
		return;
	}
	swap(heap, i, heap->size);
	printf("heap[i] is %d\n", heap->elements[i]);
	heap->size--;
	minHeapify(heap, i);
}

void printHeap(Heap *heap) {
	int i;
	printf("[");
	for (i = 1; i < heap->size; i++) {
		printf("%d,", heap->elements[i]);
	}
	if (heap->size != 0) {
		printf("%d", heap->elements[heap->size]);
	}
	printf("]\n");
}

int main(void) {
	int i;
	Heap *heap = newHeap(20);
	for (i = 0; i < 10; i++) {
		int num = (rand() % (100 - 1 + 1)) + 1;
		insert(heap, num);
	}
	printHeap(heap);
	delete(heap, 2);
	printHeap(heap);
	return 0;
}
