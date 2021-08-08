#include "stdio.h"    
#include "stdlib.h"   

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;		 // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
typedef int SElemType;   //��������

//sqd ����̬˳���
Status visit_sqd(SElemType c)
{
	printf("%d ", c);
	return OK;
}

typedef struct {
	SElemType* base; // ջ��ָ�� ��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType* top;	//	ջ��ָ��  ָ��ջ��Ԫ�صĺ�һ����ַ
	int stacksize;	// ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqdStack;

//��̬��ʼ��
Status InitStack_sqd(SqdStack *s) {
	// ����һ����ջs����ջԤ�����СΪMAXSIZE
	s->base = (SElemType*)malloc(MAXSIZE*sizeof(SElemType)); 
	s->top = s->base;
	s->stacksize = MAXSIZE;
	return OK;
}

//ջ�Ƿ�Ϊ��
Status StackIsEmpty_sqd(SqdStack s) {
	//��ջ���գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR 
	if (s.base == s.top)
		return TRUE;
	else
		return FALSE;
}

//����ջ�ĳ���
int StackLength_sqd(SqdStack s) {
	return s.top - s.base;   //ջ��ָ����ջ��ָ��Ĳ�ֵΪջ��Ԫ�ظ���
}

//���˳��ջ��ֻ������ݱ���ջ��
Status ClearStack_sqd(SqdStack *s) {
	/*if (s.base)
		return s.top = s.base;*/
	if (s->base)
		return s->top = s->base;
	return OK;
}

//����˳��ջ
Status DestroryStack_sqd(SqdStack *s) {
	if (s->base) {
		free(s->base);
		s->stacksize = 0;
		s->base = NULL;   //freeֻ�ǽ��õ�ַ���ڴ���Դ�ͷţ�ָ����ΪnullΪ��ֹҰָ������
		s->top = NULL;
	}
	return OK;
}

//ѹջ ����Ԫ��eΪ�µ�ջ��Ԫ��
Status Push_sqd(SqdStack *s,SElemType e) {
	if (s->top - s->base == s->stacksize)   //ջ�������磩
		return ERROR;
	//*s->top++ = e;
	*s->top = e;
	s->top++;
	return OK;
}

//��ջ ��ջ  ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
Status Pop_sqd(SqdStack *s,SElemType *e) {
	if (s->base == s->top)  //ջ��
		return ERROR;
	//*e = *(--s->top);
	s->top--;
	*e = *(s->top);
	return OK;
}

Status GetTop_sqd(SqdStack s,SElemType *e) {
	if (s.base == s.top)   //��ջ����Ԫ�ؿɻ�ȡ������
		return ERROR;
	*e = *(s.top-1);
	return OK;
}

//int GetTop_sqd(SqdStack s) {
//	if (s.base == s.top)
//		return ERROR;
//	return *(s.top - 1);
//}

Status StackTraverse_sqd(SqdStack s) {
	SElemType* p = (SElemType*)malloc(sizeof(SElemType));
	SElemType* q = (SElemType*)malloc(sizeof(SElemType));
	p = s.top;
	q = s.base;
	if (p == q)
		return ERROR;
	else
	{
		p--;
		while (p>=q)
		{
			visit_sqd(*p);
			p--;
		}
		printf("\n");
	}
	return OK;
}

int main_sqd() {
	int j, e, len, isEmpty;
	SElemType  e1;
	Status i;
	SqdStack s;
	i = InitStack_sqd(&s);

	isEmpty = StackIsEmpty_sqd(s);
	printf("ջs�Ƿ�գ�i=%d(1:�� 0:��)\n", isEmpty);

	if (i == OK)
	{
		for (j = 1; j <= 10; j++)
			Push_sqd(&s, j);
	}
	printf("ѹջ���ջs��");
	StackTraverse_sqd(s);

	 GetTop_sqd(s,&e);
	printf("ջ��Ԫ��Ϊ �� %d\n", e);

	Pop_sqd(&s,&e1);
	printf("%d\n", e1);
	StackTraverse_sqd(s);

	isEmpty = StackIsEmpty_sqd(s);
	printf("ջs�Ƿ�գ�i=%d(1:�� 0:��)\n", isEmpty);
	/*GetTop_sqd(s,&e);
	printf("%d\n",e);*/

	len = StackLength_sqd(s);
	printf("ջ�ĳ���Ϊ %d\n", len);

	//if (i == OK)
	//{
	//	for (j = 1; j <= 10; j++)
	//		Pop_sqd(&s,&e);
	//}
	//printf("��ջ���ջs��");
	//StackTraverse_sqd(s);

	ClearStack_sqd(&s);
	//DestroryStack_sqd(&s);

	isEmpty = StackIsEmpty_sqd(s);
	printf("ջs�Ƿ�գ�i=%d(1:�� 0:��)\n", isEmpty);

}

