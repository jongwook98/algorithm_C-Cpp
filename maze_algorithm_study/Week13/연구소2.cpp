#include<iostream>
#include<queue>
#include<cstring>
#include<cmath>

using namespace std;

vector<pair<int, int>> v;
queue<pair<int, int>> q;
pair<int, int> virus_pl[10];

int map[50][50];
bool check[50][50];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };
int ans = 10000;
int area;

void cal_area(int N) {
	memset(check, false, sizeof(check));
	for (pair<int, int> pos : v) {
		q.push({ pos });
		check[pos.first][pos.second] = true;
	}
	int cnt = 0;
	int new_area = area;
	while (!q.empty()) {
		cnt++;
		int time = q.size();
		while (time--) {
			int cy = q.front().first;
			int cx = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = cy + dy[i];
				int nx = cx + dx[i];
				
				if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
					if (!check[ny][nx] && map[ny][nx] != 1) {
						check[ny][nx] = true;
						q.push({ ny, nx });
						new_area--;
					}
				}
			}
		}
	}
	if (new_area == 0) ans = min(ans, cnt);
}

void dfs(int N, int cur,int cnt, int M) {
	if (v.size() >= M) {
		return cal_area(N);
	}
	if (cur >= cnt) return;

	v.push_back(virus_pl[cur]);
	dfs(N, cur + 1, cnt, M);
	v.pop_back();
	dfs(N, cur + 1, cnt, M);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M, info, idx = 0;
	cin >> N >> M;
	
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> info;
			map[y][x] = info;

			if (info == 2) virus_pl[idx++] = { y, x };
			else if (info == 0) area++;
		}
	}
	area += idx - M;
	dfs(N, 0, idx, M);

	if (ans == 10000) cout << -1 << '\n';
	else cout << ans - 1 << '\n';

	return 0;
}