#define _CRT_SECURE_NO_WARNINGS 1
#include "Graph.h"   //引入自己定义的头文件

Boolean visited[Default_Vertex_Size]; /* 访问标志的数组 */

//邻接表深度优先遍历：给出遍历的图g和起始顶点v
void DFS_adj(AdjGraph* g, int v, Boolean visited[]) {

	printf("%c-->", GetVerNodeValue(g, v));
	visited[v] = TRUE;  //为访问过的顶点做上标记
	int w = GetFirstAdjNeighbor(g, GetVerNodeValue(g, v)); //获取第一个邻接顶点
	while (w != -1) {
		//当邻接顶点未被访问
		if (!visited[w]) {
			DFS_adj(g, w, visited);//以该顶点为起始顶点进行深度优先遍历
		}
		//（如果该顶点未被访问，那么下一轮将以该顶点为起始顶点进行深度优先遍历）
		w = GetNextAdjNeighbor(g, GetVerNodeValue(g, v), GetVerNodeValue(g, w));
	}
}

//邻接表广度优先遍历：g:图  v:初始点  visited:标记数组
void BFS_adj(AdjGraph* g, int v, Boolean visited[]) {

	int w;  //w暂存邻接顶点
	Queue Q;
	InitQueue(&Q);

	printf("%c==>", GetVerNodeValue(g,v));
	visited[v] = TRUE;
	EnQueue(&Q,v);   //起始点入队

	while (! QueueEmpty(Q))
	{
		DeQueue(&Q, &v);	//出栈，并获取首顶点
		w = GetFirstAdjNeighbor(g,GetVerNodeValue(g,v));  //获取第一个邻接顶点
		while (w != -1) {
			if (!visited[w]) {	//当该邻接顶点未被访问
				printf("%c==>", GetVerNodeValue(g, w));
				visited[w] = TRUE;
				EnQueue(&Q,w);		//将该顶点入队，为之后访问该顶点的邻接顶点做铺垫
			}
			//获取顶点v的下一个邻接顶点（该邻接顶点的顺序在前面访问过邻接顶点w之后）
			w = GetNextAdjNeighbor(g,GetVerNodeValue(g,v),GetVerNodeValue(g,w));
		}
	}	
};

//非连通图深度优先遍历
void NonUnicomDFS_adj(AdjGraph* g, int v, Boolean visited[]) {
	//对非连通图g做深度优先遍历
	int count = g->NumVertices;
	int j;
	for (int i = v; i < v + count; i++) {
		j = (i + count) % count;  //采用循环队列思想定义j，避免数组越界
		if (!visited[j])
			DFS_adj(g, j, visited);
	}
};

//非连通图广度优先遍历
void NonUnicomBFS_adj(AdjGraph* g, int v, Boolean visited[]) {
	int count = g->NumVertices;
	int j;
	for (int i = v; i < v + count; i++) {
		j = (i + count) % count;  //采用循环队列思想定义j，避免数组越界
		if (!visited[j])
			BFS_adj(g, j, visited);
	}
};

int main_adjFB() {

	int i, j, k, num;
	VertexType a, b, c, d, e, f, g1, h, i1, j1,v, v1;

	AdjGraph g;
	InitAdjGraph(&g);
	//添加顶点
	for (i = 0; i < 10; i++)  //插入10个元素
	{
		v = 'a' + i;
		InsertAdjVertex(&g, v);
	}

	//插入边构成图
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

	printf("邻接表:\n");
	ShowAdjGraph(g);

	num = g.NumVertices;
	visited[num] = visited;

	printf("=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)
			visited[i] = FALSE;

		printf("\n邻接表的深度优先遍历:");
		DFS_adj(&g, j, visited);
	}

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //重新置零
			visited[i] = FALSE;
		printf("\n%d  邻接表的深度优先遍历:",j);
		BFS_adj(&g, j, visited);
	}

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //重新置零
			visited[i] = FALSE;
		printf("\n%d  (非连通图)邻接表的深度优先遍历:",j);
		NonUnicomDFS_adj(&g, j, visited);
	}

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //重新置零
			visited[i] = FALSE;
		printf("\n%d  (非连通图)邻接表的广度优先遍历:",j);
		NonUnicomBFS_adj(&g, j, visited);
	}

	return 0;
}