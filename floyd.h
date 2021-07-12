#pragma once
#include <stdio.h>
#define MAX_VERTICES 5
#define INF 1000L

int weight[MAX_VERTICES][MAX_VERTICES] = {
	{ 0, 16, INF, 25, INF },
	{ 16, 0, 29, INF, INF },
	{ INF, 29, 0, 12, 17 },
	{ 25, INF, 12, 0, 22 },
	{ INF, INF, 17, 22, 0 }
};

//A[i][j] i���� j������ �ִܰŸ�
int A[MAX_VERTICES][MAX_VERTICES];

void floyd(int n) {
	int i, j, k;

	//�ʱ�ȭ ����
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			A[i][j] = weight[i][j];

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];
}