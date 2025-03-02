from sys import stdin
from collections import deque
from copy import deepcopy

N, M = map(int, stdin.readline().split())
Map = [list(map(int, stdin.readline().split())) for _ in range(N)]

check = [[False for _ in range(M)] for _ in range(N)]

# 바이러스 이동 방향
dy = [0, 0, 1, -1]
dx = [1, -1, 0, 0]

Que = deque()

# 안전한 지역 개수 확인
safety_area = 0
max_area = 0

# 바이러스 deque에 넣고
# 안전한 지역은 개수 확인
for y in range(N):
    for x in range(M):
        if Map[y][x] == 2:
            Que.append([y, x])
            check[y][x] = True
        if Map[y][x] == 0:
            safety_area += 1

# 재귀로 벽 세우는 모든 경우의 수 체크
def select_wall(count, index, wall):
    # 벽을 세개 세웠으면 BFS로 안전한 지역 검사
    if count >= 3:
        return BFS(Que, check, wall, safety_area - 3)

    # 범위를 넘어가면 종료
    if index >= N*M:
        return False

    cur_y = index // M
    cur_x = index % M

    # 빈 곳일 때
    if Map[cur_y][cur_x] == 0:
        # 벽 세우고 다음 칸으로 이동
        wall.append((cur_y, cur_x))
        select_wall(count + 1, index + 1, wall)

        # 세웠던 벽 뽑고 다음 칸으로 이동
        wall.pop()
        select_wall(count, index + 1, wall)
    # 빈 곳이 아닐 때 다음 칸으로 이동
    else:
        select_wall(count, index + 1, wall)

# 벽을 다 세우면 안전 영역 확인
def BFS(Que_dup, check_dup, wall, safety_area):
    global max_area

    # 바이러스 넣어둔 deque 복사
    Que = deepcopy(Que_dup)

    check = deepcopy(check_dup)

    # 벽 세운 지역 확인 안하도록 설정
    for wall_y, wall_x in wall:
        check[wall_y][wall_x] = True

    # BFS 구조로 모든 지역 확인
    while len(Que):
        cur_y, cur_x = Que.popleft()
        for i in range(4):
            ny = cur_y + dy[i]
            nx = cur_x + dx[i]
            if 0 <= ny < N and 0 <= nx < M:
                if check[ny][nx] is False and Map[ny][nx] == 0:
                    safety_area -= 1
                    check[ny][nx] = True
                    Que.append([ny, nx])

    # 최대 영역 확인
    max_area = max(max_area, safety_area)

if __name__=="__main__":
    select_wall(0, 0, list())
    print(max_area)