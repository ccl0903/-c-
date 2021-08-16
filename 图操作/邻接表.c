#define _CRT_SECURE_NO_WARNINGS 1
#include "Graph.h"   //引入自己定义的图头文件

Boolean visited[Default_Vertex_Size]; /* 访问标志的数组 */


//初始化
void InitAdjGraph(AdjGraph *g) {
	g->MaxVertices = Default_Vertex_Size;
	g->NumEdges = g->NumVertices = 0;
	//为顶点结构表开辟空间
	g->adjList = (Vertex)malloc(sizeof(VerNode)*g->MaxVertices);
	assert(g->adjList != NULL);
	for (int i = 0; i < g->MaxVertices; i++)
		g->adjList[i].firstArc = NULL;  
}

// 获取顶点位置
int GetVerNodePos(AdjGraph *g,VertexType v){
	for (int i = 0; i < g->NumVertices; i++)
	{
		if (g->adjList[i].data == v)
			return i;
	}
	return -1;
}

//获取顶点值
VertexType GetVerNodeValue(AdjGraph *g,int v) {
	return g->adjList[v].data;
}

//打印图
void ShowAdjGraph(AdjGraph g) {
	EdgeNode* p;
	for (int i = 0; i < g.NumVertices; i++) //对顶点进行遍历
	{
		printf("%d  %c:>", i, g.adjList[i].data);//输出顶点
		p = g.adjList[i].firstArc; //指向边结构
		while (p != NULL)
		{
			printf("%d-->", p->dest);
			p = p->next;
		}
		printf("Nul.\n");
	}
	printf("\n");
}

//插入顶点
void InsertAdjVertex(AdjGraph *g,VertexType v) {
	//判断顶点表是否已满
	if (g->NumVertices >= g->MaxVertices)
		return;
	g->adjList[g->NumVertices++].data = v;  //插入
}

//插入边：在顶点vertex1和vertex2之间插入一条边
void InsertAdjEdge(AdjGraph *g,VertexType v1,VertexType v2) {
	int p1 = GetVerNodePos(g, v1); //获取v1的位置
	int p2 = GetVerNodePos(g, v2);
	if (p1 == -1 || p2 == -1)
		return;

	EdgeNode* s1,* s2;
	//无向图是双向的插入要两次
	//插入V1 --> V2的边 头插法插入
	s1 = (EdgeNode*)malloc(sizeof(EdgeNode)); // s1指向p1顶点的第一个邻接点
	assert(s1 != NULL);
	s1->dest = p2;
	s1->next = g->adjList[p1].firstArc;  
	g->adjList[p1].firstArc = s1;

	//插入V2 --> V1的边 头插法插入
	s2 = (EdgeNode*)malloc(sizeof(EdgeNode));
	assert(s2!=NULL);
	s2->dest = p1;
	s2->next = g->adjList[p2].firstArc;
	g->adjList[p2].firstArc = s2;

	g->NumEdges++;
}

// 删除边,删除顶点v1和顶点v2之间的边
void removeAdjEdge(AdjGraph *g,VertexType v1,VertexType v2) {
	int p1 = GetVerNodePos(g, v1); //获取v1的位置
	int p2 = GetVerNodePos(g, v2);
	if (p1 == -1 || p2 == -1)
		return;

	EdgeNode* p, * q = NULL;  //q 用于暂存要删除的邻接点的前驱

	//无向图是双向的，所以需要删除两边相对的边
	//删除v1 -- > v2的边
	p = g->adjList[p1].firstArc;  //p指向p1顶点的第一个邻接点
	while (p != NULL && p->dest != p2)
	{
		//从p1后面的链表中查找p2顶点，找到p2顶点，此时q指向p2顶点的前驱
		q = p;
		p = p->next;
	}
	if (p == NULL)  //p指向p1顶点的第一个邻接点，如果p为NULL，则说明p1没有邻接边
		return;
	// 判断找到的结点是否是链表内的第一个结点
	if (q == NULL)
		g->adjList[p1].firstArc = p->next;//删除头结点
	else
		q->next = p->next;//直接删除 
	free(p);  //释放空间

	//删除p2 -> p1的边
	q = NULL;
	p = g->adjList[p2].firstArc;  //p指向p2顶点的第一个邻接点
	while (p->dest != p1)
	{//从p2后面的链表中查找p1的顶点，找到p1顶点，此时q指向p1顶点的前驱
		q = p;
		p = p->next;
	}
	if (q == NULL)
		g->adjList[p2].firstArc = p->next; //q刚好为p2顶点的第一个邻接点
	else
		q->next = p->next;
	free(p);

	g->NumEdges--;
}

//获取第一个邻接顶点
int GetFirstAdjNeighbor(AdjGraph *g,VertexType v) {
	int p = GetVerNodePos(g,v); //获取顶点vertex的位置
	if (p == -1)
		return -1;
	
	EdgeNode* q = g->adjList[p].firstArc;  //q为顶点v的第一个邻接顶点
	if (q != NULL)
		return q->dest;   //返回邻接顶点的下标
	return-1;
}

//获取邻接顶点的下一个顶点：获取顶点v1的邻接顶点，该邻接顶点在v1与邻接顶点v2的下一个
int GetNextAdjNeighbor(AdjGraph *g,VertexType v1, VertexType v2) {
	int p1 = GetVerNodePos(g, v1); //获取顶点v1的位置
	int p2 = GetVerNodePos(g, v2); //获取顶点v2的位置

	EdgeNode* p = g->adjList[p1].firstArc;  //p为顶点v1的第一个邻接顶点
	while (p != NULL && p->dest != p2) //从链表中查找到指向v2顶点的结点位置
		p = p->next;
	if (p != NULL && p->next != NULL)
		return p->next->dest;  //找到，那么它的下一个结点就是所求的邻接顶点
	return -1;
}

//销毁图
void DestroyAdjGraph(AdjGraph *g) {
	EdgeNode* p;
	//释放每一个顶点指向的链表空间
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
	//释放存放顶点的空间
	free(g->adjList);
	g->adjList = NULL; //防止生成野指针
	g->NumEdges = g->MaxVertices = g->NumVertices = 0;
}


int main_adj() {
	int i, j, k,num;
	VertexType a, b, c, d, e, v, v1;
	
	AdjGraph g;
	InitAdjGraph(&g);
	//添加顶点
	for (i = 0; i < 5; i++)
	{
		v = 'a' + i;
		InsertAdjVertex(&g,v);
	}

	//插入边
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

	printf("邻接表:\n");
	ShowAdjGraph(g);

	j = GetFirstAdjNeighbor(&g, a);
	printf("%c的第一个邻接顶点：%c\n", b, g.adjList[j].data);

	k = GetNextAdjNeighbor(&g,a, g.adjList[j].data);
	printf("%c 和 %c 的下一个邻接顶点：%c\n", a, g.adjList[j].data, g.adjList[k].data);

	//删除边
	removeAdjEdge(&g,a,b);

	printf("邻接表:\n");
	ShowAdjGraph(g);
	
	return 0;
}
