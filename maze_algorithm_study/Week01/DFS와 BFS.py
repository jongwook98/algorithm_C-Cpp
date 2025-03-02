from sys import stdin
from collections import deque

# 17분

# DFS 반복문을 하는 중 이동할 수 있는 간선이 있다면 이동하고
# 이동했다는 표시를 한다.
# 그 정점에서 다시 반복문으로 정점 탐색

def DFS(V, node, node_check, output):
    for i in node[V]:
        if node_check[i] is False:
            output.append(i)
            node_check[i] = True
            DFS(i, node, node_check, output)

    return output

# BFS는 deque에 값이 사라질 때까지 반복

def BFS(N, V, node):
    output = []

    node_check = [False for _ in range(N+1)]
    Que = deque()
    Que.append(V)
    node_check[V] = True
    while len(Que):
        cur = Que.popleft()
        output.append(cur)
        for i in node[cur]:
            if node_check[i] is False:
                Que.append(i)
                node_check[i] = True

    return output

if __name__=="__main__":
    N, M, V = map(int, stdin.readline().split())
    node = [[] for _ in range(N+1)]
    for i in range(M):
        A, B = map(int, stdin.readline().split())
        node[A].append(B)
        node[B].append(A)

    # 문제 조건에 따른 sort
    for i in range(N+1):
        node[i].sort()

    # DFS에서 사용하는 변수, 첫 정점 입력
    output = [V]
    node_check = [False for _ in range(N+1)]
    node_check[V] = True

    print(' '.join(map(str, DFS(V, node, node_check, output))))
    print(' '.join(map(str, BFS(N, V, node))))