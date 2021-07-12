#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50 //�ִ� ���� ����

//���Ḯ��Ʈ�� ������ �׷���
typedef struct GraphNode {
	int vertex;					//���� ��ȣ
	struct GraphNode* link;     //���� ���
} GraphNode;

typedef struct List_Graph {
	int n;                              //���� ����
	GraphNode* adj_list[MAX_VERTICES];  //��� ������ �迭
} List_Graph;

//���Ḯ��Ʈ �׷��� �ʱ�ȭ
void graph_init(List_Graph* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++) g->adj_list[v] = NULL;
}

//���Ḯ��Ʈ ���� ����
void insert_vertex(List_Graph* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�"); return;
	}
	g->n++;
}

//���Ḯ��Ʈ ���� ����
void insert_edge(List_Graph* g, int u, int v) {
	GraphNode* node; //�ӽ� ���
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����"); return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;	
}

int visited[MAX_VERTICES]; //�湮�� ���� ǥ�� (DFS, BFS�� ���)

//���� �켱 Ž�� (Depth First Search, DFS)
void dfs_list(List_Graph* g, int v) {
	GraphNode* w;

	//���� ����
	visited[v] = 1;
	printf("%d ", v);

	for (w = g->adj_list[v]; w; w = w->link)
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
}

//BFS�� ����� ť ����
typedef struct QueueNode {
	int item;
	struct QueueNode* link;
} QueueNode;
typedef struct Queue {
	QueueNode* front, * rear;
} Queue;
void queue_init(Queue* q) {
	q->front = q->rear = NULL;
}
int is_empty(Queue* q) {
	return (q->front == NULL);
}
void enqueue(Queue* q, int item) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->item = item;
	temp->link = NULL;
	if (is_empty(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else {
		q->rear->link = temp;
		q->rear = temp;
	}
}
int dequeue(Queue* q) {
	QueueNode* temp = q->front;
	int item;
	item = temp->item;
	q->front = q->front->link;
	if (q->front == NULL) q->rear = NULL;
	free(temp);
	return item;
}

//�ʺ� �켱 Ž�� (Breadth First Search, BFS)
void bfs_list(List_Graph* g, int v) {
	GraphNode* w;
	Queue q;
	queue_init(&q);

	//���� ����
	visited[v] = 1;
	printf("%d ", v);
	enqueue(&q, v);

	while (!is_empty(&q)) {
		v = dequeue(&q);						//ť���� ���� ����
		for (w = g->adj_list[v]; w; w = w->link)	//���� ���� Ž��
			if (!visited[w->vertex]) {
				visited[w->vertex] = 1;			//���� �湮 ǥ��
				printf("%d ", w->vertex);		//���� ���
				enqueue(&q, w->vertex);			//�湮�� ���� ť�� ����
			}
	}
}