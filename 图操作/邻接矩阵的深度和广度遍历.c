#define _CRT_SECURE_NO_WARNINGS 1
#include "Graph.h"   //引入自己定义的头文件

Boolean visited[Default_Vertex_Size]; /* 访问标志的数组 */

 /*邻接矩阵结构*/
typedef struct GraphMtx
{
	int MaxVertices; //最大顶点数
	int NumVertices; //真实的顶点数
	int NumEdges; //边数
	VertexType* VerticesList; //顶点列表
	int** Edge; //边信息矩阵
}GraphMtx;


/* 用到的队列结构与函数********************************** */

/* 初始化一个空队列Q */
Status InitQueue(Queue* Q)
{
	Q->front = 0;
	Q->rear = 0;
	return  OK;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(Queue Q)
{
	if (Q.front == Q.rear) /* 队列空的标志 */
		return TRUE;
	else
		return FALSE;
}

/* 若队列未满，则插入元素e为Q新的队尾元素 */
Status EnQueue(Queue* Q, int e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)	/* 队列满的判断 */
		return ERROR;
	Q->data[Q->rear] = e;			/* 将元素e赋值给队尾 */
	Q->rear = (Q->rear + 1) % MAXSIZE;/* rear指针向后移一位置， */
								/* 若到最后则转到数组头部 */
	return  OK;
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
Status DeQueue(Queue* Q, int* e)
{
	if (Q->front == Q->rear)			/* 队列空的判断 */
		return ERROR;
	*e = Q->data[Q->front];				/* 将队头元素赋值给e */
	Q->front = (Q->front + 1) % MAXSIZE;	/* front指针向后移一位置， */
									/* 若到最后则转到数组头部 */
	return  OK;
}
/* ****************************************************** */


//深度优先遍历:  g:图  v:初始点    visited:标记数组
void DFS(GraphMtx* g,int v,Boolean visited[]) {
	//访问顶点，获取值，打印
	printf("%c-->", GetVertexValue(g,v));
	visited[v] = TRUE;  //为访问过的顶点做上标记
	int w = GetFirstNeighbor(g,GetVertexValue(g,v));//获取第一个邻接顶点下标
	while (w != -1)
	{	//当邻接顶点未被访问
		if (!visited[w])
			DFS(g,w,visited);	//以该顶点为起始顶点进行深度优先遍历
		/*
		针对于非连通图
		对第一个邻接顶点深度优先遍历完成，获取下一个邻接顶点的位置
		（如果该顶点未被访问，那么下一轮将以该顶点为起始顶点进行深度优先遍历）
		*/
		w = GetNextNeighbor(g, GetVertexValue(g, v), GetVertexValue(g, w));
	}
}

//广度优先遍历：g:图  v:初始点  visited:标记数组
void BFS(GraphMtx* g, int v, Boolean visited[]) {

	int w;  //w暂存邻接顶点
	Queue Q;  //创建循环链表
	InitQueue(&Q);

	//访问初始点
	printf("%c==>", GetVertexValue(g, v));
	visited[v] = TRUE;
	EnQueue(&Q,v);  //起始点进队
	
	while (!QueueEmpty(Q)) { //队列中存有顶点
		DeQueue(&Q,&v);  //出栈，并获取首顶点
		w = GetFirstNeighbor(g,GetVertexValue(g,v));  //获取第一个邻接顶点
		while (w != -1) {	  //存在邻接顶点
			if (!visited[w]) {//当该邻接顶点未被访问
				printf("%c==>", GetVertexValue(g,w));
				visited[w] = TRUE;  //标记为已访问
				EnQueue(&Q,w);	//将该顶点入队，为之后访问该顶点的邻接顶点做铺垫
			}
			//获取顶点v的下一个邻接顶点（该邻接顶点的顺序在前面访问过邻接顶点w之后）
			w = GetNextNeighbor(g,GetVertexValue(g,v),GetVertexValue(g,w));
		}
	}
}

//非连通图深度优先遍历
void NonUnicomDFS(GraphMtx* g, int v, Boolean visited[]) {
	int count = g->NumVertices;
	int i, j;
	for (i = v; i < v + count; i++) {
		j = (i + count) % count;  //采用循环队列思想定义j，避免数组越界
		if (!visited[j])
			DFS(g, j, visited);;
	}
};

//非连通图广度优先遍历
void NonUnicomBFS(GraphMtx* g, int v, Boolean visited[]) {
	int count = g->NumVertices;
	int i,j;
	for ( i = v; i < v + count; i++) {
		j = (i + count) % count;  //采用循环队列思想定义j，避免数组越界
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

	//添加顶点
	for (i = 0; i < num; i++)
	{
		v = 'a' + i;
		InsertVertex(&g, v);
		visited[i] = FALSE;  //初始全部为0，没有被访问过
	}

	for ( i = 0; i < num; i++)
	{
		printf("%c--", visited[i]);
	}

	printf("%c-->\n", GetVertexValue(&g, 1));

	//插入边
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

	printf("邻接矩阵:\n");
	ShowGraph(g);

	//使用深度遍历
	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //重新置零
			visited[i] = FALSE;
		printf("\n%d  邻接矩阵的深度优先遍历:", j);
		DFS(&g, j, visited);
	}


	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //重新置零
			visited[i] = FALSE;
		printf("\n%d  邻接矩阵的广度优先遍历:", j);
		BFS(&g, j, visited);
	}
	

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //重新置零
			visited[i] = FALSE;
		printf("\n%d  (非连通图)邻接矩阵的深度优先遍历:", j);
		NonUnicomDFS(&g, j, visited);
	}

	printf("\n=======================================");
	for (int j = 0; j < num; j++)
	{
		for (int i = 0; i < num; i++)  //重新置零
			visited[i] = FALSE;
		printf("\n%d  (非连通图)邻接矩阵的广度优先遍历:", j);
		NonUnicomBFS(&g, j, visited);
	}
	
	return 0;
}