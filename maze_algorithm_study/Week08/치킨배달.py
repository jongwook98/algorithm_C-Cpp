from sys import stdin

N, M = map(int, stdin.readline().split())
Map = [list(stdin.readline().split()) for _ in range(N)]

house = []
chicken = []

# 도시의 치킨 거리 초기화
DIS = 9999999

for y in range(N):
    for x in range(N):
        if Map[y][x] == '1':
            house.append([y, x])
        elif Map[y][x] == '2':
            chicken.append([y, x])


# 구한 조합으로 최소 거리 계산
def calcul_dis(arr):
    global DIS
    dis_sum = 0
    # 모든 집의 거리 검사
    for index in range(len(house)):
        dis = 999
        # 각 치킨 집과 거리 비교
        for chi in arr:
            dis = min(dis, abs(house[index][0] - chicken[chi][0]) + abs(house[index][1] - chicken[chi][1]))
        dis_sum += dis

    DIS = min(DIS, dis_sum)


# 치킨 집을 선택하는 조합을 구하는 함수 재귀함수로 구현
def select(arr, index):
    if len(arr) >= M:
        return calcul_dis(arr)

    if index >= len(chicken):
        return True

    # 배열에 넣어주는 경우
    arr.append(index)
    select(arr, index + 1)

    # 배열에 넣지않고 넘어가는 경우
    arr.pop()
    select(arr, index + 1)


chicken_arr = []
select(chicken_arr, 0)
print(DIS)