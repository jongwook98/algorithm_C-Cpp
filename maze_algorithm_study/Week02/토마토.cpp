#include<iostream>
#include<queue>
#include<cstring>

#define MAX 101

using namespace std;

typedef struct {
	int h, n, m;
}pos;

int tomato[MAX][MAX][MAX]; // h n m
bool check[MAX][MAX][MAX];
queue<pos> q;

int dh[] = { 0, 0, 0, 0, 1, -1 };
int dn[] = { 0, 0, 1, -1, 0, 0 };
int dm[] = { 1, -1, 0, 0, 0, 0 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int M, N, H;
	cin >> M >> N >> H;

	int cnt = 0;
	for (int h = 0; h < H; h++) {
		for (int n = 0; n < N; n++) {
			for (int m = 0; m < M; m++) {
				int state;
				cin >> state;
				tomato[h][n][m] = state;
				

				if (state == 0) cnt++;
				else if (state == 1) { 
					check[h][n][m] = true;
					q.push({ h, n, m }); 
				}
			}
		}
	}

	if (cnt == 0) {
		cout << 0 << '\n';
		return 0;
	}

	int day = -1;
	while (!q.empty()) {
		int time = q.size();
		while (time--) {
			int ch = q.front().h;
			int cn = q.front().n;
			int cm = q.front().m;

			q.pop();

			for (int i = 0; i < 6; i++) {
				int nh = ch + dh[i];
				int nn = cn + dn[i];
				int nm = cm + dm[i];

				if (nh >= 0 && nh < H && nn >= 0 && nn < N && nm >= 0 && nm < M) {
					if (!check[nh][nn][nm] && tomato[nh][nn][nm] == 0) {
						cnt--;
						check[nh][nn][nm] = true;
						q.push({ nh, nn, nm });
					}
				}
			}
		}
		day++;
	}

	if (!cnt) cout << day << '\n';
	else cout << -1 << '\n';

	return 0;
}