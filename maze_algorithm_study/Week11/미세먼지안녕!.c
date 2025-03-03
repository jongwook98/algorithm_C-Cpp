#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

#define MAX_SIZE 50

typedef struct {
	int y, x;
}pos;

int R, C, T;

int ans = 0;
int Map[MAX_SIZE][MAX_SIZE];
pos Air[2];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

void diffuse() {
	int temp[MAX_SIZE][MAX_SIZE] = { 0, };

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			if (Map[y][x] >= 5) {
				int diffuse_idx = 0;
				pos queue[4];

				for (int d = 0; d < 4; d++) {
					int ny = y + dy[d];
					int nx = x + dx[d];

					if (ny >= 0 && ny < R && nx >= 0 && nx < C && Map[ny][nx] != -1) {
						queue[diffuse_idx++] = (pos){ ny, nx };
					}
				}

				for (int i = 0; i < diffuse_idx; i++) {
					temp[queue[i].y][queue[i].x] += (Map[y][x] / 5);
				}
				temp[y][x] = Map[y][x] + temp[y][x] - ((Map[y][x] / 5) * diffuse_idx);
			}
			else {
				temp[y][x] += Map[y][x];
			}
		}
	}
	memcpy(Map, temp, sizeof(temp));
	Map[Air[0].y][Air[0].x] = -1;
	Map[Air[1].y][Air[1].x] = -1;

	//for (int y = 0; y < R; y++) {
	//	for (int x = 0; x < C; x++) {
	//		printf("%d ", Map[y][x]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");
}

void activate() {
	ans -= Map[Air[0].y - 1][0];
	ans -= Map[Air[1].y + 1][0];

	for (int y = Air[0].y - 2; y >= 0; y--) {
		Map[y + 1][0] = Map[y][0];
	}
	for (int x = 0; x < C - 1; x++) {
		Map[0][x] = Map[0][x + 1];
	}
	for (int y = 0; y < Air[0].y; y++) {
		Map[y][C - 1] = Map[y + 1][C - 1];
	}
	for (int x = C - 1; x > 1; x--) {
		Map[Air[0].y][x] = Map[Air[0].y][x - 1];
	}
	Map[Air[0].y][1] = 0;

	for (int y = Air[1].y + 2; y < R; y++) {
		Map[y - 1][0] = Map[y][0];
	}
	for (int x = 0; x < C - 1; x++) {
		Map[R - 1][x] = Map[R - 1][x + 1];
	}
	for (int y = R - 1; y >= Air[1].y; y--) {
		Map[y][C - 1] = Map[y - 1][C - 1];
	}
	for (int x = C - 1; x > 1; x--) {
		Map[Air[1].y][x] = Map[Air[1].y][x - 1];
	}
	Map[Air[1].y][1] = 0;

	//for (int y = 0; y < R; y++) {
	//	for (int x = 0; x < C; x++) {
	//		printf("%d ", Map[y][x]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");
}

int main() {
	scanf("%d %d %d", &R, &C, &T);
	int air_idx = 0;

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			scanf("%d", &Map[y][x]); 
			if (Map[y][x] == -1) {
				Air[air_idx++] = (pos){ y, x };
			}
			else {
				ans += Map[y][x];
			}
		}
	}

	while (T--) {
		diffuse();
		activate();
	}

	printf("%d", ans);

	return 0;
}