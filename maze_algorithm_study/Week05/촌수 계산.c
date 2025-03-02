#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>

#define MAX_NODES 101

int visited[MAX_NODES];

int adj[MAX_NODES][MAX_NODES];
int adj_size[MAX_NODES];

void dfs(int s, int e, int cnt) {
	if (s != e) {
		for (int i = 0; i < adj_size[s]; i++) {
			int next = adj[s][i];
			if (visited[next] == 0) {
				visited[next] = cnt + 1;
				dfs(next, e, cnt + 1);
			}
		}
	}
}

int main() {
	int n; 
	int a, b;
	int m;

	int x, y;

	scanf("%d", &n);
	scanf("%d %d", &a, &b);
	scanf("%d", &m);
	
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		adj[x][adj_size[x]++] = y;
		adj[y][adj_size[y]++] = x;
	}

	visited[a] = 1; // 방문 체크
	dfs(a, b, 0);

	if (visited[b] == 0) {
		printf("%d", -1);
	}
	else {
		printf("%d", visited[b]);
	}

	return 0;
}