#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX_SIZE 50

typedef struct {
	int y, x;
}pos;

pos queue[MAX_SIZE * MAX_SIZE];

char Map[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];

int w, h;

int dy[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void bfs() {
	memset(visited, false, sizeof(visited));
	int ans = 0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (!visited[y][x] && Map[y][x] == '1') {
				ans++;
				visited[y][x] = true;
				int front = 0, rear = 0;

				queue[rear++] = (pos){ y, x };

				while (front < rear) {
					pos cur = queue[front++];

					for (int d = 0; d < 8; d++) {
						int ny = cur.y + dy[d];
						int nx = cur.x + dx[d];

						if (ny >= 0 && ny < h && nx >= 0 && nx < w && !visited[ny][nx] && Map[ny][nx] == '1') {
							visited[ny][nx] = true;
							queue[rear++] = (pos){ ny, nx };
						}
					}
				}
			}
		}
	}
	printf("%d\n", ans);
}

int main() {
	while (true) {
		scanf("%d %d", &w, &h);
		if (w == 0 && h == 0) break;

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				scanf(" %c", &Map[y][x]);
			}
		}

		bfs();
	}

	return 0;
}