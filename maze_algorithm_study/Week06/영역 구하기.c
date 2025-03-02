#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX_SIZE 100

typedef struct {
	int y, x;
}pos;

pos queue[MAX_SIZE * MAX_SIZE];

bool Map[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];

int ans_size;
int ans[MAX_SIZE * MAX_SIZE];

int M, N, K;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int compare(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

void bfs() {
	for (int y = 0; y < M; y++) {
		for (int x = 0; x < N; x++) {
			if (!visited[y][x] && !Map[y][x]) {
				int front = 0, rear = 0;
				queue[rear++] = (pos){ y, x };
				visited[y][x] = true;

				ans[ans_size]++;

				while (front < rear) {
					pos cur = queue[front++];

					for (int d = 0; d < 4; d++) {
						int ny = cur.y + dy[d];
						int nx = cur.x + dx[d];

						if (ny >= 0 && ny < M && nx >= 0 && nx < N && !visited[ny][nx] && !Map[ny][nx]) {
							visited[ny][nx] = true;
							queue[rear++] = (pos){ ny, nx };

							ans[ans_size]++;
						}
					}
				}
				ans_size++;
			}
		}
	}
	qsort(ans, ans_size, sizeof(int), compare);
}

int main() {
	scanf("%d %d %d", &M, &N, &K);

	for (int i = 0; i < K; i++) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		for (int x = x1; x < x2; x++) {
			for (int y = y1; y < y2; y++) {
				Map[y][x] = true;
			}
		}
	}

	bfs();

	printf("%d\n", ans_size);
	for (int i = 0; i < ans_size; i++) {
		printf("%d ", ans[i]);
	}

	return 0;
}