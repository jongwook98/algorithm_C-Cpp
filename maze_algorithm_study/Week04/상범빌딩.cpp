#include<iostream>
#include<string>
#include<queue>
#include<cstring>

#define MAX 30

using namespace std;

typedef struct {
	int h, y, x;
}pos;

queue<pos> q;

char map[MAX][MAX][MAX];
int check[MAX][MAX][MAX];

int dh[] = { 0, 0, 0, 0, 1, -1 };
int dy[] = { 0, 0, 1, -1, 0, 0 };
int dx[] = { 1, -1, 0, 0, 0, 0 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	while (true) {

		int L, R, C;
		cin >> L >> R >> C;
		cin.ignore();

		if (L == 0 && R == 0 && C == 0) break;
		string info;
		pos end;

		memset(check, false, sizeof(check));

		for (int h = 0; h < L; h++) {
			for (int y = 0; y < R; y++) {
				getline(cin, info, '\n');
				for (int x = 0; x < C; x++) {
					map[h][y][x] = info[x];
					if (info[x] == 'S') {
						q.push({ h, y, x });
						check[h][y][x] = 1;
					}
					else if (info[x] == 'E') {
						end.h = h; end.y = y; end.x = x;
					}
				}
			}
			getline(cin, info, '\n');
		}

		while (!q.empty()) {
			int cur_h = q.front().h;
			int cur_y = q.front().y;
			int cur_x = q.front().x;

			q.pop();

			for (int i = 0; i < 6; i++) {
				int nh = cur_h + dh[i];
				int ny = cur_y + dy[i];
				int nx = cur_x + dx[i];

				if (nh >= 0 && nh < L && ny >= 0 && ny < R && nx >= 0 && nx < C) {
					if (!check[nh][ny][nx] && (map[nh][ny][nx] == '.' || map[nh][ny][nx] == 'E')) {
						check[nh][ny][nx] = check[cur_h][cur_y][cur_x] + 1;
						q.push({ nh, ny, nx });
					}
				}
			}
		}
		if (check[end.h][end.y][end.x]) cout << "Escaped in " << check[end.h][end.y][end.x] - 1 << " minute(s)." << '\n';
		else cout << "Trapped!" << '\n';
	}
	return 0;

}