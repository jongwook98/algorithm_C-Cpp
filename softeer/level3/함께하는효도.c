#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
	int y, x;
}pos;

int n, m;

int Map[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
pos friend[3];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int move_arr[3 * 3];
int initans = 0;
int ans = 0;

void cal() {
	int localans = initans;

	bool localVisited[MAX_N][MAX_N];
	pos localFriend[3];

	memcpy(localVisited, visited, sizeof(localVisited));
	memcpy(localFriend, friend, sizeof(localFriend));

	for (int i = 0; i < 3; i++) {
		for (int f = 0; f < m; f++) {
			int cy = localFriend[f].y;
			int cx = localFriend[f].x;
			int d = move_arr[i * m + f];

			int ny = cy + dy[d];
			int nx = cx + dx[d];

			localFriend[f].y = ny;
			localFriend[f].x = nx;

			if (ny >= 0 && ny < n && nx >= 0 && nx < n) {
				localFriend[f] = (pos){ ny, nx };
				if (!localVisited[ny][nx]) {
					localans += Map[ny][nx];
					localVisited[ny][nx] = true;
				}
			}
			else return;
		}
		for (int f = 0; f < m - 1; f++) {
			for (int g = f + 1; g < m; g++) {
				if ((localFriend[f].y == localFriend[g].y) && (localFriend[f].x == localFriend[g].x)) return;
			}
		}
	}
	ans = MAX(ans, localans);
}

void dfs(int cnt) {
	if (cnt >= m * 3) {
		cal();
	}
	else {
		for (int d = 0; d < 4; d++) {
			move_arr[cnt] = d;
			dfs(cnt + 1);
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			scanf("%d", &Map[y][x]);
		}
	}

	for (int i = 0; i < m; i++) {
		int y, x;
		scanf("%d %d", &y, &x);

		friend[i] = (pos){ y - 1, x - 1 };
		initans += Map[y - 1][x - 1];
		visited[y - 1][x - 1] = true;
	}

	dfs(0);

	printf("%d", ans);

	return 0;
}