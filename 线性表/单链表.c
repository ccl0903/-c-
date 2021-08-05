#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 100   //初始容量
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

Status visit_L(ElemType c)
{
	printf("%d->", c);
	return OK;
}

//单链表存储结构
typedef struct Node {
	ElemType data;		 //结点的数据结点域
	struct Node* next;   //结点的指针域用于存放后继节点
}Node, * LinkList;

//单链表的初始化
Status InitList_L(LinkList* L) {
	*L = (LinkList)malloc(sizeof(Node));		//生成头结点，使L指向头结点
	if (!(*L))
		return ERROR;
	(*L)->next = NULL;		//头结点指针域为空
	return OK;
}

//表为空若L为空表，则返回TRUE，否则返回FALSE 
Status ListIsEmpty_L(LinkList L) {
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

//返回L中数据元素个数
int ListLength_L(LinkList L) {
	int n = 0;
	LinkList p = L->next;//p指向第一个结点
	while (p)			//p未到表尾
	{
		n++;
		p = p->next;
	}
	return n;      //返回元素个数
}

/* 初始条件：链式线性表L已存在，1≤i≤ListLength_L(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
Status GetElem_L(LinkList L, int i, ElemType* e) {
	int j;
	LinkList p;			//声明一个结点
	p = L->next;		//让p指向链表的下一结点
	j = 1;				//计数器
	while (p && j < i) {//找到第i个元素的结点位置
		p = p->next;	//p指向第i个元素
		j++;
	}
	if (!p || j > i)
		return ERROR;	// 第i个元素不存在
	*e = p->data;		//获取第i个元素
	return OK;
}

//返回L中第1个与e满足关系的数据元素的位序。
int LocateElem_L(LinkList L, ElemType e) {
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		if (p->data == e)
			return i;
		p = p->next;
	}
	return 0;
}

//单链表的删除
Status ListDetele_L(LinkList *L,int i,ElemType *e) {
	int j;
	LinkList  p,q;				//p是当前元素的指针，q用于存放被删除元素的指针
	p = *L;
	j = 1;
 	while (p->next && j < i)	//遍历寻找第i个结点
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i)   //第i个结点元素不存在
		return ERROR;	
	q = p->next;
	p->next = q->next;			
	*e = q->data;				//得到q结点的元素的元素
	free(q);					//释放该空间
	return OK;
}

//单链表的插入元素，链表长度加1
Status ListInsert_L(LinkList* L, int i, ElemType e) {
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p && j < i) {//选择第i个结点
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;	
	q = (LinkList)malloc(sizeof(Node)); //生成新的结点
	q->data = e;
	q->next = p->next;
	p->next = q;
	return OK;
}

//依次对L的每个数据元素输出(遍历链表)
Status ListTraverse_L(LinkList L) {
	LinkList p = L->next;   //指向第一个结点
	while (p)
	{
		visit_L(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

//(头插法） 从链表的头部插入单个元素  
void ListInsertHead_L(LinkList* L, int n) {
	LinkList p;	  			
	p = (LinkList)malloc(sizeof(Node)); //生成新结点
	p->data = n;			//给新结点赋值
	p->next = (*L)->next;
	(*L)->next = p;				//插入表头
}

//单链表的整表创建（头插法）
//void CreateListHead_L_ALL(LinkList* L, int n) {
//	LinkList p;				
//	int i;
//	srand(time(0));
//	*L = (LinkList)malloc(sizeof(Node));
//	(*L)->next = NULL;       //建立一个带头结点的单链表
//	for (i = 0; i < n; i++) {
//		p = (LinkList)malloc(sizeof(Node)); //生成新结点
//		p->data = rand() % 100 + 1;  //随机生成100以内的数
//		p->next = (*L)->next;
//		(*L)->next = p;				//插入表头
//	}
//}

//（尾插法）常用  从链表的尾部插入单个元素
void ListInsertTail_L(LinkList* L, int n) {
	LinkList p, r;    //p为当前指针，r为尾部指针
	//*L = (LinkList)malloc(sizeof(Node));     //对链表进行初始化并将尾指针指向链表
	//必须先找到尾指针
	r = *L;
	while (!(r->next == NULL))
	{
		r = r->next;
	}
	p = (LinkList)malloc(sizeof(Node));     //创建新结点
	p->data = n;							//给新结点赋值
	r->next = p;							//p从尾部插入单链表中
	r = p;									//r重新指向尾部结点
	r->next = NULL;							//链表结束
}

//单链表的整表创建（尾插法）
//void CreateListTail_L_ALL(LinkList* L, int n) {
//	LinkList p, r;
//	int i;
//	srand(time(0));    
//	*L = (LinkList)malloc(sizeof(Node));
//	r = *L;					//*r指向尾部结点
//	for (i = 0; i < n;i++) {
//		p = (LinkList)malloc(sizeof(Node));
//		p->data = rand() % 100 + 1; //随机生成100以内的数
//		r->next = p;				//p从尾部插入单链表中
//		r = p;						//r重新指向尾部结点
//	}
//	r->next = NULL;					//链表结束
//}

//单链表的清空
Status ListClear_L(LinkList *L) {
	LinkList p, q;	
	p = (*L)->next;			//p指向第一个结点
	while (p)				//一直删除到表尾结束
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;		//头结点指针域设置为空
	return OK;
}

//线性表的合并(有去重效果)
void ListUnion_L(LinkList *La,LinkList *Lb) {
	LinkList la, lb;
	int len_La, len_Lb,i;
	ElemType e;
	la = (*La);
	lb = (*Lb);
	len_La = ListLength_L(la);
	len_Lb = ListLength_L(lb);
	for (i = 1; i <= len_Lb; i++) {
		GetElem_L(lb,i,&e);
		if (!LocateElem_L(la, e))
			ListInsertTail_L(&la,e);
	}
}

//有序表的合并(排序插入)
void MerygeList_L(LinkList La,LinkList Lb) {
	LinkList pa, pb,pc;
	pa = La->next;
	pb = Lb->next;
	pc = La;		//使用La的头结点作为pc的头结点,pc为一个辅助链表
	while (pa && pb) {
		if (pa->data < pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;   //插入比较长的表的剩余端
	free(Lb);    //释放Lb的头结点
}

int main() {

	LinkList L,La,Lb,Lc;
	ElemType e;
	Status i,ia,ib,ic;
	int j, k,index, isEmpty;
	i = InitList_L(&L);
	ia = InitList_L(&La);
	ib = InitList_L(&Lb);
	ic = InitList_L(&Lc);
	
	printf("初始化L后：ListLength(L)=%d\n", ListLength_L(L));

	//插入数据
	for (j = 1; j <= 5; j++)
	{
		i = ListInsert_L(&L, i, j);
	}
	
	printf("在L的表头依次插入1～5后：L.data=");
	ListTraverse_L(L);

	printf("在L的表头依次插入1～5后：ListLength(L)=%d \n", ListLength(L));

	isEmpty = ListIsEmpty_L(L);
	printf("L是否空：i=%d(1:是 0:否)\n", isEmpty);

	GetElem_L(L, 3, &e);
	printf("第3个元素的值为：%d\n", e);

	for (j = 6; j >= 1; j--) {
		index = LocateElem_L(L, j);
		if(index != 0)
			printf("数值%d在单链表的第%d个结点\n",j, index);
		else
			printf("数值%d不在单链表\n", j);
	}

	//删除第1个元素
	ListDetele_L(&L,1,&e);
	printf("被删除元素%d\n", e);
	ListTraverse_L(L);

	//清空链表
	ListClear_L(&L);
	ListTraverse_L(L);

	isEmpty = ListIsEmpty_L(L);
	printf("L是否空：i=%d(1:是 0:否)\n", isEmpty);

	//测试头插法
	for (k = 1; k <= 5; k++) {
		ListInsertHead_L(&L, k);
	}
	printf("L的元素(头插法)：");
	ListTraverse_L(L);

	//测试尾插法
	for (k = 1; k <= 5; k++) {
		ListInsertTail_L(&L,k);
	}
	printf("L的元素(尾插法)：");
	ListTraverse_L(L);

	ListInsert_L(&L,6,0);
	printf("L的元素(随机插入法)：");
	ListTraverse_L(L);
	
	//测试线性表合并
	for (j = 1; j <= 5; j++)
	{
		ListInsert_L(&La, ia, j);
	}
	printf("在La的表头依次插入1～5后：La.data=");
	ListTraverse_L(La);

	for (j = 3; j <= 8; j++)
	{
		ListInsert_L(&Lb, ib, j);
	}
	printf("在Lb的表头依次插入3～8后：Lb.data=");
	ListTraverse_L(Lb);

	ListUnion_L(&La, &Lb);
	printf("在合并La，Lb的表La：La.data=");
	ListTraverse_L(La);

	int len = ListLength_L(La);
	printf("在合并La，Lb的表La的长度：%d\n", len);

	ListClear_L(&La);
	ListClear_L(&Lb);
	
	for (j = 1; j <= 5;j = j+2)
	{
		ListInsertTail_L(&La,j);
	}
	printf("La的表：La.data=");
	ListTraverse_L(La);

	for (j = 2; j <= 8;j = j+2)
	{
		ListInsertTail_L(&Lb, j);
	}
	printf("Lb的表：Lb.data=");
	ListTraverse_L(Lb);

	MerygeList_L(La,Lb);
	printf("合并后La的表：La.data=");
	ListTraverse_L(La);

	return 0;
}
