#include<iostream>
#include<queue>
#include<cstring>

#define MAX 50

using namespace std;

bool map[MAX][MAX];
bool check[MAX][MAX];

queue<pair<int, int>> q;

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	for (int t = 0; t < T; t++) {
		memset(map, false, sizeof(map));
		memset(check, false, sizeof(check));

		int M, N, K;
		cin >> M >> N >> K;

		for (int k = 0; k < K; k++) {
			int X, Y;
			cin >> X >> Y;

			map[X][Y] = true;
		}

		int ans = 0;
		for (int m = 0; m < M; m++) {
			for (int n = 0; n < N; n++) {
				if (!check[m][n] && map[m][n] == true) {
					q.push({ m, n });
					ans++;
					check[m][n] = true;
				}
				while (!q.empty()) {
					int cx = q.front().first;
					int cy = q.front().second;
					q.pop();

					for (int i = 0; i < 4; i++) {
						int nx = cx + dx[i];
						int ny = cy + dy[i];

						if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
							if (!check[nx][ny] && map[nx][ny]) {
								check[nx][ny] = true;
								q.push({ nx, ny });
							}
						}
					}
				}
			}
		}
		cout << ans << '\n';
	}

	return 0;
}