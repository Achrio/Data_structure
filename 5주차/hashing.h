#pragma once
#include <stdio.h>
#include <string.h>

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
element hash_table[TABLE_SIZE];

void init_table(element ht[]) {
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		ht[i].key[0] = NULL;
	}
}

//선형 조사법
#define empty(e) (strlen(e.key)==0)
#define equal(e1, e2) (!strcmp(e1.key, e2.key))

void hash_lp_add(element item, element ht[]) {
	int i, hash_value;
	
	hash_value = i = hash_function(hash_function_char(item.key)); //문자열 숫자로 바꾸고 제산 함수
	while (!empty(ht[i])) {		  //빈 공간 찾을 때까지
		if (equal(item, ht[i])) { //똑같은 탐색 키
			fprintf(stderr, "탐색 키 중복\n"); return;
		}

		i = (i + 1) % TABLE_SIZE; //해시 주소가 중복되면 다음 공간으로

		if (i == hash_value) { //해시 테이블 끝까지 탐색 완료
			fprintf(stderr, "테이블 가득 참\n"); return;
		}
	}
	ht[i] = item; //빈 공간에 삽입
}

void hash_lp_search(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(hash_function_char(item.key)); //문자열 숫자로 바꾸고 제산 함수
	while (!empty(ht[i])) {		  //빈 공간 찾을 때까지

		if (equal(item, ht[i])) { //똑같은 탐색 키 
			fprintf(stderr, "탐색 성공 : %d\n", i); return;
		}

		i = (i + 1) % TABLE_SIZE; //해시 주소가 중복되면 다음 공간으로

		if (i == hash_value) { //해시 테이블 끝까지 탐색 완료
			fprintf(stderr, "찾는 값이 테이블에 없음\n"); return;
		}
	}
	fprintf(stderr, "찾는 값이 테이블에 없음\n");
}

