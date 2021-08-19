#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef int type;
typedef int Status;

typedef struct BsTreeNode {
	type  key;
	struct BsTreeNode* lchild;
	struct BsTreeNode* rchild;
}BsTreeNode,*BsTree;

Status SreachBST(BsTree T,int key,BsTree f,BsTree *p) {
	if (!T) {
		*p = f;
		return FALSE;
	}
	else if (key == T->key) {
		*p = T;
		return TRUE;
	}
	else if (key < T->key)
		return SreachBST(T->lchild, key, T, p);
	else
		return SreachBST(T->rchild, key, T, p);
}



Status InsertBST(BsTree *T,int key) {
	BsTree p, s;
	if (!SreachBST(*T, key, NULL, &p)) {
		s = (BsTree)malloc(sizeof(BsTreeNode));
		s->key = key;
		s->lchild = s->rchild = NULL;
		if (!p)			/*  ����sΪ�µĸ���� */
			*T = s;
		else if (key < p->key)
			p->lchild = s;
		else
			p->rchild = s;
		return TRUE;
	}
	else
		return FALSE;	 /*  �������йؼ�����ͬ�Ľ�㣬���ٲ��� */
}


Status Delete(BsTree* T) {
	BsTree q, s;
	if ((*T)->rchild == NULL) {
		q = *T;
		*T = (*T)->lchild;
		free(q);
	}
	else if((*T)->lchild == NULL)
	{
		q = *T;
		*T = (*T)->rchild;
		free(q);
	}
	else {
		q = *T;
		s = (*T)->lchild;
		while (s->rchild)  /* ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ���� */
		{
			q = s;
			s = s->rchild;
		}
		(*T)->key = s->key;
		if (q != (*T))
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;
		free(s);
	}
	return TRUE;
}

Status DeleteBST(BsTree *T,int key) {
	if (!*T) /* �����ڹؼ��ֵ���key������Ԫ�� */
		return FALSE;
	else {
		if (key == (*T)->key)
			return Delete(T);
		else if (key > (*T)->key)
			return DeleteBST(&(*T)->rchild, key);
		else
			return DeleteBST(&(*T)->lchild, key);
	}
}

void InOrderTraverse_BST(BsTree T) {
	if (T == NULL)
		return;
	InOrderTraverse_BST(T->lchild);
	printf("%d->", T->key);
	InOrderTraverse_BST(T->rchild);
}

int main_BST() {

	int i; 
	BsTree p;
	int a[10] = { 62,88,58,47,35,73,51,99,37,93 };
	BsTree T = NULL;

	for (i = 0; i < 10; i++) {
		InsertBST(&T,a[i]);
	}

	InOrderTraverse_BST(T);
	printf("\n");


	SreachBST(T,73,NULL,&p);
	InOrderTraverse_BST(p);
	//DeleteBST(&T, 93);

	return 0;
}