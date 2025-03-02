from sys import stdin
from collections import deque

N, L, R = map(int, stdin.readline().split())
Map = [list(map(int, stdin.readline().split())) for _ in range(N)]

nd = [[0, 1], [1, 0], [-1, 0], [0, -1]]

# 인근 구역 값을 비교하기 위한 deque
Que = deque()

# 국경 개봉 후 개봉된 구역에 값을 넣어주기 위해 기억하는 좌표 deque
ave_Que = deque()
Day = 0

while True:
    check = [[False for _ in range(N)] for _ in range(N)]
    stop_flag = True

    # 전체 구역을 방문하여 방문여부 확인 후 방문하지 않은 구역과 인근 지역 인구수 차이 확인
    for y in range(N):
        for x in range(N):
            if check[y][x] is False:
                Que.append([y, x])
                ave_Que.append([y, x])
                check[y][x] = True

                # 연합 칸의 개수 초기화, 연합의 인구수 초기화
                count = 1
                Sum = Map[y][x]

                while len(Que):
                    cur_y, cur_x = Que.popleft()

                    for i in range(4):
                        ny, nx = cur_y + nd[i][0], cur_x + nd[i][1]
                        if 0 <= ny < N and 0 <= nx < N:
                            if check[ny][nx] is False and L <= abs(Map[cur_y][cur_x] - Map[ny][nx]) <= R:
                                Que.append([ny, nx])
                                ave_Que.append([ny, nx])
                                check[ny][nx] = True
                                Sum += Map[ny][nx]
                                count += 1
                                stop_flag = False

                ave = Sum // count
                # 연합을 해체하고 인구 할당
                while len(ave_Que):
                    cur_y, cur_x = ave_Que.popleft()
                    Map[cur_y][cur_x] = ave

    if stop_flag is True:
        break

    Day += 1

print(Day)