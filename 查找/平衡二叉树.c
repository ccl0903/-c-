#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */
#define LH +1 /*  ��� */ 
#define EH 0  /*  �ȸ� */ 
#define RH -1 /*  �Ҹ� */ 

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

/* �������Ķ���������ṹ���� */
typedef  struct AVLTNode	/* ���ṹ */
{
	int data;	/* ������� */
	int bf; /*  ����ƽ������ */
	struct BiTNode* lchild, * rchild;	/* ���Һ���ָ�� */
} AVLTNode, * AVLTree;   

/* ���� ����֮��pָ���µ�������㣬����ת����֮ǰ���������ĸ���� */
void R_Rotate(AVLTree *p) {  //*p���ڵ�
	AVLTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = (*p);
	*p = L;
}

/*���� ����֮��Pָ���µ�������㣬����ת����֮ǰ���������ĸ����0  */
void L_Rotate(AVLTree *p) {
	AVLTree R;
	R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = (*p);
	*p = R;
}

/*  ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת���� */
void LeftBalance(AVLTree *T) {
	AVLTree L, Lr;
	L = (*T)->lchild;		/*  Lָ��T������������� */
	switch (L->bf)
	{
	case LH:  //(LL) �½�������T�����ӵ��������ϣ�Ҫ������������
		(*T)->bf = L->bf = EH;
		R_Rotate(T);
		break;
	case RH:  //(LR)�½�������T�����ӵ��������ϣ�Ҫ��˫������
		Lr = L->rchild;  //Lrָ��T�����ӵ��������� 
		switch (Lr->bf)
		{
		case LH:
			(*T)->bf = RH;
			L->bf = EH;
			break;
		case EH:
			(*T)->bf = L->bf = EH;
			break;
		case RH:
			(*T)->bf = EH;
			L->bf = LH;
			break;
		}
		Lr->bf = EH;
		L_Rotate(&(*T)->lchild);
		R_Rotate(T);
	}
}

//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����
void RightBalance(AVLTree* T) {
	AVLTree R, Rl;
	R = (*T)->rchild;
	switch (R->bf)
	{
	case RH:	// (RR)�½�������T���Һ��ӵ��������ϣ�Ҫ������������
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
	case LH:	// (RL)�½�������T���Һ��ӵ��������ϣ�Ҫ��˫������
		Rl = R->lchild;		//Rlָ��T���Һ��ӵ���������
		switch (Rl->bf) {
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		case EH:
			(*T)->bf = R->bf = EH;
			break;
		case LH:
			(*T)->bf = EH;
			R->bf = RH;
			break;
		}
		Rl->bf = EH;
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);
	}
}
/*  ����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ�� */
/*  ����Ԫ��Ϊe���½�㣬������1�����򷵻�0����������ʹ���������� */
/*  ʧȥƽ�⣬����ƽ����ת������������taller��ӳT������� */
Status InsertAVL(AVLTree* T, int e, Status* taller)
{
	if (!*T)
	{ /*  �����½�㣬�������ߡ�����tallerΪTRUE */
		*T = (AVLTree)malloc(sizeof(AVLTNode));
		(*T)->data = e; (*T)->lchild = (*T)->rchild = NULL; (*T)->bf = EH;
		*taller = TRUE;
	}
	else
	{
		if (e == (*T)->data)
		{ /*  �����Ѵ��ں�e����ͬ�ؼ��ֵĽ�����ٲ��� */
			*taller = FALSE; return FALSE;
		}
		if (e < (*T)->data)
		{ /*  Ӧ������T���������н������� */
			if (!InsertAVL(&(*T)->lchild, e, taller)) /*  δ���� */
				return FALSE;
			if (*taller) /*   �Ѳ��뵽T�����������������������ߡ� */
				switch ((*T)->bf) /*  ���T��ƽ��� */
				{
				case LH: /*  ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
					LeftBalance(T);	*taller = FALSE; break;
				case EH: /*  ԭ�����������ȸߣ��������������߶�ʹ������ */
					(*T)->bf = LH; *taller = TRUE; break;
				case RH: /*  ԭ�����������������ߣ������������ȸ� */
					(*T)->bf = EH; *taller = FALSE; break;
				}
		}
		else
		{ /*  Ӧ������T���������н������� */
			if (!InsertAVL(&(*T)->rchild, e, taller)) /*  δ���� */
				return FALSE;
			if (*taller) /*  �Ѳ��뵽T���������������������ߡ� */
				switch ((*T)->bf) /*  ���T��ƽ��� */
				{
				case LH: /*  ԭ�����������������ߣ������������ȸ� */
					(*T)->bf = EH; *taller = FALSE;	break;
				case EH: /*  ԭ�����������ȸߣ��������������߶�ʹ������  */
					(*T)->bf = RH; *taller = TRUE; break;
				case RH: /*  ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
					RightBalance(T); *taller = FALSE; break;
				}
		}
	}
	return TRUE;
}

//����
void InOrderTraverse_AVL(AVLTree T) {
	if (T == NULL)
		return;
	InOrderTraverse_AVL(T->lchild);
	printf("%d==>", T->data);
	InOrderTraverse_AVL(T->rchild);
}

int main_AVL() {

	int i;
	int a[10] = { 3,2,1,4,5,6,7,10,9,8 };
	AVLTree T = NULL;
	Status taller;
	for (i = 0; i < 10; i++)
	{
 		InsertAVL(&T, a[i], &taller);
	}

	InOrderTraverse_AVL(T);
	return 0;
}