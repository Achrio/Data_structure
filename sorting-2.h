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
		//pivot보다 작으면 low++, pivot보다 큰 값 나오면 정지
		do low++;
		while (low <= right && list[low] < pivot);

		//pivot보다 크면 high--, pivot보다 작은 값 나오면 정지
		do
			high--;
		while (high >= left && list[high] > pivot);

		//list[low]와 list[high] 값 swap
		if (low < high) SWAP(list[low], list[high], temp);
	
	//이를 low와 high가 교차할 때까지 반복
	} while (low < high);

	//high와 pivot 값 swap
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
	QueueType queues[BUCKETS]; //기수마다의 레코드를 담을 큐

	for (b = 0; b < BUCKETS; b++) init(&queues[b]);

	for (d = 0; d < DIGITS; d++) {
		//자릿수마다 기수대로 큐에 담는다
		for (i = 0; i < n; i++)
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		//기수 순으로 레코드를 빼내서 정렬한다
		for (b = i = 0; b < BUCKETS; b++)
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;
	}
}