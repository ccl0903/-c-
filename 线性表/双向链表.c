#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;/* ElemType���͸���ʵ������������������Ϊint */

//˫������
typedef struct DulNode
{
	ElemType data;
	struct DulNode* prior;    	/*ֱ��ǰ��ָ��*/
	struct DulNode* next;		/*ֱ�Ӻ��ָ��*/
} DulNode, * DuLinkList;

//��ӡ
Status visit_D(ElemType c)
{
	printf("%d<->", c);
	return OK;
}

//˫����ĳ�ʼ��
Status InitList_D(DuLinkList *L) {
	*L = (DuLinkList)malloc(sizeof(DulNode));
	if (!(*L))
		return ERROR;
	(*L)->next = NULL;
	(*L)->prior = NULL;
	return OK;
}

//˫�����Ƿ�Ϊ�ձ�Ϊ��,��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE 
Status ListIsEmpty_D(DuLinkList L) {
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

//����˫�����Ԫ�ظ���
int ListLength_D(DuLinkList L) {
	int n = 0;
	DuLinkList p = L->next;		//pָ���һ�����
	while (p) {		
		n++;
		p = p->next;
	}
	return n;    //����Ԫ�ظ���
}

//��������������
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

//��e����L�е�i������Ԫ�ص�ֵ 
Status GetElem_D(DuLinkList L,int key,ElemType *e) {
	int j;
	DuLinkList p;
	p = L->next;
	j = 1;
	while (p && j < key)//�ҵ���key - 1��Ԫ�صĽ��λ��ֹͣ
	{
		p = p->next;
		j++;
	}
	if (!p || j > key)
		return ERROR;
	*e = p->data;
	return OK;
}

//����L�е�1����e�����ϵ������Ԫ�ص�λ��
int LocateElem_D(DuLinkList L,ElemType e) {
	int i = 0;
	DuLinkList p = L->next;  //pָ����Ԫ���
	while (p)
	{
		i++;
		if (p->data == e)
			return i;
		p = p->next;
	}
	return 0;
}

//˫����Ķ������
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
	//��ʱp�ڵ�i-1�����
	if (!p || j > i)
		return ERROR; //��i��Ԫ�ز�����
	s = (DuLinkList)malloc(sizeof(DulNode));
	s->data = e;
	//s->prior = p->prior;
	//p->prior->next = s;
	//s->next = p;
	//p->prior = s;
	/*ͷ�巨�Ͳ��뷨�����Ⱥ�˳�� ����4�����Ⱥ�˳������ı�˳�������������ȷ�����ڴ�ĵ�ַ˳���Ǵ��󣬷ǳ�ҪС��*/
	s->prior = p;
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	return OK;
}
 
//ͷ�巨
void InsertListHead_D(DuLinkList* L, int n) {
	DuLinkList p,s;
	p = *L;
	s = (DuLinkList)malloc(sizeof(DulNode));   
	s->data = n;   //��ֵ
	/*ͷ�巨�Ͳ��뷨�����Ⱥ�˳�� ����4�����Ⱥ�˳������ı�˳�������������ȷ�����ڴ�ĵ�ַ˳���Ǵ��󣬷ǳ�ҪС��*/
	s->prior = p;         
	s->next = p->next;
	if (p->next != NULL)
		p->next->prior = s;
	p->next = s;
	return OK;
}

//β�巨
void InsertListTail_D(DuLinkList *L,int n) {
	DuLinkList p,s;
	p = *L;
	while (p->next != NULL)  
	{
		p = p->next;		//pָ��β���
	}
	s = (DuLinkList)malloc(sizeof(DulNode));    //�����½�㣬�����½��s����˫������
	s->data = n;
	/* β�巨���������Ⱥ�˳�� */
	s->prior = p;
	p->next = s;
	p = s;
	p->next = NULL;
}

//˫�����ɾ��,ɾ����i��Ԫ��
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

//˫��������/����
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
	(*L)->next = NULL;		//ͷ���ָ��������Ϊ��
	return OK;
}


int main_D() {
	DuLinkList L;
	ElemType e;
	Status i;
	int j, k, index, isEmpty,len;
	i = InitList_D(&L);

	isEmpty = ListIsEmpty_D(L);
	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n", isEmpty);

	//for (k = 1; k <= 5; k++)
	//{
	//	InsertListHead_D(&L,k);
	//}
	//printf("ʹ��ͷ�巨���в�����˫����");

	//ListTraverse_D(L);

	for (k = 1; k <= 5; k++)
	{
		InsertListTail_D(&L, k);
	}

	printf("ʹ��β�巨���в�����˫����");
	ListTraverse_D(L);

	ListInsert_D(&L, 3, 0);
	printf("ʹ�ö��㷨���в�����˫����");
	ListTraverse_D(L);

	//len = ListLength_D(L);
	//printf("��Ϊ %d\n", len);

	//GetElem_D(L, 4, &e);
	//printf("ֵ Ϊ %d\n", e);

	//j = 4;
	//index = LocateElem_D(L,j);
	//printf("����%d�ڵ�%d��λ�á�\n",j , index);

	//j = 3;
	//ListDetele_D(&L,j,&e);
	//printf("ɾ����%d��Ԫ�� %d\n",j,e);
	//printf("ɾ����%d��Ԫ�غ��˫����",j);
	//ListTraverse_D(L);

	ListClear_D(&L);
	isEmpty = ListIsEmpty_D(L);
	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n", isEmpty);

	return 0;
}