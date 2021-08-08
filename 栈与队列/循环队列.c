#include "stdio.h"    
#include "stdlib.h"  

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;		 // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
typedef int QElemType;   //���е���������

typedef struct {
	QElemType data[MAXSIZE];  //��̬�������
	int front;				 //ͷָ��
	int rear;				 //βָ��  �����в��գ�ָ�����βԪ�ص���һ��λ��
}SqQueue;

//��ʾ��ӡ
Status visit_sq(QElemType c)
{
	printf("%d ", c);
	return OK;
}

//��ʼ��һ������
Status InitQueue(SqQueue *q) {
	//��Ϊ�Ǿ�̬�������飬����Ϊq->data ��̬����ռ�
	q->front = 0;
	q->rear = 0;   
	return OK;
}

//��ն���
Status ClearQueue_sq(SqQueue* q) {
	q->front = q->rear = 0;
	return OK;
}

//�ж϶����Ƿ�Ϊ�� ,�򷵻�TRUE,���򷵻�FALSE
Status QueueIsEmpty_sq(SqQueue q) {
	if (q.front == q.rear)  // ���пյı�־
		return TRUE;
	else
		return FALSE;
}

//���ض��еĳ���
int QueueLength_sq(SqQueue q) {
	return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

//��ȡ��ͷԪ��
QElemType GetQueueHead_sq(SqQueue q) {
	if (q.front == q.rear)  //����Ϊ��
		return ERROR;
	return q.data[q.front];  //��ͷԪ��
}

//��� ������δ���������Ԫ��eΪQ�µĶ�βԪ��
Status EnQueue_sq(SqQueue *q,QElemType e) {
	if ((q->rear + 1) % MAXSIZE == q->front)  //����
		return ERROR;
	q->data[q->rear] = e;		//��Ԫ��e��ֵ����β
	q->rear = (q->rear + 1) % MAXSIZE;	//rearָ�������һλ�ã�ѭ������
	return OK;
}

//���� �����в��գ���ɾ��Q�ж�ͷԪ�أ���e������ֵ
Status DeQueue_sq(SqQueue *q,QElemType *e) {
	if (q->rear == q->front)	//�Կ�
		return ERROR;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;   //frontָ�������һλ��
	return OK;
}

//��������
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
	printf("��ʼ�����к󣬶��пշ�%u(1:�� 0:��)\n", isEmpty);

	printf("���������Ͷ���Ԫ��(������%d��),-1Ϊ��ǰ������: ", MAXSIZE - 1);
	do
	{
		/* scanf("%d",&d); */
		d = i;
		if (d == -1)    //i=-1ʱ,֤����ʼ��ʧ��
			break;
		i++;
		EnQueue_sq(&q,d);
	} while (i <  MAXSIZE );

	len = QueueLength_sq(q);
	printf("���г���Ϊ: %d\n", len);
	printf("���ڶ����е�Ԫ��Ϊ: \n");
	QueueTraverse_sq(q);

	ClearQueue_sq(&q);
	isEmpty = QueueIsEmpty_sq(q);
	printf("��ն��к�, ���пշ�%u(1:�� 0:��)\n", isEmpty);


	for (j = 0; j < MAXSIZE; j++)
	{
		EnQueue_sq(&q, j);
		if (j==19)
		{
			for (k = 0; k < MAXSIZE;k++) {
				res = k+100;
				DeQueue_sq(&q, &d);
				printf("ɾ����Ԫ��ֵΪ%d  \t", d);
				EnQueue_sq(&q,res);
				printf("���β������%d\n",res);
			}
		}
	}

	printf("���ڶ����е�Ԫ��Ϊ: \n");
	QueueTraverse_sq(q);

	res = GetQueueHead_sq(q);
	printf("ѭ�����еĶ�ͷԪ�� %d \n", res);
	
	return 0;
}