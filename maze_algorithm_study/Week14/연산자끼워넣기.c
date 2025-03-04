#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int N;
int num_arr[11];
int op_arr[10];

int op_num[4];

int min_ans = (int)1e9;
int max_ans = (int)-1e9;

void cal() {
	int result = num_arr[0];

	for (int i = 0; i < N - 1; i++) {
		if (op_arr[i] == 0) {
			result += num_arr[i + 1];
		}
		else if (op_arr[i] == 1) {
			result -= num_arr[i + 1];
		}
		else if (op_arr[i] == 2) {
			result *= num_arr[i + 1];
		}
		else {
			result /= num_arr[i + 1];
		}
	}

	min_ans = MIN(min_ans, result);
	max_ans = MAX(max_ans, result);
}

void per(int idx) {
	if (idx == N - 1) {
		cal();
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (op_num[i] > 0) {
				op_arr[idx] = i;
				op_num[i] -= 1;
				per(idx + 1);

				op_num[i] += 1;
			}
		}
	}
}

int main() {
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++) {
		scanf("%d", &num_arr[i]);
	}
	for (int i = 0; i < 4; i++) {
		scanf("%d", &op_num[i]);
	}

	per(0);

	printf("%d\n%d", max_ans, min_ans);

	return 0;
}