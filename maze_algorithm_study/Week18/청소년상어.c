#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int ans;

typedef struct {
	bool alive;
	int y, x;
	int d;
}Fish;

int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

void move_fish(int Map[4][4], Fish fish[16], Fish shark) {
	for (int i = 0; i < 16; i++) {
		if (fish[i].alive) {
			int y = fish[i].y;
			int x = fish[i].x;
			int d = fish[i].d;

			for (int di = 0; di < 8; di++) {
				int nd = (d + di) % 8;

				int ny = y + dy[nd];
				int nx = x + dx[nd];

				if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4 && !(ny == shark.y && nx == shark.x)) {
					int target = Map[ny][nx];
					Map[ny][nx] = i;
					fish[i].y = ny;
					fish[i].x = nx;

					fish[i].d = nd;

					if (fish[target].alive) {
						fish[target].y = y;
						fish[target].x = x;
					}
					Map[y][x] = target;

					break;
				}
			}
		}
	}
}

void dfs(int score, int Map[4][4], Fish fish[16], Fish shark) {
	bool moved = false;

	int newMap[4][4];
	Fish newFish[16];

	memcpy(newMap, Map, sizeof(newMap));
	//memcpy(newMap, Map, sizeof(Map)); 제대로 복사 안됨,,
	//매개변수로 전달된 Map은 배열 전체가 아니라 포인터처럼 취급되어서 포인터 크기를 반환한다.
	memcpy(newFish, fish, sizeof(newFish));

	move_fish(newMap, newFish, shark);

	for (int step = 1; step < 4; step++) {
		int ny = shark.y + dy[shark.d] * step;
		int nx = shark.x + dx[shark.d] * step;

		if (!(ny >= 0 && ny < 4 && nx >= 0 && nx < 4)) break;
		if (!newFish[newMap[ny][nx]].alive) continue;

		int target = newMap[ny][nx];

		moved = true;
		Fish newFish_copy[16];
		Fish newShark = shark;

		memcpy(newFish_copy, newFish, sizeof(newFish_copy));

		newShark.y = ny; newShark.x = nx;
		newShark.d = newFish_copy[target].d;

		newFish_copy[target].alive = false;

		dfs(score + (target + 1), newMap, newFish_copy, newShark);
	}

	if (!moved) {
		ans = MAX(ans, score);
	}
}

int main() {
	Fish fish[16];
	Fish shark;

	int Map[4][4];

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int a, b;
			scanf("%d %d", &a, &b);
			Map[y][x] = a - 1;
			fish[a - 1] = (Fish){ true, y, x, b - 1 };
		}
	}

	shark = (Fish){ true, 0, 0, fish[Map[0][0]].d };
	fish[Map[0][0]].alive = false;

	dfs(Map[0][0] + 1, Map, fish, shark);

	printf("%d", ans);

	return 0;
}