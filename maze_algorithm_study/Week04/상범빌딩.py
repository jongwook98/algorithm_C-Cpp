from sys import stdin
from collections import deque

# 1초 사이에 이동할 수 있는 거리들
dz = [0, 0, 0, 0, 1, -1]
dy = [0, 0, 1, -1, 0, 0]
dx = [1, -1, 0, 0, 0, 0]

while True:
    # 빌딩 정보, 종료 플래그 받는 곳
    L, R, C = map(int, stdin.readline().split())
    if L == R == C == 0:
        break

    # 빈 공간 생성, 방문 확인 변수 생성
    Map = [[[[] for _ in range(C)] for _ in range(R)] for _ in range(L)]
    check = [[[False for _ in range(C)] for _ in range(R)] for _ in range(L)]

    # 주어진 입력으로 맵 정보 저장
    for f in range(L):
        Map[f] = [list(stdin.readline().strip()) for _ in range(R)]
        # 의미없는 개행 날리기
        LF = input()

    Que = deque()

    # 시작위치 찾고, 시작위치를 거리 0 으로 설정
    for z in range(L):
        for y in range(R):
            for x in range(C):
                if Map[z][y][x] == 'S':
                    Que.append([z, y, x])
                    check[z][y][x] = 0

    # 탈출 가능, 불가능 플래그
    flag = 0
    while len(Que):
        cur_z, cur_y, cur_x = Que.popleft()
        # 이동할 수 있는 방법의 가지 수
        for i in range(6):
            nz = cur_z + dz[i]
            ny = cur_y + dy[i]
            nx = cur_x + dx[i]
            if 0 <= nz < L and 0 <= ny < R and 0 <= nx < C:
                # 방문하지 않았고, 벽이 아니라면 이동 가능
                if check[nz][ny][nx] is False and Map[nz][ny][nx] != '#':
                    Que.append([nz, ny, nx])
                    check[nz][ny][nx] = check[cur_z][cur_y][cur_x] + 1
                # 탈출 지점이면 Que.clear, 걸린 시간 출력
                if Map[nz][ny][nx] == 'E':
                    print("Escaped in", check[nz][ny][nx], "minute(s).")
                    flag = 1
                    Que.clear()
    if flag == 0:
        print("Trapped!")