#pragma once
#include "search.h"     //���� Ž�� �Լ� ���Ե� ��� ����
#define INDEX_SIZE 10	//�ε��� ���̺� ũ��
#define n 7				//������ ��

int* list;

typedef struct {
	int key;   //�ε����� ����� ��
	int index; //�ε��� ��
} itable;
itable index_list[INDEX_SIZE]; //�ε��� ���̺�

//���� ���� Ž��
int search_index(int key) {
	int i, low, high;

	//����Ʈ ���� �� �� �ƴ� ��� (�ּҰ����� �۰ų� �ִ밪���� ŭ)
	if (key<list[0] || key > list[n - 1]) return -1;

	//�ε��� ���̺� ����, Ű �� ���� ����
	for (i = 0; i < INDEX_SIZE; i++)
		if (index_list[i].key <= key &&
			index_list[i + 1].key > key) break;

	if (i == INDEX_SIZE) { //�ε��� ���̺� ��
		low = index_list[i - 1].index;
		high = n - 1;
	}
	else {
		low = index_list[i].index;
		high = index_list[i + 1].index - 1;
	}

	//���� ������ ���� Ž��
	return seq_search(key, low, high);
}