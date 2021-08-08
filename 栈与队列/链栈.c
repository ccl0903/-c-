#include "stdio.h"    
#include "stdlib.h"   

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;		 // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
typedef int SElemType;   //��������

//��ջ�洢�ṹ
typedef struct StackNode {
	SElemType data;
	struct SatckNode* next;
}StackNode,*pLinkStack;

typedef struct {
	pLinkStack top;         //ջ��ָ��
	int count;				//ջԪ�ؼ�����
}LinkStack;


//visit_ls���ڴ�ӡ��ʾ ls ������ջ��
Status visit_ls(SElemType c)
{
	printf("%d ", c);
	return OK;
}

//��ջ��ʼ��
Status InitStack_ls(LinkStack *s) {
	s->top = (pLinkStack)malloc(sizeof(StackNode));
	if (!s->top)
		return ERROR; //����ʧ��
	s->top = NULL;	  //�����ͷ����Ϊջ�������ģ����û�б�Ҫ����ͷ���
	s->count = 0;
	return OK;
}

//���ջ�� ��S��Ϊ��ջ
Status ClearStack_ls(LinkStack *s) {
	pLinkStack p,q;
	p = s->top;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
	s->count = 0;
	s->top = NULL; //��ֹ����Ұָ��
	return OK;
}

// ��ջSΪ��ջ���򷵻�TRUE�����򷵻�FALSE
Status StackIsEmpty_ls(LinkStack s) {
	if (s.top == NULL)
		return TRUE;
	else
		return ERROR;
}

// ����ջ�ĳ���
int StackLength_ls(LinkStack s) {
	return s.count;
}

//ѹջ
Status Push_ls(LinkStack *s,SElemType e) {
	//����ѹջ����Ҫ�ж���ջ��ֻҪ�пռ��ڴ�Ϳ�����ջ
	pLinkStack p;
	p = (pLinkStack)malloc(sizeof(StackNode));
	p->data = e;
	p->next = s->top;  //���½�����ջ��
	s->top = p;        //��ջ��ָ��ָ���½��
	s->count++;		   //ջ��������1
	return OK;
}

//��ջ
Status Pop_ls(LinkStack *s,SElemType *e) {
	pLinkStack p;
	if (s->count == 0)
		return ERROR;
	p = s->top;			//p��ż���Ҫɾ����ջ��Ԫ��
	*e = p->data;
	s->top = p->next;    
	free(p);
	s->count--;
	return OK;
}

//��ȡջ��Ԫ��
Status GetTop_ls(LinkStack s,SElemType *e) {
	if (s.top == NULL)
		return ERROR;
	else
		*e = s.top->data;
	return OK;
}

//����ջԪ��
Status StackTraverse_ls(LinkStack s) {
	pLinkStack p;
	p = s.top;
	while (p) {
		visit_ls(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

int main_ls() {
	int j, isEmpty, len;
	SElemType e;
	Status i;
	LinkStack s;

	i  = InitStack_ls(&s);

	isEmpty = StackIsEmpty_ls(s);
	printf("ջ�շ�%d(1:�� 0:��)\n", isEmpty);

	if (i == OK)
	{
		for (j = 1; j <= 10; j++) {
			Push_ls(&s,j);
		}
	}
	printf("ջ��Ԫ������Ϊ��");
	StackTraverse_ls(s);

	isEmpty = StackIsEmpty_ls(s);
	printf("ջ�շ�%d(1:�� 0:��)\n", isEmpty);

	len = StackLength_ls(s);
	GetTop_ls(s,&e);
	printf("ջ��Ԫ�� e = %d ջ�ĳ���Ϊ%d\n", e, len);
	
	Pop_ls(&s,&e);
	len = StackLength_ls(s);
	printf("������ջ��Ԫ�� e=%d  ջ�ĳ���Ϊ%d\n", e,len);
	printf("��ջ��ջ��Ԫ������Ϊ��");
	StackTraverse_ls(s);

	ClearStack_ls(&s);
	printf("���ջ��\n");

	isEmpty = StackIsEmpty_ls(s);
	printf("ջ�շ�%d(1:�� 0:��)\n", isEmpty);

	return 0;
}