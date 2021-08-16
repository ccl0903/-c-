#define _CRT_SECURE_NO_WARNINGS 1
#include "Graph.h"   //�����Լ������ͷ�ļ�

Boolean visited[Default_Vertex_Size]; /* ���ʱ�־������ */

//�ڽӱ�������ȱ���������������ͼg����ʼ����v
void DFS_adj(AdjGraph* g, int v, Boolean visited[]) {

	printf("%c-->", GetVerNodeValue(g, v));
	visited[v] = TRUE;  //Ϊ���ʹ��Ķ������ϱ��
	int w = GetFirstAdjNeighbor(g, GetVerNodeValue(g, v)); //��ȡ��һ���ڽӶ���
	while (w != -1) {
		//���ڽӶ���δ������
		if (!visited[w]) {
			DFS_adj(g, w, visited);//�Ըö���Ϊ��ʼ�������������ȱ���
		}
		//������ö���δ�����ʣ���ô��һ�ֽ��Ըö���Ϊ��ʼ�������������ȱ�����
		w = GetNextAdjNeighbor(g, GetVerNodeValue(g, v), GetVerNodeValue(g, w));
	}
}

//�ڽӱ������ȱ�����g:ͼ  v:��ʼ��  visited:�������
void BFS_adj(AdjGraph* g, int v, Boolean visited[]) {

	int w;  //w�ݴ��ڽӶ���
	Queue Q;
	InitQueue(&Q);

	printf("%c==>", GetVerNodeValue(g,v));
	visited[v] = TRUE;
	EnQueue(&Q,v);   //��ʼ�����

	while (! QueueEmpty(Q))
	{
		DeQueue(&Q, &v);	//��ջ������ȡ�׶���
		w = GetFirstAdjNeighbor(g,GetVerNodeValue(g,v));  //��ȡ��һ���ڽӶ���
		while (w != -1) {
			if (!visited[w]) {	//�����ڽӶ���δ������
				printf("%c==>", GetVerNodeValue(g, w));
				visited[w] = TRUE;
				EnQueue(&Q,w);		//���ö�����ӣ�Ϊ֮����ʸö�����ڽӶ������̵�
			}
			//��ȡ����v����һ���ڽӶ��㣨���ڽӶ����˳����ǰ����ʹ��ڽӶ���w֮��
			w = GetNextAdjNeighbor(g,GetVerNodeValue(g,v),GetVerNodeValue(g,w));
		}
	}	
};

//����ͨͼ������ȱ���
void NonUnicomDFS_adj(AdjGraph* g, int v, Boolean visited[]) {
	//�Է���ͨͼg��������ȱ���
	int count = g->NumVertices;
	int j;
	for (int i = v; i < v + count; i++) {
		j = (i + count) % count;  //����ѭ������˼�붨��j����������Խ��
		if (!visited[j])
			DFS_adj(g, j, visited);
	}
};

//����ͨͼ������ȱ���
void NonUnicomBFS_adj(AdjGraph* g, int v, Boolean visited[]) {
	int count = g->NumVertices;
	int j;
	for (int i = v; i < v + count; i++) {
		j = (i + count) % count;  //����ѭ������˼�붨��j����������Խ��
		if (!visited[j])
			BFS_adj(g, j, visited);
	}
};

int main_adjFB() {

	int i, j, k, num;
	VertexType a, b, c, d, e, f, g1, h, i1, j1,v, v1;

	AdjGraph g;
	InitAdjGraph(&g);
	//��Ӷ���
	for (i = 0; i < 10; i++)  //����10��Ԫ��
	{
		v = 'a' + i;
		InsertAdjVertex(&g, v);
	}

	//����߹���ͼ
	a = 'a';
	b = 'b';
	c = 'c';
	d = 'd';
	e = 'e';
	f = 'f';
	g1 = 'g';
	h = 'h';
	i1 = 'i';
	j1 = 'j';
	InsertAdjEdge(&g, a, b);
	InsertAdjEdge(&g, a, c);
	InsertAdjEdge(&g, a, d);
	InsertAdjEdge(&g, b, c);
	InsertAdjEdge(&g, b, e);
	InsertAdjEdge(&g, c, d);
	InsertAdjEdge(&g, c, e);
	InsertAdjEdge(&g, d, e);
	InsertAdjEdge(&g, f, g1);
	InsertAdjEdge(&g, h, j1);
	InsertAdjEdge(&g, h, i1);
	InsertAdjEdge(&g, i1, j1);

	printf("�ڽӱ�:\n");
	ShowAdjGraph(g);

	num = g.NumVertices;
	visited[num] = visited;

	printf("=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)
			visited[i] = FALSE;

		printf("\n�ڽӱ��������ȱ���:");
		DFS_adj(&g, j, visited);
	}

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //��������
			visited[i] = FALSE;
		printf("\n%d  �ڽӱ��������ȱ���:",j);
		BFS_adj(&g, j, visited);
	}

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //��������
			visited[i] = FALSE;
		printf("\n%d  (����ͨͼ)�ڽӱ��������ȱ���:",j);
		NonUnicomDFS_adj(&g, j, visited);
	}

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //��������
			visited[i] = FALSE;
		printf("\n%d  (����ͨͼ)�ڽӱ�Ĺ�����ȱ���:",j);
		NonUnicomBFS_adj(&g, j, visited);
	}

	return 0;
}