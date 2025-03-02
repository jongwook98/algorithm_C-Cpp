#include<iostream>
#include<queue>
#include<cstring>

#define MAX 300

using namespace std;

queue<pair<int, int>> q;
int check[MAX][MAX];

int dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		int I;
		cin >> I;
		
		int cur_y, cur_x, end_y, end_x;
		cin >> cur_y >> cur_x;
		cin >> end_y >> end_x;

		if (cur_y == end_y && cur_x == end_x) {
			cout << 0 << '\n';
			continue;
		}
		q.push({ cur_y, cur_x });

		while (!q.empty()) {
			int cy = q.front().first;
			int cx = q.front().second;
			q.pop();

			for (int i = 0; i < 8; i++) {
				int ny = cy + dy[i];
				int nx = cx + dx[i];

				if (ny >= 0 && ny < I && nx >= 0 && nx < I) {
					if (ny == end_y && nx == end_x) {
						cout << check[cy][cx] + 1 << '\n';
						while (!q.empty()) q.pop();
						break;
					}
					if (!check[ny][nx]) {
						check[ny][nx] = check[cy][cx] + 1;
						q.push({ ny, nx });
					}
				}
			}
		}
		while (!q.empty()) q.pop();

		for (int y = 0; y < MAX; y++) {
			for (int x = 0; x < MAX; x++) check[y][x] = 0;
		}
	}
	return 0;
}