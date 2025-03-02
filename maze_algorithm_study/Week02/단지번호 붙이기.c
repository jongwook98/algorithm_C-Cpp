#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 25

typedef struct {
	int y, x;
}pos;

int dy[] = { 0, 0, -1, 1 };
int dx[] = { 1, -1, 0, 0 };

int village[MAX_SIZE * MAX_SIZE];
char map[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];

int compare(const void* A, const void* B) {
	return *(int*)A - *(int*)B;
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf(" %c", &map[i][j]);
		}
	}

	pos queue[MAX_SIZE * MAX_SIZE];

	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j] && map[i][j] == '1') {
				int num = 1;
				visited[i][j] = true;
				int front = 0, rear = 0;
				queue[rear++] = (pos){ i, j };
				
				while (front < rear) {
					int cy = queue[front].y;
					int cx = queue[front++].x;

					for (int d = 0; d < 4; d++) {
						int ny = cy + dy[d];
						int nx = cx + dx[d];

						if (ny >= 0 && ny < N && nx >= 0 && nx < N && !visited[ny][nx] && map[ny][nx] == '1') {
							num++;
							visited[ny][nx] = true;
							queue[rear++] = (pos){ ny, nx };
						}
					}
				}
				village[cnt++] = num;
			}
		}
	}
	qsort(village, cnt, sizeof(int), compare);

	printf("%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		printf("%d\n", village[i]);
	}

	return 0;
}