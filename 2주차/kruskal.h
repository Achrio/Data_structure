#pragma once
#define MAX_VERTICES 100
#define INF 1000L
#include "union_find.h"
#include <stdio.h>

//간선 구조체
typedef struct {
	int key;	  //간선 가중치
	int u; int v; //정점1 - 정점2
} element;

//최소 히프
typedef struct {
	element heap[MAX_VERTICES];
	int heap_size;
} HeapType;
void init(HeapType* h) { h->heap_size = 0; }
int is_empty(HeapType* h) {
	if (h->heap_size == 0) return 1;
	else return 0;
}
void insert_min_heap(HeapType* h, element item) {
	int i; i = ++(h->heap_size);
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key) child++;
		if (temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//가중치 간선 삽입 (weight = 가중치, 정점 u-v를 연결하는 간선)
void insert_heap_edge(HeapType* h, int u, int v, int weight) {
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}

//Kruskal MST 알고리즘
void kruskal(int n) {
	int edge_accepted = 0; //현재까지 선택한 간선 수
	HeapType h;			   //히프
	int uset, vset;		   //정점 u와 정점 v의 집합 번호
	element e;			   //히프 요소

	init(&h);			   //히프 초기화
	
	//그래프 간선 삽입
	insert_heap_edge(&h, 0, 1, 16);
	insert_heap_edge(&h, 0, 3, 25);
	insert_heap_edge(&h, 1, 2, 29);
	insert_heap_edge(&h, 2, 3, 12);
	insert_heap_edge(&h, 2, 4, 17);
	insert_heap_edge(&h, 3, 4, 22);

	set_init(n);						//집합 초기화
	while (edge_accepted < (n - 1)) {	//간선 수 < (n-1) 될 때까지 반복 ((간선 수 = n-1) = 최소 비용 그래프가 되는 조건) 
		e = delete_min_heap(&h);		//간선 선택 (루트 노드 삭제하고 반환 = (최소 히프이므로) 최소 가중치 간선 삭제하고 반환)
		uset = set_find(e.u);			//선택된 간선으로 연결된 정점 e의 집합 find
		vset = set_find(e.v);			//선택된 간선으로 연결된 정점 v의 집합 find

		//집합이 다르다 -> 사이클이 생성되지 않는다 -> 해당 간선을 선택할 수 있다
		if (uset != vset) { 
			printf("(%d, %d) %d \n", e.u, e.v, e.key);
			edge_accepted++;	   //선택한 간선 갯수 증가
			set_union(uset, vset); //해당 간선을 선택했으므로 같은 집합이 됨, 집합을 결합
		}
	}
}
