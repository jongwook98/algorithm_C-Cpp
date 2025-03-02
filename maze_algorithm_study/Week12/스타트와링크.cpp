#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>

using namespace std;

vector<int> v;

bool check[20];
int map[20][20];
int ans = 1000000000;

void cal(int N) {
	int A = 0;
	memset(check, false, sizeof(check));
	for (int i : v) {
		check[i] = true;
		for (int j : v) {
			A += map[i][j];
		}
	}
	int B = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!check[i] && !check[j]) B += map[i][j];
		}
	}
	ans = min(ans, abs(A - B));
}

void dfs(int idx, int N) {
	if (v.size() >= N / 2) {
		return cal(N);
	}
	if (idx >= N)
		return;

	v.push_back(idx);
	dfs(idx + 1, N);
	v.pop_back();
	dfs(idx + 1, N);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, info;
	cin >> N;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> info;
			map[y][x] = info;
		}
	}

	dfs(0, N);

	cout << ans << '\n';

	return 0;
}