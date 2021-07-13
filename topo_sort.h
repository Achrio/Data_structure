#pragma once
#include "graph.h"
#include "stack.h"

void topo_sort(GraphType* g) {
	int i;
	StackType s;
	GraphNode* node;

	//진입 차수 계산
	int* in_degree = (int*)malloc(g->n * sizeof(int)); //진입 차수 저장할 배열
	for (i = 0; i < g->n; i++) in_degree[i] = 0; //초기화
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i]; //정점 i에서 나오는 간선들
		while (node != NULL) {
			in_degree[node->vertex]++; //정점 i의 간선과 연결된 정점의 진입 차수를 증가
			node = node->link;
		}
	}

	//진입 차수 0인 정점 스택에 삽입
	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}

	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("%d", w);
		node = g->adj_list[w];		//각 정점 진입 차수 변경
		while (node != NULL) {		
			int u = node->vertex;	//해당 정점과 연결된 정점의
			in_degree[u]--;			//진입 차수 감소
			if (in_degree[u] == 0) push(&s, u); //진입 차수 0이면 스택에 삽입
			node = node->link;		//다음 정점
		}
	}
	free(in_degree);
	return;

}