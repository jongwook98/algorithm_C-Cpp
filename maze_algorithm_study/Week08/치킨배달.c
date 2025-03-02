#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define MAX_SIZE 50

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define abs(a) ((a) > 0 ? (a) : (-(a)))

typedef struct {
	int y, x;
}pos;

char Map[MAX_SIZE][MAX_SIZE];
pos house[MAX_SIZE * MAX_SIZE]; // �� �迭
pos chicken[MAX_SIZE * MAX_SIZE]; // ġŲ �迭

int house_num;
int chicken_num;

int sel_chicken_num[13]; // ���� �� ġŲ �� �迭

int N, M;

int ans = (int)1e9;

void cal_ans() {
	int sum = 0;

	for (int h = 0; h < house_num; h++) {
		pos house_pos = house[h];
		int dis = (int)1e9;
		for (int c = 0; c < M; c++) {
			pos chicken_pos = chicken[sel_chicken_num[c]];

			dis = MIN(dis, (abs(house_pos.y - chicken_pos.y) + abs(house_pos.x - chicken_pos.x)));
		}
		sum += dis;
	}

	ans = MIN(ans, sum);
}

void dfs(int cur, int num) {
	if (num == M) {
		cal_ans();
	}
	else if (cur < chicken_num) {
		sel_chicken_num[num] = cur;
		dfs(cur + 1, num + 1); // ����� ��,
		dfs(cur + 1, num); // ���� �ʾ��� ��,
	}
}

int main() {
	scanf("%d %d", &N, &M);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			scanf(" %c", &Map[y][x]);

			if (Map[y][x] == '1') {
				house[house_num++] = (pos){ y, x };
			}
			else if (Map[y][x] == '2') {
				chicken[chicken_num++] = (pos){ y, x };
			}
		}
	}

	dfs(0, 0); // ���� (���� �ε���, ���� �� ��)

	printf("%d", ans);

	return 0;
}