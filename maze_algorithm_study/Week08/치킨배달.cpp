#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>

#define MAX 50

using namespace std;

vector<pair<int, int>> sel;

pair<int, int> ch[MAX * MAX];
vector<pair<int, int>> house;

int ans = 10000000;
int short_dis[MAX * MAX];

void cal_dis() {
	int sum = 0;
	int idx = 0;

	memset(short_dis, 0, sizeof(short_dis));

	for (pair<int, int> pos : house) {
		for (pair<int, int> des : sel) {
			int cal = abs(pos.first - des.first) + abs(pos.second - des.second);
			if (short_dis[idx] == 0) short_dis[idx] = cal;
			else short_dis[idx] = min(short_dis[idx], cal);
		}
		sum += short_dis[idx++];
	}		
	ans = min(ans, sum);
}

void dfs(int index, int cur, int max) {
	if (sel.size() >= index) {
		cal_dis();
		return;
	}

	for (int i = cur; i < max; i++) {
		sel.push_back(ch[i]);
		dfs(index, i + 1, max);

		sel.pop_back();
	}

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M;
	cin >> N >> M;

	int idx = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int info;
			cin >> info;

			if (info == 1) house.push_back({ y, x });
			else if (info == 2) ch[idx++] = {y, x};
		}
	}

	dfs(M, 0, idx);

	cout << ans << '\n';

	return 0;
}