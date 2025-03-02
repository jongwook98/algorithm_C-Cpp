from sys import stdin
from collections import deque

TestCase = int(stdin.readline().strip())
dy = [0, 0, 1, -1]
dx = [1, -1, 0, 0]

for _ in range(TestCase):
    M, N, K = map(int, stdin.readline().split())

    # 빈 맵 생성
    Map = [[0 for _ in range(M)] for _ in range(N)]
    check = [[False for _ in range(M)] for _ in range(N)]

    # 배추의 위치를 저장하는 deque
    cab_Que = deque()

    # 배추위치 저장, 배추 심기
    for _ in range(K):
        x, y = map(int, stdin.readline().split())
        cab_Que.append([y, x])
        Map[y][x] = 1

    # BFS 탐색하는 deque
    Que = deque()
    # 그룹을 세는 변수 count
    count = 0

    # 배추가 심어져 있는 구간에서 탐색 시작
    while len(cab_Que):
        cab_y, cab_x = cab_Que.popleft()
        # 이미 방문한 위치라면 continue로 스킵
        if check[cab_y][cab_x] is not False:
            continue

        # 방문하지 않은 지역이라면 count + 1 해주고 그 위치에서 BFS 완전 탐색
        count += 1
        Que.append([cab_y, cab_x])
        check[cab_y][cab_x] = True
        while len(Que):
            cur_y, cur_x = Que.popleft()

            for i in range(4):
                ny = cur_y + dy[i]
                nx = cur_x + dx[i]

                if 0 <= ny < N and 0 <= nx < M:
                    if check[ny][nx] is False and Map[ny][nx] == 1:
                        Que.append([ny, nx])
                        check[ny][nx] = True
    print(count)