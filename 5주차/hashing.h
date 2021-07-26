#pragma once
#include <stdio.h>
#include <string.h>

//���� �Լ�
#define M 7 //���̺� ũ��

int hash_function(int key) {
	int hash_index = key % M;
	if (hash_index < 0) hash_index += M; //������ ���
	return hash_index;
}

//���ڿ� �ؽ� �Լ�
int hash_function_char(char* key) {
	int hash_index = 0;
	while (*key) hash_index = g * hash_index + *key++;
	return hash_index;
}

//�ؽ� ���̺�
#define KEY_SIZE 10
#define TABLE_SIZE 13

typedef struct {
	char key[KEY_SIZE];
} element;
element hash_table[TABLE_SIZE];

void init_table(element ht[]) {
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		ht[i].key[0] = NULL;
	}
}

//���� �����
#define empty(e) (strlen(e.key)==0)
#define equal(e1, e2) (!strcmp(e1.key, e2.key))

void hash_lp_add(element item, element ht[]) {
	int i, hash_value;
	
	hash_value = i = hash_function(hash_function_char(item.key)); //���ڿ� ���ڷ� �ٲٰ� ���� �Լ�
	while (!empty(ht[i])) {		  //�� ���� ã�� ������
		if (equal(item, ht[i])) { //�Ȱ��� Ž�� Ű
			fprintf(stderr, "Ž�� Ű �ߺ�\n"); return;
		}

		i = (i + 1) % TABLE_SIZE; //�ؽ� �ּҰ� �ߺ��Ǹ� ���� ��������

		if (i == hash_value) { //�ؽ� ���̺� ������ Ž�� �Ϸ�
			fprintf(stderr, "���̺� ���� ��\n"); return;
		}
	}
	ht[i] = item; //�� ������ ����
}

void hash_lp_search(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(hash_function_char(item.key)); //���ڿ� ���ڷ� �ٲٰ� ���� �Լ�
	while (!empty(ht[i])) {		  //�� ���� ã�� ������

		if (equal(item, ht[i])) { //�Ȱ��� Ž�� Ű 
			fprintf(stderr, "Ž�� ���� : %d\n", i); return;
		}

		i = (i + 1) % TABLE_SIZE; //�ؽ� �ּҰ� �ߺ��Ǹ� ���� ��������

		if (i == hash_value) { //�ؽ� ���̺� ������ Ž�� �Ϸ�
			fprintf(stderr, "ã�� ���� ���̺� ����\n"); return;
		}
	}
	fprintf(stderr, "ã�� ���� ���̺� ����\n");
}

