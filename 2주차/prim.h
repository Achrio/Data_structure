#pragma once
#include <stdio.h>
#define MAX_VERTICES 5
#define INF 1000L

//그래프 가중치가 담긴 단순한 2차원 배열
int weight[MAX_VERTICES][MAX_VERTICES] = {
	{ 0, 16, INF, 25, INF },
	{ 16, 0, 29, INF, INF },
	{ INF, 29, 0, 12, 17 },
	{ 25, INF, 12, 0, 22 },
	{ INF, INF, 17, 22, 0 }
};

int selected[MAX_VERTICES]; //정점 선택 여부
int dist[MAX_VERTICES];		//신장 트리 - 정점 사이 가중치

//최소 dist 값 갖는 정점 반환
int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i < n; i++) {
		if (!selected[i]) {		//선택 안한 정점을 선택할 정점으로 '임시' 배정
			v = i;
			break;
		}
	}
	for (i = 0; i < n; i++) {
		if (!selected[i] && (dist[i] < dist[v])) v = i; //선택을 안했으며, 앞서 일단 임시 선택된 정점보다 dist값 작으면 임시 선택 정점을 교체
	}
	
	return (v);
}

//s = 시작 정점, n = 정점 개수
void prim(int s, int n) {
	int i, u, v;

	//초기화, dist 값은 모두 INF(사실상 무한대, 매우 큰 값)
	for (u = 0; u < n; u++) {
		dist[u] = INF; selected[u] = 0;
	}
	dist[s] = 0; //시작 정점

	for (i = 0; i < n; i++) {		//선택할 정점을 찾는 과정
		u = get_min_vertex(n);			//최소 dist 값 갖는 정점 반환 (= 정점 선택함)
		selected[u] = 1;				//정점이 선택됐으므로 선택했다고 표시
		if (dist[u] == INF) return;		//선택한 정점의 오류 방지
		printf("%d ", u);

		for (v = 0; v < n; v++) {								//선택 정점 - 인접 정점 간선의 가중치를 비교하여 인접 정점의 dist 값을 교체해주는 과정
			if (weight[u][v] != INF)								//가중치 값이 INF가 아니고 (= 간선이 존재하고)
				if (!selected[v] && weight[u][v] < dist[v])			//선택되지 않았고, 인접 정점으로의 간선의 가중치 값이 인접 정점과의 거리보다 짧으면
					dist[v] = weight[u][v];							//인접 정점의 dist 값을 변경해준다
		}
	}
}