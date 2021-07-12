#pragma once
#define MAX_VERTICES 100  //최대 정점 갯수
int parent[MAX_VERTICES]; //부모 노드
int num[MAX_VERTICES];    //각 집합 크기

//노드 담을 배열 초기화
//루트의 정점은 -1을 가지도록 초기화 -> 처음엔 다 각자의 집합을 이루고 있도록 구현
void set_init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}

//find - 정점이 속하는 집합을 찾는다
int set_find(int vertex) {
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); //그룹의 루트 노드까지 거슬러 올라감
	s = i; //위의 반복문의 결과 i는 집합의 대표 원소 (루트 노드의 정점)
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s; //집합의 모든 원소들의 부모를 s(루트 노드의 정점)로 설정
	
	return s; //루트 노드의 정점 반환
}

//union - 정점이 속한 집합끼리 합친다
void set_union(int s1, int s2) {

	//크기가 더 큰 집합으로 루트 노드를 정한다
	if (num[s1] < num[s2]) {
		parent[s1] = s2;     //집합이 합쳐졌으니 루트 노드를 하나로 통일
		num[s2] += num[s1];  //집합이 합쳐졌으니 집합의 노드 갯수도 합침
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];  //위와 동일
	}
}