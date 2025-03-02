from sys import stdin
from copy import deepcopy

Map = [[0 for _ in range(4)] for _ in range(4)]
fish = [[0, 0, 0] for _ in range(17)]

ans = 0
Max = 0

dy = [-1, -1, 0, 1, 1, 1, 0, -1]
dx = [0, -1, -1, -1, 0, 1, 1, 1]

for i in range(4):
    str = list(map(int, stdin.readline().split()))
    for j in range(4):
        Map[i][j] = str[2 * j]
        fish[str[2 * j]] = [i, j, str[2 * j + 1] - 1]

shark = [0, 0, fish[Map[0][0]][2]]
fish[Map[0][0]] = [-1, -1, -1]
ans += Map[0][0]

Map[0][0] = 0

def mv_fish():
    global fish, Map

    for i in range(1, 17):
        if fish[i][0] == -1: continue
        cy, cx, cd = fish[i]

        for j in range(8):
            ny, nx = cy + dy[(cd + j) % 8], cx + dx[(cd + j) % 8]
            if 0 <= ny < 4 and 0 <= nx < 4 and (ny != shark[0] or nx != shark[1]):
                fish[Map[ny][nx]], fish[i] = [cy, cx, fish[Map[ny][nx]][2]], [ny, nx, (cd + j) % 8]
                Map[ny][nx], Map[cy][cx] = i, Map[ny][nx]
                break

def dfs():
    global fish, shark, Map, ans, Max

    pre_Map = deepcopy(Map)
    pre_fish = deepcopy(fish)

    mv_fish()

    cy, cx, cd = shark
    for i in range(1, 4):
        ny, nx = cy + dy[cd] * i, cx + dx[cd] * i
        if 0 <= ny < 4 and 0 <= nx < 4 and Map[ny][nx] != 0:
            temp = Map[ny][nx]

            ans += temp
            Max = max(ans, Max)
            shark = [ny, nx, fish[temp][2]]
            Map[ny][nx] = 0
            fish[temp][0] = -1

            dfs()

            ans -= temp
            shark = [cy, cx, cd]
            fish[temp][0] = ny
            Map[ny][nx] = temp

    Map = deepcopy(pre_Map)
    fish = deepcopy(pre_fish)

dfs()

print(Max)