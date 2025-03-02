#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

typedef struct {
	int y, x;
}point;

typedef struct {
	int d, s;
}info;

int Map[50][50];
bool check[50][50];

point mv[] = { {0, -1}, {-1, -1}, {-1, 0}, { -1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1 } };
point dia[] = { {-1, -1 }, {-1, 1}, {1, -1}, {1, 1} };
queue<info> q;
queue<point> q_cl;
queue<point> q_cl_m;

void cloud_magic(int N, int d, int s) {

	memset(check, false, sizeof(check));
	
	// move, rain
	while (!q_cl.empty()) {
		int ny = (q_cl.front().y + N + mv[d].y * s) % N;
		int nx = (q_cl.front().x + N + mv[d].x * s) % N;
		q_cl.pop();

		Map[ny][nx] += 1;
		check[ny][nx] = true;
		q_cl_m.push({ ny, nx });
	}

	// duplicate
	while (!q_cl_m.empty()) {
		int y = q_cl_m.front().y;
		int x = q_cl_m.front().x;
		q_cl_m.pop();
		for (int i = 0; i < 4; i++) {
			int dy = y + dia[i].y;
			int dx = x + dia[i].x;

			if (dy >= 0 && dy < N && dx >= 0 && dx < N) {
				if (Map[dy][dx]) Map[y][x] += 1;
			}
		}
	}

	// generate_cloud
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (Map[y][x] >= 2 && !check[y][x]) {
				q_cl.push({ y, x });
				Map[y][x] -= 2;
			}
		}
	}

}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) cin >> Map[i][j];
	}

	int di, si;
	for (int i = 0; i < M; i++) {
		cin >> di >> si;
		q.push({ di - 1, si % N});
	}

	q_cl.push({ N - 1, 0 });
	q_cl.push({ N - 1, 1 });
	q_cl.push({ N - 2, 0 });
	q_cl.push({ N - 2, 1 });

	info spe;
	while (!q.empty()) {
		spe = q.front();
		q.pop();
		di = spe.d; si = spe.s;
		cloud_magic(N, di, si);
	}

	int ans = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) ans += Map[y][x];
	}

	cout << ans << '\n';

	return 0;
}