#define _CRT_SECURE_NO_WARNINGS 1
#include "Graph.h"   //�����Լ������ͷ�ļ�

 /*�ڽӾ���ṹ*/
typedef struct GraphMtx
{
	int MaxVertices; //��󶥵���
	int NumVertices; //��ʵ�Ķ�����
	int NumEdges; //����
	VertexType* VerticesList; //�����б�
	int** Edge; //����Ϣ����
}GraphMtx;


//��ʼ��
void InitGraph(GraphMtx *g) {
	g->MaxVertices = Default_Vertex_Size;  //��ʼ��������
	g->NumVertices = g->NumEdges = 0; //��ʼ���������ͱ���

	//���䶥�㴢��ռ��б�
	g->VerticesList = (VertexType*)malloc(sizeof(VertexType)*(g->MaxVertices));
	assert(g->VerticesList != NULL);

	//���ٱ���Ϣ�洢����Ŀռ䣨��ά����Ķ�̬���٣�
	g->Edge = (int**)malloc(sizeof(int*)*g->MaxVertices);  //����������
	assert(g->Edge != NULL);
	//ÿһ���ھ���Ŀռ俪��
	for (int i = 0; i < g->MaxVertices; i++)
	{
		g->Edge[i] = (int*)malloc(sizeof(int) * g->MaxVertices);
	}
	for (int i = 0; i < g->MaxVertices;i++) {
		for (int j = 0; j < g->MaxVertices;j++) {
			g->Edge[i][j] = 0;		//��ʼ����Ϊ0
		}
	}
}

//��ȡ�����λ��
int GetVertexPos(GraphMtx *g,VertexType v) {

	for (int i = 0; i < g->MaxVertices; i++) {
		if (g->VerticesList[i] == v)
			return i;
	}
	return -1;  
}

//���ʶ����ȡֵ
VertexType GetVertexValue(GraphMtx *g,int v) {
	return g->VerticesList[v];
}

// ��ӡͼ��Ϣ
void ShowGraph(GraphMtx g) {
	printf("   ");
	//��ȡ���㣬����ӡ
	for (int i = 0; i < g.NumVertices; i++)
		printf("%c  ",g.VerticesList[i]);
	printf("\n");
	//��ȡ�ߣ�����ӡ
	for (int i = 0; i < g.NumVertices;i++) {
		printf("%c  ", g.VerticesList[i]);
		for (int j = 0; j < g.NumVertices; j++) {
			printf("%d  ", g.Edge[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//���붥��
void InsertVertex(GraphMtx *g,VertexType v) {
	if (g->NumVertices >= g->MaxVertices)//�ж϶���ռ��Ƿ�����
		return;
	g->VerticesList[g->NumVertices++] = v; //��v����VerticesList
}

//����ߣ���v1��v2���������
void InsertEdge(GraphMtx *g,VertexType v1,VertexType v2) {
	int p1 = GetVertexPos(g, v1); //��ȡv1����λ��
	int p2 = GetVertexPos(g, v2); //��ȡv2����λ��
	if (p1 == -1 || p2 == -1)
		return;
	if (g->Edge[p1][p2] != 0)	//���Ѵ���
		return;
	//����ͼ�洢��˫��
	g->Edge[p1][p2] = g->Edge[p2][p1] = 1;
	g->NumEdges++;  //��¼ʵ�ʱ���
}

//ɾ����
void RemoveEdge(GraphMtx *g,VertexType v1,VertexType v2) {
	//�������������±�λ��
	int p1 = GetVertexPos(g, v1); //��ȡv1����λ��
	int p2 = GetVertexPos(g, v2); //��ȡv2����λ��

	if (p1 == -1 || p2 == -1)
		return;
	if (g->Edge[p1][p2] == 0)	//�߲�����
		return;
	//���
	g->Edge[p1][p2] = g->Edge[p2][p1] = 0;
	g->NumEdges--;  //��¼ʵ�ʱ���
}

//ɾ������
void RemoveVertex(GraphMtx *g,VertexType v) {
	int p = GetVertexPos(g,v);
	int i,j;
	if (p == -1)
		return;
	//�ͷŶ���
	int numedge = 0;
	//��Ҫ�ͷŶ���֮��Ķ�����һǰ��
	for (i = p; i < g->MaxVertices - 1; i++)
		g->VerticesList[i] = g->VerticesList[i + 1];
	//ͳ����Ҫɾ�����������ı�����
	for (i = 0; i < g->NumVertices; i++) {
		if (g->Edge[p][i] != 0)
			numedge++;
	}
	//ɾ�����ͷŶ��������ıߣ����Ĵ�ű���Ϣ�ľ���
	for (i = p; i < g->NumVertices - 1; i++) {// ɾ����
		//��Ҫɾ����֮�������һ��ǰ�ƶ�һ��
		for (j = 0; j < g->NumVertices; j++)
			g->Edge[i][j] = g->Edge[i + 1][j];
	}
	for (i = p; i < g->NumVertices;i++ ) {//ɾ����
		//��Ҫɾ����֮�������һ��ǰ�ƶ�һ��
		for (j = 0; j < g->NumVertices; j++) {
			g->Edge[j][i] = g->Edge[j][i + 1];
		}
	}
	g->NumVertices--;
	g->NumEdges = numedge;
}

//��ȡv��һ���ڽӶ��㣨�±꣩
int  GetFirstNeighbor(GraphMtx* g, VertexType v)
{
	//��ȡ����v����λ��
	int p = GetVertexPos(g, v);
	if (p == -1)
		return -1;
	//�Զ���������������Ǹ�������v����
	for (int i = 0; i < g->NumVertices; ++i)
	{
		if (g->Edge[p][i] == 1)//�ж��Ƿ��ҵ�
			return i;//�ҵ�������
	}
	return -1;
}


//��ȡ��һ���ڽӶ���(�±�)����ȡ����v��һ���ڽӶ���w���ڽӶ���
int  GetNextNeighbor(GraphMtx* g, VertexType v, VertexType w)
{
	//��ȡv��w����λ��
	int pv = GetVertexPos(g, v);
	int pw = GetVertexPos(g, w);
	if (pv == -1 || pw == -1)
		return -1;
	//��v���ڽӶ���w��λ������������ҵ���һ����v���ڵĶ��㣬������
	for (int i = pw + 1; i < g->NumVertices; ++i)
	{
		if (g->Edge[pv][i] == 1)
			return i;
	}
	return -1;
}

//����ͼ
void DestroyGraph(GraphMtx* g)
{	//�ͷŶ���
	free(g->VerticesList);
	g->VerticesList = NULL;
	//�ͷűߴ洢�ṹ����
	for (int i = 0; i < g->NumVertices; ++i)
	{
		free(g->Edge[i]);
	}
	free(g->Edge);//�ͷŴ����ָ��Ŀռ�
	g->Edge = NULL;
	g->MaxVertices = g->NumEdges = g->NumVertices = 0;
}


int main_graph()
{
	GraphMtx g;
	int i, j,k;
	VertexType a, b, c, d, e,v, v1;
	InitGraph(&g);

	//��Ӷ���
	for ( i = 0; i < 5; i++)
	{
		v = 'a' + i;
		InsertVertex(&g,v);
	}

	//�����
	a = 'a';
	b = 'b';
	c = 'c';
	d = 'd';
	e = 'e';
	InsertEdge(&g, a,b );
	InsertEdge(&g, a, d);
	InsertEdge(&g, b, c);
	InsertEdge(&g, c, d);
	InsertEdge(&g, d, e);
	
	printf("�ڽӾ���:\n");
	ShowGraph(g);

	//ɾ����
	RemoveEdge(&g, c, d);   
	//ɾ������
	RemoveVertex(&g, e);

	printf("�ڽӾ���:\n");
	ShowGraph(g);

	i = GetVertexPos(&g,b);
	printf("����%d\n", i);

	j = GetFirstNeighbor(&g, a);
	printf("%c�ĵ�һ���ڽӶ��㣺%c\n", a, g.VerticesList[j]);


	k = GetNextNeighbor(&g, a, g.VerticesList[j]);
	printf("%c �� %c ����һ���ڽӶ��㣺%c\n", a,g.VerticesList[j],g.VerticesList[k]);

	//����ͼ
	DestroyGraph(&g);
	printf("�ڽӾ���:\n");
	ShowGraph(g);

	return 0;
}
