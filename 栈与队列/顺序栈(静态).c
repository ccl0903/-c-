#include "stdio.h"    
#include "stdlib.h"   

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;
typedef int SElemType;   //��������

//��̬˳��ջ�ṹ      ����������з��䣬��baseָ�룬ֻ���õ�topָ ��
typedef struct {
	SElemType data[MAXSIZE];
	int top;  //ջ��ָ��
	//int base;	//ջ��ָ��,��Ϊ��˳���baseָ����ԶΪ0����ʡ��
}SqStack;

Status visit_Ssq(SElemType c)
{
	printf("%d ", c);
	return OK;
}

//ջ��ʼ��
Status InitStack(SqStack *S) {
	//S->data = (SElemType*)malloc(MAXSIZE * sizeof(SElemType));
	S->top = -1;
	return OK;
}

//���ջԪ��
Status ClearStack(SqStack *S) {
	S->top = -1;   /* ˳��ջ�ٶ�top=-1ʱΪ��ջ��ÿ����һ��Ԫ��top+1������һ��Ԫ���ǣ�topΪ0...*/
	return OK;
}

//�ж�ջ�Ƿ�Ϊ��
Status StackISEmpty(SqStack S) {
	if (S.top == -1)
		return TRUE;
	else
		return FALSE;
}

//����ջ����(Ԫ�ظ���)
int StackLength(SqStack S) {
	return S.top + 1;       
}

//��ȡջ��Ԫ��,��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR 
Status GetTop(SqStack S,SElemType *e) {
	if (S.top == -1)
		return ERROR;
	else
		*e = S.data[S.top];
	return OK;
}

//ѹջ ����Ԫ��eΪ�µ�ջ��Ԫ��
Status Push_sq(SqStack *S,SElemType e) {
	//���ж�ջ�Ƿ�ջ�����ڽ�topָ������һλ���������Ԫ��e�����ջ��
	if (S->top == MAXSIZE - 1)  //ջ��
		return ERROR;  
	S->top++;
	S->data[S->top] = e;
	return OK;
}

//��ջ  ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR 
Status Pop_sq(SqStack *S,SElemType *e) {
	if (S->top == -1)   //���ж��Ƿ�Ϊ��ջ
		return ERROR;
	*e = S->data[S->top];   //��Ҫɾ����ջ��Ԫ�ظ�ֵ��e
	S->top--;              //topָ������
	return OK;
}

/*	����ջԪ��  ��ջ�׵�ջ�����ζ�ջ��ÿ��Ԫ����ʾ
	���ھ�̬˳���������鷽ʽ���еײ�洢����Ϊֻ��Ҫ���������������*/
Status StackTraverse_sq(SqStack S) {
	int i;
	i = 0;
	while (S.top > -1)    //topָ���λ����ʵ��������±���һһ��Ӧ
	{
		visit_Ssq(S.data[S.top--]);
	}
	printf("\n");
	return OK;
}

int main_sq() {
	int j,e,len, isEmpty;
	Status i;
	SqStack s;
	i = InitStack(&s);
	if (i == OK)
	{
		for (j = 1; j <= 10; j++)
			Push_sq(&s,j);
	}
	printf("ѹջ���ջs��");
	StackTraverse_sq(s);

	GetTop(s,&e);
	printf("��ʱs��ջ��Ԫ��Ϊ %d\n", e);

	Pop_sq(&s,&e);
	printf("������ջ��Ԫ�� e = %d\n", e);
	printf("��ջ���ջs��");
	StackTraverse_sq(s);

	len  = StackLength(s);
	printf("ջs��Ԫ�ظ��� %d\n",len);

	isEmpty = StackISEmpty(s);
	printf("ջs�Ƿ�գ�i=%d(1:�� 0:��)\n", isEmpty);

	ClearStack(&s);
	printf("ջ���");

	isEmpty = StackISEmpty(s);
	printf("ջs�Ƿ�գ�i=%d(1:�� 0:��)\n", isEmpty);

}