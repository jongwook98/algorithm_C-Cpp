#include<iostream>
#include<vector>

typedef struct {
	int m, s, d;
}fire;

using namespace std;

vector<fire> map[50][50];
vector<fire> temp[50][50];

int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void move_fire(int N) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			while (!map[y][x].empty()) {
				fire info = map[y][x].back();
				map[y][x].pop_back();

				int new_s = info.s % N;
				int new_y = (y + N + dy[info.d] * new_s) % N;
				int new_x = (x + N + dx[info.d] * new_s) % N;
				temp[new_y][new_x].push_back({ info.m, info.s, info.d });
			}
		}
	}
}

void act_fire(int N) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (!temp[y][x].empty()) {
				int new_m = 0, new_s = 0, new_d, cnt = temp[y][x].size();
				bool odd = false, even = false;
				while (!temp[y][x].empty()) {
					fire info = temp[y][x].back();
					temp[y][x].pop_back();

					new_m += info.m;
					new_s += info.s;
					new_d = info.d;
					if (info.d % 2) odd = true;
					else even = true;
				}
				if (cnt > 1) {
					new_m /= 5; new_s /= cnt;
					if (new_m == 0) continue;
					if (odd && even) for (int i = 1; i < 8; i += 2) map[y][x].push_back({ new_m, new_s, i });
					else for (int i = 0; i < 7; i += 2) map[y][x].push_back({ new_m, new_s, i });
				}
				else map[y][x].push_back({ new_m, new_s, new_d });
			}
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M, K, y, x;
	fire info;
	cin >> N >> M >> K;

	while (M--) {
		cin >> y >> x >> info.m >> info.s >> info.d;
		map[y - 1][x - 1].push_back({ info.m, info.s, info.d });
	}

	while (K--) {
		move_fire(N);
		act_fire(N);
	}

	int ans = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (!map[y][x].empty()) for (fire info : map[y][x]) ans += info.m;
		}
	}

	cout << ans << '\n';
	return 0;
}
