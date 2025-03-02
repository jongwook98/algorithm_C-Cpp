#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>

#define MAX 50

using namespace std;

int map[MAX][MAX];
bool check[MAX][MAX];

queue<pair<int, int>> q;
vector<pair<int, int>> v[MAX * MAX];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N, L, R;
	cin >> N >> L >> R;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int po;
			cin >> po;
			map[y][x] = po;
		}
	}

	int time = -1;
	bool fin = false;

	while (true) {
		if (fin) break;
		memset(check, false, sizeof(check));

		time += 1;
		fin = true;
		int cnt = -1;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (!check[y][x]) {
					check[y][x] = true;
					q.push({ y, x });
					v[++cnt].push_back({ y, x });

					while (!q.empty()) {
						int cy = q.front().first;
						int cx = q.front().second;
						q.pop();

						for (int i = 0; i < 4; i++) {
							int ny = cy + dy[i];
							int nx = cx + dx[i];

							if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
								if (!check[ny][nx] && abs(map[cy][cx] - map[ny][nx]) <= R && abs(map[cy][cx] - map[ny][nx]) >= L) {
									check[ny][nx] = true;
									v[cnt].push_back({ ny, nx });
									q.push({ ny, nx });
								}
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < MAX * MAX; i++) {
			if (v[i].size() > 1) fin = false;
			else if (v[i].empty()) break;

			int sum = 0;
			for (pair<int, int> pos : v[i])	sum += map[pos.first][pos.second];
			int new_po = sum / v[i].size(); // segfault 1번째 -> 0으로 나누는 경우 -> size 0이 되면 break 함
			for (pair<int, int> pos : v[i]) map[pos.first][pos.second] = new_po;

			while (!v[i].empty()) v[i].pop_back();
		}
	}

	cout << time << '\n';

	return 0;
}