#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

bool check[1001];
vector<int> go[1001];
queue<int> bfs;

void DFS(int cur) {
	cout << cur << " ";
	// 해당 노드와 이어진 노드 중 방문하지 않은 노드 DFS 재귀
	for (int next : go[cur]) {
		if (!check[next]) {
			check[next] = true;
			DFS(next);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, M, V;
	cin >> N >> M >> V;

	check[V] = true;
	bfs.push(V);
	for (int i = 0; i < M; i++) {
		int from, to;
		cin >> from >> to;

		go[from].push_back(to);
		go[to].push_back(from);
	}

	//모든 정점에서의 간선 정렬
	for (int i = 0; i < 1001; i++) {
		sort(go[i].begin(), go[i].end());
	}

	DFS(V);

	//방문 확인 변수 초기화
	memset(check, false, sizeof(check));
	check[V] = true;

	cout << '\n';

	while (!bfs.empty()) {
		int cur = bfs.front();
		cout << cur << " ";
		bfs.pop();

		for (int next : go[cur]) {
			if (!check[next]) {
				check[next] = true;
				bfs.push(next);
			}
		}
	}

	cout << '\n';
	return 0;
}