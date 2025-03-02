// 모듈화 한다면, while 문 모듈화 가능할 듯,,

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAX_SIZE 8

typedef struct {
	int y, x;
	char type;
}info;

char Map[MAX_SIZE][MAX_SIZE];

info CCTV_info[MAX_SIZE];
int CCTV_dir[MAX_SIZE]; // 조합에서 사용
int CCTV_num;

int N, M;

int init_ans = 0;
int ans = (int)1e9;

void cal_ans() {
	bool visited[MAX_SIZE][MAX_SIZE];
	memset(visited, false, sizeof(visited));

	int local_ans = init_ans;

	for (int num = 0; num < CCTV_num; num++) {
		int cy = CCTV_info[num].y;
		int cx = CCTV_info[num].x;

		int ny = cy;
		int nx = cx;
		if (CCTV_info[num].type == '1') {
			if (CCTV_dir[num] == 0) {
				ny = cy + 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny + 1;
					nx = cx;
				}
			}

			else if (CCTV_dir[num] == 1) {
				ny = cy - 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny - 1;
					nx = nx;
				}
			}

			else if (CCTV_dir[num] == 2) {
				ny = cy;
				nx = cx + 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx + 1;
				}
			}

			else if (CCTV_dir[num] == 3) {
				ny = cy;
				nx = cx - 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx - 1;
				}
			}
		}

		else if (CCTV_info[num].type == '2') {
			if (CCTV_dir[num] == 0) {
				ny = cy + 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny + 1;
					nx = nx;
				}
				ny = cy - 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny - 1;
					nx = nx;
				}
			}

			else if (CCTV_dir[num] == 1) {
				ny = cy;
				nx = cx - 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx - 1;
				}

				ny = cy;
				nx = cx + 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx + 1;
				}
			}
		}

		else if (CCTV_info[num].type == '3') {
			if (CCTV_dir[num] == 0) {
				ny = cy + 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny + 1;
					nx = nx;
				}
				ny = cy;
				nx = cx + 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx + 1;
				}
			}

			else if (CCTV_dir[num] == 1) {
				ny = cy;
				nx = cx + 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx + 1;
				}

				ny = cy - 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny - 1;
					nx = nx;
				}
			}

			else if (CCTV_dir[num] == 2) {
				ny = cy - 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny - 1;
					nx = nx;
				}

				ny = cy;
				nx = cx - 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx - 1;
				}
			}

			else if (CCTV_dir[num] == 3) {
				ny = cy;
				nx = cx - 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx - 1;
				}

				ny = cy + 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny + 1;
					nx = nx;
				}
			}
		}
		else if (CCTV_info[num].type == '4') {
			if (CCTV_dir[num] == 0) {
				ny = cy + 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny + 1;
					nx = nx;
				}
				ny = cy;
				nx = cx + 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx + 1;
				}

				ny = cy - 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny - 1;
					nx = nx;
				}
			}

			else if (CCTV_dir[num] == 1) {
				ny = cy;
				nx = cx + 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx + 1;
				}
				ny = cy - 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny - 1;
					nx = nx;
				}

				ny = cy;
				nx = cx - 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx - 1;
				}
			}

			else if (CCTV_dir[num] == 2) {
				ny = cy - 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny - 1;
					nx = nx;
				}
				ny = cy;
				nx = cx - 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx - 1;
				}

				ny = cy + 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny + 1;
					nx = nx;
				}
			}

			else if (CCTV_dir[num] == 3) {
				ny = cy;
				nx = cx - 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx - 1;
				}
				ny = cy + 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny + 1;
					nx = nx;
				}

				ny = cy;
				nx = cx + 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx + 1;
				}
			}
		}
		else if (CCTV_info[num].type == '5') {
			if (CCTV_dir[num] == 0) {
				ny = cy + 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny + 1;
					nx = nx;
				}
				ny = cy;
				nx = cx + 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx + 1;
				}

				ny = cy - 1;
				nx = cx;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny - 1;
					nx = nx;
				}

				ny = cy;
				nx = cx - 1;

				while (ny >= 0 && ny < N && nx >= 0 && nx < M && Map[ny][nx] != '6') {
					if (Map[ny][nx] == '0' && !visited[ny][nx]) {
						visited[ny][nx] = true;
						local_ans--;
					}
					ny = ny;
					nx = nx - 1;
				}
			}
		}
	}
//	printf("%d\n", local_ans);
	ans = MIN(ans, local_ans);
}

void dfs(int cur) {
	if (cur == CCTV_num) {
		cal_ans();
	}
	else {
		if (CCTV_info[cur].type == '5') {
			CCTV_dir[cur] = 0;
			dfs(cur + 1);
		}
		else if (CCTV_info[cur].type == '2') {
			CCTV_dir[cur] = 0;
			dfs(cur + 1);

			CCTV_dir[cur] = 1;
			dfs(cur + 1);
		}
		else {
			for (int i = 0; i < 4; i++) {
				CCTV_dir[cur] = i;
				dfs(cur + 1);
			}
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			scanf(" %c", &Map[y][x]);

			if (Map[y][x] == '0') {
				init_ans++;
			}
			else if (Map[y][x] != '0' && Map[y][x] != '6') {
				CCTV_info[CCTV_num++] = (info){ y, x, Map[y][x]};
			}
		}
	}

	dfs(0); // CCTV 번호

	printf("%d", ans);

	return 0;
}
