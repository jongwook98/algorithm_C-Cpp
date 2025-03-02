from sys import stdin
from collections import deque

N = int(stdin.readline().strip())
A, B = map(int, stdin.readline().split())
M = int(stdin.readline().strip())

# 1 ~ N 까지의 입력이므로 N + 1 로 저장하여 입력값 가공 없이 사용
node = [[] for _ in range(N + 1)]
check = [False for _ in range(N + 1)]

for _ in range(M):
    # 양방향으로 방문 할 수 있도록 저장
    x, y = map(int, stdin.readline().split())
    node[x].append(y)
    node[y].append(x)

def BFS():
    # 두 사람 중 한 사람을 시작 노드로 저장 및 탐색
    Que = deque()
    Que.append(A)
    check[A] = 0

    while len(Que):
        cur = Que.popleft()
        for pos in node[cur]:
            if check[pos] is False:
                check[pos] = check[cur] + 1
                Que.append(pos)

            if pos == B:
                return print(check[pos])

    # 두 사람의 관계가 끊어져있다면 -1 출력
    return print(-1)

if __name__=="__main__":
    BFS()