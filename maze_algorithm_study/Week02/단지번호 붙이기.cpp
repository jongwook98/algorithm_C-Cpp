#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>

#define MAX 25

using namespace std;

bool map[MAX][MAX];
int check[MAX][MAX];
string info;

queue<pair<int, int>> q;

vector<int> ans;

int dy[] = { 1, 0, -1, 0 };
int dx[] = { 0, 1, 0, -1 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int N;
	cin >> N;

	cin.ignore();
	for (int y = 0; y < N; y++) {
		getline(cin, info, '\n');
		int x = 0;
		for (char ch : info) {
			map[y][x++] = ch - '0';
		}
	}

	int cnt = 0;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (check[y][x] == false && map[y][x] == true) {
				int length = 0;
				q.push({ y, x });
				check[y][x] = 1;

				while (!q.empty()) {
					length++;
					int cur_y = q.front().first;
					int cur_x = q.front().second;
					q.pop();

					for (int i = 0; i < 4; i++) {
						int ny = cur_y + dy[i];
						int nx = cur_x + dx[i];

						if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
							if (!check[ny][nx] && map[ny][nx]) {
								check[ny][nx] = check[cur_y][cur_x] + 1;
								q.push({ ny, nx });
							}
						}
					}
				}
				cnt++;
				ans.push_back(length);
			}

		}
	}

	sort(ans.begin(), ans.end());

	cout << cnt << '\n';
	for (int out : ans) cout << out << '\n';

	return 0;
}