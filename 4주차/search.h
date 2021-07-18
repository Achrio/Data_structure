#pragma once
#include <stdio.h>

int* list;

//순차 탐색
int seq_search(int key, int low, int high) {
	int i;
	for (i = low; i <= high; i++)
		if (list[i] == key) return i;
	return -1;
}

int seq_search2(int key, int low, int high) {
	int i;
	list[high + 1] = key;
	for (i = low; list[i] != key; i++); //키 값 찾으면 종료
	if (i == (high + 1)) return -1;		//탐색 성공
	else return i;						//탐색 실패
}

int sorted_seq_search(int key, int low, int high) {
	int i;
	for (i = low; i <= high; i++) {
		if (list[i] > key) return -1; //항목 값이 키값보다 더 크면 종료
		if (list[i] == key) return i; //키 값 찾으면 종료
	}
}

//이진 탐색
int search_binary(int key, int low, int high) {
	int middle;
	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])	 //탐색 성공
			return middle;
		else if (key < list[middle]) //왼쪽 부분 리스트 탐색
			return search_binary(key, low, middle - 1);
		else                         //오른쪽 부분 리스트 탐색
			return search_binary(key, middle + 1, high);
	}
	return -1; //탐색 실패
}

int search_binary2(int key, int low, int high) {
	int middle;
	while (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])     //탐색 성공
			return middle;
		else if (key > list[middle]) //왼쪽 부분 리스트 탐색
			low = middle + 1;
		else                         //오른쪽 부분 리스트 탐색
			high = middle - 1;
	}
	return -1; //탐색 실패
}