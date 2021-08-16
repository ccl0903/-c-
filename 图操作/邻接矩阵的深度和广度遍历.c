#define _CRT_SECURE_NO_WARNINGS 1
#include "Graph.h"   //�����Լ������ͷ�ļ�

Boolean visited[Default_Vertex_Size]; /* ���ʱ�־������ */

 /*�ڽӾ���ṹ*/
typedef struct GraphMtx
{
	int MaxVertices; //��󶥵���
	int NumVertices; //��ʵ�Ķ�����
	int NumEdges; //����
	VertexType* VerticesList; //�����б�
	int** Edge; //����Ϣ����
}GraphMtx;


/* �õ��Ķ��нṹ�뺯��********************************** */

/* ��ʼ��һ���ն���Q */
Status InitQueue(Queue* Q)
{
	Q->front = 0;
	Q->rear = 0;
	return  OK;
}

/* ������QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
Status QueueEmpty(Queue Q)
{
	if (Q.front == Q.rear) /* ���пյı�־ */
		return TRUE;
	else
		return FALSE;
}

/* ������δ���������Ԫ��eΪQ�µĶ�βԪ�� */
Status EnQueue(Queue* Q, int e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)	/* ���������ж� */
		return ERROR;
	Q->data[Q->rear] = e;			/* ��Ԫ��e��ֵ����β */
	Q->rear = (Q->rear + 1) % MAXSIZE;/* rearָ�������һλ�ã� */
								/* ���������ת������ͷ�� */
	return  OK;
}

/* �����в��գ���ɾ��Q�ж�ͷԪ�أ���e������ֵ */
Status DeQueue(Queue* Q, int* e)
{
	if (Q->front == Q->rear)			/* ���пյ��ж� */
		return ERROR;
	*e = Q->data[Q->front];				/* ����ͷԪ�ظ�ֵ��e */
	Q->front = (Q->front + 1) % MAXSIZE;	/* frontָ�������һλ�ã� */
									/* ���������ת������ͷ�� */
	return  OK;
}
/* ****************************************************** */


//������ȱ���:  g:ͼ  v:��ʼ��    visited:�������
void DFS(GraphMtx* g,int v,Boolean visited[]) {
	//���ʶ��㣬��ȡֵ����ӡ
	printf("%c-->", GetVertexValue(g,v));
	visited[v] = TRUE;  //Ϊ���ʹ��Ķ������ϱ��
	int w = GetFirstNeighbor(g,GetVertexValue(g,v));//��ȡ��һ���ڽӶ����±�
	while (w != -1)
	{	//���ڽӶ���δ������
		if (!visited[w])
			DFS(g,w,visited);	//�Ըö���Ϊ��ʼ�������������ȱ���
		/*
		����ڷ���ͨͼ
		�Ե�һ���ڽӶ���������ȱ�����ɣ���ȡ��һ���ڽӶ����λ��
		������ö���δ�����ʣ���ô��һ�ֽ��Ըö���Ϊ��ʼ�������������ȱ�����
		*/
		w = GetNextNeighbor(g, GetVertexValue(g, v), GetVertexValue(g, w));
	}
}

//������ȱ�����g:ͼ  v:��ʼ��  visited:�������
void BFS(GraphMtx* g, int v, Boolean visited[]) {

	int w;  //w�ݴ��ڽӶ���
	Queue Q;  //����ѭ������
	InitQueue(&Q);

	//���ʳ�ʼ��
	printf("%c==>", GetVertexValue(g, v));
	visited[v] = TRUE;
	EnQueue(&Q,v);  //��ʼ�����
	
	while (!QueueEmpty(Q)) { //�����д��ж���
		DeQueue(&Q,&v);  //��ջ������ȡ�׶���
		w = GetFirstNeighbor(g,GetVertexValue(g,v));  //��ȡ��һ���ڽӶ���
		while (w != -1) {	  //�����ڽӶ���
			if (!visited[w]) {//�����ڽӶ���δ������
				printf("%c==>", GetVertexValue(g,w));
				visited[w] = TRUE;  //���Ϊ�ѷ���
				EnQueue(&Q,w);	//���ö�����ӣ�Ϊ֮����ʸö�����ڽӶ������̵�
			}
			//��ȡ����v����һ���ڽӶ��㣨���ڽӶ����˳����ǰ����ʹ��ڽӶ���w֮��
			w = GetNextNeighbor(g,GetVertexValue(g,v),GetVertexValue(g,w));
		}
	}
}

//����ͨͼ������ȱ���
void NonUnicomDFS(GraphMtx* g, int v, Boolean visited[]) {
	int count = g->NumVertices;
	int i, j;
	for (i = v; i < v + count; i++) {
		j = (i + count) % count;  //����ѭ������˼�붨��j����������Խ��
		if (!visited[j])
			DFS(g, j, visited);;
	}
};

//����ͨͼ������ȱ���
void NonUnicomBFS(GraphMtx* g, int v, Boolean visited[]) {
	int count = g->NumVertices;
	int i,j;
	for ( i = v; i < v + count; i++) {
		j = (i + count) % count;  //����ѭ������˼�붨��j����������Խ��
		if (!visited[j])
			BFS(g, j, visited);
	}
};


int main() {
	
	GraphMtx g;
	int i, j, k,num = 8;
	VertexType a, b, c, d, e, f, g1, h, v, v1;
	visited[5] = visited;

	InitGraph(&g);

	//��Ӷ���
	for (i = 0; i < num; i++)
	{
		v = 'a' + i;
		InsertVertex(&g, v);
		visited[i] = FALSE;  //��ʼȫ��Ϊ0��û�б����ʹ�
	}

	for ( i = 0; i < num; i++)
	{
		printf("%c--", visited[i]);
	}

	printf("%c-->\n", GetVertexValue(&g, 1));

	//�����
	a = 'a';
	b = 'b';
	c = 'c';
	d = 'd';
	e = 'e';
	f = 'f';
	g1 = 'g';
	h = 'h';
	InsertEdge(&g, a, b);
	InsertEdge(&g, a, d);
	InsertEdge(&g, b, c);
	InsertEdge(&g, c, d);
	InsertEdge(&g, d, e);
	InsertEdge(&g, f, g1);
	InsertEdge(&g, g1, h);

	printf("�ڽӾ���:\n");
	ShowGraph(g);

	//ʹ����ȱ���
	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //��������
			visited[i] = FALSE;
		printf("\n%d  �ڽӾ����������ȱ���:", j);
		DFS(&g, j, visited);
	}


	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //��������
			visited[i] = FALSE;
		printf("\n%d  �ڽӾ���Ĺ�����ȱ���:", j);
		BFS(&g, j, visited);
	}
	

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //��������
			visited[i] = FALSE;
		printf("\n%d  (����ͨͼ)�ڽӾ����������ȱ���:", j);
		NonUnicomDFS(&g, j, visited);
	}

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //��������
			visited[i] = FALSE;
		printf("\n%d  (����ͨͼ)�ڽӾ���Ĺ�����ȱ���:", j);
		NonUnicomBFS(&g, j, visited);
	}
	
	return 0;
}