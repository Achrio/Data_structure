#pragma once
#include <stdio.h>

#define INT_MAX 2147483647
#define MAX_VERTICES 5
#define INF 1000

int weight[MAX_VERTICES][MAX_VERTICES] = {
	{ 0, 16, INF, 25, INF },
	{ 16, 0, 29, INF, INF },
	{ INF, 29, 0, 12, 17 },
	{ 25, INF, 12, 0, 22 },
	{ INF, INF, 17, 22, 0 }
};

int distance[MAX_VERTICES]; //시작 정점으로부터의 최단 경로 거리
int found[MAX_VERTICES];	//방문한 정점

//distance가 가장 짧은 정점 선택
int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void shortest_path(int start, int n) {
	int i, u, w;

	//초기화 과정
	for (i = 0; i < n; i++) {
		distance[i] = weight[start][i];
		found[i] = 0;
	}

	//시작 정점
	found[start] = 1;
	distance[start] = 0;

	//기존 경로 vs choose에서 선택한 정점 거쳐가는 경로
	for (i = 0; i < n - 1; i++) {
		u = choose(distance, n, found);
		found[u] = 1;
		for (w = 0; w < n; w++) {
			if (!found[w])
				if (distance[u] + weight[u][w] < distance[w])
					distance[w] = distance[u] + weight[u][w];
		}
	}
}