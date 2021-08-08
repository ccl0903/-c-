#include "stdio.h"    
#include "stdlib.h"   

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;
typedef int SElemType;   //数据类型

//静态顺序栈结构      利用数组进行分配，简化base指针，只采用当top指 针
typedef struct {
	SElemType data[MAXSIZE];
	int top;  //栈顶指针
	//int base;	//栈底指针,因为是顺序表，base指针永远为0可以省略
}SqStack;

Status visit_Ssq(SElemType c)
{
	printf("%d ", c);
	return OK;
}

//栈初始化
Status InitStack(SqStack *S) {
	//S->data = (SElemType*)malloc(MAXSIZE * sizeof(SElemType));
	S->top = -1;
	return OK;
}

//清空栈元素
Status ClearStack(SqStack *S) {
	S->top = -1;   /* 顺序栈假定top=-1时为空栈，每增加一个元素top+1，当有一个元素是，top为0...*/
	return OK;
}

//判断栈是否为空
Status StackISEmpty(SqStack S) {
	if (S.top == -1)
		return TRUE;
	else
		return FALSE;
}

//返回栈长度(元素个数)
int StackLength(SqStack S) {
	return S.top + 1;       
}

//获取栈顶元素,若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR 
Status GetTop(SqStack S,SElemType *e) {
	if (S.top == -1)
		return ERROR;
	else
		*e = S.data[S.top];
	return OK;
}

//压栈 插入元素e为新的栈顶元素
Status Push_sq(SqStack *S,SElemType e) {
	//先判断栈是否栈满，在将top指针上移一位，最后数据元素e添加入栈顶
	if (S->top == MAXSIZE - 1)  //栈满
		return ERROR;  
	S->top++;
	S->data[S->top] = e;
	return OK;
}

//出栈  若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR 
Status Pop_sq(SqStack *S,SElemType *e) {
	if (S->top == -1)   //先判断是否为空栈
		return ERROR;
	*e = S->data[S->top];   //将要删除的栈顶元素赋值给e
	S->top--;              //top指针下移
	return OK;
}

/*	遍历栈元素  从栈底到栈顶依次对栈中每个元素显示
	由于静态顺序表采用数组方式进行底层存储，因为只需要进行数组遍历即可*/
Status StackTraverse_sq(SqStack S) {
	int i;
	i = 0;
	while (S.top > -1)    //top指针的位序其实跟数组的下标是一一对应
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
	printf("压栈后的栈s：");
	StackTraverse_sq(s);

	GetTop(s,&e);
	printf("此时s的栈的元素为 %d\n", e);

	Pop_sq(&s,&e);
	printf("弹出的栈顶元素 e = %d\n", e);
	printf("出栈后的栈s：");
	StackTraverse_sq(s);

	len  = StackLength(s);
	printf("栈s的元素个数 %d\n",len);

	isEmpty = StackISEmpty(s);
	printf("栈s是否空：i=%d(1:是 0:否)\n", isEmpty);

	ClearStack(&s);
	printf("栈清空");

	isEmpty = StackISEmpty(s);
	printf("栈s是否空：i=%d(1:是 0:否)\n", isEmpty);

}