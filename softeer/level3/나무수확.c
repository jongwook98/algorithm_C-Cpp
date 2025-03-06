// dp를 정하는 기준이 독립적이지 않을 때,,
// 지피티가 해결한 문제, 숙지해보자..

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 상태: 경로에서의 누적 과일 합과, 경로 상에서의 최대 과일값
typedef struct {
	int sum;
	int max;
} State;

// 동적 배열로 상태 집합을 관리하기 위한 구조체
typedef struct {
	State* states;
	int count;
	int capacity;
} StateList;

// StateList 초기화
void initStateList(StateList* list) {
	list->capacity = 4;
	list->count = 0;
	list->states = (State*)malloc(sizeof(State) * list->capacity);
}

// StateList 메모리 해제
void freeStateList(StateList* list) {
	free(list->states);
}

// StateList에 상태 추가
void pushState(StateList* list, State s) {
	if (list->count == list->capacity) {
		list->capacity *= 2;
		list->states = (State*)realloc(list->states, sizeof(State) * list->capacity);
	}
	list->states[list->count++] = s;
}

// 두 상태 s와 t에 대해, s가 t를 지배(dominates)한다는 것은
// s.sum >= t.sum && s.max >= t.max (단, 둘 다 같으면 동등)
// 이 경우, t는 불필요한 상태입니다.
bool dominates(State s, State t) {
	return (s.sum >= t.sum && s.max >= t.max);
}

// 리스트 내에서 상태 가지치기: 서로 지배 관계가 있으면 하나만 남김
void prune(StateList* list) {
	for (int i = 0; i < list->count; i++) {
		for (int j = i + 1; j < list->count; ) {
			if (dominates(list->states[i], list->states[j])) {
				// 상태 i가 j를 지배하면 j를 제거
				list->states[j] = list->states[list->count - 1];
				list->count--;
			}
			else if (dominates(list->states[j], list->states[i])) {
				// 상태 j가 i를 지배하면 i를 제거하고 restart
				list->states[i] = list->states[list->count - 1];
				list->count--;
				i = -1; // 바깥 루프를 재시작하기 위해 i를 -1로 설정
				break;
			}
			else {
				j++;
			}
		}
	}
}

// 주어진 상태 집합에 현재 셀의 값(cell)만큼 업데이트한 상태들을 새 리스트로 반환
StateList updateStateList(StateList* list, int cell) {
	StateList newList;
	initStateList(&newList);
	for (int i = 0; i < list->count; i++) {
		State s = list->states[i];
		State ns;
		ns.sum = s.sum + cell;
		ns.max = (s.max < cell ? cell : s.max);
		pushState(&newList, ns);
	}
	prune(&newList);
	return newList;
}

// 두 상태 집합을 합친 후, 각 상태에 현재 셀 값(cell)을 업데이트하고 가지치기하여 반환
StateList mergeStateLists(StateList* A, StateList* B, int cell) {
	StateList newList;
	initStateList(&newList);
	// A 경로에서 업데이트
	for (int i = 0; i < A->count; i++) {
		State s = A->states[i];
		State ns;
		ns.sum = s.sum + cell;
		ns.max = (s.max < cell ? cell : s.max);
		pushState(&newList, ns);
	}
	// B 경로에서 업데이트
	for (int i = 0; i < B->count; i++) {
		State s = B->states[i];
		State ns;
		ns.sum = s.sum + cell;
		ns.max = (s.max < cell ? cell : s.max);
		pushState(&newList, ns);
	}
	prune(&newList);
	return newList;
}

int Map[MAX_N][MAX_N];
int N;

StateList dp[MAX_N + 1][MAX_N + 1];

int main(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Map[i][j]);
		}
	}

	// 초기화: dp[i][j] 1-indexed로 (i,j) corresponds to Map[i-1][j-1]
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			initStateList(&dp[i][j]);
		}
	}

	// Base case: (1,1)
	pushState(&dp[1][1], (State) { Map[0][0], Map[0][0] });

	// 첫 행: (1,j), j>=2
	for (int j = 2; j <= N; j++) {
		dp[1][j] = updateStateList(&dp[1][j - 1], Map[0][j - 1]);
	}

	// 첫 열: (i,1), i>=2
	for (int i = 2; i <= N; i++) {
		dp[i][1] = updateStateList(&dp[i - 1][1], Map[i - 1][0]);
	}

	// 나머지 셀
	for (int i = 2; i <= N; i++) {
		for (int j = 2; j <= N; j++) {
			dp[i][j] = mergeStateLists(&dp[i - 1][j], &dp[i][j - 1], Map[i - 1][j - 1]);
		}
	}

	// dp[N][N]에 저장된 상태들 중 최대 (sum + max) 값을 찾음
	int answer = 0;
	for (int k = 0; k < dp[N][N].count; k++) {
		int val = dp[N][N].states[k].sum + dp[N][N].states[k].max;
		if (val > answer) answer = val;
	}
	printf("%d\n", answer);

	// 메모리 해제
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			freeStateList(&dp[i][j]);
		}
	}
	return 0;
}
