#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX_SIZE 50

typedef struct {
	int x, y;
}pos;

bool Map[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];

pos queue[MAX_SIZE * MAX_SIZE];

int M, N, K;

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

void bfs() {
	int ans = 0;

	memset(visited, false, sizeof(visited));

	for (int x = 0; x < M; x++) {
		for (int y = 0; y < N; y++) {
			if (Map[x][y] && !visited[x][y]) {
				ans++;

				int front = 0, rear = 0;
				queue[rear++] = (pos){ x, y };
				visited[x][y] = true;

				while (front < rear) {
					pos cur = queue[front++];

					for (int d = 0; d < 4; d++) {
						int nx = cur.x + dx[d];
						int ny = cur.y + dy[d];

						if (nx >= 0 && nx < M && ny >= 0 && ny < N && !visited[nx][ny] && Map[nx][ny]) {
							visited[nx][ny] = true;
							queue[rear++] = (pos){ nx, ny };
						}
					}
				}
			}
		}
	}

	printf("%d\n", ans);
}

int main() {
	int T;
	scanf(" %d", &T);

	while (T--) {
		scanf("%d %d %d", &M, &N, &K);
		memset(Map, false, sizeof(Map));

		for (int i = 0; i < K; i++) {
			int x, y;
			scanf("%d %d", &x, &y);

			Map[x][y] = true;
		}

		bfs();
	}

	return 0;
}