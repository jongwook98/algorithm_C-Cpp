#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

#define MAX 100

using namespace std;

queue<pair<int, int>> q;

bool map[MAX][MAX];
bool check[MAX][MAX];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

vector<int> ans;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int M, N, K;
	cin >> M >> N >> K;

	while (K--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		for (int i = x1; i < x2; i++) {
			for (int j = y1; j < y2; j++) {
				map[j][i] = true;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!check[j][i] && !map[j][i]) {
				int cnt = 1;
				check[j][i] = true;
				q.push({ j, i });
				while (!q.empty()) {
					int cy = q.front().first;
					int cx = q.front().second;
					q.pop();

					for (int s = 0; s < 4; s++) {
						int ny = cy + dy[s];
						int nx = cx + dx[s];

						if (ny >= 0 && ny < M && nx >= 0 && nx < N) {
							if (!check[ny][nx] && !map[ny][nx]) {
								check[ny][nx] = true;
								q.push({ ny, nx });
								cnt++;
							}
						}
					}	
					if (q.empty()) ans.push_back(cnt);
				}
			}
		}
	}
	sort(ans.begin(), ans.end());

	cout << ans.size() << '\n';
	for (int an : ans) cout << an << " ";
	cout << '\n';

	return 0;
}