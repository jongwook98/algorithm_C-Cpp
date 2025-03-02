#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 30

typedef struct {
	int l, r, c;
}pos;

char Map[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE][MAX_SIZE];
pos queue[MAX_SIZE * MAX_SIZE * MAX_SIZE];

int L = 1, R = 1, C = 1;
pos Start, End;

int dl[] = { 1, -1, 0, 0, 0, 0 };
int dr[] = { 0, 0, 1, -1, 0, 0 };
int dc[] = { 0, 0, 0, 0, 1, -1 };

void bfs() {
	memset(visited, 0, sizeof(visited));
	int front = 0, rear = 0;

	queue[rear++] = Start;
	visited[Start.l][Start.r][Start.c] = 1;

	while (front < rear && visited[End.l][End.r][End.c] == 0) {
		pos cur = queue[front++];

		for (int d = 0; d < 6; d++) {
			int nl = cur.l + dl[d];
			int nr = cur.r + dr[d];
			int nc = cur.c + dc[d];

			if (nl >= 0 && nl < L && nr >= 0 && nr < R && nc >= 0 && nc < C && visited[nl][nr][nc] == 0 && Map[nl][nr][nc] != '#') {
				visited[nl][nr][nc] = visited[cur.l][cur.r][cur.c] + 1;
				queue[rear++] = (pos){ nl, nr, nc };
			}
		}
	}

	if (visited[End.l][End.r][End.c] == 0) {
		printf("Trapped!\n");
	}
	else {
		printf("Escaped in %d minute(s).\n", visited[End.l][End.r][End.c] - 1);
	}
}

int main() {
	
	while (true)
	{
		scanf("%d %d %d", &L, &R, &C);
		if (L == 0 && R == 0 && C == 0) {
			break;
		}
		for (int l = 0; l < L; l++) {
			for (int r = 0; r < R; r++) {
				for (int c = 0; c < C; c++) {
					scanf(" %c", &Map[l][r][c]); // 공백 문자 무시
					if (Map[l][r][c] == 'S') {
						Start = (pos){ l, r, c };
					}
					else if (Map[l][r][c] == 'E') {
						End = (pos){ l, r, c };
					}
				}
			}
		}

		bfs();
	}
	return 0;
}