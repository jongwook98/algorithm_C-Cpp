#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1001

int adj[MAX_NODES][MAX_NODES];
int adj_size[MAX_NODES];
bool visited[MAX_NODES];
int queue[MAX_NODES];

int compare(const void* A, const void* B) {
	return *(int*)A - *(int*)B;
}

void dfs(int cur) {
	printf("%d ", cur);
	visited[cur] = true;

	for (int i = 0; i < adj_size[cur]; i++) {
		int next = adj[cur][i];
		if (!visited[next]) {
			dfs(next);
		}
	}
}
void bfs(int start) {
	int front = 0, rear = 0;
	queue[rear++] = start;
	visited[start] = true;

	while (front < rear) {
		int cur = queue[front++];
		printf("%d ", cur);

		for (int i = 0; i < adj_size[cur]; i++) {
			int next = adj[cur][i];
			if (!visited[next]) {
				queue[rear++] = next;
				visited[next] = true;
			}
		}
	}
}

int main() {
	int N, M, V;
	scanf("%d %d %d", &N, &M, &V);

	for (int i = 0; i < M; i++) {
		int A, B;
		scanf("%d %d", &A, &B);

		adj[A][adj_size[A]++] = B;
		adj[B][adj_size[B]++] = A;
	}
	
	for (int i = 1; i <= N; i++) {
		qsort(adj[i], adj_size[i], sizeof(int), compare);
	}

	memset(visited, false, sizeof(visited));
	dfs(V);
	printf("\n");

	memset(visited, false, sizeof(visited));
	bfs(V);
	printf("\n");

	return 0;
}