#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//��������
#define TElemType char
//�����
typedef struct TreeNode
{
	TElemType data; //������
	struct TreeNode* fristChild; //����ָ��
	struct TreeNode* nextSibling;  //�ֵ�ָ��
}TreeNode,*Tree;


//������
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

//��ȡ�����
Tree Root(Tree T) {
	if(T!=NULL)
		return T;
	return NULL;
}

//��ȡ��һ�����ӽ��
Tree FirstChild(Tree T) {
	if (T == NULL)
		return NULL;
	return T->fristChild;
}

//��һ���ֵܽ��
Tree NextSibling(Tree T) {
	if (T == NULL)
		return NULL;
	return T->nextSibling;
}

//���ҽ��
Tree Sreach(Tree T,TElemType key) {
	if (T == NULL)
		return NULL;
	if (T->data == key)//���Ҹ����
		return T;
	//�Ҳ������ӽ�����
	Tree P = Sreach(T->fristChild, key);
	if (P != NULL)
		return P;
	return Sreach(T->nextSibling, key);  //�����ֵܽ��
}

//���Ҹ����
Tree Parent(Tree T,Tree P) {
	if (T == NULL || P == NULL || P == T)	//Ҫ����Ϊ����㣺�޸����
		return NULL;
	Tree Q = T->fristChild;
	Tree parent;
	while (Q != NULL && Q!= P)
	{
		parent = Parent(Q,P);   //�Ȳ���һ��ĺ��ӽ��
		if (parent != NULL)
			return parent;
		Q = Q->nextSibling; //���ӽ��û�ҵ������ֵܽ��
	}

	if (Q != NULL && Q == P)
		return T;
	return NULL;
}

int main() {
	Tree T,root,Tp,Ts,Tc;
	char key;
	printf("�밴ǰ�����������(��:'ABDH##I##EJ###CF##G##')\n");
	CreateTree(&T);

	printf("\nǰ�����������T:");
	PreOrderTraverse_lt(T);

	Tc = FirstChild(T);
	printf("\n������T���ӽ��: %c", Tc->data);

	Ts = NextSibling(Tc);
	printf("\n������T���ֵܽ��: %c", Ts->data);

	Tp = Parent(T,Tc);
	printf("\n������B�ĸ��ڵ�: %c", Tp->data);

	root = Root(T);
	printf("\n������B�ĸ��ڵ�: %c", root->data);

	key = 'B';
	root = Sreach(T, key);
	printf("\n������%c�ĸ��ڵ�: %c",key, root->data);

	return 0;
}