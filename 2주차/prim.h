#pragma once
#include <stdio.h>
#define MAX_VERTICES 5
#define INF 1000L

//�׷��� ����ġ�� ��� �ܼ��� 2���� �迭
int weight[MAX_VERTICES][MAX_VERTICES] = {
	{ 0, 16, INF, 25, INF },
	{ 16, 0, 29, INF, INF },
	{ INF, 29, 0, 12, 17 },
	{ 25, INF, 12, 0, 22 },
	{ INF, INF, 17, 22, 0 }
};

int selected[MAX_VERTICES]; //���� ���� ����
int dist[MAX_VERTICES];		//���� Ʈ�� - ���� ���� ����ġ

//�ּ� dist �� ���� ���� ��ȯ
int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i < n; i++) {
		if (!selected[i]) {		//���� ���� ������ ������ �������� '�ӽ�' ����
			v = i;
			break;
		}
	}
	for (i = 0; i < n; i++) {
		if (!selected[i] && (dist[i] < dist[v])) v = i; //������ ��������, �ռ� �ϴ� �ӽ� ���õ� �������� dist�� ������ �ӽ� ���� ������ ��ü
	}
	
	return (v);
}

//s = ���� ����, n = ���� ����
void prim(int s, int n) {
	int i, u, v;

	//�ʱ�ȭ, dist ���� ��� INF(��ǻ� ���Ѵ�, �ſ� ū ��)
	for (u = 0; u < n; u++) {
		dist[u] = INF; selected[u] = 0;
	}
	dist[s] = 0; //���� ����

	for (i = 0; i < n; i++) {		//������ ������ ã�� ����
		u = get_min_vertex(n);			//�ּ� dist �� ���� ���� ��ȯ (= ���� ������)
		selected[u] = 1;				//������ ���õ����Ƿ� �����ߴٰ� ǥ��
		if (dist[u] == INF) return;		//������ ������ ���� ����
		printf("%d ", u);

		for (v = 0; v < n; v++) {								//���� ���� - ���� ���� ������ ����ġ�� ���Ͽ� ���� ������ dist ���� ��ü���ִ� ����
			if (weight[u][v] != INF)								//����ġ ���� INF�� �ƴϰ� (= ������ �����ϰ�)
				if (!selected[v] && weight[u][v] < dist[v])			//���õ��� �ʾҰ�, ���� ���������� ������ ����ġ ���� ���� �������� �Ÿ����� ª����
					dist[v] = weight[u][v];							//���� ������ dist ���� �������ش�
		}
	}
}