#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

int map[8][8];
int wall_map[8][8];

queue<pair<int, int>> init;
//queue<pair<int, int>> q;

vector<pair<int, int>> wall;

int ans = 0;
int safety;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

bool check[8][8];

int count_safety(int N, int M) {
	int res = safety - 3;

	memset(check, false, sizeof(check));
	memcpy(wall_map, map, sizeof(map));

	//memcpy(&q, &init, sizeof(init))

	queue<pair<int, int>> q(init);

	for (pair<int, int> pos : wall) {
		wall_map[pos.first][pos.second] = 1;
	}

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];
			if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
				if (!check[ny][nx] && wall_map[ny][nx] == 0) {
					res--;
					check[ny][nx] = true;
					q.push({ ny, nx });
				}
			}
		}
	}

	return res;
}

void make_wall(int index, int N, int M) {
	if (wall.size() >= 3) {
		ans = max(ans, count_safety(N, M));
		return;
	}

	for (int next = index + 1; next < N * M; next++) {
		int y = next / M;
		int x = next % M;
		if (map[y][x] == 0) {
			wall.push_back({ y, x });
			make_wall(next, N, M);

			wall.pop_back();
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M;
	cin >> N >> M;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int info;
			cin >> info;
			map[y][x] = info;

			if (info == 2) init.push({ y, x });
			else if (info == 0) safety++;
		}
	}

	make_wall(-1, N, M);

	cout << ans << '\n';
	return 0;
}