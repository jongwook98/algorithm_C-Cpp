#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

int map[8][8];
bool check[8][8];

int ans;
int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

// 현재 좌표, 맵 크기, 공사가능크기, 구멍 깊이, 
void dfs(int y, int x, int N, int K, bool deg, int cnt) {
	ans = max(ans, cnt);

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
			if (!check[ny][nx] && map[ny][nx] < map[y][x]) {
				check[ny][nx] = true;
				dfs(ny, nx, N, K, deg, cnt + 1);
				check[ny][nx] = false;
			}
			else if (!deg && !check[ny][nx] && map[ny][nx] - K < map[y][x]) {
				check[ny][nx] = true;
				int temp = map[ny][nx];
				map[ny][nx] = map[y][x] - 1;

				dfs(ny, nx, N, K, true, cnt + 1);

				map[ny][nx] = temp;
				check[ny][nx] = false;
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int test_case;
	int T;
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(map, 0, sizeof(map));
		ans = 0;
		int max_h = 0;

		int N, K, deg;
		cin >> N >> K;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> deg;
				map[y][x] = deg;

				max_h = max(max_h, deg);
			}
		}
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (map[y][x] == max_h) {
					memset(check, false, sizeof(check));
					check[y][x] = true;
					dfs(y, x, N, K, 0, 1);
				}
			}
		}

		cout << "#" << test_case << " " << ans << '\n';
	}

	return 0;
}