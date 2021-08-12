#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//数据类型
#define TElemType char
//树结点
typedef struct TreeNode
{
	TElemType data; //数据域
	struct TreeNode* fristChild; //孩子指针
	struct TreeNode* nextSibling;  //兄弟指针
}TreeNode,*Tree;


//创建树
void CreateTree(Tree *T) {
	TElemType h;
	scanf("%c", &h);
	if (h == '#')
		*T = NULL;
	else {
		*T = (Tree)malloc(sizeof(TreeNode));
		assert(*T != NULL);
		(*T)->data = h;
		CreateTree(&(*T)->fristChild);
		CreateTree(&(*T)->nextSibling);
	}
}

//获取根结点
Tree Root(Tree T) {
	if(T!=NULL)
		return T;
	return NULL;
}

//获取第一个孩子结点
Tree FirstChild(Tree T) {
	if (T == NULL)
		return NULL;
	return T->fristChild;
}

//第一个兄弟结点
Tree NextSibling(Tree T) {
	if (T == NULL)
		return NULL;
	return T->nextSibling;
}

//查找结点
Tree Sreach(Tree T,TElemType key) {
	if (T == NULL)
		return NULL;
	if (T->data == key)//查找根结点
		return T;
	//找不到往子结点查找
	Tree P = Sreach(T->fristChild, key);
	if (P != NULL)
		return P;
	return Sreach(T->nextSibling, key);  //查找兄弟结点
}

//查找父结点
Tree Parent(Tree T,Tree P) {
	if (T == NULL || P == NULL || P == T)	//要查结点为根结点：无父结点
		return NULL;
	Tree Q = T->fristChild;
	Tree parent;
	while (Q != NULL && Q!= P)
	{
		parent = Parent(Q,P);   //先查这一层的孩子结点
		if (parent != NULL)
			return parent;
		Q = Q->nextSibling; //孩子结点没找到，查兄弟结点
	}

	if (Q != NULL && Q == P)
		return T;
	return NULL;
}

int main() {
	Tree T,root,Tp,Ts,Tc;
	char key;
	printf("请按前序输入二叉树(如:'ABDH##I##EJ###CF##G##')\n");
	CreateTree(&T);

	printf("\n前序遍历二叉树T:");
	PreOrderTraverse_lt(T);

	Tc = FirstChild(T);
	printf("\n二叉树T的子结点: %c", Tc->data);

	Ts = NextSibling(Tc);
	printf("\n二叉树T的兄弟结点: %c", Ts->data);

	Tp = Parent(T,Tc);
	printf("\n二叉树B的父节点: %c", Tp->data);

	root = Root(T);
	printf("\n二叉树B的根节点: %c", root->data);

	key = 'B';
	root = Sreach(T, key);
	printf("\n二叉树%c的根节点: %c",key, root->data);

	return 0;
}