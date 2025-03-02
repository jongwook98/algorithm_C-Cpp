#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

#define MAP_SIZE 101

typedef struct {
	int y, x;
}pos;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

char map[MAP_SIZE][MAP_SIZE];
int visited[MAP_SIZE][MAP_SIZE];

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf(" %c", &map[i][j]);
		}
	}

	pos queue[MAP_SIZE * MAP_SIZE];
	visited[1][1] = 1;
	int front = 0, rear = 0;

	queue[rear++] = (pos){ 1, 1 };

	while (front < rear) {
		int cy = queue[front].y;
		int cx = queue[front++].x;

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny > 0 && ny <= N && nx > 0 && nx <= M && map[ny][nx] == '1') {
				if (visited[ny][nx] == 0) {
					queue[rear++] = (pos){ ny, nx };

					visited[ny][nx] = visited[cy][cx] + 1;
				}
			}
		}
	}

	printf("%d", visited[N][M]);

	return 0;
}