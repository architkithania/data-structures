#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int size;
    int capacity;
    int *elements;
    int lastUsedIndex;
}   *ArrayList;

ArrayList newArrayList(int capacity) {
    ArrayList arr = malloc(sizeof(ArrayList));
    arr->capacity = capacity;
    arr->size = 0;
    arr->elements = calloc(capacity, sizeof(int));
    return arr;
}

bool expand(ArrayList arr) {
    printf("expanding\n");
    int *tempElems = realloc(arr->elements, arr->capacity * 2);
    if (tempElems == NULL) {
        return false;
    }
    arr->capacity *= 2;
    arr->elements = tempElems;
    return true;
}

void add(ArrayList arr, int x) {
    if (arr->capacity == arr->size) {
        expand(arr);
    }
    arr->elements[arr->lastUsedIndex] = x;
    arr->lastUsedIndex++;
    arr->size++;
}

int get(ArrayList arr, int i) {
    return arr->elements[i];
}

void set(ArrayList arr, int i, int x) {
    if (i <= arr->capacity - 1) {
        arr->elements[i] = x;
        arr->size++;
        return;
    }
    expand(arr);
    set(arr, i, x);
}

int main(void) {
    int i;
    ArrayList list = newArrayList(10);
    for (int i = 0; i < 30; i++) {
        set(list, i, i * 2);
    }
    return 0;
}
