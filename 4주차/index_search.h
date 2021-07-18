#pragma once
#include "search.h"     //순차 탐색 함수 포함된 헤더 파일
#define INDEX_SIZE 10	//인덱스 테이블 크기
#define n 7				//데이터 수

int* list;

typedef struct {
	int key;   //인덱스에 저장된 값
	int index; //인덱스 값
} itable;
itable index_list[INDEX_SIZE]; //인덱스 테이블

//색인 순차 탐색
int search_index(int key) {
	int i, low, high;

	//리스트 범위 내 값 아닌 경우 (최소값보다 작거나 최대값보다 큼)
	if (key<list[0] || key > list[n - 1]) return -1;

	//인덱스 테이블 조사, 키 값 구간 결정
	for (i = 0; i < INDEX_SIZE; i++)
		if (index_list[i].key <= key &&
			index_list[i + 1].key > key) break;

	if (i == INDEX_SIZE) { //인덱스 테이블 끝
		low = index_list[i - 1].index;
		high = n - 1;
	}
	else {
		low = index_list[i].index;
		high = index_list[i + 1].index - 1;
	}

	//예상 범위만 순차 탐색
	return seq_search(key, low, high);
}