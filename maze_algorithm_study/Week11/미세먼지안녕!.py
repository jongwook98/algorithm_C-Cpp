from sys import stdin

R, C, T = map(int, stdin.readline().split())

Map = [list(map(int, stdin.readline().split())) for _ in range(R)]
air_ = []

mv_ = [[0, 1], [1, 0], [0, -1], [-1, 0]]

out = 2

for y in range(R):
    if Map[y][0] == -1:
        air_.append(y)


def spread():
    global Map
    # 확산이 한번에 이루어지므로 확산 맵을 만들어서 값 저장
    sp_Map = [[0 for _ in range(C)] for _ in range(R)]
    for y in range(R):
        for x in range(C):
            if Map[y][x] >= 5:
                # 확산이 일어난 방향 수
                dis_ = 0
                pl = Map[y][x] // 5
                for i in range(4):
                    ny, nx = y + mv_[i][0], x + mv_[i][1]
                    if 0 <= ny < R and 0 <= nx < C:
                        if Map[ny][nx] != -1:
                            dis_ += 1
                            sp_Map[ny][nx] += pl

                # 확산이 일어난 방향만큼 빼 줌
                Map[y][x] -= pl * dis_

    # 전체 맵에 확산 맵만큼 더한다
    for y in range(R):
        for x in range(C):
            Map[y][x] += sp_Map[y][x]


def oper():
    global Map
    # 공기청정기가 위쪽, 아래쪽에 대한 동작 방식구현
    for i in range(2):
        temp = 0
        for x in range(1, C):
            Map[air_[i]][x], temp = temp, Map[air_[i]][x]

        if i == 0:
            for y in range(air_[i] - 1, -1, -1):
                Map[y][C - 1], temp = temp, Map[y][C - 1]

            for x in range(C - 2, -1, -1):
                Map[0][x], temp = temp, Map[0][x]

            for y in range(1, air_[i]):
                Map[y][0], temp = temp, Map[y][0]

        else:
            for y in range(air_[i] + 1, R):
                Map[y][C - 1], temp = temp, Map[y][C - 1]

            for x in range(C - 2, -1, -1):
                Map[R - 1][x], temp = temp, Map[R - 1][x]

            for y in range(R - 2, air_[i], -1):
                Map[y][0], temp = temp, Map[y][0]


# 전체 맵의 미세먼지 계산
def cal():
    global out
    for y in range(R):
        for x in range(C):
            out += Map[y][x]


for _ in range(T):
    spread()
    oper()

cal()
print(out)
