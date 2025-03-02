#include<iostream>
#include<queue>
#include<cstring>

#define MAX 50

using namespace std;

queue<pair<int, int>> q;

bool map[MAX][MAX];
bool check[MAX][MAX];

int dy[] = { -1, -1, 0, 1, 1, 1, -1, 0 };
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	while (true) {
		int w, h;
		cin >> w >> h;

		if (w == 0 && h == 0) break;

		memset(map, false, sizeof(map));
		memset(check, false, sizeof(check));

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				bool info;
				cin >> info;
				map[y][x] = info;
			}
		}

		int ans = 0;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				if (!check[y][x] && map[y][x]) {
					ans++;
					check[y][x] = true;
					q.push({ y, x });

					while (!q.empty()) {
						int cy = q.front().first;
						int cx = q.front().second;
						q.pop();

						for (int i = 0; i < 8; i++) {
							int ny = cy + dy[i];
							int nx = cx + dx[i];

							if (ny >= 0 && ny < h && nx >= 0 && nx < w) {
								if (!check[ny][nx] && map[ny][nx]) {
									check[ny][nx] = true;
									q.push({ ny ,nx });
								}
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