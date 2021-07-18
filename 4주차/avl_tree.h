#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct AvlNode {
	int data;
	struct AvlNode* left_child, * right_child;
}AvlNode;
AvlNode* root;

//LL ȸ��
AvlNode* rotate_LL(AvlNode* parent) {
	AvlNode* child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

//RR ȸ��
AvlNode* rotate_RR(AvlNode* parent) {
	AvlNode* child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}

//RL ȸ�� �Լ�
AvlNode* rotate_RL(AvlNode* parent) {
	AvlNode* child = parent->right_child;
	parent->right_child = rotate_LL(child);
	return rotate_RR(parent);
}

//LR ȸ�� �Լ�
AvlNode* rotate_LR(AvlNode* parent) {
	AvlNode* child = parent->left_child;
	parent->left_child = rotate_RR(child);
	return rotate_LL(parent);
}

//Ʈ�� ���� ��ȯ
int get_height(AvlNode* node) {
	int height = 0;
	if (node != NULL)
		//���� ���� Ʈ���� ������ ���� Ʈ�� �� �� ū ���� +1 = Ʈ���� ����
		height = 1 + max(get_height(node->left_child), get_height(node->right_child)); 
	return height;
}

//��� ���� �μ� ��ȯ
int get_height_diff(AvlNode* node) {
	if (node == NULL) return 0;
	//���� ���� Ʈ�� �μ��� ������ ���� Ʈ�� �μ��� ��
	return get_height(node->left_child) - get_height(node->right_child);
}

//���� Ʈ���� ����� �Լ�
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

	//0. Ʈ���� ������� ��
	if (*root == NULL) {
		*root = (AvlNode*)malloc(sizeof(AvlNode)); //��Ʈ ���� �Ҵ�
		if (*root == NULL) {
			fprintf(stderr, "�޸� �Ҵ� ����\n"); exit(1);
		}
		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}

	//1. �߰��� ������ < ��Ʈ ������
	else if (new_key < (*root)->data) {
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		*root = rebalance(root);
	}

	//2. �߰��� ������ > ��Ʈ ������
	else if (new_key > (*root)->data) {
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		*root = rebalance(root);
	}
}

AvlNode* avl_search(AvlNode* node, int key) {
	if (node == NULL) return NULL;
	printf("%d ", node->data);

	//0. ã���� ��ȯ
	if (key == node->data) return node;

	//1. key�� ��尪���� ���� => ���� ����Ʈ���� ��� Ž��
	else if (key < node->data)
		return avl_search(node->left_child, key);

	//2. key�� ��尪���� ŭ => ������ ����Ʈ���� ��� Ž��
	else
		return avl_search(node->right_child, key);
}