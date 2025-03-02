from sys import stdin
from collections import deque
import heapq
from copy import deepcopy

N, M = map(int, stdin.readline().split())
Map = [list(map(int, stdin.readline().split())) for _ in range(N)]

mv = [(0, 1), (0, -1), (1, 0), (-1, 0)]

que = deque()
candi = []

score = 0

def rotate(Map):
    new_Map = [[0 for _ in range(N)] for _ in range(N)]
    for y in range(N):
        for x in range(N):
            new_Map[N - 1 - x][y] = Map[y][x]

    Map = deepcopy(new_Map)
    gravity(Map, 1)

def gravity(Map, flag):
    new_Map = [[-2 for _ in range(N)] for _ in range(N)]
    block = deque()
    for x in range(N):
        idx = N - 1
        for y in range(N -1, -1, -1):
            if Map[y][x] == -2:
                continue
            elif Map[y][x] == -1:
                while block:
                    new_Map[idx][x] = block.popleft()
                    idx -= 1
                new_Map[y][x] = -1
                idx = y - 1
            else:
                block.append(Map[y][x])
        while block:
            new_Map[idx][x] = block.popleft()
            idx -= 1

    Map = deepcopy(new_Map)
    #for y in range(N):
    #    print(Map[y], sep = " ")

    if flag == 0:
        rotate(Map)
    elif flag == 1:
        find_block(Map)


def find_block(Map):
    global score, candi, block_que, que, comp
    check = [[[False for _ in range(N)] for _ in range(N)] for _ in range(M + 1)]
    block_que = []
    candi.clear()

    idx = -1
    for y in range(N):
        for x in range(N):
            if Map[y][x] != 0 and Map[y][x] != -1 and Map[y][x] != -2:
                cur_c = Map[y][x]

                if check[cur_c][y][x] is False:
                    block_que.append(deque())
                    idx += 1
                    check[cur_c][y][x] = True
                    bb = [y, x]
                    rb = 0

                    cnt = 1
                    que.append((y, x))
                    block_que[idx].append((y, x))

                    while que:
                        cur_y, cur_x = que.popleft()
                        for i in range(4):
                            ny, nx = cur_y + mv[i][0], cur_x + mv[i][1]
                            if 0 <= ny < N and 0 <= nx < N:
                                if check[cur_c][ny][nx] is False and (Map[ny][nx] == cur_c or Map[ny][nx] == 0):
                                    if Map[ny][nx] == 0: rb += 1
                                    elif (Map[ny][nx] == cur_c and ny < bb[0]): bb = [ny, nx]
                                    elif (Map[ny][nx] == cur_c and ny == bb[0] and nx < bb[1]): bb = [ny, nx]

                                    check[cur_c][ny][nx] = True
                                    cnt += 1
                                    que.append((ny, nx))
                                    block_que[idx].append((ny, nx))

                    if cnt > 1:
                        heapq.heappush(candi, (-cnt, -rb, -bb[0], -bb[1], cur_c, idx))

    if candi:
        num, _, _, _, cc, idx = heapq.heappop(candi)
        score += num**2

        while block_que[idx]:
            cur_y, cur_x = block_que[idx].popleft()
            Map[cur_y][cur_x] = -2

        gravity(Map, 0)

    #for y in range(N):
    #    print(Map[y], sep = " ")

    else:
        return print(score)

find_block(Map)