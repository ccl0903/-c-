#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */
#define LH +1 /*  左高 */ 
#define EH 0  /*  等高 */ 
#define RH -1 /*  右高 */ 

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

/* 二叉树的二叉链表结点结构定义 */
typedef  struct AVLTNode	/* 结点结构 */
{
	int data;	/* 结点数据 */
	int bf; /*  结点的平衡因子 */
	struct BiTNode* lchild, * rchild;	/* 左右孩子指针 */
} AVLTNode, * AVLTree;   

/* 右旋 处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点 */
void R_Rotate(AVLTree *p) {  //*p根节点
	AVLTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = (*p);
	*p = L;
}

/*左旋 处理之后P指向新的树根结点，即旋转处理之前的右子树的根结点0  */
void L_Rotate(AVLTree *p) {
	AVLTree R;
	R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = (*p);
	*p = R;
}

/*  对以指针T所指结点为根的二叉树作左平衡旋转处理 */
void LeftBalance(AVLTree *T) {
	AVLTree L, Lr;
	L = (*T)->lchild;		/*  L指向T的左子树根结点 */
	switch (L->bf)
	{
	case LH:  //(LL) 新结点插入在T的左孩子的左子树上，要作单右旋处理
		(*T)->bf = L->bf = EH;
		R_Rotate(T);
		break;
	case RH:  //(LR)新结点插入在T的左孩子的右子树上，要作双旋处理
		Lr = L->rchild;  //Lr指向T的左孩子的右子树根 
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

//对以指针T所指结点为根的二叉树作右平衡旋转处理
void RightBalance(AVLTree* T) {
	AVLTree R, Rl;
	R = (*T)->rchild;
	switch (R->bf)
	{
	case RH:	// (RR)新结点插入在T的右孩子的右子树上，要作单左旋处理
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
	case LH:	// (RL)新结点插入在T的右孩子的左子树上，要作双旋处理
		Rl = R->lchild;		//Rl指向T的右孩子的左子树根
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
/*  若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */
/*  数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树 */
/*  失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。 */
Status InsertAVL(AVLTree* T, int e, Status* taller)
{
	if (!*T)
	{ /*  插入新结点，树“长高”，置taller为TRUE */
		*T = (AVLTree)malloc(sizeof(AVLTNode));
		(*T)->data = e; (*T)->lchild = (*T)->rchild = NULL; (*T)->bf = EH;
		*taller = TRUE;
	}
	else
	{
		if (e == (*T)->data)
		{ /*  树中已存在和e有相同关键字的结点则不再插入 */
			*taller = FALSE; return FALSE;
		}
		if (e < (*T)->data)
		{ /*  应继续在T的左子树中进行搜索 */
			if (!InsertAVL(&(*T)->lchild, e, taller)) /*  未插入 */
				return FALSE;
			if (*taller) /*   已插入到T的左子树中且左子树“长高” */
				switch ((*T)->bf) /*  检查T的平衡度 */
				{
				case LH: /*  原本左子树比右子树高，需要作左平衡处理 */
					LeftBalance(T);	*taller = FALSE; break;
				case EH: /*  原本左、右子树等高，现因左子树增高而使树增高 */
					(*T)->bf = LH; *taller = TRUE; break;
				case RH: /*  原本右子树比左子树高，现左、右子树等高 */
					(*T)->bf = EH; *taller = FALSE; break;
				}
		}
		else
		{ /*  应继续在T的右子树中进行搜索 */
			if (!InsertAVL(&(*T)->rchild, e, taller)) /*  未插入 */
				return FALSE;
			if (*taller) /*  已插入到T的右子树且右子树“长高” */
				switch ((*T)->bf) /*  检查T的平衡度 */
				{
				case LH: /*  原本左子树比右子树高，现左、右子树等高 */
					(*T)->bf = EH; *taller = FALSE;	break;
				case EH: /*  原本左、右子树等高，现因右子树增高而使树增高  */
					(*T)->bf = RH; *taller = TRUE; break;
				case RH: /*  原本右子树比左子树高，需要作右平衡处理 */
					RightBalance(T); *taller = FALSE; break;
				}
		}
	}
	return TRUE;
}

//中序
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