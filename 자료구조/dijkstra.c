#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF (int)1e9

typedef struct Edge {
	int to, weight;
	struct Edge* next;
}Edge;

Edge* graph[1000];

void addEdge(int u, int v, int w) {
	Edge* edge = malloc(sizeof(Edge));
	edge->to = v;
	edge->weight = w;
	edge->next = graph[u];
	graph[u] = edge;
}

typedef struct {
	int vertex, dist;
}Node;

typedef struct {
	Node* data;
	int size;
	int capacity;
}MinHeap;

MinHeap* createHeap(int capacity) {
	MinHeap* heap = malloc(sizeof(MinHeap));
	heap->capacity = capacity;
	heap->size = 0;
	heap->data = malloc((capacity + 1) * sizeof(Node));
	return heap;
}

void swapNode(Node* a, Node* b) {
	Node temp = *a;
	*a = *b;
	*b = temp;
}

void pushMinHeap(MinHeap* heap, int vertex, int dist) {
	if (heap->size >= heap->capacity) {
		heap->capacity *= 2;
		heap->data = realloc(heap->data, (heap->capacity + 1) * sizeof(Node));
	}
	heap->size++;
	heap->data[heap->size] = (Node){ vertex, dist };

	int i = heap->size;
	while (i > 1 && heap->data[i].dist < heap->data[i / 2].dist) {
		swapNode(&heap->data[i], &heap->data[i / 2]);
		i /= 2;
	}
}

Node popMinHeap(MinHeap* heap) {
	if (heap->size == 0) return (Node) { -1, -1 };
	Node top = heap->data[1];
	heap->data[1] = heap->data[heap->size--];

	int i = 1;
	while (i * 2 <= heap->size) {
		int smallest = i * 2;
		if (i * 2 + 1 <= heap->size && heap->data[i * 2 + 1].dist < heap->data[smallest].dist)
			smallest = i * 2 + 1;
		if (heap->data[i].dist < heap->data[smallest].dist) break;
		swapNode(&heap->data[i], &heap->data[smallest]);

		i = smallest;
	}
	return top;
}

void freeMinHeap(MinHeap* heap) {
	free(heap->data);
	free(heap);
}

void dijkstra(int source, int n) {
	int* dist = malloc(n * sizeof(int));
	bool* visited = malloc(n * sizeof(bool));
	for (int i = 0; i < n; i++) {
		dist[i] = INF;
		visited[i] = false;
	}
	dist[source] = 0;

	MinHeap* heap = createHeap(10);
	pushMinHeap(heap, source, 0);

	while (heap->size > 0) {
		Node node = popMinHeap(heap);
		int u = node.vertex;
		if (visited[u]) continue;
		visited[u] = true;

		for (Edge* e = graph[u]; e != NULL; e = e->next) {
			int v = e->to;
			int w = e->weight;
			if (!visited[v] && dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pushMinHeap(heap, v, dist[v]);
			}
		}
	}

	printf("정점 %d에서 시작한 최단 거리:\n", source);
	for (int i = 0; i < n; i++) {
		if (dist[i] == INF)
			printf("%d: INF\n", i);
		else
			printf("%d: %d\n", i, dist[i]);
	}

	free(dist);
	free(visited);
	freeMinHeap(heap);
}

int main(void) {
	int n, m;
	// n: 정점 수, m: 간선 수 (0-indexed 또는 1-indexed에 맞춰 입력)
	scanf("%d %d", &n, &m);

	// 그래프 배열 초기화
	for (int i = 0; i < n; i++) {
		graph[i] = NULL;
	}

	// m개의 간선 입력 (예: u v w)
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		// 만약 입력이 0-indexed가 아니라면 u, v에 -1을 해줍니다.
		addEdge(u, v, w);
		// 무방향 그래프인 경우 아래도 추가:
		addEdge(v, u, w);
	}

	int source;
	scanf("%d", &source);

	dijkstra(source, n);

	// 할당된 간선 메모리 해제
	for (int i = 0; i < n; i++) {
		Edge* e = graph[i];
		while (e) {
			Edge* temp = e;
			e = e->next;
			free(temp);
		}
	}

	return 0;
}