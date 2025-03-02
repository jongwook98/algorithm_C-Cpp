TC = int(input().strip())
mv = [[0, 1], [1, 0], [0, -1], [-1, 0]]
score = 0


def DFS(Map, check, info, N, K):
    global score
    # info 를 y, x 좌표, 공사 여부, 공사 깊이를 받도록 공사
    cur_y, cur_x, chance, deg = info

    # 이동 가능 방향
    for i in range(4):
        ny, nx = cur_y + mv[i][0], cur_x + mv[i][1]
        if 0 <= ny < N and 0 <= nx < N:
            if check[ny][nx] is False:
                # 다음 지역이 현재 지역 - 공사 깊이 보다 낮다면 등산로로 추가
                if Map[ny][nx] < Map[cur_y][cur_x] - deg:
                    # 방문 체크
                    check[ny][nx] = check[cur_y][cur_x] + 1
                    if score < check[ny][nx]:
                        score = check[ny][nx]

                    # 다음 DFS 정보 업데이트
                    info = [ny, nx, chance, 0]
                    DFS(Map, check, info, N, K)
                    # 방문 해제
                    check[ny][nx] = False

                # 현재 공사한 적 없고, 다음 지역이 공사를 했을 때 등산로로 만들 수 있다면 추가
                elif chance == 0 and Map[ny][nx] - K < Map[cur_y][cur_x]:
                    # 방문 체크
                    check[ny][nx] = check[cur_y][cur_x] + 1
                    if score < check[ny][nx]:
                        score = check[ny][nx]

                    # 다음 DFS 정보 업데이트 공사 여부 소멸, 공사 깊이 : 현재 지역 보다 높이 1 낮게 공사
                    info = [ny, nx, 1, Map[ny][nx] - Map[cur_y][cur_x] + 1]
                    DFS(Map, check, info, N, K)
                    # 방문 해제
                    check[ny][nx] = False


# 테스트케이스 만큼 반복
for T in range(TC):
    N, K = map(int, input().split())
    Map = [list(map(int, input().split())) for _ in range(N)]

    # Start Point 리스트, 가장 높은 지역, 등산로 길이 초기화
    SP = []
    highest = 0
    score = 0

    for y in range(N):
        for x in range(N):
            # 가장 높은 지역의 높이가 바뀌면 SP 초기화
            if highest < Map[y][x]:
                highest = Map[y][x]
                SP.clear()
                SP.append([y, x])
            elif highest == Map[y][x]:
                SP.append([y, x])

    # SP 만큼 반복, DFS 탐색 가장 긴 등산로 탐색
    for y, x in SP:
        check = [[False for _ in range(N)] for _ in range(N)]
        check[y][x] = 1
        DFS(Map, check, [y, x, 0, 0], N, K)

    # 출력 형식
    print("#", T + 1, " ", score, sep="")