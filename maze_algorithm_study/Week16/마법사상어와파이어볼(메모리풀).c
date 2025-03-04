// 이동하는 좌표 잘 확인하기, 
// 동적할당 안하고 풀었더니,, 사용한 메모리 147820KB 약 144MB
// 시간은 24ms 통과

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_SIZE 50

typedef struct {
	int m, s, d;
}info;

typedef struct {
	int y, x;
}pos;

int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int N, M, K;

//info fire_arr[MAX_SIZE][MAX_SIZE][MAX_SIZE]; // 틀림
info fire_arr[MAX_SIZE][MAX_SIZE][MAX_SIZE * MAX_SIZE];
int fire_idx[MAX_SIZE][MAX_SIZE];
//info temp_arr[MAX_SIZE][MAX_SIZE][MAX_SIZE]; // 틀림
//info temp_arr[MAX_SIZE][MAX_SIZE][MAX_SIZE * MAX_SIZE];
int temp_idx[MAX_SIZE][MAX_SIZE];

void fusion() {
	//memset(fire_arr, 0, sizeof(fire_arr)); 시간 초과
	memset(fire_idx, 0, sizeof(fire_idx));

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (temp_idx[y][x] == 0) continue;

			info sum = (info){ 0, 0, 0 };
			int nd = temp_arr[y][x][0].d;
			bool allEven = true, allOdd = true;
			for (int i = 0; i < temp_idx[y][x]; i++) {
				sum.m += temp_arr[y][x][i].m;
				sum.s += temp_arr[y][x][i].s;
				
				if (temp_arr[y][x][i].d % 2 == 0) {
					allOdd = false;
				}
				else {
					allEven = false;
				}
			}

			if (temp_idx[y][x] >= 2 && sum.m >= 5) {
				for (int d = 0; d < 4; d++) {
					if (allOdd || allEven) {
						nd = d * 2;
					}
					else {
						nd = d * 2 + 1;
					}
					fire_arr[y][x][fire_idx[y][x]++] = (info){ sum.m / 5, sum.s / temp_idx[y][x], nd };
				}
			}
			else if (temp_idx[y][x] == 1) {
				fire_arr[y][x][fire_idx[y][x]++] = (info){ sum.m, sum.s, nd };
			}
		}
	}
}

void move_fire() {
	//memset(temp_arr, 0, sizeof(temp_arr)); 시간 초과
	memset(temp_idx, 0, sizeof(temp_idx));

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			for (int i = 0; i < fire_idx[y][x]; i++) {
				int ny = (y + dy[fire_arr[y][x][i].d] * fire_arr[y][x][i].s) % N;
				if (ny < 0) {
					ny += N;
				}
				int nx = (x + dx[fire_arr[y][x][i].d] * fire_arr[y][x][i].s) % N;
				if (nx < 0) {
					nx += N;
				}

				temp_arr[ny][nx][temp_idx[ny][nx]++] = fire_arr[y][x][i];
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &K);

	int r, c, m, s, d;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &r, &c, &m, &s, &d);
		fire_arr[r - 1][c - 1][fire_idx[r - 1][c - 1]++] = (info){ m, s, d };
	}

	while (K--) {
		move_fire();
		fusion();
	}

	int ans = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			for (int i = 0; i < fire_idx[y][x]; i++) {
				ans += fire_arr[y][x][i].m;
			}
		}
	}

	printf("%d", ans);

	return 0;
}