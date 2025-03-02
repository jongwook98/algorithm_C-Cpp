#include<iostream>
#include<vector>
#include<queue>

#define MAX 101

using namespace std;

vector<int> edge[MAX];
queue<int> q;

int check[MAX];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	int A, B;
	cin >> A >> B;
	q.push(A);
	int m;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int next : edge[cur]) {
			if (!check[next]) {
				check[next] = check[cur] + 1;
				q.push(next);
			}
			if (next == B) {
				cout << check[next] << '\n';
				return 0;
			}
		}
	}

	cout << -1 << '\n';
	return 0;
}