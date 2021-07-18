#pragma once
#include <stdio.h>

int* list;

//���� Ž��
int seq_search(int key, int low, int high) {
	int i;
	for (i = low; i <= high; i++)
		if (list[i] == key) return i;
	return -1;
}

int seq_search2(int key, int low, int high) {
	int i;
	list[high + 1] = key;
	for (i = low; list[i] != key; i++); //Ű �� ã���� ����
	if (i == (high + 1)) return -1;		//Ž�� ����
	else return i;						//Ž�� ����
}

int sorted_seq_search(int key, int low, int high) {
	int i;
	for (i = low; i <= high; i++) {
		if (list[i] > key) return -1; //�׸� ���� Ű������ �� ũ�� ����
		if (list[i] == key) return i; //Ű �� ã���� ����
	}
}

//���� Ž��
int search_binary(int key, int low, int high) {
	int middle;
	if (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])	 //Ž�� ����
			return middle;
		else if (key < list[middle]) //���� �κ� ����Ʈ Ž��
			return search_binary(key, low, middle - 1);
		else                         //������ �κ� ����Ʈ Ž��
			return search_binary(key, middle + 1, high);
	}
	return -1; //Ž�� ����
}

int search_binary2(int key, int low, int high) {
	int middle;
	while (low <= high) {
		middle = (low + high) / 2;
		if (key == list[middle])     //Ž�� ����
			return middle;
		else if (key > list[middle]) //���� �κ� ����Ʈ Ž��
			low = middle + 1;
		else                         //������ �κ� ����Ʈ Ž��
			high = middle - 1;
	}
	return -1; //Ž�� ����
}