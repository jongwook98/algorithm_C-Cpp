#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5000

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int next_node;
    char c;
}road;

typedef struct {
    road* arr;
    int count;
    int capacity;
}roadList;

int N, M;
char s[MAX_SIZE];
roadList node[MAX_SIZE];

char path[MAX_SIZE];
bool visited[MAX_SIZE];

int ans;

void initList(roadList* list) {
    list->capacity = 4;
    list->count = 0;
    list->arr = (road*)malloc(list->capacity * sizeof(road));
}

void freeList(roadList* list) {
    free(list->arr);
}

void pushList(roadList* list, int next, char c) {
    if (list->capacity == list->count) {
        list->capacity *= 2;
        list->arr = (road*)realloc(list->arr, list->capacity * sizeof(road));
    }
    list->arr[list->count++] = (road){ next, c };
}

void update_dp(int dp[], char c, int new_dp[]) {
    new_dp[0] = 0;
    for (int j = 1; j <= M; j++) {
        if (s[j - 1] == c) {
            new_dp[j] = (dp[j - 1] + 1 > dp[j] ? dp[j - 1] + 1 : dp[j]);
        }
        else {
            new_dp[j] = (dp[j] > new_dp[j - 1] ? dp[j] : new_dp[j - 1]);
        }
    }
}

void find_path(int cur, int dp[]) {
    bool moved = false;

    for (int i = 0; i < node[cur].count; i++) {
        int nn = node[cur].arr[i].next_node;
        char nc = node[cur].arr[i].c;
        if (!visited[nn]) {
            moved = true;
            int new_dp[MAX_SIZE + 1];
            update_dp(dp, nc, new_dp);
            visited[nn] = true;

            find_path(nn, new_dp);
            visited[nn] = false;
        }
    }
    if (!moved) {
        if (dp[M] > ans)
            ans = dp[M];
    }
}

int main(void)
{

    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        initList(&node[i]);
    }

    for (int i = 0; i < M; i++) {
        scanf(" %c", &s[i]);
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        char c;
        scanf("%d %d %c", &u, &v, &c);

        pushList(&node[u - 1], v - 1, c);
        pushList(&node[v - 1], u - 1, c);
    }

    visited[0] = true;
    int init_dp[MAX_SIZE + 1] = { 0 };

    find_path(0, init_dp);

    printf("%d", ans);

    for (int i = 0; i < N; i++) {
        freeList(&node[i]);
    }

    return 0;
}