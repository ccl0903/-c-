#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 100   //��ʼ����
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

//������洢�ṹ
typedef struct Node {
	ElemType data;		 //�������ݽ����
	struct Node* next;   //����ָ�������ڴ�ź�̽ڵ�
}Node, * LinkList;

//������ĳ�ʼ��
Status InitList_L(LinkList* L) {
	*L = (LinkList)malloc(sizeof(Node));		//����ͷ��㣬ʹLָ��ͷ���
	if (!(*L))
		return ERROR;
	(*L)->next = NULL;		//ͷ���ָ����Ϊ��
	return OK;
}

//��Ϊ����LΪ�ձ��򷵻�TRUE�����򷵻�FALSE 
Status ListIsEmpty_L(LinkList L) {
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

//����L������Ԫ�ظ���
int ListLength_L(LinkList L) {
	int n = 0;
	LinkList p = L->next;//pָ���һ�����
	while (p)			//pδ����β
	{
		n++;
		p = p->next;
	}
	return n;      //����Ԫ�ظ���
}

/* ��ʼ��������ʽ���Ա�L�Ѵ��ڣ�1��i��ListLength_L(L) */
/* �����������e����L�е�i������Ԫ�ص�ֵ */
Status GetElem_L(LinkList L, int i, ElemType* e) {
	int j;
	LinkList p;			//����һ�����
	p = L->next;		//��pָ���������һ���
	j = 1;				//������
	while (p && j < i) {//�ҵ���i��Ԫ�صĽ��λ��
		p = p->next;	//pָ���i��Ԫ��
		j++;
	}
	if (!p || j > i)
		return ERROR;	// ��i��Ԫ�ز�����
	*e = p->data;		//��ȡ��i��Ԫ��
	return OK;
}

//����L�е�1����e�����ϵ������Ԫ�ص�λ��
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

//�������ɾ��
Status ListDetele_L(LinkList *L,int i,ElemType *e) {
	int j;
	LinkList  p,q;				//p�ǵ�ǰԪ�ص�ָ�룬q���ڴ�ű�ɾ��Ԫ�ص�ָ��
	p = *L;
	j = 1;
 	while (p->next && j < i)	//����Ѱ�ҵ�i�����
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i)   //��i�����Ԫ�ز�����
		return ERROR;	
	q = p->next;
	p->next = q->next;			
	*e = q->data;				//�õ�q����Ԫ�ص�Ԫ��
	free(q);					//�ͷŸÿռ�
	return OK;
}

//������Ĳ���Ԫ�أ������ȼ�1
Status ListInsert_L(LinkList* L, int i, ElemType e) {
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p && j < i) {//ѡ���i�����
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;	
	q = (LinkList)malloc(sizeof(Node)); //�����µĽ��
	q->data = e;
	q->next = p->next;
	p->next = q;
	return OK;
}

//���ζ�L��ÿ������Ԫ�����(��������)
Status ListTraverse_L(LinkList L) {
	LinkList p = L->next;   //ָ���һ�����
	while (p)
	{
		visit_L(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

//(ͷ�巨�� �������ͷ�����뵥��Ԫ��  
void ListInsertHead_L(LinkList* L, int n) {
	LinkList p;	  			
	p = (LinkList)malloc(sizeof(Node)); //�����½��
	p->data = n;			//���½�㸳ֵ
	p->next = (*L)->next;
	(*L)->next = p;				//�����ͷ
}

//���������������ͷ�巨��
//void CreateListHead_L_ALL(LinkList* L, int n) {
//	LinkList p;				
//	int i;
//	srand(time(0));
//	*L = (LinkList)malloc(sizeof(Node));
//	(*L)->next = NULL;       //����һ����ͷ���ĵ�����
//	for (i = 0; i < n; i++) {
//		p = (LinkList)malloc(sizeof(Node)); //�����½��
//		p->data = rand() % 100 + 1;  //�������100���ڵ���
//		p->next = (*L)->next;
//		(*L)->next = p;				//�����ͷ
//	}
//}

//��β�巨������  �������β�����뵥��Ԫ��
void ListInsertTail_L(LinkList* L, int n) {
	LinkList p, r;    //pΪ��ǰָ�룬rΪβ��ָ��
	//*L = (LinkList)malloc(sizeof(Node));     //��������г�ʼ������βָ��ָ������
	//�������ҵ�βָ��
	r = *L;
	while (!(r->next == NULL))
	{
		r = r->next;
	}
	p = (LinkList)malloc(sizeof(Node));     //�����½��
	p->data = n;							//���½�㸳ֵ
	r->next = p;							//p��β�����뵥������
	r = p;									//r����ָ��β�����
	r->next = NULL;							//�������
}

//���������������β�巨��
//void CreateListTail_L_ALL(LinkList* L, int n) {
//	LinkList p, r;
//	int i;
//	srand(time(0));    
//	*L = (LinkList)malloc(sizeof(Node));
//	r = *L;					//*rָ��β�����
//	for (i = 0; i < n;i++) {
//		p = (LinkList)malloc(sizeof(Node));
//		p->data = rand() % 100 + 1; //�������100���ڵ���
//		r->next = p;				//p��β�����뵥������
//		r = p;						//r����ָ��β�����
//	}
//	r->next = NULL;					//�������
//}

//����������
Status ListClear_L(LinkList *L) {
	LinkList p, q;	
	p = (*L)->next;			//pָ���һ�����
	while (p)				//һֱɾ������β����
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;		//ͷ���ָ��������Ϊ��
	return OK;
}

//���Ա�ĺϲ�(��ȥ��Ч��)
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

//�����ĺϲ�(�������)
void MerygeList_L(LinkList La,LinkList Lb) {
	LinkList pa, pb,pc;
	pa = La->next;
	pb = Lb->next;
	pc = La;		//ʹ��La��ͷ�����Ϊpc��ͷ���,pcΪһ����������
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
	pc->next = pa ? pa : pb;   //����Ƚϳ��ı��ʣ���
	free(Lb);    //�ͷ�Lb��ͷ���
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
	
	printf("��ʼ��L��ListLength(L)=%d\n", ListLength_L(L));

	//��������
	for (j = 1; j <= 5; j++)
	{
		i = ListInsert_L(&L, i, j);
	}
	
	printf("��L�ı�ͷ���β���1��5��L.data=");
	ListTraverse_L(L);

	printf("��L�ı�ͷ���β���1��5��ListLength(L)=%d \n", ListLength(L));

	isEmpty = ListIsEmpty_L(L);
	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n", isEmpty);

	GetElem_L(L, 3, &e);
	printf("��3��Ԫ�ص�ֵΪ��%d\n", e);

	for (j = 6; j >= 1; j--) {
		index = LocateElem_L(L, j);
		if(index != 0)
			printf("��ֵ%d�ڵ�����ĵ�%d�����\n",j, index);
		else
			printf("��ֵ%d���ڵ�����\n", j);
	}

	//ɾ����1��Ԫ��
	ListDetele_L(&L,1,&e);
	printf("��ɾ��Ԫ��%d\n", e);
	ListTraverse_L(L);

	//�������
	ListClear_L(&L);
	ListTraverse_L(L);

	isEmpty = ListIsEmpty_L(L);
	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n", isEmpty);

	//����ͷ�巨
	for (k = 1; k <= 5; k++) {
		ListInsertHead_L(&L, k);
	}
	printf("L��Ԫ��(ͷ�巨)��");
	ListTraverse_L(L);

	//����β�巨
	for (k = 1; k <= 5; k++) {
		ListInsertTail_L(&L,k);
	}
	printf("L��Ԫ��(β�巨)��");
	ListTraverse_L(L);

	ListInsert_L(&L,6,0);
	printf("L��Ԫ��(������뷨)��");
	ListTraverse_L(L);
	
	//�������Ա�ϲ�
	for (j = 1; j <= 5; j++)
	{
		ListInsert_L(&La, ia, j);
	}
	printf("��La�ı�ͷ���β���1��5��La.data=");
	ListTraverse_L(La);

	for (j = 3; j <= 8; j++)
	{
		ListInsert_L(&Lb, ib, j);
	}
	printf("��Lb�ı�ͷ���β���3��8��Lb.data=");
	ListTraverse_L(Lb);

	ListUnion_L(&La, &Lb);
	printf("�ںϲ�La��Lb�ı�La��La.data=");
	ListTraverse_L(La);

	int len = ListLength_L(La);
	printf("�ںϲ�La��Lb�ı�La�ĳ��ȣ�%d\n", len);

	ListClear_L(&La);
	ListClear_L(&Lb);
	
	for (j = 1; j <= 5;j = j+2)
	{
		ListInsertTail_L(&La,j);
	}
	printf("La�ı�La.data=");
	ListTraverse_L(La);

	for (j = 2; j <= 8;j = j+2)
	{
		ListInsertTail_L(&Lb, j);
	}
	printf("Lb�ı�Lb.data=");
	ListTraverse_L(Lb);

	MerygeList_L(La,Lb);
	printf("�ϲ���La�ı�La.data=");
	ListTraverse_L(La);

	return 0;
}
