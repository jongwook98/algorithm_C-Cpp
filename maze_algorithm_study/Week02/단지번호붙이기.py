from sys import stdin
from collections import deque

# 10분

N = int(stdin.readline().strip())   # 격자 크기 입력
Map = [list(map(int, stdin.readline().strip())) for _ in range(N)] # Map 정보 입력
check = [[False] * N for _ in range(N)] # 방문여부 확인

# 현재 위치를 기준으로 상 하 좌 우 체크
dy = [0, 0, 1, -1]
dx = [1, -1, 0, 0]

value = 0       # 단지 번호
output_arr = [] # 단지 수 저장 리스트

Que = deque()

# 맵 크기 만큼 완전 탐색
for y in range(N):
    for x in range(N):

        # 방문하지 않고, Map상에서 집이 있는 위치라면 deque 구조에 넣는다
        if Map[y][x] == 1 and check[y][x] is False:

            # 단지번호 늘리고, 집의 수 초기화
            value += 1
            count = 0
            check[y][x] = value
            Que.append((y, x))

            # BFS 구조로 인접한 방문하지 않은 집 탐색
            while len(Que):
                cur_y, cur_x = Que.popleft()
                count += 1
                for i in range(4):
                    ny = cur_y + dy[i]
                    nx = cur_x + dx[i]
                    if 0 <= ny < N and 0 <= nx < N:
                        if Map[ny][nx] == 1 and check[ny][nx] is False:
                            check[ny][nx] = value
                            Que.append((ny, nx))

            # BFS 구조가 끝나면 단지 수 저장 리스트에 저장
            output_arr.append(count)

# 단지 수 오름차순 정렬
output_arr.sort()

# 결과 출력
print(value)
for i in range(len(output_arr)):
    print(output_arr[i])