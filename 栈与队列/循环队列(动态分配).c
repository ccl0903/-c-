#include "stdio.h"    
#include "stdlib.h"  

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;		 // Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int QElemType;   //队列的数据类型

typedef struct {
	QElemType* data;   //存储空间（动态初始化）
	int front;		//头指针
	int rear;		//尾指针 指向队尾元素的后一个地址
}sqdQueue;

//显示  sqd代表动态循环队列
Status visit_sqd_queue(QElemType c)
{
	printf("%d ", c);
	return OK;
}

//初始化队列
Status InitQueue_sqd(sqdQueue *q) {
	q->data = (QElemType*)malloc(MAXSIZE*sizeof(QElemType));  //为队列分配一个最大容扯为 MASIZE 的数组空间
	if (!q->data)
		return ERROR;
	q->front = 0;					//头指针和尾指针置为零 ， 队列为空
	q->rear = 0;
	return OK;  
}

//清空队列
Status ClearQueue_sqd(sqdQueue *q) {
	//将队头指针和队尾指针都置为0
	q->front = q->rear = 0;
	return OK;
}

//判断队列是否为空 ,则返回TRUE,否则返回FALSE
Status QueueIsEmpty_sqd(sqdQueue q) {

	if (q.front == q.rear)
		return TRUE;
	else
		return FALSE;
}

//返回队列的长度
int QueueLength_sqd(sqdQueue q) {
	return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

//入队 若队列未满，则插入元素e为Q新的队尾元素
Status EnQueue_sqd(sqdQueue *q,QElemType e) {
	if ((q->rear + 1) % MAXSIZE == q->front)
		return ERROR;
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
	return OK;

}

//出队 若队列不空，则删除Q中队头元素，用e返回其值
Status DeQueue_sqd(sqdQueue *q,QElemType *e) {
	if (q->front == q->rear)
		return ERROR;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	return OK;
}

//获取队头元素
QElemType GetQueueHead_sqd(sqdQueue q) {
	return q.data[q.front];
}

//遍历队列
void QueueTraverse_sqd(sqdQueue q) {
	int i = q.front;
	while ((i + q.front) != q.rear)
	{
		visit_sqd_queue(q.data[i]);
		i = (i + 1) % MAXSIZE;
	}
	printf("\n");
	return OK;
}

//int main() {
//	Status i;
//	int j, isEmpty, len, k, res;
//	QElemType d;
//	sqdQueue q;
//	i = InitQueue_sqd(&q);
//
//	isEmpty = QueueIsEmpty_sqd(q);
//	printf("初始化队列后，队列空否？%u(1:空 0:否)\n", isEmpty);
//
//	printf("请输入整型队列元素(不超过%d个),-1为提前结束符: ", MAXSIZE - 1);
//	do
//	{
//		/* scanf("%d",&d); */
//		d = i;
//		if (d == -1)    //i=-1时,证明初始化失败
//			break;
//		i++;
//		EnQueue_sqd(&q,d);
//	} while (i < MAXSIZE);
//
//	len = QueueLength_sqd(q);
//	printf("队列长度为: %d\n", len);
//	printf("现在队列中的元素为: \n");
//	QueueTraverse_sqd(q);
//
//	ClearQueue_sqd(&q);
//	printf("循环队列清空~~~~~");
//	isEmpty = QueueIsEmpty_sqd(q);
//	printf("初始化队列后，队列空否？%u(1:空 0:否)\n", isEmpty);
//
//	for (j = 0; j < MAXSIZE; j++)
//	{
//		EnQueue_sqd(&q, j);
//		if (j == 19)
//		{
//			for (k = 0; k < MAXSIZE; k++) {
//				res = k + 100;
//				DeQueue_sqd(&q,&d);
//				printf("删除的元素值为%d  \t", d);
//				EnQueue_sqd(&q, res);
//				printf("向队尾插入了%d\n", res);
//			}
//		}
//	}
//	printf("现在队列中的元素为: \n");
//	QueueTraverse_sqd(q);
//
//	res = GetQueueHead_sqd(q);
//	printf("循环队列的队头元素 %d \n",res);
//	return 0;
//}