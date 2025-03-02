from sys import stdin
from collections import deque

N, M, K = map(int, stdin.readline().split())
Map = deque()
temp_cnt = [[0 for _ in range(N)] for _ in range(N)]
temp = deque()

mv = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]]

for _ in range(M):
    y, x, m, s, d = map(int, stdin.readline().split())
    Map.append((y - 1, x - 1, m, s, d))

def move_fire():
    global Map, temp, temp_cnt
    while Map:
        y, x, m, s, d = Map.popleft()
        new_s = s % N
        ny, nx = (y + N + mv[d][0] * new_s) % N, (x + N + mv[d][1] * new_s) % N
        temp.append((ny, nx, m, s, d))
        temp_cnt[ny][nx] += 1

def act_fire():
    global Map, temp, temp_cnt
    temp_map = [[[0, 0, 0, False, False] for _ in range(N)] for _ in range(N)]
    while temp:
        y, x, m, s, d = temp.popleft()
        temp_map[y][x][0] += m
        temp_map[y][x][1] += s
        temp_map[y][x][2] = d
        if d % 2: temp_map[y][x][3] = True
        else: temp_map[y][x][4] = True

    for y in range(N):
        for x in range(N):
            if temp_cnt[y][x] > 1:
                if temp_map[y][x][0] // 5 > 0:
                    m, s, d, odd, even = temp_map[y][x]
                    if odd is True and even is True:
                        for i in range(1, 8, 2):
                            Map.append((y, x, m // 5, s // temp_cnt[y][x], i))
                    else:
                        for i in range(0, 7, 2):
                            Map.append((y, x, m // 5, s // temp_cnt[y][x], i))

            elif temp_cnt[y][x] == 1:
                m, s, d, odd, even = temp_map[y][x]
                Map.append((y, x, m, s, d))
            temp_cnt[y][x] = 0

for _ in range(K):
    move_fire()
    act_fire()

ans = 0
while Map:
    _, _, m, _, _ = Map.popleft()
    ans += m

print(ans)
