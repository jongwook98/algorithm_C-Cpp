#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX_SIZE 300

typedef struct {
	int y, x;
}pos;

int l;

int visited[MAX_SIZE][MAX_SIZE];
pos Start, End;
pos queue[MAX_SIZE * MAX_SIZE];

int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

void bfs() {
	int front = 0, rear = 0;
	queue[rear++] = Start;

	memset(visited, 0, sizeof(visited));
	visited[Start.y][Start.x] = 1;

	while (front < rear && visited[End.y][End.x] == 0) {
		pos cur = queue[front++];

		for (int d = 0; d < 8; d++) {
			int ny = cur.y + dy[d];
			int nx = cur.x + dx[d];

			if (ny >= 0 && ny < l && nx >= 0 && nx < l && visited[ny][nx] == 0) {
				visited[ny][nx] = visited[cur.y][cur.x] + 1;
				queue[rear++] = (pos){ ny, nx };
			}
		}
	}

	printf("%d\n", visited[End.y][End.x] - 1);
}

int main() {
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &l);
		scanf("%d %d", &Start.y, &Start.x);
		scanf("%d %d", &End.y, &End.x);

		bfs();
	}

	return 0;
}