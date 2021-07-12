#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50 //최대 정점 개수

//연결리스트로 구현한 그래프
typedef struct GraphNode {
	int vertex;					//정점 번호
	struct GraphNode* link;     //연결 노드
} GraphNode;

typedef struct List_Graph {
	int n;                              //정점 갯수
	GraphNode* adj_list[MAX_VERTICES];  //헤드 포인터 배열
} List_Graph;

//연결리스트 그래프 초기화
void graph_init(List_Graph* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++) g->adj_list[v] = NULL;
}

//연결리스트 정점 삽입
void insert_vertex(List_Graph* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과"); return;
	}
	g->n++;
}

//연결리스트 간선 연결
void insert_edge(List_Graph* g, int u, int v) {
	GraphNode* node; //임시 노드
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류"); return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;	
}

int visited[MAX_VERTICES]; //방문한 정점 표시 (DFS, BFS에 사용)

//깊이 우선 탐색 (Depth First Search, DFS)
void dfs_list(List_Graph* g, int v) {
	GraphNode* w;

	//시작 정점
	visited[v] = 1;
	printf("%d ", v);

	for (w = g->adj_list[v]; w; w = w->link)
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
}

//BFS에 사용할 큐 구현
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

//너비 우선 탐색 (Breadth First Search, BFS)
void bfs_list(List_Graph* g, int v) {
	GraphNode* w;
	Queue q;
	queue_init(&q);

	//시작 정점
	visited[v] = 1;
	printf("%d ", v);
	enqueue(&q, v);

	while (!is_empty(&q)) {
		v = dequeue(&q);						//큐에서 정점 추출
		for (w = g->adj_list[v]; w; w = w->link)	//인접 정점 탐색
			if (!visited[w->vertex]) {
				visited[w->vertex] = 1;			//정점 방문 표시
				printf("%d ", w->vertex);		//정점 출력
				enqueue(&q, w->vertex);			//방문한 정점 큐에 저장
			}
	}
}