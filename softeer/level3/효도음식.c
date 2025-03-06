#include <stdio.h>

#define MAX_N 100000
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int ARR[MAX_N];
int sum[MAX_N + 1];

int N;

int main(void)
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &ARR[i]);
		if (i != 0) {
			sum[i + 1] = sum[i] + ARR[i];
		}
		else
			sum[i + 1] = ARR[i];
	}

	long long answer = (long long)-1e15;

	long long MAX_L[MAX_N];
	long long MAX_R[MAX_N];

	for (int i = 0; i < MAX_N; i++) {
		MAX_L[i] = (long long)-1e15;
		MAX_R[i] = (long long)-1e15;
	}

	int min_prefix = 0;
	for (int i = 1; i <= N - 1; i++) {
		int current = sum[i] - min_prefix;
		if (sum[i] < min_prefix)
			min_prefix = sum[i];
		if (i == 1)
			MAX_L[i] = current;
		else
			MAX_L[i] = MAX(MAX_L[i - 1], current);
	}

	int max_suffix = sum[N];
	for (int i = N - 1; i >= 1; i--) {
		int current = max_suffix - sum[i];
		if (sum[i] > max_suffix)
			max_suffix = sum[i];
		if (i == N - 1)
			MAX_R[i] = current;
		else
			MAX_R[i] = MAX(MAX_R[i + 1], current);
	}

	for (int i = 1; i <= N - 2; i++) {
		answer = MAX(answer, MAX_L[i] + MAX_R[i + 1]);
	}

	printf("%lld", answer);

	return 0;
}
			e = e->next;
			free(temp);
		}
	}

	return 0;
}