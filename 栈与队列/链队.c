#include "stdio.h"    
#include "stdlib.h"  

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */


typedef int Status;		 // Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int QElemType;   //队列的数据类型

//队列链式存储结构
typedef struct {
	QElemType data;
	struct QNode* next;
}QNode,*QueuePtr;

typedef struct {
	QueuePtr front;		//队头指针
	QueuePtr rear;		//队尾指针
}LinkQueue;


//显示   lq代表链式队列
Status visit_lq(QElemType c)
{
	printf("%d ", c);
	return OK;
}

//初始化队列
Status InitLinkQueue(LinkQueue *q){
	q->front = q->rear = (QueuePtr)malloc(sizeof(QNode));
	q->front->next = NULL;
	return OK;
}

//销毁链队列
Status DestroyQueue(LinkQueue *q) {
	QueuePtr p;
	while (q->front)
	{
		p = q->front->next;   //指向队头结点的下一个元素
		free(q->front);
		q->front = p;
	}
	return OK;
}

//清空队列
Status ClearLinkQueue(LinkQueue *q) {
	QueuePtr p, s;
	p = q->front->next;			//p 存放后面全部要删除的元素
	q->rear = q->front;
	q->front->next = NULL;
	while (p) {
		s = p;     //s存放即将删出的元素
		p = p->next;
		free(s);
	}
	return OK;
}

//判断队列是否为空 ,则返回TRUE,否则返回FALSE
Status LinkQueueIsEmpty(LinkQueue q) {
	if (q.rear == q.front)
		return TRUE;
	else
		return FALSE;
}

//返回队列的长度
int LinkQueueLength(LinkQueue q) {
	int i = 0;
	//方法一
	while (q.front->next != NULL) {
		i++;
		q.front = q.front->next;
	}
	//方法二
	/*while (q.front != q.rear)    
	{
		i++;
		q.front = q.front->next;
	}*/
	return i;
}

//入队 若队列未满，则插入元素e为Q新的队尾元素
Status EnLinkQueue(LinkQueue *q,QElemType e) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));    //生成一个新结点
	//因为采用链式存储，理论上不需要进行判断队满情况,但要为了程序健壮性需要判断内存是否分配成功
	if (!p)    //内存分配失败
		return ERROR;
	p->data = e;
	p->next = NULL;
 	q->rear->next = p;
	q->rear = p;
	return OK;
}

//出队 若队列不空，则删除Q中队头元素，用e返回其值
Status DeLinkQueue(LinkQueue *q,QElemType *e) {
	QueuePtr p = q->front->next;  //p指向队首元素
	if (q->front == q->rear)	  //队满
		return ERROR;
	*e = p->data;
	q->front->next = p->next;
	if (p == q->rear)		//若队头==队尾，则删除后将rear指向头结点
		q->rear = q->front;
	free(p);				//队首元素出队
	return OK;
}

//获取队头元素
QElemType GetLinkQueueHead(LinkQueue q) {
	if (q.front == q.rear)
		return ERROR;
	QueuePtr p = q.front->next;
	return p->data;
}

//遍历队列
void LinkQueueTraverse(LinkQueue q) {
	QueuePtr p;
	p = q.front->next;
	while (p)
	{
		visit_lq(p->data);
		p = p->next;
	}
	printf("\n");
}


int main() {
	Status i;
	int j, isEmpty, len, k, res;
	QElemType d;
	LinkQueue q;
	i = InitLinkQueue(&q);

	isEmpty = LinkQueueIsEmpty(q);
	printf("初始化队列后，队列空否？%u(1:空 0:否)\n", isEmpty);

	printf("往栈队中插入 %d个元素 : \n", MAXSIZE - 1);

	for ( j = 0; j < MAXSIZE -1; j++)
	{
 		EnLinkQueue(&q, j);
	}

	len = LinkQueueLength(q);
	printf("队列长度为: %d\n", len);
	printf("现在队列中的元素为: \n");
	LinkQueueTraverse(q);

	ClearLinkQueue(&q);

	isEmpty = LinkQueueIsEmpty(q);
	printf("队列空否？%u(1:空 0:否)\n", isEmpty);

	for (j = 0; j < MAXSIZE; j++)
	{
		EnLinkQueue(&q,j);
		if (j == 19)
		{
			for (k = 0; k < MAXSIZE; k++) {
				res = k + 100;
				DeLinkQueue(&q,&d);
				printf("删除的元素值为%d  \t", d);
				EnLinkQueue(&q,res);
				printf("向队尾插入了%d\n", res);
			}
		}
	}

	printf("现在队列中的元素为: \n");
	LinkQueueTraverse(q);

	isEmpty = LinkQueueIsEmpty(q);
	printf("队列空否？%u(1:空 0:否)\n", isEmpty);

	res = GetLinkQueueHead(q);
	printf("链队的队头元素 %d \n", res);


	return 0;
}