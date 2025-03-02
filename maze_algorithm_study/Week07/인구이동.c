#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_SIZE 50
#define abs(a) ((a) > 0 ? (a) : (-(a)))

void find_group();
void move_population();

typedef struct {
	int sum, member_num;
	int new_population;
}group_info;

typedef struct {
	int y, x;
}pos;

int Map[MAX_SIZE][MAX_SIZE];
pos queue[MAX_SIZE * MAX_SIZE];

group_info group[MAX_SIZE * MAX_SIZE]; // 0은 찾은 그룹 수, 1부터 그룹 멤버 수
int member[MAX_SIZE][MAX_SIZE];


int N, L, R;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int ans = 0;

void move_population() {
	for (int i = 1; i < group[0].member_num; i++) {
		group[i].new_population = group[i].sum / group[i].member_num;
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			Map[y][x] = group[member[y][x]].new_population;
		}
	}

	//for (int y = 0; y < N; y++) {
	//	for (int x = 0; x < N; x++) {
	//		printf("%d ", Map[y][x]);
	//	}
	//	printf("\n");
	//}

	ans++;

	find_group();
}

void find_group() {
	memset(group, 0, sizeof(group));
	memset(member, 0, sizeof(member));

	int group_num = 1;
	bool flag = false;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (member[y][x] == 0) {
				int front = 0, rear = 0;
				queue[rear++] = (pos){ y, x };

				member[y][x] = group_num;
				group[group_num++] = (group_info){ Map[y][x], 1 };

				while (front < rear) {
					pos cur = queue[front++];

					for (int d = 0; d < 4; d++) {
						int ny = cur.y + dy[d];
						int nx = cur.x + dx[d];

						if (ny >= 0 && ny < N && nx >= 0 && nx < N && member[ny][nx] == 0) {
							int diff = abs(Map[cur.y][cur.x] - Map[ny][nx]);

							if (diff >= L && diff <= R) {
								member[ny][nx] = member[cur.y][cur.x];

								group[member[cur.y][cur.x]].sum += Map[ny][nx];
								group[member[cur.y][cur.x]].member_num++;

								queue[rear++] = (pos){ ny, nx };

								flag = true;
							}
						}
					}
				}
			}
		}
	}

	//for (int y = 0; y < N; y++) {
	//	for (int x = 0; x < N; x++) {
	//		printf("member : %d", member[y][x]);
	//	}
	//	printf("\n");
	//}

	//for (int i = 0; i < group_num; i++) {
	//	printf("sum : %d member : %d new : %d\n", group[i].sum, group[i].member_num, group[i].new_population);
	//}

	group[0].member_num = group_num;

	if (flag) {
		move_population();
	}
}

int main() {
	scanf("%d %d %d", &N, &L, &R);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			scanf(" %d", &Map[y][x]);
		}
	}

	find_group();

	printf("%d", ans);

	return 0;
}