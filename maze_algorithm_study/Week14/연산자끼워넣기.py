from sys import stdin

N = int(stdin.readline().strip())
arr = list(map(int, stdin.readline().split()))

# 기호의 개수
symbol_ = list(map(int, stdin.readline().split()))

MAX = -1000000000
MIN = 1000000000

# DFS 순열 결과를 계산하는 함수
def cal(arr, res):
    global MAX, MIN

    # new_arr = arr[:] 이 후 new_arr[i] = new_arr[i] symbol new_arr[i + 1] 했을 경우 틀림
    # num 을 계속 가져가는 방식으로 바꿈

    num = arr[0]

    for i in range(len(res)):
        if res[i] == 0:
            num = num + arr[i + 1]
        elif res[i] == 1:
            num = num - arr[i + 1]
        elif res[i] == 2:
            num = num * arr[i + 1]
        elif res[i] == 3:
            if num > 0:
                num = num // arr[i + 1]
            elif num < 0:
                num = -(abs(num) // arr[i + 1])

    MAX = max(MAX, num)
    MIN = min(MIN, num)

def DFS(arr, symbol_, res, N):
    if len(res) == N - 1:
        return cal(arr, res)

    for i in range(4):
        # 남은 기호가 있을 경우 넣고 DFS
        if symbol_[i] > 0:
            res.append(i)
            symbol_[i] -= 1

            DFS(arr, symbol_, res, N)

            # 넣지 않은 경우
            res.pop()
            symbol_[i] += 1

DFS(arr, symbol_, [], N)

print(MAX)
print(MIN)
