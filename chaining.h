#pragma once
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

typedef struct ListNode {
	element item;
	struct ListNode* link;
} ListNode;
ListNode* hash_table[TABLE_SIZE];

#define equal(e1, e2) (!strcmp(e1.key, e2.key))

void hash_lp_add(element item, ListNode* ht[]) {
	int hash_value = hash_function(hash_function_char(item.key)); //���ڿ� ���ڷ� �ٲٰ� ���� �Լ�
	
	ListNode* ptr;
	ListNode* node_before = NULL;
	ListNode* node = ht[hash_value];

	for (; node; node_before = node, node = node->link) {
		if (equal(node->item, item)) {
			fprintf(stderr, "Ž��Ű �ߺ�\n"); return;
		}
	}
	ptr = (ListNode*)malloc(sizeof(ListNode));
	ptr->item = item; ptr->link = NULL;

	if (node_before) node_before->link = ptr; //���� ���Ḯ��Ʈ�� ���� ��
	else ht[hash_value] = ptr;				  //���� ���Ḯ��Ʈ�� ���� ��
}

void hash_lp_search(element item, ListNode* ht[]) {
	ListNode* node;

	int hash_value = hash_function(hash_function_char(item.key)); //���ڿ� ���ڷ� �ٲٰ� ���� �Լ�
	for (node = ht[hash_value]; node; node = node->link) {		  //�� ���� ã�� ������
		if (equal(node->item, item)) { //�Ȱ��� Ž�� Ű 
			printf("Ž�� ���� : %d\n", hash_value); return;
		}
	}
	fprintf(stderr, "ã�� ���� ���̺� ����\n");
}

