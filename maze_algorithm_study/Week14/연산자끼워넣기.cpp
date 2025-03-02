#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

vector<int> v;

int num[11];
int sign[4];
int insign[4];

long long MIN = 1000000000000;
long long MAX = -1000000000000;

void cal(int N) {
	int idx = 0;
	long long ans = num[idx++];
	for (int sig : v) {
		if (sig == 0) ans += num[idx++];
		else if (sig == 1) ans -= num[idx++];
		else if (sig == 2) ans *= num[idx++];
		else if (sig == 3) {
			if (ans > 0) ans /= num[idx++];
			else {
				ans *= -1;
				ans /= num[idx++];
				ans *= -1;
			}
		}
	}
	MIN = min(MIN, ans);
	MAX = max(MAX, ans);
}

void dfs(int N) {
	if (v.size() == N) return cal(N);

	for (int i = 0; i < 4; i++) {
		if (insign[i] < sign[i]) {
			
			insign[i] += 1;
			v.push_back(i);
			dfs(N);
			v.pop_back();
			insign[i] -= 1;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> M;
		num[i] = M;
	}
	for (int i = 0; i < 4; i++) {
		cin >> M;
		sign[i] = M;
	}

	dfs(N - 1);

	cout << MAX << '\n';
	cout << MIN << '\n';

	return 0;
}