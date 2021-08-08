#include "stdio.h"    
#include "stdlib.h"  

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* �洢�ռ��ʼ������ */


typedef int Status;		 // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
typedef int QElemType;   //���е���������

//������ʽ�洢�ṹ
typedef struct {
	QElemType data;
	struct QNode* next;
}QNode,*QueuePtr;

typedef struct {
	QueuePtr front;		//��ͷָ��
	QueuePtr rear;		//��βָ��
}LinkQueue;


//��ʾ   lq������ʽ����
Status visit_lq(QElemType c)
{
	printf("%d ", c);
	return OK;
}

//��ʼ������
Status InitLinkQueue(LinkQueue *q){
	q->front = q->rear = (QueuePtr)malloc(sizeof(QNode));
	q->front->next = NULL;
	return OK;
}

//����������
Status DestroyQueue(LinkQueue *q) {
	QueuePtr p;
	while (q->front)
	{
		p = q->front->next;   //ָ���ͷ������һ��Ԫ��
		free(q->front);
		q->front = p;
	}
	return OK;
}

//��ն���
Status ClearLinkQueue(LinkQueue *q) {
	QueuePtr p, s;
	p = q->front->next;			//p ��ź���ȫ��Ҫɾ����Ԫ��
	q->rear = q->front;
	q->front->next = NULL;
	while (p) {
		s = p;     //s��ż���ɾ����Ԫ��
		p = p->next;
		free(s);
	}
	return OK;
}

//�ж϶����Ƿ�Ϊ�� ,�򷵻�TRUE,���򷵻�FALSE
Status LinkQueueIsEmpty(LinkQueue q) {
	if (q.rear == q.front)
		return TRUE;
	else
		return FALSE;
}

//���ض��еĳ���
int LinkQueueLength(LinkQueue q) {
	int i = 0;
	//����һ
	while (q.front->next != NULL) {
		i++;
		q.front = q.front->next;
	}
	//������
	/*while (q.front != q.rear)    
	{
		i++;
		q.front = q.front->next;
	}*/
	return i;
}

//��� ������δ���������Ԫ��eΪQ�µĶ�βԪ��
Status EnLinkQueue(LinkQueue *q,QElemType e) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));    //����һ���½��
	//��Ϊ������ʽ�洢�������ϲ���Ҫ�����ж϶������,��ҪΪ�˳���׳����Ҫ�ж��ڴ��Ƿ����ɹ�
	if (!p)    //�ڴ����ʧ��
		return ERROR;
	p->data = e;
	p->next = NULL;
 	q->rear->next = p;
	q->rear = p;
	return OK;
}

//���� �����в��գ���ɾ��Q�ж�ͷԪ�أ���e������ֵ
Status DeLinkQueue(LinkQueue *q,QElemType *e) {
	QueuePtr p = q->front->next;  //pָ�����Ԫ��
	if (q->front == q->rear)	  //����
		return ERROR;
	*e = p->data;
	q->front->next = p->next;
	if (p == q->rear)		//����ͷ==��β����ɾ����rearָ��ͷ���
		q->rear = q->front;
	free(p);				//����Ԫ�س���
	return OK;
}

//��ȡ��ͷԪ��
QElemType GetLinkQueueHead(LinkQueue q) {
	if (q.front == q.rear)
		return ERROR;
	QueuePtr p = q.front->next;
	return p->data;
}

//��������
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
	printf("��ʼ�����к󣬶��пշ�%u(1:�� 0:��)\n", isEmpty);

	printf("��ջ���в��� %d��Ԫ�� : \n", MAXSIZE - 1);

	for ( j = 0; j < MAXSIZE -1; j++)
	{
 		EnLinkQueue(&q, j);
	}

	len = LinkQueueLength(q);
	printf("���г���Ϊ: %d\n", len);
	printf("���ڶ����е�Ԫ��Ϊ: \n");
	LinkQueueTraverse(q);

	ClearLinkQueue(&q);

	isEmpty = LinkQueueIsEmpty(q);
	printf("���пշ�%u(1:�� 0:��)\n", isEmpty);

	for (j = 0; j < MAXSIZE; j++)
	{
		EnLinkQueue(&q,j);
		if (j == 19)
		{
			for (k = 0; k < MAXSIZE; k++) {
				res = k + 100;
				DeLinkQueue(&q,&d);
				printf("ɾ����Ԫ��ֵΪ%d  \t", d);
				EnLinkQueue(&q,res);
				printf("���β������%d\n", res);
			}
		}
	}

	printf("���ڶ����е�Ԫ��Ϊ: \n");
	LinkQueueTraverse(q);

	isEmpty = LinkQueueIsEmpty(q);
	printf("���пշ�%u(1:�� 0:��)\n", isEmpty);

	res = GetLinkQueueHead(q);
	printf("���ӵĶ�ͷԪ�� %d \n", res);


	return 0;
}