#pragma once
#define MAX_VERTICES 100
#define INF 1000L
#include "union_find.h"
#include <stdio.h>

//���� ����ü
typedef struct {
	int key;	  //���� ����ġ
	int u; int v; //����1 - ����2
} element;

//�ּ� ����
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

//����ġ ���� ���� (weight = ����ġ, ���� u-v�� �����ϴ� ����)
void insert_heap_edge(HeapType* h, int u, int v, int weight) {
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}

//Kruskal MST �˰���
void kruskal(int n) {
	int edge_accepted = 0; //������� ������ ���� ��
	HeapType h;			   //����
	int uset, vset;		   //���� u�� ���� v�� ���� ��ȣ
	element e;			   //���� ���

	init(&h);			   //���� �ʱ�ȭ
	
	//�׷��� ���� ����
	insert_heap_edge(&h, 0, 1, 16);
	insert_heap_edge(&h, 0, 3, 25);
	insert_heap_edge(&h, 1, 2, 29);
	insert_heap_edge(&h, 2, 3, 12);
	insert_heap_edge(&h, 2, 4, 17);
	insert_heap_edge(&h, 3, 4, 22);

	set_init(n);						//���� �ʱ�ȭ
	while (edge_accepted < (n - 1)) {	//���� �� < (n-1) �� ������ �ݺ� ((���� �� = n-1) = �ּ� ��� �׷����� �Ǵ� ����) 
		e = delete_min_heap(&h);		//���� ���� (��Ʈ ��� �����ϰ� ��ȯ = (�ּ� �����̹Ƿ�) �ּ� ����ġ ���� �����ϰ� ��ȯ)
		uset = set_find(e.u);			//���õ� �������� ����� ���� e�� ���� find
		vset = set_find(e.v);			//���õ� �������� ����� ���� v�� ���� find

		//������ �ٸ��� -> ����Ŭ�� �������� �ʴ´� -> �ش� ������ ������ �� �ִ�
		if (uset != vset) { 
			printf("(%d, %d) %d \n", e.u, e.v, e.key);
			edge_accepted++;	   //������ ���� ���� ����
			set_union(uset, vset); //�ش� ������ ���������Ƿ� ���� ������ ��, ������ ����
		}
	}
}
