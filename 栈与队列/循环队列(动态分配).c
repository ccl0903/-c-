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
	QElemType* data;   //�洢�ռ䣨��̬��ʼ����
	int front;		//ͷָ��
	int rear;		//βָ�� ָ���βԪ�صĺ�һ����ַ
}sqdQueue;

//��ʾ  sqd����̬ѭ������
Status visit_sqd_queue(QElemType c)
{
	printf("%d ", c);
	return OK;
}

//��ʼ������
Status InitQueue_sqd(sqdQueue *q) {
	q->data = (QElemType*)malloc(MAXSIZE*sizeof(QElemType));  //Ϊ���з���һ������ݳ�Ϊ MASIZE ������ռ�
	if (!q->data)
		return ERROR;
	q->front = 0;					//ͷָ���βָ����Ϊ�� �� ����Ϊ��
	q->rear = 0;
	return OK;  
}

//��ն���
Status ClearQueue_sqd(sqdQueue *q) {
	//����ͷָ��Ͷ�βָ�붼��Ϊ0
	q->front = q->rear = 0;
	return OK;
}

//�ж϶����Ƿ�Ϊ�� ,�򷵻�TRUE,���򷵻�FALSE
Status QueueIsEmpty_sqd(sqdQueue q) {

	if (q.front == q.rear)
		return TRUE;
	else
		return FALSE;
}

//���ض��еĳ���
int QueueLength_sqd(sqdQueue q) {
	return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

//��� ������δ���������Ԫ��eΪQ�µĶ�βԪ��
Status EnQueue_sqd(sqdQueue *q,QElemType e) {
	if ((q->rear + 1) % MAXSIZE == q->front)
		return ERROR;
	q->data[q->rear] = e;
	q->rear = (q->rear + 1) % MAXSIZE;
	return OK;

}

//���� �����в��գ���ɾ��Q�ж�ͷԪ�أ���e������ֵ
Status DeQueue_sqd(sqdQueue *q,QElemType *e) {
	if (q->front == q->rear)
		return ERROR;
	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	return OK;
}

//��ȡ��ͷԪ��
QElemType GetQueueHead_sqd(sqdQueue q) {
	return q.data[q.front];
}

//��������
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
//	printf("��ʼ�����к󣬶��пշ�%u(1:�� 0:��)\n", isEmpty);
//
//	printf("���������Ͷ���Ԫ��(������%d��),-1Ϊ��ǰ������: ", MAXSIZE - 1);
//	do
//	{
//		/* scanf("%d",&d); */
//		d = i;
//		if (d == -1)    //i=-1ʱ,֤����ʼ��ʧ��
//			break;
//		i++;
//		EnQueue_sqd(&q,d);
//	} while (i < MAXSIZE);
//
//	len = QueueLength_sqd(q);
//	printf("���г���Ϊ: %d\n", len);
//	printf("���ڶ����е�Ԫ��Ϊ: \n");
//	QueueTraverse_sqd(q);
//
//	ClearQueue_sqd(&q);
//	printf("ѭ���������~~~~~");
//	isEmpty = QueueIsEmpty_sqd(q);
//	printf("��ʼ�����к󣬶��пշ�%u(1:�� 0:��)\n", isEmpty);
//
//	for (j = 0; j < MAXSIZE; j++)
//	{
//		EnQueue_sqd(&q, j);
//		if (j == 19)
//		{
//			for (k = 0; k < MAXSIZE; k++) {
//				res = k + 100;
//				DeQueue_sqd(&q,&d);
//				printf("ɾ����Ԫ��ֵΪ%d  \t", d);
//				EnQueue_sqd(&q, res);
//				printf("���β������%d\n", res);
//			}
//		}
//	}
//	printf("���ڶ����е�Ԫ��Ϊ: \n");
//	QueueTraverse_sqd(q);
//
//	res = GetQueueHead_sqd(q);
//	printf("ѭ�����еĶ�ͷԪ�� %d \n",res);
//	return 0;
//}