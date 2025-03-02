# Week16

## 마법사 상어와 파이어볼([https://www.acmicpc.net/problem/20056](https://www.acmicpc.net/problem/20056))

### 1. 문제 요약

- 구현

### 2. 푸는 과정

```
1) 파이어볼의 입력 python - deque, cpp - vector

2) 이동 -> 1번 행과 N번 행, 1번 열과 N번 열이 이어져 있으므로 한 칸씩 움직이지 않고 한번에 이동되는 좌표를 계산하여 입력

3) 합체 - 해당 좌표에 파이어볼 2개 이상 있다면 해당 과정을 수행하여 파이어볼 구조에 입력
```

### 3. 총평 및 주의 사항

```
1. python의 경우 파이어볼의 입력을 deque가 아닌 (y, x)를 키값으로 갖는 dictionary(list) 구조로
작성한다면해당 좌표의 fireball 개수를 바로 알 수 있으므로 더 빠른 시간안에 가능했을 것 같다.
```

```
cpp
구현하는데 어려움은 없었으나 문제가 주어지는 입력의 순서를 잘 확인할 것,
나머지를 구할 때 피제수가 음수가 되지 않도록 확인하기
```

### 4. 결과

문제 풀이 순서 CPP → python

> 정답 여부 : 정답,    소요 시간 python: 30분, cpp : 100분
> 

![Week16.PNG](../img/python/Week16.PNG)

![Week16.PNG](../img/cpp/Week16.PNG)

---
