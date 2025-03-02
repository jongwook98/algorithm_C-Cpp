#include<iostream>
#include<vector>
#include<cstring>

#define MAX 50

using namespace std;

int map[MAX][MAX];
int new_map[MAX][MAX];
int mach[2];

int dy[] = { 0, 0, 1, -1 };
int dx[] = { 1, -1, 0, 0 };

void blow(int R, int C) {
	int temp1 = 0, temp2;
	for (int x = 1; x < C; x++) {
		temp2 = map[mach[0]][x];
		map[mach[0]][x] = temp1;
		temp1 = temp2;
	}
	for (int y = mach[0] - 1; y >= 0; y--) {
		temp2 = map[y][C - 1];
		map[y][C - 1] = temp1;
		temp1 = temp2;
	}
	for (int x = C - 2; x >= 0; x--) {
		temp2 = map[0][x];
		map[0][x] = temp1;
		temp1 = temp2;
	}
	for (int y = 1; y < mach[0]; y++) {
		temp2 = map[y][0];
		map[y][0] = temp1;
		temp1 = temp2;
	}

	temp1 = 0;
	for (int x = 1; x < C; x++) {
		temp2 = map[mach[1]][x];
		map[mach[1]][x] = temp1;
		temp1 = temp2;
	}
	for (int y = mach[1] + 1; y < R; y++) {
		temp2 = map[y][C - 1];
		map[y][C - 1] = temp1;
		temp1 = temp2;
	}
	for (int x = C - 2; x >= 0; x--) {
		temp2 = map[R - 1][x];
		map[R - 1][x] = temp1;
		temp1 = temp2;
	}
	for (int y = R - 2; y > mach[1]; y--) {
		temp2 = map[y][0];
		map[y][0] = temp1;
		temp1 = temp2;
	}

}

void diffuse(int R, int C, int fin) {
	for (int time = 0; time < fin; time++) {
		memset(new_map, 0, sizeof(new_map));
		for (int y = 0; y < R; y++) {
			for (int x = 0; x < C; x++) {
				int cnt = 0;
				int diff = map[y][x] / 5;
				if (diff > 0) {
					for (int i = 0; i < 4; i++) {
						int ny = y + dy[i];
						int nx = x + dx[i];

						if (ny >= 0 && ny < R && nx >= 0 && nx < C) {
							if (!(nx == 0 && (ny == mach[0] || ny == mach[1]))) {
								cnt++;
								new_map[ny][nx] += diff;
							}
						}
					}
				}
				new_map[y][x] += map[y][x] - diff * cnt;
			}
		}
		for (int y = 0; y < R; y++) {
			for (int x = 0; x < C; x++) {
				map[y][x] = new_map[y][x];
			}
		}
		blow(R, C);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int R, C, T, amt;
	cin >> R >> C >> T;

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cin >> amt;
			map[y][x] = amt;

			if (amt == -1) mach[1] = y;
		}
	}
	mach[0] = mach[1] - 1;

	diffuse(R, C, T);

	int ans = 0;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			ans += map[y][x];
		}
	}

	cout << ans + 2 << '\n';
	return 0;
}