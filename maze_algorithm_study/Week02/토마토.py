from sys import stdin
from collections import deque

# 16분

# 현재 위치를 기준으로 오른쪽 왼쪼 앞 뒤 위 아래 체크
DZ = [0, 0, 0, 0, 1, -1]
DY = [0, 0, 1, -1, 0, 0]
DX = [1, -1, 0, 0, 0, 0]

# 인접한 토마토 체크하는 BFS 함수
def BFS(Que, check, count):
    while len(Que):
        # 현재 위치 가져오기
        cur_z, cur_y, cur_x = Que.popleft()

        # 인접한 토마토 검사
        for i in range(6):
            nz = cur_z + DZ[i]
            ny = cur_y + DY[i]
            nx = cur_x + DX[i]

            # 토마토 상자의 크기를 넘어서지 않는 조건 설정
            if 0 <= nz < H and 0 <= ny < N and 0 <= nx < M:
                # 익지 않은 토마토가 있고, 방문하지 않았더라면 deque 구조에 append
                if tomato[nz][ny][nx] == 0 and check[nz][ny][nx] is False:
                    Que.append((nz, ny, nx))
                    # 방문정보에는 몇 일에 방문했는지 적고
                    check[nz][ny][nx] = check[cur_z][cur_y][cur_x] + 1

                    # 익지 않은 토마토 개수 감소
                    count -= 1

                    # 익지 않은 토마토가 없다면 마지막으로 넣었던 방문 정보 반환
                    if count == 0:
                        return check[nz][ny][nx]

    # BFS 함수를 돌아도 함수가 종료되지 않았다면
    # 익지 않은 토마토가 있는 것으로 보고 -1 반환
    return (-1)

if __name__=="__main__":
    # 상자의 크기 입력
    M, N, H = map(int, stdin.readline().split())
    # 상자의 크기만큼 방문정보 초기화
    check = [[[False for _ in range(M)] for _ in range(N)] for _ in range(H)]

    # 토마토 정보 입력
    tomato = [[list(map(int, stdin.readline().split())) for _ in range(N)] for _ in range(H)]

    # 익지 않은 토마토 변수 초기화
    count = 0
    Que = deque()

    for h in range(H):
        for n in range(N):
            for m in range(M):
                # 익지 않은 토마토가 있다면 개수 + 1
                if tomato[h][n][m] == 0:
                    count += 1

                # 익은 토마토는 deque 구조에 넣고 방문 정보 0으로 입력
                elif tomato[h][n][m] == 1:
                    Que.append((h, n, m))
                    check[h][n][m] = 0

    # 익지 않은 토마토가 없다면 0 출력
    if count == 0:
        print(0)
    # 있다면 BFS 함수 실행
    else:
        print(BFS(Que, check, count))