from sys import stdin

N = int(stdin.readline().strip())
member = [list(map(int, stdin.readline().split())) for _ in range(N)]

diff = 1e9


def spec(Ateam):
    global diff

    Aspec = 0
    Bspec = 0

    Bteam = []
    for mem in range(N):
        if not mem in Ateam:
            Bteam.append(mem)

    for i in range(len(Ateam)):
        for j in range(len(Ateam)):
            if i != j:
                Aspec += member[Ateam[i]][Ateam[j]]
                Bspec += member[Bteam[i]][Bteam[j]]

    diff = min(diff, abs(Aspec - Bspec))

def make_team(team, index):
    if len(team) == N // 2:
        return spec(team)

    if index >= N:
        return False

    team.append(index)
    make_team(team, index + 1)

    team.pop()
    make_team(team, index + 1)


team = []
make_team(team, 0)

print(diff)