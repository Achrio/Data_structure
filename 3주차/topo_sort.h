#pragma once
#include "graph.h"
#include "stack.h"

void topo_sort(GraphType* g) {
	int i;
	StackType s;
	GraphNode* node;

	//���� ���� ���
	int* in_degree = (int*)malloc(g->n * sizeof(int)); //���� ���� ������ �迭
	for (i = 0; i < g->n; i++) in_degree[i] = 0; //�ʱ�ȭ
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i]; //���� i���� ������ ������
		while (node != NULL) {
			in_degree[node->vertex]++; //���� i�� ������ ����� ������ ���� ������ ����
			node = node->link;
		}
	}

	//���� ���� 0�� ���� ���ÿ� ����
	init(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0) push(&s, i);
	}

	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("%d", w);
		node = g->adj_list[w];		//�� ���� ���� ���� ����
		while (node != NULL) {		
			int u = node->vertex;	//�ش� ������ ����� ������
			in_degree[u]--;			//���� ���� ����
			if (in_degree[u] == 0) push(&s, u); //���� ���� 0�̸� ���ÿ� ����
			node = node->link;		//���� ����
		}
	}
	free(in_degree);
	return;

}