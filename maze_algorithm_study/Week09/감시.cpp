#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>

using namespace std;

typedef struct {
	int type, y, x;
}cctv_info;

vector<pair<int, int>> dir[5][4];
vector<int> sel;
cctv_info cctv[8];
pair<int, int> mv[] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
bool check[8][8];

int b_t[] = { 4, 2, 4, 4, 1 };
int map[8][8];
int init, ans = 1000000;

void cal(int N, int M) {
	memset(check, false, sizeof(check));
	int area = init;
	int idx = 0;

	for (int di : sel) {
		int type = cctv[idx].type;
		for (pair<int, int> nmv : dir[type][di]) {
			int cur_y = cctv[idx].y; int cur_x = cctv[idx].x;
			while (true) {
				cur_y = cur_y + nmv.first;
				cur_x = cur_x + nmv.second;
				if (cur_y >= 0 && cur_y < N && cur_x >= 0 && cur_x < M) {
					if (!check[cur_y][cur_x] && map[cur_y][cur_x] == 0) {
						area -= 1;
						check[cur_y][cur_x] = true;
					}
					if (map[cur_y][cur_x] == 6) break;
				}
				else break;
			}
		}
		idx += 1;
	}
	ans = min(ans, area);
	return;
}

void dfs(int N, int M, int cnt, int size) {
	if (cnt >= size) return cal(N, M);

	int ty = cctv[cnt].type;
	for (int j = 0; j < 4; j++) {
		if (j >= b_t[ty]) break;

		sel.push_back(j);
		dfs(N, M, cnt + 1, size);
		sel.pop_back();
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	dir[0][0].push_back(mv[0]); dir[0][1].push_back(mv[1]); dir[0][2].push_back(mv[2]); dir[0][3].push_back(mv[3]);
	dir[1][0].push_back(mv[0]); dir[1][0].push_back(mv[2]); dir[1][1].push_back(mv[1]); dir[1][1].push_back(mv[3]);
	dir[2][0].push_back(mv[0]); dir[2][0].push_back(mv[1]); dir[2][1].push_back(mv[1]); dir[2][1].push_back(mv[2]);
	dir[2][2].push_back(mv[2]); dir[2][2].push_back(mv[3]); dir[2][3].push_back(mv[3]); dir[2][3].push_back(mv[0]);

	dir[3][0].push_back(mv[0]); dir[3][0].push_back(mv[1]); dir[3][0].push_back(mv[2]);
	dir[3][1].push_back(mv[1]); dir[3][1].push_back(mv[2]); dir[3][1].push_back(mv[3]);
	dir[3][2].push_back(mv[2]); dir[3][2].push_back(mv[3]); dir[3][2].push_back(mv[0]);
	dir[3][3].push_back(mv[3]); dir[3][3].push_back(mv[0]); dir[3][3].push_back(mv[1]);

	dir[4][0].push_back(mv[0]); dir[4][0].push_back(mv[1]); dir[4][0].push_back(mv[2]); dir[4][0].push_back(mv[3]);

	int N, M, info, num = 0;
	cin >> N >> M;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> info;
			map[y][x] = info;
			if (info != 0 && info != 6) cctv[num++] = {info - 1, y, x};
			if (info == 0) init += 1;
		}
	}
	dfs(N, M, 0, num);

	cout << ans << '\n';
	return 0;
}