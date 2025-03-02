from collections import deque

# 나이트의 이동 방향 저장
dy = [-2, -2, -1, 1, 2, 2, 1, -1]
dx = [-1, 1, 2, 2, 1, -1, -2, -2]

def BFS():
    # 맵 크기 입력, 방문 확인 변수 생성
    I = int(input())
    check = [[False for _ in range(I)] for _ in range(I)]

    # 시작 좌표, 골 좌표 저장
    init_y, init_x = map(int, input().split())
    goal_y, goal_x = map(int, input().split())

    Que = deque([[init_y, init_x]])
    check[init_y][init_x] = 0

    # 시작 좌표와 골 좌표가 같을 때 처리
    if init_y == goal_y and init_x == goal_x:
        return print(0)

    # deque 구조로 BFS 구조 기반 완전 탐색
    while len(Que):
        cur_y, cur_x = Que.popleft()
        for i in range(8):
            ny = cur_y + dy[i]
            nx = cur_x + dx[i]
            if 0 <= ny < I and 0 <= nx < I:
                if check[ny][nx] is False:
                    check[ny][nx] = check[cur_y][cur_x] + 1
                    Que.append([ny, nx])

                if ny == goal_y and nx == goal_x:
                    return print(check[ny][nx])

if __name__=="__main__":
    TC = int(input())
    for _ in range(TC):
        BFS()