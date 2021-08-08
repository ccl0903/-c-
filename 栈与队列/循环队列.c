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
	QElemType data[MAXSIZE];  //静态数组分配
	int front;				 //头指针
	int rear;				 //尾指针  若队列不空，指向队列尾元素的下一个位置
}SqQueue;

//显示打印
Status visit_sq(QElemType c)
{
	printf("%d ", c);
	return OK;
}

//初始化一个队列
Status InitQueue(SqQueue *q) {
	//因为是静态创建数组，无需为q->data 动态分配空间
	q->front = 0;
	q->rear = 0;   
	return OK;
}

//清空队列
Status ClearQueue_sq(SqQueue* q) {
	q->front = q->rear = 0;
	return OK;
}

//判断队列是否为空 ,则返回TRUE,否则返回FALSE
Status QueueIsEmpty_sq(SqQueue q) {
	if (q.front == q.rear)  // 队列空的标志
		return TRUE;
	else
		return FALSE;
}

//返回队列的长度
int QueueLength_sq(SqQueue q) {
	return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

//获取队头元素
QElemType GetQueueHead_sq(SqQueue q) {
	if (q.front == q.rear)  //队列为空
		return ERROR;
	return q.data[q.front];  //队头元素
}

//入队 若队列未满，则插入元素e为Q新的队尾元素
Status EnQueue_sq(SqQueue *q,QElemType e) {
	if ((q->rear + 1) % MAXSIZE == q->front)  //队满
		return ERROR;
	q->data[q->rear] = e;		//将元素e赋值给队尾
	q->rear = (q->rear + 1) % MAXSIZE;	//rear指针向后移一位置，循环队列
	return OK;
}

//出队 若队列不空，则删除Q中队头元素，用e返回其值
Status DeQueue_sq(SqQueue *q,QElemType *e) {
	if (q->rear == q->front)	//对空
		return ERROR;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;   //front指针向后移一位置
	return OK;
}

//遍历队列
void QueueTraverse_sq(SqQueue q) {
	int i = q.front;
	while ((i+q.front) != q.rear)
	{
		visit_sq(q.data[i]);
		i = (i + 1) % MAXSIZE;
	}
	printf("\n");
	return OK;
}

int main_sq1() {
	Status i;
	int j, isEmpty, len,k,res;
	QElemType d;
	SqQueue q;
	i = InitQueue(&q);

	isEmpty = QueueIsEmpty_sq(q);
	printf("初始化队列后，队列空否？%u(1:空 0:否)\n", isEmpty);

	printf("请输入整型队列元素(不超过%d个),-1为提前结束符: ", MAXSIZE - 1);
	do
	{
		/* scanf("%d",&d); */
		d = i;
		if (d == -1)    //i=-1时,证明初始化失败
			break;
		i++;
		EnQueue_sq(&q,d);
	} while (i <  MAXSIZE );

	len = QueueLength_sq(q);
	printf("队列长度为: %d\n", len);
	printf("现在队列中的元素为: \n");
	QueueTraverse_sq(q);

	ClearQueue_sq(&q);
	isEmpty = QueueIsEmpty_sq(q);
	printf("清空队列后, 队列空否？%u(1:空 0:否)\n", isEmpty);


	for (j = 0; j < MAXSIZE; j++)
	{
		EnQueue_sq(&q, j);
		if (j==19)
		{
			for (k = 0; k < MAXSIZE;k++) {
				res = k+100;
				DeQueue_sq(&q, &d);
				printf("删除的元素值为%d  \t", d);
				EnQueue_sq(&q,res);
				printf("向队尾插入了%d\n",res);
			}
		}
	}

	printf("现在队列中的元素为: \n");
	QueueTraverse_sq(q);

	res = GetQueueHead_sq(q);
	printf("循环队列的队头元素 %d \n", res);
	
	return 0;
}