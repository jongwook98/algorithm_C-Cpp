#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define abs(a) ((a) > 0 ? (a) : (-(a)))

#define MAX_SIZE 20

int N;
int adj[MAX_SIZE][MAX_SIZE];
bool team[MAX_SIZE];

int ans = (int)1e9;

void cal_diff() {
	int queue_start[MAX_SIZE / 2];
	int queue_link[MAX_SIZE / 2];

	int start_idx = 0;
	int link_idx = 0;

	int start_sum = 0;
	int link_sum = 0;

	for (int i = 0; i < N; i++) {
		if (team[i]) {
			queue_start[start_idx++] = i;
		}
		else {
			queue_link[link_idx++] = i;
		}
	}

	for (int a = 0; a < start_idx; a++) {
		for (int b = 0; b < start_idx; b++) {
			if (a == b) continue;

			start_sum += adj[queue_start[a]][queue_start[b]];
		}

	}
	for (int a = 0; a < link_idx; a++) {
		for (int b = 0; b < link_idx; b++) {
			if (a == b) continue;

			link_sum += adj[queue_link[a]][queue_link[b]];
		}
	}
	ans = MIN(ans, abs(start_sum - link_sum));
}

void dfs(int cur, int num) { //현재 idx, 고른 수
	if (num == N / 2) {
		cal_diff();
	}
	else if (cur < N) {
		team[cur] = true;
		dfs(cur + 1, num + 1);

		team[cur] = false;
		dfs(cur + 1, num);
	}
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &adj[i][j]);
		}
	}

	dfs(0, 0);

	printf("%d", ans);

	return 0;
}