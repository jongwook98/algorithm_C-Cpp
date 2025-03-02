#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 8

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
	int y, x;
}pos;

int Map[MAX_SIZE][MAX_SIZE];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int N, K;

int Max_height = 0;
pos Start[MAX_SIZE * MAX_SIZE];

bool visited[MAX_SIZE][MAX_SIZE];

int Start_idx = 0;
int ans = 0;

void dfs(int cur_y, int cur_x, int height, int num, bool used) {
	for (int d = 0; d < 4; d++) {
		int ny = cur_y + dy[d];
		int nx = cur_x + dx[d];

		if (ny >= 0 && ny < N && nx >= 0 && nx < N && !visited[ny][nx]) {
			if (Map[ny][nx] < height) {
				visited[ny][nx] = true;
				dfs(ny, nx, Map[ny][nx], num + 1, used);
				visited[ny][nx] = false;
			}
			else if (Map[ny][nx] >= height && used == false) {
				if (Map[ny][nx] - K < Map[cur_y][cur_x]) {
					visited[ny][nx] = true;
					dfs(ny, nx, Map[cur_y][cur_x] - 1, num + 1, true);
					visited[ny][nx] = false;
				}
			}
		}
	}
	ans = MAX(ans, num);
}

int main(void)
{
	int test_case;
	int T;

	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		Max_height = 0;
		Start_idx = 0;
		memset(Start, 0, sizeof(Start));
		memset(visited, false, sizeof(visited));
		ans = 0;

		scanf("%d %d", &N, &K);

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				scanf("%d", &Map[y][x]);

				if (Max_height < Map[y][x]) {
					Max_height = Map[y][x];
					Start_idx = 0;
					memset(Start, 0, sizeof(Start));

					Start[Start_idx++] = (pos){ y, x };
				}
				else if (Max_height == Map[y][x]) {
					Start[Start_idx++] = (pos){ y, x };
				}
			}
		}
		for (int i = 0; i < Start_idx; i++) {
			visited[Start[i].y][Start[i].x] = true;
			dfs(Start[i].y, Start[i].x, Map[Start[i].y][Start[i].x], 1, false);
			visited[Start[i].y][Start[i].x] = false;
		}
		printf("#%d %d\n", test_case, ans);
	}
	return 0;
}