#define _CRT_SECURE_NO_WARNINGS 1
#include "Graph.h"   //引入自己定义的头文件

 /*邻接矩阵结构*/
typedef struct GraphMtx
{
	int MaxVertices; //最大顶点数
	int NumVertices; //真实的顶点数
	int NumEdges; //边数
	VertexType* VerticesList; //顶点列表
	int** Edge; //边信息矩阵
}GraphMtx;


//初始化
void InitGraph(GraphMtx *g) {
	g->MaxVertices = Default_Vertex_Size;  //初始化最大边数
	g->NumVertices = g->NumEdges = 0; //初始化顶点数和边数

	//分配顶点储存空间列表
	g->VerticesList = (VertexType*)malloc(sizeof(VertexType)*(g->MaxVertices));
	assert(g->VerticesList != NULL);

	//开辟边信息存储矩阵的空间（二维数组的动态开辟）
	g->Edge = (int**)malloc(sizeof(int*)*g->MaxVertices);  //总行数开辟
	assert(g->Edge != NULL);
	//每一行内具体的空间开辟
	for (int i = 0; i < g->MaxVertices; i++)
	{
		g->Edge[i] = (int*)malloc(sizeof(int) * g->MaxVertices);
	}
	for (int i = 0; i < g->MaxVertices;i++) {
		for (int j = 0; j < g->MaxVertices;j++) {
			g->Edge[i][j] = 0;		//初始设置为0
		}
	}
}

//获取顶点的位置
int GetVertexPos(GraphMtx *g,VertexType v) {

	for (int i = 0; i < g->MaxVertices; i++) {
		if (g->VerticesList[i] == v)
			return i;
	}
	return -1;  
}

//访问顶点获取值
VertexType GetVertexValue(GraphMtx *g,int v) {
	return g->VerticesList[v];
}

// 打印图信息
void ShowGraph(GraphMtx g) {
	printf("   ");
	//获取顶点，并打印
	for (int i = 0; i < g.NumVertices; i++)
		printf("%c  ",g.VerticesList[i]);
	printf("\n");
	//获取边，并打印
	for (int i = 0; i < g.NumVertices;i++) {
		printf("%c  ", g.VerticesList[i]);
		for (int j = 0; j < g.NumVertices; j++) {
			printf("%d  ", g.Edge[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//插入顶点
void InsertVertex(GraphMtx *g,VertexType v) {
	if (g->NumVertices >= g->MaxVertices)//判断顶点空间是否已满
		return;
	g->VerticesList[g->NumVertices++] = v; //将v放入VerticesList
}

//插入边：在v1和v2顶点间插入边
void InsertEdge(GraphMtx *g,VertexType v1,VertexType v2) {
	int p1 = GetVertexPos(g, v1); //获取v1顶点位置
	int p2 = GetVertexPos(g, v2); //获取v2顶点位置
	if (p1 == -1 || p2 == -1)
		return;
	if (g->Edge[p1][p2] != 0)	//边已存在
		return;
	//无向图存储是双向
	g->Edge[p1][p2] = g->Edge[p2][p1] = 1;
	g->NumEdges++;  //记录实际边数
}

//删除边
void RemoveEdge(GraphMtx *g,VertexType v1,VertexType v2) {
	//求出两个顶点的下标位置
	int p1 = GetVertexPos(g, v1); //获取v1顶点位置
	int p2 = GetVertexPos(g, v2); //获取v2顶点位置

	if (p1 == -1 || p2 == -1)
		return;
	if (g->Edge[p1][p2] == 0)	//边不存在
		return;
	//清空
	g->Edge[p1][p2] = g->Edge[p2][p1] = 0;
	g->NumEdges--;  //记录实际边数
}

//删除顶点
void RemoveVertex(GraphMtx *g,VertexType v) {
	int p = GetVertexPos(g,v);
	int i,j;
	if (p == -1)
		return;
	//释放顶点
	int numedge = 0;
	//将要释放顶点之后的顶点逐一前移
	for (i = p; i < g->MaxVertices - 1; i++)
		g->VerticesList[i] = g->VerticesList[i + 1];
	//统计与要删除顶点相连的边条数
	for (i = 0; i < g->NumVertices; i++) {
		if (g->Edge[p][i] != 0)
			numedge++;
	}
	//删除与释放顶点相连的边（更改存放边信息的矩阵）
	for (i = p; i < g->NumVertices - 1; i++) {// 删除行
		//将要删除行之后的行逐一向前移动一行
		for (j = 0; j < g->NumVertices; j++)
			g->Edge[i][j] = g->Edge[i + 1][j];
	}
	for (i = p; i < g->NumVertices;i++ ) {//删除列
		//将要删除列之后的列逐一向前移动一列
		for (j = 0; j < g->NumVertices; j++) {
			g->Edge[j][i] = g->Edge[j][i + 1];
		}
	}
	g->NumVertices--;
	g->NumEdges = numedge;
}

//获取v第一个邻接顶点（下标）
int  GetFirstNeighbor(GraphMtx* g, VertexType v)
{
	//获取顶点v所在位置
	int p = GetVertexPos(g, v);
	if (p == -1)
		return -1;
	//对顶点进行搜索，看那个顶点与v相连
	for (int i = 0; i < g->NumVertices; ++i)
	{
		if (g->Edge[p][i] == 1)//判断是否，找到
			return i;//找到即返回
	}
	return -1;
}


//获取下一个邻接顶点(下标)：获取顶点v下一个邻接顶点w的邻接顶点
int  GetNextNeighbor(GraphMtx* g, VertexType v, VertexType w)
{
	//获取v和w所在位置
	int pv = GetVertexPos(g, v);
	int pw = GetVertexPos(g, w);
	if (pv == -1 || pw == -1)
		return -1;
	//从v的邻接顶点w的位置向后搜索，找到第一个与v相邻的顶点，即所求
	for (int i = pw + 1; i < g->NumVertices; ++i)
	{
		if (g->Edge[pv][i] == 1)
			return i;
	}
	return -1;
}

//销毁图
void DestroyGraph(GraphMtx* g)
{	//释放顶点
	free(g->VerticesList);
	g->VerticesList = NULL;
	//释放边存储结构的列
	for (int i = 0; i < g->NumVertices; ++i)
	{
		free(g->Edge[i]);
	}
	free(g->Edge);//释放存放行指针的空间
	g->Edge = NULL;
	g->MaxVertices = g->NumEdges = g->NumVertices = 0;
}


int main_graph()
{
	GraphMtx g;
	int i, j,k;
	VertexType a, b, c, d, e,v, v1;
	InitGraph(&g);

	//添加顶点
	for ( i = 0; i < 5; i++)
	{
		v = 'a' + i;
		InsertVertex(&g,v);
	}

	//插入边
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
	
	printf("邻接矩阵:\n");
	ShowGraph(g);

	//删除边
	RemoveEdge(&g, c, d);   
	//删除顶点
	RemoveVertex(&g, e);

	printf("邻接矩阵:\n");
	ShowGraph(g);

	i = GetVertexPos(&g,b);
	printf("数：%d\n", i);

	j = GetFirstNeighbor(&g, a);
	printf("%c的第一个邻接顶点：%c\n", a, g.VerticesList[j]);


	k = GetNextNeighbor(&g, a, g.VerticesList[j]);
	printf("%c 和 %c 的下一个邻接顶点：%c\n", a,g.VerticesList[j],g.VerticesList[k]);

	//销毁图
	DestroyGraph(&g);
	printf("邻接矩阵:\n");
	ShowGraph(g);

	return 0;
}
