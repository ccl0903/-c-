#define _CRT_SECURE_NO_WARNINGS 1
#include "Graph.h"   //�����Լ������ͼͷ�ļ�

Boolean visited[Default_Vertex_Size]; /* ���ʱ�־������ */


//��ʼ��
void InitAdjGraph(AdjGraph *g) {
	g->MaxVertices = Default_Vertex_Size;
	g->NumEdges = g->NumVertices = 0;
	//Ϊ����ṹ���ٿռ�
	g->adjList = (Vertex)malloc(sizeof(VerNode)*g->MaxVertices);
	assert(g->adjList != NULL);
	for (int i = 0; i < g->MaxVertices; i++)
		g->adjList[i].firstArc = NULL;  
}

// ��ȡ����λ��
int GetVerNodePos(AdjGraph *g,VertexType v){
	for (int i = 0; i < g->NumVertices; i++)
	{
		if (g->adjList[i].data == v)
			return i;
	}
	return -1;
}

//��ȡ����ֵ
VertexType GetVerNodeValue(AdjGraph *g,int v) {
	return g->adjList[v].data;
}

//��ӡͼ
void ShowAdjGraph(AdjGraph g) {
	EdgeNode* p;
	for (int i = 0; i < g.NumVertices; i++) //�Զ�����б���
	{
		printf("%d  %c:>", i, g.adjList[i].data);//�������
		p = g.adjList[i].firstArc; //ָ��߽ṹ
		while (p != NULL)
		{
			printf("%d-->", p->dest);
			p = p->next;
		}
		printf("Nul.\n");
	}
	printf("\n");
}

//���붥��
void InsertAdjVertex(AdjGraph *g,VertexType v) {
	//�ж϶�����Ƿ�����
	if (g->NumVertices >= g->MaxVertices)
		return;
	g->adjList[g->NumVertices++].data = v;  //����
}

//����ߣ��ڶ���vertex1��vertex2֮�����һ����
void InsertAdjEdge(AdjGraph *g,VertexType v1,VertexType v2) {
	int p1 = GetVerNodePos(g, v1); //��ȡv1��λ��
	int p2 = GetVerNodePos(g, v2);
	if (p1 == -1 || p2 == -1)
		return;

	EdgeNode* s1,* s2;
	//����ͼ��˫��Ĳ���Ҫ����
	//����V1 --> V2�ı� ͷ�巨����
	s1 = (EdgeNode*)malloc(sizeof(EdgeNode)); // s1ָ��p1����ĵ�һ���ڽӵ�
	assert(s1 != NULL);
	s1->dest = p2;
	s1->next = g->adjList[p1].firstArc;  
	g->adjList[p1].firstArc = s1;

	//����V2 --> V1�ı� ͷ�巨����
	s2 = (EdgeNode*)malloc(sizeof(EdgeNode));
	assert(s2!=NULL);
	s2->dest = p1;
	s2->next = g->adjList[p2].firstArc;
	g->adjList[p2].firstArc = s2;

	g->NumEdges++;
}

// ɾ����,ɾ������v1�Ͷ���v2֮��ı�
void removeAdjEdge(AdjGraph *g,VertexType v1,VertexType v2) {
	int p1 = GetVerNodePos(g, v1); //��ȡv1��λ��
	int p2 = GetVerNodePos(g, v2);
	if (p1 == -1 || p2 == -1)
		return;

	EdgeNode* p, * q = NULL;  //q �����ݴ�Ҫɾ�����ڽӵ��ǰ��

	//����ͼ��˫��ģ�������Ҫɾ��������Եı�
	//ɾ��v1 -- > v2�ı�
	p = g->adjList[p1].firstArc;  //pָ��p1����ĵ�һ���ڽӵ�
	while (p != NULL && p->dest != p2)
	{
		//��p1����������в���p2���㣬�ҵ�p2���㣬��ʱqָ��p2�����ǰ��
		q = p;
		p = p->next;
	}
	if (p == NULL)  //pָ��p1����ĵ�һ���ڽӵ㣬���pΪNULL����˵��p1û���ڽӱ�
		return;
	// �ж��ҵ��Ľ���Ƿ��������ڵĵ�һ�����
	if (q == NULL)
		g->adjList[p1].firstArc = p->next;//ɾ��ͷ���
	else
		q->next = p->next;//ֱ��ɾ�� 
	free(p);  //�ͷſռ�

	//ɾ��p2 -> p1�ı�
	q = NULL;
	p = g->adjList[p2].firstArc;  //pָ��p2����ĵ�һ���ڽӵ�
	while (p->dest != p1)
	{//��p2����������в���p1�Ķ��㣬�ҵ�p1���㣬��ʱqָ��p1�����ǰ��
		q = p;
		p = p->next;
	}
	if (q == NULL)
		g->adjList[p2].firstArc = p->next; //q�պ�Ϊp2����ĵ�һ���ڽӵ�
	else
		q->next = p->next;
	free(p);

	g->NumEdges--;
}

//��ȡ��һ���ڽӶ���
int GetFirstAdjNeighbor(AdjGraph *g,VertexType v) {
	int p = GetVerNodePos(g,v); //��ȡ����vertex��λ��
	if (p == -1)
		return -1;
	
	EdgeNode* q = g->adjList[p].firstArc;  //qΪ����v�ĵ�һ���ڽӶ���
	if (q != NULL)
		return q->dest;   //�����ڽӶ�����±�
	return-1;
}

//��ȡ�ڽӶ������һ�����㣺��ȡ����v1���ڽӶ��㣬���ڽӶ�����v1���ڽӶ���v2����һ��
int GetNextAdjNeighbor(AdjGraph *g,VertexType v1, VertexType v2) {
	int p1 = GetVerNodePos(g, v1); //��ȡ����v1��λ��
	int p2 = GetVerNodePos(g, v2); //��ȡ����v2��λ��

	EdgeNode* p = g->adjList[p1].firstArc;  //pΪ����v1�ĵ�һ���ڽӶ���
	while (p != NULL && p->dest != p2) //�������в��ҵ�ָ��v2����Ľ��λ��
		p = p->next;
	if (p != NULL && p->next != NULL)
		return p->next->dest;  //�ҵ�����ô������һ��������������ڽӶ���
	return -1;
}

//����ͼ
void DestroyAdjGraph(AdjGraph *g) {
	EdgeNode* p;
	//�ͷ�ÿһ������ָ�������ռ�
	for (int i = 0; i < g->NumVertices; i++)
	{
		p = g->adjList[i].firstArc;
		while (p != NULL)
		{
			g->adjList[i].firstArc = p->next;
			free(p);
			p = g->adjList[i].firstArc;
		}
	}
	//�ͷŴ�Ŷ���Ŀռ�
	free(g->adjList);
	g->adjList = NULL; //��ֹ����Ұָ��
	g->NumEdges = g->MaxVertices = g->NumVertices = 0;
}


int main_adj() {
	int i, j, k,num;
	VertexType a, b, c, d, e, v, v1;
	
	AdjGraph g;
	InitAdjGraph(&g);
	//��Ӷ���
	for (i = 0; i < 5; i++)
	{
		v = 'a' + i;
		InsertAdjVertex(&g,v);
	}

	//�����
	a = 'a';
	b = 'b';
	c = 'c';
	d = 'd';
	e = 'e';
	InsertAdjEdge(&g, a, b);
	InsertAdjEdge(&g, a, c);
	InsertAdjEdge(&g, a, d);
	InsertAdjEdge(&g, b, c);
	InsertAdjEdge(&g, b, e);
	InsertAdjEdge(&g, c, d);
	InsertAdjEdge(&g, c, e);
	InsertAdjEdge(&g, d, e);

	i = GetVerNodePos(&g, d);
	printf("%d\n", i);

	printf("�ڽӱ�:\n");
	ShowAdjGraph(g);

	j = GetFirstAdjNeighbor(&g, a);
	printf("%c�ĵ�һ���ڽӶ��㣺%c\n", b, g.adjList[j].data);

	k = GetNextAdjNeighbor(&g,a, g.adjList[j].data);
	printf("%c �� %c ����һ���ڽӶ��㣺%c\n", a, g.adjList[j].data, g.adjList[k].data);

	//ɾ����
	removeAdjEdge(&g,a,b);

	printf("�ڽӱ�:\n");
	ShowAdjGraph(g);
	
	return 0;
}
