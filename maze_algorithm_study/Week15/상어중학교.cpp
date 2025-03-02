#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

typedef struct {
	int block, rb, by, bx, idx;
}info;

int map[20][20];
int new_map[20][20];
bool check[20][20][6];

queue<pair<int, int>> q;
queue<int> b_q;
vector<info> v;
vector<pair<int, int>> b_v[20 * 20];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };
int ans;

void gravity(int N, bool step);
void rotate(int N);
void find_block(int N);

bool compare(info a, info b) {
	if (a.block == b.block) {
		if (a.rb == b.rb) {
			if (a.by == b.by) {
				return a.bx > b.bx;
			}
			else return a.by > b.by;
		}
		else return a.rb > b.rb;
	}
	else return a.block > b.block;
}

void rotate(int N) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			new_map[N - 1 - x][y] = map[y][x];
		}
	}
	memcpy(map, new_map, sizeof(new_map));

	gravity(N, false);
}

void gravity(int N, bool step) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			new_map[y][x] = -2;
		}
	}

	for (int x = 0; x < N; x++) {
		int to_y = N - 1;
		for (int y = N - 1; y >= 0; y--) {
			if (map[y][x] == -1) {
				while (!b_q.empty()) {
					new_map[to_y--][x] = b_q.front();
					b_q.pop();
				}
				to_y = y - 1;
				new_map[y][x] = map[y][x];
			}
			else if (!(map[y][x] == -2)) b_q.push(map[y][x]);
		}
		while (!b_q.empty()) {
			new_map[to_y--][x] = b_q.front();
			b_q.pop();
		}
	}

	memcpy(map, new_map, sizeof(new_map));

	if (step) rotate(N);
	else find_block(N);
}

void find_block(int N) {
	int col;
	memset(check, false, sizeof(check));

	int idx = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			col = map[y][x];
			if (col > 0 && !check[y][x][col]) {
				check[y][x][col] = true;
				q.push({ y, x });
				b_v[idx].push_back({ y, x });
				int cnt = 1, rb = 0, by = y, bx = x;
				while (!q.empty()) {
					int cy = q.front().first;
					int cx = q.front().second;
					q.pop();

					for (int i = 0; i < 4; i++) {
						int ny = cy + dy[i];
						int nx = cx + dx[i];
						if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
							if (!check[ny][nx][col] && (map[ny][nx] == col || map[ny][nx] == 0)) {
								if (map[ny][nx] == 0) rb++;
								else if (by > ny) by = ny;
								else if (by == ny && bx > nx) bx = nx;
								cnt++;
								check[ny][nx][col] = true;
								q.push({ ny, nx });
								b_v[idx].push_back({ ny, nx });
							}
						}
					}
				}
				if (cnt > 1) v.push_back({ cnt, rb, by, bx, idx });
				idx++;
			}
		}
	}
	if (v.size() == 0) return;
	else {
		sort(v.begin(), v.end(), compare);
		info A;
		A = v[0];

		ans += int(pow(A.block, 2));
		
		for (pair<int, int> pos : b_v[A.idx]) {
			map[pos.first][pos.second] = -2;
		}
		v.clear();
		for (int i = 0; i < 20 * 20; i++) {
			b_v[i].clear();
		}
		gravity(N, true);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M, info;
	cin >> N >> M;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> info;
			map[y][x] = info;
		}
	}

	find_block(N);

	cout << ans << '\n';
	return 0;
}
