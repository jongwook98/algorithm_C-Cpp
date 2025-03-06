#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int* data;
	int front, rear;
	int capacity;
}queue;

queue* createQueue(int capacity) {
	queue* Q = malloc(sizeof(queue));
	Q->capacity = 4;
	Q->front = 0; Q->rear = 0;
	Q->data = malloc(sizeof(int) * Q->capacity);

	return Q;
}

void clearQueue(queue* Q) {
	Q->front = 0; Q->rear = 0;
}

void freeQueue(queue* Q) {
	free(Q->data);
	free(Q);
}

void pushQueue(queue* Q, int value) {
	if (Q->rear >= Q->capacity) {
		Q->capacity *= 2;
		Q->data = realloc(Q->data, sizeof(int) * Q->capacity);
	}
	Q->data[Q->rear++] = value;
}

int popQueue(queue* Q) {
	if (Q->front >= Q->rear) return -1;

	return Q->data[Q->front++];
}

int main() {
	queue* Q = createQueue(10);
	pushQueue(Q, 3);
	pushQueue(Q, 7);
	pushQueue(Q, 1);
	pushQueue(Q, 5);
	pushQueue(Q, 16);
	pushQueue(Q, 36);

	while (Q->front < Q->rear) {
		printf("%d\n", popQueue(Q));
	}

	printf("%d", popQueue(&Q));
	printf("%d", popQueue(&Q));

	return 0;
}