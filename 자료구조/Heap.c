#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int* data;
	int size;
	int capacity;
}Heap;

Heap* createHeap(int capacity) {
	Heap* heap = malloc(sizeof(Heap));
	heap->capacity = capacity;

	heap->data = malloc(sizeof(int) * (capacity + 1));
	heap->size = 0;

	return heap;
}

void swap(int* a, int* b) {
	int tmp = *b;
	*b = *a;
	*a = tmp;
}

void insertMinHeap(Heap* heap, int value) {
	if (heap->size >= heap->capacity) {
		heap->capacity *= 2;
		heap->data = realloc(heap->data, (heap->capacity + 1) * sizeof(int));
	}
	heap->size++;
	heap->data[heap->size] = value;

	int i = heap->size;
	while (i > 1 && heap->data[i] < heap->data[i / 2]) {
		swap(&heap->data[i], &heap->data[i / 2]);
		i /= 2;
	}
}

void insertMaxHeap(Heap* heap, int value) {
	if (heap->size >= heap->capacity) {
		heap->capacity *= 2;
		heap->data = realloc(heap->data, (heap->capacity + 1) * sizeof(int));
	}
	heap->size++;
	heap->data[heap->size] = value;

	int i = heap->size;
	while (i > 1 && heap->data[i] > heap->data[i / 2]) {
		swap(&heap->data[i], &heap->data[i / 2]);
		i /= 2;
	}
}

int removeMin(Heap* heap) {
	if (heap->size == 0) return -1;
	int min = heap->data[1];
	heap->data[1] = heap->data[heap->size];
	heap->size--;
	
	int i = 1;

	while (2 * i <= heap->size) {
		int smallest = 2 * i;
		if (2 * i + 1 <= heap->size && heap->data[i * 2 + 1] < heap->data[smallest])
			smallest = i * 2 + 1;
		if (heap->data[smallest] > heap->data[i])
			break;
		swap(&heap->data[i], &heap->data[smallest]);
		i = smallest;
	}
	return min;
}

int removeMax(Heap* heap) {
	if (heap->size == 0) return -1;
	int max = heap->data[1];
	heap->data[1] = heap->data[heap->size];
	heap->size--;

	int i = 1;

	while (2 * i <= heap->size) {
		int largest = i * 2;
		if (i * 2 + 1 <= heap->size && heap->data[i * 2 + 1] > heap->data[largest])
			largest = i * 2 + 1;
		if (heap->data[largest] < heap->data[i])
			break;
		swap(&heap->data[i], &heap->data[largest]);
		i = largest;
	}
	return max;
}

void freeHeap(Heap* heap) {
	free(heap->data);
	free(heap);
}

int main(void) {
	Heap* minheap = createHeap(10);
	insertMinHeap(minheap, 5);
	insertMinHeap(minheap, 3);
	insertMinHeap(minheap, 8);
	insertMinHeap(minheap, 17);
	insertMinHeap(minheap, 31);
	insertMinHeap(minheap, 21);
	insertMinHeap(minheap, 1);

	Heap* maxheap = createHeap(10);
	insertMaxHeap(maxheap, 5);
	insertMaxHeap(maxheap, 3);
	insertMaxHeap(maxheap, 8);
	insertMaxHeap(maxheap, 17);
	insertMaxHeap(maxheap, 31);
	insertMaxHeap(maxheap, 21);
	insertMaxHeap(maxheap, 1);


	while (minheap->size > 0) {
		printf("%d ", removeMin(minheap));
	}
	printf("\n");

	freeHeap(minheap);

	while (maxheap->size > 0) {
		printf("%d ", removeMax(maxheap));
	}
	printf("\n");

	freeHeap(maxheap);


	return 0;
}