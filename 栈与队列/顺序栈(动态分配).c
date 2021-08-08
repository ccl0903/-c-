#include "stdio.h"    
#include "stdlib.h"   

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;		 // Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int SElemType;   //数据类型

//sqd 代表动态顺序表
Status visit_sqd(SElemType c)
{
	printf("%d ", c);
	return OK;
}

typedef struct {
	SElemType* base; // 栈底指针 在栈构造之前和销毁之后，base的值为NULL
	SElemType* top;	//	栈顶指针  指向栈底元素的后一个地址
	int stacksize;	// 当前已分配的存储空间，以元素为单位
}SqdStack;

//动态初始化
Status InitStack_sqd(SqdStack *s) {
	// 构造一个空栈s，该栈预定义大小为MAXSIZE
	s->base = (SElemType*)malloc(MAXSIZE*sizeof(SElemType)); 
	s->top = s->base;
	s->stacksize = MAXSIZE;
	return OK;
}

//栈是否为空
Status StackIsEmpty_sqd(SqdStack s) {
	//若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR 
	if (s.base == s.top)
		return TRUE;
	else
		return FALSE;
}

//返回栈的长度
int StackLength_sqd(SqdStack s) {
	return s.top - s.base;   //栈顶指针与栈底指针的差值为栈的元素个数
}

//清空顺序栈（只清空数据保留栈）
Status ClearStack_sqd(SqdStack *s) {
	/*if (s.base)
		return s.top = s.base;*/
	if (s->base)
		return s->top = s->base;
	return OK;
}

//销毁顺序栈
Status DestroryStack_sqd(SqdStack *s) {
	if (s->base) {
		free(s->base);
		s->stacksize = 0;
		s->base = NULL;   //free只是将该地址的内存资源释放，指针置为null为防止野指针生成
		s->top = NULL;
	}
	return OK;
}

//压栈 插入元素e为新的栈顶元素
Status Push_sqd(SqdStack *s,SElemType e) {
	if (s->top - s->base == s->stacksize)   //栈满（上溢）
		return ERROR;
	//*s->top++ = e;
	*s->top = e;
	s->top++;
	return OK;
}

//出栈 出栈  若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status Pop_sqd(SqdStack *s,SElemType *e) {
	if (s->base == s->top)  //栈空
		return ERROR;
	//*e = *(--s->top);
	s->top--;
	*e = *(s->top);
	return OK;
}

Status GetTop_sqd(SqdStack s,SElemType *e) {
	if (s.base == s.top)   //空栈，无元素可获取，报错
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
	printf("栈s是否空：i=%d(1:是 0:否)\n", isEmpty);

	if (i == OK)
	{
		for (j = 1; j <= 10; j++)
			Push_sqd(&s, j);
	}
	printf("压栈后的栈s：");
	StackTraverse_sqd(s);

	 GetTop_sqd(s,&e);
	printf("栈顶元素为 ： %d\n", e);

	Pop_sqd(&s,&e1);
	printf("%d\n", e1);
	StackTraverse_sqd(s);

	isEmpty = StackIsEmpty_sqd(s);
	printf("栈s是否空：i=%d(1:是 0:否)\n", isEmpty);
	/*GetTop_sqd(s,&e);
	printf("%d\n",e);*/

	len = StackLength_sqd(s);
	printf("栈的长度为 %d\n", len);

	//if (i == OK)
	//{
	//	for (j = 1; j <= 10; j++)
	//		Pop_sqd(&s,&e);
	//}
	//printf("弹栈后的栈s：");
	//StackTraverse_sqd(s);

	ClearStack_sqd(&s);
	//DestroryStack_sqd(&s);

	isEmpty = StackIsEmpty_sqd(s);
	printf("栈s是否空：i=%d(1:是 0:否)\n", isEmpty);

}

