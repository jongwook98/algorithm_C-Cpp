from sys import stdin
from collections import deque
from copy import deepcopy

N, M = map(int, stdin.readline().split())
Map = [list(map(int, stdin.readline().split())) for _ in range(N)]

# CCTV 종류에 따른 관찰 구역
dir_ = [deque([1, 0, 0, 0]), deque([1, 0, 1, 0]), deque([1, 0, 0, 1]), deque([1, 0, 1, 1]), deque([1, 1, 1, 1])]
mv = [[0, 1], [1, 0], [0, -1], [-1, 0]]
# CCTV 종류에 따른 중복을 조합 중복을 피하기 위한 값
back_ = [3, 1, 3, 3, 0]

CCTV_ = []
init_area = 0

# CCTV 설치 위치, 종류 저장, 빈 칸 개수 저장
for y in range(N):
    for x in range(M):
        if Map[y][x] in (1, 2, 3, 4, 5):
            CCTV_.append([y, x, Map[y][x] - 1])
        elif Map[y][x] == 0:
            init_area += 1

# 최소 사각지대 영역 초기화
min_area = init_area


# 구해진 조합으로 사각지대의 수 찾는 함수
def find_area(arr):
    global min_area
    search_area = init_area
    check = [[False for _ in range(M)] for _ in range(N)]
    for num, dr in enumerate(arr):
        # CCTV 종류의 따른 관찰 범위 가져오기
        Que = deepcopy(dir_[CCTV_[num][2]])
        # 조합에 따른 감시 지역으로 방향 돌리기
        for _ in range(dr):
            Que.appendleft(Que.pop())

        for i in range(4):
            if Que[i]:
                cy, cx = CCTV_[num][0], CCTV_[num][1]
                while True:
                    # 영역을 넘어서거나 벽을 만나기 전까지 계속 검사
                    ny, nx = cy + mv[i][0], cx + mv[i][1]
                    if 0 <= ny < N and 0 <= nx < M:
                        if Map[ny][nx] == 6:
                            break
                        # 빈 곳이고 해당 지역을 방문하지 않았다면 사각지대 - 1, 방문 여부 최신화하기
                        elif Map[ny][nx] == 0 and check[ny][nx] is False:
                            check[ny][nx] = True
                            search_area -= 1
                        cy, cx = ny, nx
                    else:
                        break

    # 사각지대 최소 값 갱신
    min_area = min(min_area, search_area)


# 조합을 구하는 함수
def select_dir(arr, index):
    if len(arr) >= len(CCTV_):
        return find_area(arr)
    # CCTV 종류에 맞게 감시 영역이 중복되지 않도록 백트래킹
    if index > back_[CCTV_[len(arr)][2]]:
        return False

    # 조합에 숫자를 넣은 경우 -> 다음 CCTV의 방향 설정을 위해 index = 0 으로 초기화
    arr.append(index)
    select_dir(arr, 0)

    # 조합에 숫자를 넣지 않은 경우 -> 현재 CCTV의 다음 방향에 대한 조합을 구하기 위해 index + 1 로 재귀
    arr.pop()
    select_dir(arr, index + 1)


make_dir = []
select_dir(make_dir, 0)
print(min_area)
