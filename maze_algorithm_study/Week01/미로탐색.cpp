#include<iostream>
#include<string>
#include<queue>
#include<vector>

#define MAX 101

using namespace std;

int check[MAX][MAX];
bool map[MAX][MAX];
string info;

queue<pair<int, int>> q;
vector<pair<int, int>> mv;


int main()
{
	mv.push_back({ 1, 0 });
	mv.push_back({ 0, 1 });
	mv.push_back({ -1, 0 });
	mv.push_back({ 0, -1 });

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M;
	cin >> N >> M;

	cin.ignore();
	for (int y = 0; y < N; y++) {
		getline(cin, info, '\n');
		for (int x = 0; x < M; x++) {
			map[y][x] = info[x] - 48;
		}
	}

	q.push({ 0, 0 });
	check[0][0] = 1;
	while (!q.empty()) {
		int cur_y = q.front().first;
		int cur_x = q.front().second;

		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = cur_y + mv[i].first;
			int nx = cur_x + mv[i].second;

			if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
				if (check[ny][nx] == 0 && map[ny][nx] == true) {
					q.push({ ny, nx });
					check[ny][nx] = check[cur_y][cur_x] + 1;
				}
			}
		}
	}

	cout << check[N - 1][M - 1] << '\n';

	/*for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cout << map[y][x] << " ";
			cout << check[y][x] << " ";
		}
		cout << '\n';
	}*/

	return 0;
}
