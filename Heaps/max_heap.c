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

int parentNode(int i) {
	return i >> 1;
}

int leftNode(int i) {
	return i << 1;
}

int rightNode(int i) {
	return (i << 1) + 1;
}

void swap(Heap *heap, int ind1, int ind2) {
	T temp = heap->elements[ind1];
	heap->elements[ind1] = heap->elements[ind2];
	heap->elements[ind2] = temp;
}

void maxHeapify(Heap *heap, int i) {
	int left = leftNode(i);
	int right = rightNode(i);
	int largest = i;
	if (left <= heap->size && heap->elements[largest] < heap->elements[left]) {
		largest = left;
	}
	if (right <= heap->size && heap->elements[largest] < heap->elements[right]) {
		largest = right;
	}
	if (largest != i) {
		swap(heap, i, largest);
		maxHeapify(heap, largest);
	}
}

T extractMax(Heap *heap) {
	if (heap->size < 1) {
		printf("Heap Underflow\n");
		return EMPTY_RETURN;
	}
	T max = heap->elements[1];
	heap->elements[1] = heap->elements[heap->size];
	heap->size--;
	maxHeapify(heap, 1);
	return max;
}

void increaseKey(Heap *heap, int i, T key) {
	heap->elements[i] = key;
	while (i > 1 && heap->elements[parentNode(i)] < heap->elements[i]) {
		swap(heap, parentNode(i), i);
		i = parentNode(i);
	}
}

void insert(Heap *heap, T key) {
	if (heap->size >= heap->capacity) {
		printf("Heap Overflow\n");
		return;
	}
	heap->size++;
	heap->elements[heap->size] = 0;
	increaseKey(heap, heap->size, key);
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
	for (i = 1; i <= 10; i++) {
		insert(heap, i);
	}
	printHeap(heap);
	insert(heap, 15);
	printHeap(heap);
	return 0;
}
