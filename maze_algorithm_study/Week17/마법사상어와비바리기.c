#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 50

typedef struct {
	int y, x;
}point;

typedef struct {
	point* arr;
	int count;
	int capacity;
}cloudList;

cloudList cloud;

int Map[MAX_SIZE][MAX_SIZE];
bool fcloud[MAX_SIZE][MAX_SIZE];

int N, M;

int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

void initList(cloudList* list) {
	list->capacity = 4;
	list->count = 0;
	list->arr = (point*)malloc(list->capacity * sizeof(point));
}

void clearList(cloudList* list) {
	list->count = 0;
}

void freeList(cloudList* list) {
	free(list->arr);
}

void makeCloud(cloudList* list, point pos) {
	if (list->capacity == list->count) {
		list->capacity *= 2;
		list->arr = (point*)realloc(list->arr, list->capacity * sizeof(point));
	}
	list->arr[list->count++] = pos;
}

void moveCloud(cloudList* list, int d, int s) {
	for (int i = 0; i < list->count; i++) {
		int ny = (list->arr[i].y + dy[d] * s) % N;
		if (ny < 0) ny += N;

		int nx = (list->arr[i].x + dx[d] * s) % N;
		if (nx < 0) nx += N;

		list->arr[i].y = ny;
		list->arr[i].x = nx;
	}
}

void rain(cloudList* list) {
	memset(fcloud, false, sizeof(fcloud));

	for (int i = 0; i < list->count; i++) {
		int y = list->arr[i].y;
		int x = list->arr[i].x;

		Map[y][x] += 1;
		fcloud[y][x] = true;
	}
}

int dup_dy[] = { -1, -1, 1, 1 };
int dup_dx[] = { -1, 1, 1, -1 };

void duplicate(cloudList* list) {
	for (int i = 0; i < list->count; i++) {
		int y = list->arr[i].y;
		int x = list->arr[i].x;

		for (int d = 0; d < 4; d++) {
			int ny = y + dup_dy[d];
			int nx = x + dup_dx[d];

			if (ny >= 0 && ny < N && nx >= 0 && nx < N && Map[ny][nx] > 0) {
				Map[y][x] += 1;
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	initList(&cloud);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			scanf("%d", &Map[y][x]);
		}
	}

	for (int y = N - 2; y < N; y++) {
		for (int x = 0; x < 2; x++) {
			makeCloud(&cloud, (point) { y, x });
		}
	}

	for (int m = 0; m < M; m++) {
		int d, s;
		scanf("%d %d", &d, &s);

		moveCloud(&cloud, d - 1, s);
		rain(&cloud);
		duplicate(&cloud);
		
		clearList(&cloud);

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (!fcloud[y][x] && Map[y][x] >= 2) {
					makeCloud(&cloud, (point) { y, x });
					Map[y][x] -= 2;
				}
			}
		}

		//printf("\n");
		//for (int y = 0; y < N; y++) {
		//	for (int x = 0; x < N; x++) {
		//		printf("%d ", Map[y][x]);
		//	}
		//	printf("\n");
		//}
	}

	int ans = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			ans += Map[y][x];
		}
	}

	printf("%d", ans);

	freeList(&cloud);

	return 0;
}