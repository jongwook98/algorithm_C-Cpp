from sys import stdin
from collections import deque

N, M = map(int, stdin.readline().split())
Map = [list(map(int, stdin.readline().split())) for _ in range(N)]

mv_q = deque()

q_cl = deque()
q_cl_m = deque()

check = [[False for _ in range(N)] for _ in range(N)]

mv = [[0, -1], [-1, -1], [-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1]]
dia = [[-1, -1], [-1, 1], [1, 1], [1, -1]]

q_cl.append((N-1, 0))
q_cl.append((N-1, 1))
q_cl.append((N-2, 0))
q_cl.append((N-2, 1))

for _ in range(M):
    d, s = map(int, stdin.readline().split())
    mv_q.append((d - 1, s % N))

while mv_q:
    di, si = mv_q.popleft()
    while q_cl:
        y, x = q_cl.popleft()
        ny = (y + N + mv[di][0] * si) % N
        nx = (x + N + mv[di][1] * si) % N

        Map[ny][nx] += 1
        check[ny][nx] = True
        q_cl_m.append((ny, nx))

    while q_cl_m:
        cy, cx = q_cl_m.popleft()
        for i in range(4):
            dy, dx = cy + dia[i][0], cx + dia[i][1]
            if 0 <= dy < N and 0 <= dx < N and Map[dy][dx] > 0:
                Map[cy][cx] += 1

    for y in range(N):
        for x in range(N):
            if Map[y][x] >= 2 and not check[y][x]:
                Map[y][x] -= 2
                q_cl.append((y, x))
            check[y][x] = False

ans = 0
for y in range(N):
    for x in range(N):
        ans += Map[y][x]

print(ans)