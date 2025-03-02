from sys import stdin
from collections import deque

# 인접한 섬 좌표
dy = [-1, -1, -1, 0, 0, 1, 1, 1]
dx = [-1, 0, 1, -1, 1, -1, 0, 1]

while True:
    w, h = map(int, stdin.readline().split())
    # 높이, 너비 정보가 0, 0 이면 종료
    if w == 0 and h == 0:
        break

    # 맵 정보, 방문 정보 초기화
    Map = [list(stdin.readline().split()) for _ in range(h)]
    check = [[False for _ in range(w)] for _ in range(h)]

    # deque, 섬 개수 초기화
    Que = deque()
    land_num = 0

    for y in range(h):
        for x in range(w):
            # 방문한 적 없고, 땅이라면 BFS 완전탐색 시작
            if check[y][x] is False and Map[y][x] == '1':
                Que.append([y, x])
                check[y][x] = True
                land_num += 1

                # BFS 사이클
                while len(Que):
                    cur_y, cur_x = Que.popleft()
                    for i in range(8):
                        ny = cur_y + dy[i]
                        nx = cur_x + dx[i]
                        if 0 <= ny < h and 0 <= nx < w:
                            if check[ny][nx] is False and Map[ny][nx] == '1':
                                Que.append([ny, nx])
                                check[ny][nx] = True

    # BFS 사이클 수 출력
    print(land_num)