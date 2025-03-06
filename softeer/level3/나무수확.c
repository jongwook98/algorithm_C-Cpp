// dp�� ���ϴ� ������ ���������� ���� ��,,
// ����Ƽ�� �ذ��� ����, �����غ���..

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// ����: ��ο����� ���� ���� �հ�, ��� �󿡼��� �ִ� ���ϰ�
typedef struct {
	int sum;
	int max;
} State;

// ���� �迭�� ���� ������ �����ϱ� ���� ����ü
typedef struct {
	State* states;
	int count;
	int capacity;
} StateList;

// StateList �ʱ�ȭ
void initStateList(StateList* list) {
	list->capacity = 4;
	list->count = 0;
	list->states = (State*)malloc(sizeof(State) * list->capacity);
}

// StateList �޸� ����
void freeStateList(StateList* list) {
	free(list->states);
}

// StateList�� ���� �߰�
void pushState(StateList* list, State s) {
	if (list->count == list->capacity) {
		list->capacity *= 2;
		list->states = (State*)realloc(list->states, sizeof(State) * list->capacity);
	}
	list->states[list->count++] = s;
}

// �� ���� s�� t�� ����, s�� t�� ����(dominates)�Ѵٴ� ����
// s.sum >= t.sum && s.max >= t.max (��, �� �� ������ ����)
// �� ���, t�� ���ʿ��� �����Դϴ�.
bool dominates(State s, State t) {
	return (s.sum >= t.sum && s.max >= t.max);
}

// ����Ʈ ������ ���� ����ġ��: ���� ���� ���谡 ������ �ϳ��� ����
void prune(StateList* list) {
	for (int i = 0; i < list->count; i++) {
		for (int j = i + 1; j < list->count; ) {
			if (dominates(list->states[i], list->states[j])) {
				// ���� i�� j�� �����ϸ� j�� ����
				list->states[j] = list->states[list->count - 1];
				list->count--;
			}
			else if (dominates(list->states[j], list->states[i])) {
				// ���� j�� i�� �����ϸ� i�� �����ϰ� restart
				list->states[i] = list->states[list->count - 1];
				list->count--;
				i = -1; // �ٱ� ������ ������ϱ� ���� i�� -1�� ����
				break;
			}
			else {
				j++;
			}
		}
	}
}

// �־��� ���� ���տ� ���� ���� ��(cell)��ŭ ������Ʈ�� ���µ��� �� ����Ʈ�� ��ȯ
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

// �� ���� ������ ��ģ ��, �� ���¿� ���� �� ��(cell)�� ������Ʈ�ϰ� ����ġ���Ͽ� ��ȯ
StateList mergeStateLists(StateList* A, StateList* B, int cell) {
	StateList newList;
	initStateList(&newList);
	// A ��ο��� ������Ʈ
	for (int i = 0; i < A->count; i++) {
		State s = A->states[i];
		State ns;
		ns.sum = s.sum + cell;
		ns.max = (s.max < cell ? cell : s.max);
		pushState(&newList, ns);
	}
	// B ��ο��� ������Ʈ
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

	// �ʱ�ȭ: dp[i][j] 1-indexed�� (i,j) corresponds to Map[i-1][j-1]
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			initStateList(&dp[i][j]);
		}
	}

	// Base case: (1,1)
	pushState(&dp[1][1], (State) { Map[0][0], Map[0][0] });

	// ù ��: (1,j), j>=2
	for (int j = 2; j <= N; j++) {
		dp[1][j] = updateStateList(&dp[1][j - 1], Map[0][j - 1]);
	}

	// ù ��: (i,1), i>=2
	for (int i = 2; i <= N; i++) {
		dp[i][1] = updateStateList(&dp[i - 1][1], Map[i - 1][0]);
	}

	// ������ ��
	for (int i = 2; i <= N; i++) {
		for (int j = 2; j <= N; j++) {
			dp[i][j] = mergeStateLists(&dp[i - 1][j], &dp[i][j - 1], Map[i - 1][j - 1]);
		}
	}

	// dp[N][N]�� ����� ���µ� �� �ִ� (sum + max) ���� ã��
	int answer = 0;
	for (int k = 0; k < dp[N][N].count; k++) {
		int val = dp[N][N].states[k].sum + dp[N][N].states[k].max;
		if (val > answer) answer = val;
	}
	printf("%d\n", answer);

	// �޸� ����
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			freeStateList(&dp[i][j]);
		}
	}
	return 0;
}
