#pragma once
#include <stdio.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];

	do {
		//pivot���� ������ low++, pivot���� ū �� ������ ����
		do low++;
		while (low <= right && list[low] < pivot);

		//pivot���� ũ�� high--, pivot���� ���� �� ������ ����
		do
			high--;
		while (high >= left && list[high] > pivot);

		//list[low]�� list[high] �� swap
		if (low < high) SWAP(list[low], list[high], temp);
	
	//�̸� low�� high�� ������ ������ �ݺ�
	} while (low < high);

	//high�� pivot �� swap
	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

#define BUCKETS 10
#define DIGITS 4

void radix_sort(int list[], int n) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS]; //��������� ���ڵ带 ���� ť

	for (b = 0; b < BUCKETS; b++) init(&queues[b]);

	for (d = 0; d < DIGITS; d++) {
		//�ڸ������� ������ ť�� ��´�
		for (i = 0; i < n; i++)
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		//��� ������ ���ڵ带 ������ �����Ѵ�
		for (b = i = 0; b < BUCKETS; b++)
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;
	}
}