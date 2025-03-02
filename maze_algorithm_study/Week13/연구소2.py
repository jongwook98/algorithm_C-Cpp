from sys import stdin
from collections import deque
from itertools import combinations
from copy import deepcopy

mv = [[0, 1], [1, 0], [0, -1], [-1, 0]]

min_time = 1e9
N, M = map(int, stdin.readline().split())

# 초기 맵 저장
Map_init = [list(map(int, stdin.readline().split())) for _ in range(N)]
# 바이러스 위치 후보 저장
virus_pos = []

cnt = 0

# 바이러스 위치 저장, 빈칸 개수 파악
for y in range(N):
    for x in range(N):
        if Map_init[y][x] == 2:
            virus_pos.append([y, x])
            Map_init[y][x] = 0
        if Map_init[y][x] == 0:
            cnt += 1

# 빈칸 + 바이러스 후보에서 바이러스 개수 만큼 빼주기
cnt -= M

# 조합을 만들 크기
comb = [i for i in range(len(virus_pos))]

# BFS 탐색으로 걸리는 시간 측정
def BFS(Map, virus_pos, arr, cnt):
    Que = deque()
    for index in arr:
        # 바이러스를 놓은 부분을 2 -> 0 -> 1로 바꿔주기
        Que.append((virus_pos[index][0], virus_pos[index][1]))
        Map[virus_pos[index][0]][virus_pos[index][1]] = 1

    while Que:
        cur_y, cur_x = Que.popleft()
        time = Map[cur_y][cur_x]
        for i in range(4):
            ny, nx = cur_y + mv[i][0], cur_x + mv[i][1]

            if 0 <= ny < N and 0 <= nx < N:
                if Map[ny][nx] == 0:
                    Que.append((ny, nx))
                    Map[ny][nx] = Map[cur_y][cur_x] + 1
                    cnt -= 1

    if cnt == 0:
        # 처음에 놓은 바이러스를 1로 설정했으니 1 빼서 계산
        return time - 1
    # 빈칸이 남았다면 초기값 리턴
    else: return 1e9

# 조합갯수만큼 BFS 함수 실행
for arr in combinations(comb, M):
    cur_time = BFS(deepcopy(Map_init), virus_pos, arr, cnt)
    min_time = min(min_time, cur_time)

if min_time == 1e9:
    print(-1)
else:
    print(min_time)