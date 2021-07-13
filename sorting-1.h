#pragma once
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

//���� ����
void selection_sort(int list[], int n) {
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		//�ּҰ� ã�� ����
		for (j = i + 1; j < n; j++)
			if (list[j] < list[least]) least = j;
		//�ּҰ��� �� ��ȯ
		SWAP(list[i], list[least], temp);
	}
}


//���� ����
void insertion_sort(int list[], int n) {
	int i, j, key;

	//key�� ����
	for (i = 1; i < n; i++) {
		key = list[i];

		//key ���� ���ڵ� ���� ��
		//�� �� ���ڵ���� �� �Ϸ�, Ȥ�� ���ڵ尡 key���� �۰ų� ������ ����
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];

		list[j + 1] = key;
	}
	//���ڵ带 ��� key�� ������ ������ �ݺ�
}


//���� ����
void bubble_sort(int list[], int n) {
	int i, j, temp;

	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}

//�� ����

//first���� last���� gap��ŭ ������ ��ҵ� ���� ����
void inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap) list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
//gap ������ -> ���� ����
void shell_sort(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

//�պ� ����
int sorted[8]; //�պ� �������� ������ �� �ʿ��� ����

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	//�պ� ���� : sorted�� ���� ������ ä���ֱ�
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else					sorted[k++] = list[j++];
	}

	//�պ� ���� : ���� ���ڵ�� �ϰ� ����
	if (i > mid)
		for (l = j; l <= right; l++) sorted[k++] = list[l];
	else
		for (l = i; l < mid; l++)	 sorted[k++] = list[l];

	//�պ� �Ϸ� : sorted�� ���ĵ� ����Ʈ�� list�� ����
	for (l = left; l <= right; l++) list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		//mid�� �������� ������ ������
		mid = (left + right) / 2;

		//���� �κп��� call-back
		merge_sort(list, left, mid);

		//������ �κп��� call-back
		merge_sort(list, mid + 1, right);
		
		//���� �κ�-������ �κ� �պ�
		merge(list, left, mid, right);
	}
}