#include<iostream>
#include<algorithm>

using namespace std;

typedef struct {
	int num, dir;
}info;

typedef struct {
	int y, x, dir;
}pos;

int Map[4][4];

pos fish[17];
pos sh;

int ans;
int Max;

int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

void move_fish() {

	for (int i = 1; i <= 16; i++) {
		int cy = fish[i].y; int cx = fish[i].x; int cd = fish[i].dir;
		if (cy < 0 || cx < 0) continue;

		for (int j = 0; j < 8; j++) {
			int ny = cy + dy[(cd + j) % 8];
			int nx = cx + dx[(cd + j) % 8];

			if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {
				if (ny != sh.y || nx != sh.x) {
					int temp = Map[ny][nx];
					Map[ny][nx] = i;
					Map[cy][cx] = temp;

					fish[i] = { ny, nx, (cd + j) % 8 };
					fish[temp].y = cy; fish[temp].x = cx;

					break;
				}
			}
		}
	}
}

void dfs() {
	int pre_Map[4][4];
	pos pre_fish[17];

	/*
	cout << "ans : " << ans << " Max : " << Max << '\n';
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			cout << Map[y][x] << " " << fish[Map[y][x]].dir << " ";
		}
		cout << '\n';
	}
	cout << "sh : " << sh.y << " " << sh.x << " " << sh.dir << '\n' << '\n';
	*/

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) pre_Map[i][j] = Map[i][j];
	}

	for (int i = 1; i <= 16; i++) {
		pre_fish[i] = fish[i];
	}

	move_fish();

	for (int i = 1; i <= 3; i++) {
		int ny = sh.y + dy[sh.dir] * i;
		int nx = sh.x + dx[sh.dir] * i;

		if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {
			if (Map[ny][nx] != 0) {
				pos yet_sh = sh;
				int temp = Map[ny][nx];

				pos yet_fish = fish[temp];

				ans += temp;
				Max = max(Max, ans);
				
				sh = { ny, nx, fish[temp].dir };
				fish[temp] = { -1, -1, -1 };
				
				Map[ny][nx] = 0;

				dfs();

				ans -= temp;
				Map[ny][nx] = temp;
				sh = yet_sh;
				fish[temp] = yet_fish;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) Map[i][j] = pre_Map[i][j];
	}
	for (int i = 1; i <= 16; i++) fish[i] = pre_fish[i];
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int fish_num, fish_dir;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> fish_num >> fish_dir;
			Map[i][j] = fish_num;
			fish[fish_num] = { i, j, fish_dir - 1 };
		}
	}

	ans += Map[0][0];
	sh = { 0, 0, fish[Map[0][0]].dir };
	fish[Map[0][0]] = { -1, -1, -1 };
	
	Map[0][0] = 0;
	dfs();

	cout << Max << '\n';

	return 0;
}