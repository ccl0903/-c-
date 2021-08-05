#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

//双向链表
typedef struct DulNode
{
	ElemType data;
	struct DulNode* prior;    	/*直接前驱指针*/
	struct DulNode* next;		/*直接后继指针*/
} DulNode, * DuLinkList;

//打印
Status visit_D(ElemType c)
{
	printf("%d<->", c);
	return OK;
}

//双链表的初始化
Status InitList_D(DuLinkList *L) {
	*L = (DuLinkList)malloc(sizeof(DulNode));
	if (!(*L))
		return ERROR;
	(*L)->next = NULL;
	(*L)->prior = NULL;
	return OK;
}

//双链表是否为空表为空,若L为空表，则返回TRUE，否则返回FALSE 
Status ListIsEmpty_D(DuLinkList L) {
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

//返回双链表的元素个数
int ListLength_D(DuLinkList L) {
	int n = 0;
	DuLinkList p = L->next;		//p指向第一个结点
	while (p) {		
		n++;
		p = p->next;
	}
	return n;    //返回元素个数
}

//遍历链表返回数据
Status ListTraverse_D(DuLinkList L)
{
	DuLinkList p = L->next;
	while (p)
	{
		visit_D(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

//用e返回L中第i个数据元素的值 
Status GetElem_D(DuLinkList L,int key,ElemType *e) {
	int j;
	DuLinkList p;
	p = L->next;
	j = 1;
	while (p && j < key)//找到第key - 1个元素的结点位置停止
	{
		p = p->next;
		j++;
	}
	if (!p || j > key)
		return ERROR;
	*e = p->data;
	return OK;
}

//返回L中第1个与e满足关系的数据元素的位序。
int LocateElem_D(DuLinkList L,ElemType e) {
	int i = 0;
	DuLinkList p = L->next;  //p指向首元结点
	while (p)
	{
		i++;
		if (p->data == e)
			return i;
		p = p->next;
	}
	return 0;
}

//双链表的定点插入
Status ListInsert_D(DuLinkList* L, int i,ElemType e) {
	int j;
	DuLinkList p,s;
	p = *L;
	j = 1;
	while (p &&j < i)
	{
		p = p->next;    
		j++;
	}
	//此时p在第i-1个结点
	if (!p || j > i)
		return ERROR; //第i个元素不存在
	s = (DuLinkList)malloc(sizeof(DulNode));
	s->data = e;
	//s->prior = p->prior;
	//p->prior->next = s;
	//s->next = p;
	//p->prior = s;
	/*头插法和插入法都有先后顺序 以下4步有先后顺序，如果改变顺序造成输出结果正确，但内存的地址顺序是错误，非常要小心*/
	s->prior = p;
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	return OK;
}
 
//头插法
void InsertListHead_D(DuLinkList* L, int n) {
	DuLinkList p,s;
	p = *L;
	s = (DuLinkList)malloc(sizeof(DulNode));   
	s->data = n;   //赋值
	/*头插法和插入法都有先后顺序 以下4步有先后顺序，如果改变顺序造成输出结果正确，但内存的地址顺序是错误，非常要小心*/
	s->prior = p;         
	s->next = p->next;
	if (p->next != NULL)
		p->next->prior = s;
	p->next = s;
	return OK;
}

//尾插法
void InsertListTail_D(DuLinkList *L,int n) {
	DuLinkList p,s;
	p = *L;
	while (p->next != NULL)  
	{
		p = p->next;		//p指向尾结点
	}
	s = (DuLinkList)malloc(sizeof(DulNode));    //创建新结点，并将新结点s插入双链表中
	s->data = n;
	/* 尾插法不用区分先后顺序 */
	s->prior = p;
	p->next = s;
	p = s;
	p->next = NULL;
}

//双链表的删除,删除第i个元素
Status ListDetele_D(DuLinkList *L,int i,ElemType *e) {
	int j;
	DuLinkList p;
	p = *L;
	j = 1;
	while (p->next && j <= i )
	{
		p = p->next;
		j++;
	}
	if (!(p->next) || j > i+1)
		return ERROR;
	*e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

//双链表的清空/销毁
Status ListClear_D(DuLinkList *L) {
	DuLinkList p, q;
	p = (*L)->next;
	if (!p)
		return;
	while (p->next != NULL) {
		q = p->next;
		p->prior->next = p->next;
		p->next->prior = p->prior;
		free(p);
		p = q;
	}
	(*L)->next = NULL;		//头结点指针域设置为空
	return OK;
}


int main_D() {
	DuLinkList L;
	ElemType e;
	Status i;
	int j, k, index, isEmpty,len;
	i = InitList_D(&L);

	isEmpty = ListIsEmpty_D(L);
	printf("L是否空：i=%d(1:是 0:否)\n", isEmpty);

	//for (k = 1; k <= 5; k++)
	//{
	//	InsertListHead_D(&L,k);
	//}
	//printf("使用头插法进行插入后的双链表：");

	//ListTraverse_D(L);

	for (k = 1; k <= 5; k++)
	{
		InsertListTail_D(&L, k);
	}

	printf("使用尾插法进行插入后的双链表：");
	ListTraverse_D(L);

	ListInsert_D(&L, 3, 0);
	printf("使用定点法进行插入后的双链表：");
	ListTraverse_D(L);

	//len = ListLength_D(L);
	//printf("表长为 %d\n", len);

	//GetElem_D(L, 4, &e);
	//printf("值 为 %d\n", e);

	//j = 4;
	//index = LocateElem_D(L,j);
	//printf("数字%d在第%d个位置。\n",j , index);

	//j = 3;
	//ListDetele_D(&L,j,&e);
	//printf("删除第%d个元素 %d\n",j,e);
	//printf("删除第%d个元素后的双链表：",j);
	//ListTraverse_D(L);

	ListClear_D(&L);
	isEmpty = ListIsEmpty_D(L);
	printf("L是否空：i=%d(1:是 0:否)\n", isEmpty);

	return 0;
}