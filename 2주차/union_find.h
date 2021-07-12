#pragma once
#define MAX_VERTICES 100  //�ִ� ���� ����
int parent[MAX_VERTICES]; //�θ� ���
int num[MAX_VERTICES];    //�� ���� ũ��

//��� ���� �迭 �ʱ�ȭ
//��Ʈ�� ������ -1�� �������� �ʱ�ȭ -> ó���� �� ������ ������ �̷�� �ֵ��� ����
void set_init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
		num[i] = 1;
	}
}

//find - ������ ���ϴ� ������ ã�´�
int set_find(int vertex) {
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p); //�׷��� ��Ʈ ������ �Ž��� �ö�
	s = i; //���� �ݺ����� ��� i�� ������ ��ǥ ���� (��Ʈ ����� ����)
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s; //������ ��� ���ҵ��� �θ� s(��Ʈ ����� ����)�� ����
	
	return s; //��Ʈ ����� ���� ��ȯ
}

//union - ������ ���� ���ճ��� ��ģ��
void set_union(int s1, int s2) {

	//ũ�Ⱑ �� ū �������� ��Ʈ ��带 ���Ѵ�
	if (num[s1] < num[s2]) {
		parent[s1] = s2;     //������ ���������� ��Ʈ ��带 �ϳ��� ����
		num[s2] += num[s1];  //������ ���������� ������ ��� ������ ��ħ
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];  //���� ����
	}
}