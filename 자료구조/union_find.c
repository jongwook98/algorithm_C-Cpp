#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int parent[MAX];
int rank[MAX];

// 초기화: 각 노드는 자기 자신을 부모로 가지며, 랭크는 0으로 초기화
void init_union_find(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// find 연산 (경로 압축 적용)
// x의 루트(대표자)를 찾습니다.
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // 경로 압축
    }
    return parent[x];
}

// union 연산 (Union by Rank 적용)
// a와 b가 속한 집합을 합칩니다.
void union_sets(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    
    if (rootA == rootB)
        return; // 이미 같은 집합

    // 랭크가 낮은 트리를 높은 트리에 붙입니다.
    if (rank[rootA] < rank[rootB]) {
        parent[rootA] = rootB;
    } else if (rank[rootA] > rank[rootB]) {
        parent[rootB] = rootA;
    } else {
        parent[rootB] = rootA;
        rank[rootA]++;
    }
}

int main(void) {
    int n = 10;  // 예제에서는 10개의 원소 사용
    init_union_find(n);
    
    // 몇 가지 union 연산 실행
    union_sets(1, 2);
    union_sets(2, 3);
    union_sets(4, 5);
    union_sets(6, 7);
    union_sets(5, 6);
    union_sets(3, 4);
    
    // find 연산 테스트
    printf("find(1) = %d\n", find(1));
    printf("find(2) = %d\n", find(2));
    printf("find(3) = %d\n", find(3));
    printf("find(4) = %d\n", find(4));
    printf("find(5) = %d\n", find(5));
    printf("find(6) = %d\n", find(6));
    printf("find(7) = %d\n", find(7));
    printf("find(8) = %d\n", find(8));  // 아직 합쳐지지 않은 독립 노드

    return 0;
}
