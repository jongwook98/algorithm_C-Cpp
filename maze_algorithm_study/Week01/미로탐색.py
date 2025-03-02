from sys import stdin
from collections import deque

# 11분
# 인접한 칸
DY = [0, 0, 1, -1]
DX = [1, -1, 0, 0]

# BFS 구조로 목적지에 도착하면 무게값을 return 하는 함수
# 맵에서 벗어나지 않도록, 한 번 가본곳은 check를 이용해서
# 다시 들어가지 않도록, 또 check는 출발점에서부터 이동한 거리

def find_min_path(N, M, Maze, check, Que):
    while len(Que):
        cur_y, cur_x = Que.popleft()
        for i in range(4):
            ny = cur_y + DY[i]
            nx = cur_x + DX[i]

            if 0 <= ny < N and 0 <= nx < M:
                if check[ny][nx] is False and Maze[ny][nx] == 1:
                    check[ny][nx] = check[cur_y][cur_x] + 1
                    Que.append((ny, nx))

                    if ny == (N-1) and nx == (M-1):
                        return check[ny][nx]

# 출발점을 deque에 넣고 BFS함수를 호출하여 최단거리 계산
if __name__ =="__main__":
    N, M = map(int, stdin.readline().split())
    Maze = [list(map(int, stdin.readline().strip())) for _ in range(N)]

    check = [[False] * M for _ in range(N)]

    Que = deque()
    Que.append((0, 0))
    check[0][0] = 1

    print(find_min_path(N, M, Maze, check, Que))