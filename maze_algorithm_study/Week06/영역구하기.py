from sys import stdin
from collections import deque

dy = [0, 0, -1, 1]
dx = [-1, 1, 0, 0]

# 나누어지는 영역 저장 리스트
output = []

M, N, K = map(int, stdin.readline().split())
Map = [[False for _ in range(N)] for _ in range(M)]

# 사각형 좌표 정보로 맵에 벽 생성(방문했다고 표기)
for _ in range(K):
    sx, sy, fx, fy = map(int, stdin.readline().split())
    for y in range(sy, fy):
        for x in range(sx, fx):
            Map[y][x] = True

Que = deque()

for y in range(M):
    for x in range(N):
        # 방문한 곳이 아니라면 BFS 사이클 시작
        if Map[y][x] is False:

            Que.append([y, x])
            Map[y][x] = True

            # 영역의 크기
            area = 1

            while len(Que):
                cur_y, cur_x = Que.popleft()
                for i in range(4):
                    ny = cur_y + dy[i]
                    nx = cur_x + dx[i]
                    if 0 <= ny < M and 0 <= nx < N:
                        if Map[ny][nx] is False:
                            Que.append([ny, nx])
                            Map[ny][nx] = True
                            area += 1

            # 분리되는 영역 저장
            output.append(area)

# 영역 정렬, 출력
output.sort()
print(len(output))
print(" ".join(map(str, output)))