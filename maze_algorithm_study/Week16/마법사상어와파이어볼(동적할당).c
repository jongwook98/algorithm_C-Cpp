#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX_SIZE 50

typedef struct {
	int m, s, d;
}Fireball;

typedef struct {
	Fireball* arr;
	int count;
	int capacity;
}FireballList;

FireballList grid[MAX_SIZE][MAX_SIZE];
FireballList newGrid[MAX_SIZE][MAX_SIZE];

int N, M, K;

int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void initGrid(FireballList board[][MAX_SIZE]) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			board[y][x].capacity = 4;
			board[y][x].count = 0;
			board[y][x].arr = (Fireball*)malloc(board[y][x].capacity * sizeof(Fireball));
		}
	}
}

void clearGrid(FireballList board[][MAX_SIZE]) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++)
			board[y][x].count = 0;
	}
}

void freeGrid(FireballList board[][MAX_SIZE]) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++)
			free(board[y][x].arr);
	}
}

void pushFireball(FireballList* list, Fireball fb) {
	if (list->capacity == list->count) {
		list->capacity *= 2;
		list->arr = (Fireball*)realloc(list->arr, list->capacity * sizeof(Fireball));
	}
	list->arr[list->count++] = fb;
}

void moveFireball() {
	clearGrid(newGrid);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			for (int i = 0; i < grid[y][x].count; i++) {
				int ny = (y + (dy[grid[y][x].arr[i].d] * grid[y][x].arr[i].s)) % N;
				if (ny < 0) ny += N;

				int nx = (x + (dx[grid[y][x].arr[i].d] * grid[y][x].arr[i].s)) % N;
				if (nx < 0) nx += N;

				pushFireball(&newGrid[ny][nx], grid[y][x].arr[i]);
			}
		}
	}
}

void fusion() {
	clearGrid(grid);
	
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (newGrid[y][x].count == 0) continue;
			else if (newGrid[y][x].count == 1) {
				pushFireball(&grid[y][x], newGrid[y][x].arr[0]);
			}
			else {
				Fireball sum = (Fireball){ 0, 0, 0 };
				bool allOdd = true, allEven = true;

				for (int i = 0; i < newGrid[y][x].count; i++) {
					sum.m += newGrid[y][x].arr[i].m;
					sum.s += newGrid[y][x].arr[i].s;

					if (newGrid[y][x].arr[i].d % 2) {
						allOdd = false;
					}
					else {
						allEven = false;
					}
				}
				if (sum.m >= 5) {
					for (int d = 0; d < 4; d++) {
						if (allOdd || allEven) {
							pushFireball(&grid[y][x], (Fireball) { sum.m / 5, sum.s / newGrid[y][x].count, d * 2 });
						}
						else {
							pushFireball(&grid[y][x], (Fireball) { sum.m / 5, sum.s / newGrid[y][x].count, d * 2 + 1 });
						}
					}
				}
			}
		}
	}
}


int main() {
	scanf("%d %d %d", &N, &M, &K);
	initGrid(grid);
	initGrid(newGrid);

	for (int i = 0; i < M; i++) {
		int r, c, m, s, d;
		scanf("%d %d %d %d %d", &r, &c, &m, &s, &d);
		pushFireball(&grid[r - 1][c - 1], (Fireball) { m, s, d });
	}

	while (K--) {
		moveFireball();
		fusion();
	}

	int ans = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			for (int i = 0; i < grid[y][x].count; i++) {
				ans += grid[y][x].arr[i].m;
			}
		}
	}

	printf("%d", ans);

	freeGrid(grid);
	freeGrid(newGrid);

	return 0;
}