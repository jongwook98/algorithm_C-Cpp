#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 8
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
	int y, x;
}pos;

int N, M;

int Map[MAX_SIZE][MAX_SIZE];
int init_ans;
int ans;

int init_virus;

pos init_queue[MAX_SIZE * MAX_SIZE];

pos wall_queue[3];
bool init_visited[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];

int init_front, init_rear;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

void bfs() {
	int front = 0, rear = init_virus;
	int safety_area = init_ans - 3;
	pos queue[MAX_SIZE * MAX_SIZE];

	for (int i = 0; i < init_virus; i++) {
		queue[i] = init_queue[i];
	}

	memcpy(visited, init_visited, sizeof(init_visited));

	for (int i = 0; i < 3; i++) {
		visited[wall_queue[i].y][wall_queue[i].x] = true;
	}

	while (front < rear) {
		int cy = queue[front].y;
		int cx = queue[front++].x;

		for (int d = 0; d < 4; d++) {
			int ny = cy + dy[d];
			int nx = cx + dx[d];

			if (ny >= 0 && ny < N && nx >= 0 && nx < M && !visited[ny][nx] && Map[ny][nx] == 0) {
				visited[ny][nx] = true;
				safety_area--;
				queue[rear++] = (pos){ ny, nx };
			}
		}
	}
	ans = max(safety_area, ans);
}

void dfs(int xy, int num) {
	if (num == 3) {
		bfs();
	}
	else if (xy < M*N) {
		if (Map[xy / M][xy % M] == 0) {
			wall_queue[num] = (pos){ xy / M, xy % M };
			dfs(xy + 1, num + 1);
		}
		dfs(xy + 1, num);
	}
}

int main() {
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &Map[i][j]);

			if (Map[i][j] == 2) {
				init_queue[init_rear++] = (pos){ i, j };
				init_virus++;
				init_visited[i][j] = true;
			}
			else if (Map[i][j] == 0) {
				init_ans++;
			}
		}
	}

	dfs(0, 0);

	printf("%d", ans);

	return 0;
}