#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 101

typedef struct {
	int x, y, h;
}pos;

int Map[MAX_SIZE][MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE][MAX_SIZE];
pos queue[MAX_SIZE * MAX_SIZE * MAX_SIZE];

int day = 0;
int unripe = 0;
int ripe = 0;
int front = 0, rear = 0;

int M, N, H;

int dx[] = { 1, -1, 0, 0, 0, 0 };
int dy[] = { 0, 0, 1, -1, 0, 0 };
int dh[] = { 0, 0, 0, 0, 1, -1 };

void bfs() {
	while (unripe > 0) {
		bool flag = true;
		int rep = rear - front;

		while (rep--) {
			int cx = queue[front].x;
			int cy = queue[front].y;
			int ch = queue[front++].h;

			for (int d = 0; d < 6; d++) {
				int nx = cx + dx[d];
				int ny = cy + dy[d];
				int nh = ch + dh[d];

				if (nx >= 0 && nx < M && ny >= 0 && ny < N && nh >= 0 && nh < H && !visited[nx][ny][nh] && Map[nx][ny][nh] == 0) {
					visited[nx][ny][nh] = true;
					unripe--;
					queue[rear++] = (pos){ nx, ny, nh };

					flag = false;
				}
			}
		}
		day++;
		if (flag == true) {
			break;
		}
	}

	if (unripe > 0) printf("%d", -1);
	else printf("%d", day);
}

int main() {
	scanf("%d %d %d", &M, &N, &H);

	for (int h = 0; h < H; h++) {
		for (int n = 0; n < N; n++) {
			for (int m = 0; m < M; m++) {
				scanf(" %d", &Map[m][n][h]);

				if (Map[m][n][h] == 0) unripe++;
				else if (Map[m][n][h] == 1) {
					queue[rear++] = (pos){ m, n, h };
					visited[m][n][h] = true;
				}
			}
		}
	}

	bfs();

	return 0;
}