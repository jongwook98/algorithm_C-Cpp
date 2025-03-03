#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAX_SIZE 50

typedef struct {
	int y, x;
}pos;

int N, M;
int Map[MAX_SIZE][MAX_SIZE];

int area = 0;
int ans = (int)1e9;

pos virus[MAX_SIZE * MAX_SIZE];
int virus_num = 0;

int virus_arr[10];

pos queue[MAX_SIZE * MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

void bfs() {
	int front = 0, rear = 0;
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < M; i++) {
		queue[rear++] = virus[virus_arr[i]];
		visited[virus[virus_arr[i]].y][virus[virus_arr[i]].x] = 1;
	}

	int local_area = area;
	int time = 1;

	while (front < rear && local_area > 0) {
		pos cur = queue[front++];

		for (int d = 0; d < 4; d++) {
			int ny = cur.y + dy[d];
			int nx = cur.x + dx[d];

			if (ny >= 0 && ny < N && nx >= 0 && nx < N && visited[ny][nx] == 0 && Map[ny][nx] != 1) {
				visited[ny][nx] = visited[cur.y][cur.x] + 1;
				local_area--;

				time = MAX(time, visited[ny][nx]);

				queue[rear++] = (pos){ ny, nx };
			}
		}
	}

	if (local_area == 0) {
		ans = MIN(ans, time - 1);
	}
}

void comb(int idx, int sel) {
	if (sel == M) {
		bfs();
	}
	else if (idx < virus_num){
		virus_arr[sel] = idx;
		comb(idx + 1, sel + 1);

		comb(idx + 1, sel); // 선택 안 함
	}
}

int main() {
	scanf("%d %d", &N, &M);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			scanf("%d", &Map[y][x]);

			if (Map[y][x] != 1) {
				area++;
			}
			if (Map[y][x] == 2) {
				virus[virus_num++] = (pos){ y, x };
			}
		}
	}
	area -= M;

	comb(0, 0);

	if (ans == (int)1e9) {
		printf("%d", -1);
	}
	else {
		printf("%d", ans);
	}

	return 0;
}