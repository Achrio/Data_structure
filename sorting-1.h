#pragma once
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

//선택 정렬
void selection_sort(int list[], int n) {
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		//최소값 찾는 과정
		for (j = i + 1; j < n; j++)
			if (list[j] < list[least]) least = j;
		//최소값과 값 교환
		SWAP(list[i], list[least], temp);
	}
}


//삽입 정렬
void insertion_sort(int list[], int n) {
	int i, j, key;

	//key를 선택
	for (i = 1; i < n; i++) {
		key = list[i];

		//key 앞의 레코드 값과 비교
		//맨 앞 레코드까지 비교 완료, 혹은 레코드가 key보다 작거나 같으면 종료
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];

		list[j + 1] = key;
	}
	//레코드를 모두 key로 선택할 때까지 반복
}


//버블 정렬
void bubble_sort(int list[], int n) {
	int i, j, temp;

	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}

//셀 정렬

//first부터 last까지 gap만큼 떨어진 요소들 삽입 정렬
void inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap) list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
//gap 나눠서 -> 삽입 정렬
void shell_sort(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

//합병 정렬
int sorted[8]; //합병 과정에서 정렬할 때 필요한 공간

void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	//합병 진행 : sorted에 작은 순으로 채워넣기
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else					sorted[k++] = list[j++];
	}

	//합병 진행 : 남은 레코드들 일괄 복사
	if (i > mid)
		for (l = j; l <= right; l++) sorted[k++] = list[l];
	else
		for (l = i; l < mid; l++)	 sorted[k++] = list[l];

	//합병 완료 : sorted에 정렬된 리스트를 list로 복사
	for (l = left; l <= right; l++) list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		//mid를 기준으로 반으로 나눈다
		mid = (left + right) / 2;

		//왼쪽 부분에서 call-back
		merge_sort(list, left, mid);

		//오른쪽 부분에서 call-back
		merge_sort(list, mid + 1, right);
		
		//왼쪽 부분-오른쪽 부분 합병
		merge(list, left, mid, right);
	}
}