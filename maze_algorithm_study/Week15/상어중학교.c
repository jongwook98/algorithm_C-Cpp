#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 20

typedef struct {
	int y, x;
}pos;

typedef struct {
	int size;
	int by, bx;
	int rain_block;
}info;

int Map[MAX_SIZE][MAX_SIZE];

int N, M;

bool flag = true;

info block_info;
pos block_pos_arr[MAX_SIZE * MAX_SIZE];

pos queue[MAX_SIZE * MAX_SIZE];
pos temp_pos_arr[MAX_SIZE * MAX_SIZE];
pos rain_block_arr[MAX_SIZE * MAX_SIZE];

int ans = 0;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };


void rotate() {
	int temp_Map[MAX_SIZE][MAX_SIZE] = { 0, };

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			temp_Map[y][x] = Map[x][N - 1 - y];
		}
	}
	memcpy(Map, temp_Map, sizeof(temp_Map));
}

void gravity() {
	for (int x = 0; x < N; x++) {
		int bh = N - 1;
		for (int y = N - 1; y >= 0; y--) {
			if (Map[y][x] == -1) {
				bh = y - 1;
			}
			else if (Map[y][x] != -2) {
				Map[bh][x] = Map[y][x];
				if (bh-- != y) {
					Map[y][x] = -2;
				}
			}
		}
	}
}

void get_score() {
	ans += block_info.size * block_info.size;

	for (int i = 0; i < block_info.size; i++) {
		int y = block_pos_arr[i].y;
		int x = block_pos_arr[i].x;

		Map[y][x] = -2;
	}
}

void find_block_group() {
	bool visited[MAX_SIZE][MAX_SIZE];
	memset(visited, false, sizeof(visited));
	memset(temp_pos_arr, 0, sizeof(temp_pos_arr));

	block_info = (info){ 0, 0, 0, 0 };

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (Map[y][x] != -2 && Map[y][x] != 0 && Map[y][x] != -1 && !visited[y][x]) {
				int block_num = 0;
				int rain_idx = 0;
				int front = 0, rear = 0;

				temp_pos_arr[block_num++] = (pos){ y, x };
				visited[y][x] = true;
				queue[rear++] = (pos){ y, x };

				while (front < rear) {
					pos cur = queue[front++];

					for (int d = 0; d < 4; d++) {
						int ny = cur.y + dy[d];
						int nx = cur.x + dx[d];

						if (ny >= 0 && ny < N && nx >= 0 && nx < N && !visited[ny][nx] && ((Map[ny][nx] == 0) || (Map[ny][nx] == Map[y][x]))) {
							if (Map[ny][nx] == 0) {
								rain_block_arr[rain_idx++] = (pos){ ny, nx };

								visited[ny][nx] = true;
								temp_pos_arr[block_num++] = (pos){ ny, nx };
								queue[rear++] = (pos){ ny, nx };
							}
							else if (Map[ny][nx] == Map[y][x]) {
								visited[ny][nx] = true;
								temp_pos_arr[block_num++] = (pos){ ny, nx };
								queue[rear++] = (pos){ ny, nx };
							}
						}
					}
				}

				for (int i = 0; i < rain_idx; i++) {
					pos rpos = rain_block_arr[i];
					visited[rpos.y][rpos.x] = false;
				}

				bool change_flag = false;
				if (block_info.size < block_num) {
					change_flag = true;
				}
				else if (block_info.size == block_num) {
					if (block_info.rain_block < rain_idx) {
						change_flag = true;
					}
					else if (block_info.rain_block == rain_idx) {
						if (block_info.by < y) {
							change_flag = true;
						}
						else if (block_info.by == y) {
							if (block_info.bx < x) {
								change_flag = true;
							}
						}
					}
				}

				if (change_flag == true) {
					block_info = (info){ block_num, y, x, rain_idx };
					memcpy(block_pos_arr, temp_pos_arr, sizeof(temp_pos_arr));
				}
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			scanf("%d", &Map[y][x]);
		}
	}

	while (flag) {
		flag = false;

		find_block_group();

		if (block_info.size > 1) {
			get_score();
			flag = true;
		}

		gravity();
		rotate();
		gravity();

		//for (int y = 0; y < N; y++) {
		//	for (int x = 0; x < N; x++) {
		//		printf("%d ", Map[y][x]);
		//	}
		//	printf("\n");
		//}
		//printf("%d %d %d %d\n", block_info.size, block_info.by, block_info.bx, block_info.rain_block);
	}
	printf("%d", ans);

	return 0;
}