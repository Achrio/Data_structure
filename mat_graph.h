#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50 //�ִ� ���� ����

//�迭�� ������ �׷���
typedef struct Mat_Graph {
	int n;										//���� ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];    //���� ǥ���� �迭
} Mat_Graph;

//�迭 �׷��� �ʱ�ȭ
void graph_init(Mat_Graph* g) {
	g->n = 0;									//���� ���� �ʱ�ȭ
	for (int r = 0; r < MAX_VERTICES; r++)
		for (int c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;				//���� �ʱ�ȭ
}

//�迭 �׷��� ���� ����
void insert_vertex(Mat_Graph* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ���� ���� �ʰ�"); return;
	}

	g->n++; //���� ���� +1
}

//�迭 �׷��� ���� ����
void insert_edge(Mat_Graph* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
	}

	//���� ����
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

int visited[MAX_VERTICES]; //�湮�� ���� ǥ�� (DFS, BFS�� ���)

//���� �켱 Ž�� (Depth First Search, DFS)
void dfs_mat(Mat_Graph* g, int v) {
	int w; //Ž���ϴ� ���� ����

	//���� ����
	visited[v] = 1;
	printf("%d ", v);

	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
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
void bfs_mat(Mat_Graph* g, int v) {
	int w; //Ž���ϴ� ���� ����
	Queue q; //�湮�� ������ ��Ƶ� ť
	queue_init(&q);

	//���� ����
	visited[v] = 1;
	printf("%d ", v);
	enqueue(&q, v);

	while (!is_empty(&q)) {
		v = dequeue(&q);							 //ť���� ���� ����
		for (w = 0; w < g->n; w++)					 //���� ���� Ž��
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = 1;						 //���� �湮 ǥ��
				printf("%d ", w);                    //���� ���
				enqueue(&q, w);                      //�湮�� ���� ť�� ����
			}
	}
}