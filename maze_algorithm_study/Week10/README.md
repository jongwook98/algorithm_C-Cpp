# Week10

## 등산로조성([https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq&](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq&))

### 1. 문제 요약

- DFS와 조건을 이용한 문제 풀이

### 2. 푸는 과정

```
1) 지도를 입력 받고 가장 높은 구역 배열로 저장
2) DFS 이용하여 가장 높은 곳으로 부터 낮은곳으로 이동하면서 특별한 조건인 공사의 여부와 공사 가능 깊이 설정하여 탐색
3) 가능한 모든 경우 DFS를 이용하여 탐색
```

### 3. 총평 및 주의 사항

```
1. 가장 짧은 패스를 찾는 것이 아니므로 BFS로 풀기 어려움
2. DFS 구현 시 각각의 패스마다 방문 체크, 해제 확인하기
```

### 4. 결과

> 정답 여부 : 정답,    소요 시간: 70분, cpp : 40분
> 

![Week10.PNG](../img/python/Week10.PNG)
![Week10.PNG](../img/cpp/Week10.PNG)

---
