#pragma once
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//제산 함수
#define M 7 //테이블 크기

int hash_function(int key) {
	int hash_index = key % M;
	if (hash_index < 0) hash_index += M; //음수일 경우
	return hash_index;
}

//문자열 해싱 함수
int hash_function_char(char* key) {
	int hash_index = 0;
	while (*key) hash_index = g * hash_index + *key++;
	return hash_index;
}

//해시 테이블
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
	int hash_value = hash_function(hash_function_char(item.key)); //문자열 숫자로 바꾸고 제산 함수
	
	ListNode* ptr;
	ListNode* node_before = NULL;
	ListNode* node = ht[hash_value];

	for (; node; node_before = node, node = node->link) {
		if (equal(node->item, item)) {
			fprintf(stderr, "탐색키 중복\n"); return;
		}
	}
	ptr = (ListNode*)malloc(sizeof(ListNode));
	ptr->item = item; ptr->link = NULL;

	if (node_before) node_before->link = ptr; //기존 연결리스트가 있을 때
	else ht[hash_value] = ptr;				  //기존 연결리스트가 없을 때
}

void hash_lp_search(element item, ListNode* ht[]) {
	ListNode* node;

	int hash_value = hash_function(hash_function_char(item.key)); //문자열 숫자로 바꾸고 제산 함수
	for (node = ht[hash_value]; node; node = node->link) {		  //빈 공간 찾을 때까지
		if (equal(node->item, item)) { //똑같은 탐색 키 
			printf("탐색 성공 : %d\n", hash_value); return;
		}
	}
	fprintf(stderr, "찾는 값이 테이블에 없음\n");
}

