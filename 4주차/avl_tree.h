#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct AvlNode {
	int data;
	struct AvlNode* left_child, * right_child;
}AvlNode;
AvlNode* root;

//LL 회전
AvlNode* rotate_LL(AvlNode* parent) {
	AvlNode* child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

//RR 회전
AvlNode* rotate_RR(AvlNode* parent) {
	AvlNode* child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}

//RL 회전 함수
AvlNode* rotate_RL(AvlNode* parent) {
	AvlNode* child = parent->right_child;
	parent->right_child = rotate_LL(child);
	return rotate_RR(parent);
}

//LR 회전 함수
AvlNode* rotate_LR(AvlNode* parent) {
	AvlNode* child = parent->left_child;
	parent->left_child = rotate_RR(child);
	return rotate_LL(parent);
}

//트리 높이 반환
int get_height(AvlNode* node) {
	int height = 0;
	if (node != NULL)
		//왼쪽 서브 트리와 오른쪽 서브 트리 중 더 큰 값에 +1 = 트리의 높이
		height = 1 + max(get_height(node->left_child), get_height(node->right_child)); 
	return height;
}

//노드 균형 인수 반환
int get_height_diff(AvlNode* node) {
	if (node == NULL) return 0;
	//왼쪽 서브 트리 인수와 오른쪽 서브 트리 인수의 차
	return get_height(node->left_child) - get_height(node->right_child);
}

//균형 트리로 만드는 함수
AvlNode* rebalance(AvlNode** node) {
	int height_diff = get_height_diff(*node);
	if (height_diff > 1) {
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}
	else if (height_diff < -1) {
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}
	return *node;
}

AvlNode* avl_add(AvlNode** root, int new_key) {

	//0. 트리가 비어있을 때
	if (*root == NULL) {
		*root = (AvlNode*)malloc(sizeof(AvlNode)); //루트 동적 할당
		if (*root == NULL) {
			fprintf(stderr, "메모리 할당 에러\n"); exit(1);
		}
		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}

	//1. 추가할 데이터 < 루트 데이터
	else if (new_key < (*root)->data) {
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		*root = rebalance(root);
	}

	//2. 추가할 데이터 > 루트 데이터
	else if (new_key > (*root)->data) {
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		*root = rebalance(root);
	}
}

AvlNode* avl_search(AvlNode* node, int key) {
	if (node == NULL) return NULL;
	printf("%d ", node->data);

	//0. 찾으면 반환
	if (key == node->data) return node;

	//1. key가 노드값보다 작음 => 왼쪽 서브트리로 계속 탐색
	else if (key < node->data)
		return avl_search(node->left_child, key);

	//2. key가 노드값보다 큼 => 오른쪽 서브트리로 계속 탐색
	else
		return avl_search(node->right_child, key);
}