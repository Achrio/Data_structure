#pragma once
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50 //최대 정점 개수

//배열로 구현한 그래프
typedef struct Mat_Graph {
	int n;										//정점 갯수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];    //간선 표시할 배열
} Mat_Graph;

//배열 그래프 초기화
void graph_init(Mat_Graph* g) {
	g->n = 0;									//정점 갯수 초기화
	for (int r = 0; r < MAX_VERTICES; r++)
		for (int c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;				//간선 초기화
}

//배열 그래프 정점 삽입
void insert_vertex(Mat_Graph* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점 개수 초과"); return;
	}

	g->n++; //정점 개수 +1
}

//배열 그래프 간선 연결
void insert_edge(Mat_Graph* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
	}

	//간선 연결
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

int visited[MAX_VERTICES]; //방문한 정점 표시 (DFS, BFS에 사용)

//깊이 우선 탐색 (Depth First Search, DFS)
void dfs_mat(Mat_Graph* g, int v) {
	int w; //탐색하는 정점 변수

	//시작 정점
	visited[v] = 1;
	printf("%d ", v);

	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
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
void bfs_mat(Mat_Graph* g, int v) {
	int w; //탐색하는 정점 변수
	Queue q; //방문한 정점을 담아둘 큐
	queue_init(&q);

	//시작 정점
	visited[v] = 1;
	printf("%d ", v);
	enqueue(&q, v);

	while (!is_empty(&q)) {
		v = dequeue(&q);							 //큐에서 정점 추출
		for (w = 0; w < g->n; w++)					 //인접 정점 탐색
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = 1;						 //정점 방문 표시
				printf("%d ", w);                    //정점 출력
				enqueue(&q, w);                      //방문한 정점 큐에 저장
			}
	}
}