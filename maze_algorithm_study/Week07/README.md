# Week7

## 인구 이동([https://www.acmicpc.net/problem/16234](https://www.acmicpc.net/problem/16234))

### 1. 문제 요약

- 인구 차이 조건에 맞게 BFS를 활용하여 푸는 문제

### 2. 푸는 과정

```
1) 전체 구역을 방문하여 방문하지 않은 구역과 인근 지역 인구수 차이 확인
2) 인구수 차이가 조건에 맞는다면 BFS 구조로 연합의 크기, 인구합을 구해 평균을 계산
3) Que의 deque가 비었다면 해당 연합을 다 찾은것으로 확인하고 인구 할당
4) 반복하여 모든 구역에서 인구수 차이가 조건에 만족하는 구간이 없다면 종료
```

### 3. 총평 및 주의 사항

```
1. BFS 방문조건, 인구수 차이 조건에 맞게 조건문 잘 구현하기

2. 문제를 풀 때 구조를 생각하여 어떻게 구현하는 것이 시간복잡도가 짧은지 생각하고 구현하기.

모든 연합을 찾고나서 인구이동 한 알고리즘은 시간초과가 나지 않는것에 비해
연합을 찾고 인구이동 -> 다른 구간의 연합 탐색 -> 인구이동의 알고리즘은 시간초과 문제 발생
 -> pypy3 로 제출 문제해결
```

```
cpp

vector 사이즈 할당할 때 들어갈 수 있는 최대 경우는 MAX가 아닌 MAX * MAX
```

### 4. 결과

> 정답 여부 : 정답,    소요 시간: 30분, cpp : 55분
> 

![Untitled](../img/python/Week7.png)
![Untitled](../img/cpp/Week7.PNG)

---
