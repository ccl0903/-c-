#include "stdio.h"    
#include "stdlib.h"   

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;		 // Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int SElemType;   //数据类型

//链栈存储结构
typedef struct StackNode {
	SElemType data;
	struct SatckNode* next;
}StackNode,*pLinkStack;

typedef struct {
	pLinkStack top;         //栈顶指针
	int count;				//栈元素计数器
}LinkStack;


//visit_ls用于打印显示 ls 检查代表栈链
Status visit_ls(SElemType c)
{
	printf("%d ", c);
	return OK;
}

//链栈初始化
Status InitStack_ls(LinkStack *s) {
	s->top = (pLinkStack)malloc(sizeof(StackNode));
	if (!s->top)
		return ERROR; //创建失败
	s->top = NULL;	  //链表的头部作为栈顶是最方便的，因此没有必要设置头结点
	s->count = 0;
	return OK;
}

//清空栈链 把S置为空栈
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
	s->top = NULL; //防止生成野指针
	return OK;
}

// 若栈S为空栈，则返回TRUE，否则返回FALSE
Status StackIsEmpty_ls(LinkStack s) {
	if (s.top == NULL)
		return TRUE;
	else
		return ERROR;
}

// 返回栈的长度
int StackLength_ls(LinkStack s) {
	return s.count;
}

//压栈
Status Push_ls(LinkStack *s,SElemType e) {
	//链表压栈不需要判断满栈，只要有空间内存就可以入栈
	pLinkStack p;
	p = (pLinkStack)malloc(sizeof(StackNode));
	p->data = e;
	p->next = s->top;  //将新结点插人栈顶
	s->top = p;        //将栈顶指针指向新结点
	s->count++;		   //栈计数器加1
	return OK;
}

//出栈
Status Pop_ls(LinkStack *s,SElemType *e) {
	pLinkStack p;
	if (s->count == 0)
		return ERROR;
	p = s->top;			//p存放即将要删除的栈顶元素
	*e = p->data;
	s->top = p->next;    
	free(p);
	s->count--;
	return OK;
}

//获取栈顶元素
Status GetTop_ls(LinkStack s,SElemType *e) {
	if (s.top == NULL)
		return ERROR;
	else
		*e = s.top->data;
	return OK;
}

//遍历栈元素
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
	printf("栈空否：%d(1:空 0:否)\n", isEmpty);

	if (i == OK)
	{
		for (j = 1; j <= 10; j++) {
			Push_ls(&s,j);
		}
	}
	printf("栈中元素依次为：");
	StackTraverse_ls(s);

	isEmpty = StackIsEmpty_ls(s);
	printf("栈空否：%d(1:空 0:否)\n", isEmpty);

	len = StackLength_ls(s);
	GetTop_ls(s,&e);
	printf("栈顶元素 e = %d 栈的长度为%d\n", e, len);
	
	Pop_ls(&s,&e);
	len = StackLength_ls(s);
	printf("弹出的栈顶元素 e=%d  栈的长度为%d\n", e,len);
	printf("弹栈后栈中元素依次为：");
	StackTraverse_ls(s);

	ClearStack_ls(&s);
	printf("清空栈。\n");

	isEmpty = StackIsEmpty_ls(s);
	printf("栈空否：%d(1:空 0:否)\n", isEmpty);

	return 0;
}