#ifndef _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define GRAPH_INFINITY 65535 /* 用65535来代表∞ */
#define Default_Vertex_Size  10	/*设置默认的顶点个数*/
#define MAXSIZE 10 /* 数组存储空间初始分配量 */


typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义  */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */
typedef int Boolean; /* Boolean是布尔类型,其值是TRUE或FALSE */


/*======================邻接矩阵结构与函数声明======================*/
typedef struct GraphMtx GraphMtx;  /*声明邻接矩阵*/
void InitGraph(GraphMtx* g);  /*邻接矩阵初始化*/
int GetVertexPos(GraphMtx* g, VertexType v); /*邻接矩阵获取顶点的位置*/
void ShowGraph(GraphMtx g);		/*邻接矩阵打印图信息*/
void InsertVertex(GraphMtx* g, VertexType v);		/*邻接矩阵插入顶点*/
void RemoveEdge(GraphMtx* g, VertexType v1, VertexType v2);  /*邻接矩阵删除边*/
void RemoveVertex(GraphMtx* g, VertexType v);	 /*邻接矩阵删除顶点*/
int  GetFirstNeighbor(GraphMtx* g, VertexType v);  /*邻接矩阵获取v第一个邻接顶点*/
int  GetNextNeighbor(GraphMtx* g, VertexType v, VertexType w);/*邻接矩阵获取下一个邻接顶点(下标)：获取顶点v下一个邻接顶点w的邻接顶点*/
void DestroyGraph(GraphMtx* g);	 /*销毁邻接矩阵*/
VertexType GetVertexValue(GraphMtx* g, int v);  /*访问顶点获取值*/

/*======================邻接表结构与函数声明======================*/
//typedef struct EdgeNode EdgeNode; //边结构
//typedef struct VerNode VerNode, * Vertex;	//顶点结构
//typedef struct AdjGraph AdjGraph;	//邻接表(无向图)
//void InitAdjGraph(AdjGraph* g);		/*邻接表初始化*/
//边结构
typedef struct EdgeNode {
	int dest;//存放顶点下标
	struct EdgeNode* next; //指向下个边结构指针
	//EdgeType weight; //权,用于网
}EdgeNode;

//顶点结构
typedef struct VerNode {
	VertexType data; //顶点数据
	EdgeNode* firstArc;  //指向边结构指针
}VerNode, * Vertex;

//邻接表(无向图)
typedef struct AdjGraph {
	int MaxVertices; //最大顶点个数
	int NumVertices; //实际顶点个数
	int NumEdges;  //边的条数

	Vertex adjList; //指向顶点结构表
}AdjGraph;

int GetVerNodePos(AdjGraph* g, VertexType v);  /*获取顶点位置*/
void ShowAdjGraph(AdjGraph g);		/*打印图*/
void InsertAdjVertex(AdjGraph* g, VertexType v);	/*插入顶点*/
void InsertAdjEdge(AdjGraph* g, VertexType v1, VertexType v2);		/*插入边：在顶点vertex1和vertex2之间插入一条边*/
void removeAdjEdge(AdjGraph* g, VertexType v1, VertexType v2);		/*删除边,删除顶点v1和顶点v2之间的边*/
int GetFirstAdjNeighbor(AdjGraph* g, VertexType v);		/*获取第一个邻接顶点*/
int GetNextAdjNeighbor(AdjGraph* g, VertexType v1, VertexType v2);	/*获取邻接顶点的下一个顶点：获取顶点v1的邻接顶点，该邻接顶点在v1与邻接顶点v2的下一个*/
void DestroyAdjGraph(AdjGraph* g);		/*销毁图*/
VertexType GetVerNodeValue(AdjGraph* g, int v);   /*获取顶点值*/
/* ****************************************************** */

/*======================深度优先遍历(连通图遍历)======================*/
void DFS(GraphMtx* g, int v, Boolean visited[]);	//邻接矩阵深度优先遍历:  g:图  v:初始点    visited:标记数组
void BFS(GraphMtx* g, int v, Boolean visited[]);	//邻接矩阵广度优先遍历：g:图  v:初始点  visited:标记数组

void DFS_adj(AdjGraph* g, int v, Boolean visited[]); //邻接表深度优先遍历：给出遍历的图g和起始顶点v
void BFS_adj(AdjGraph* g, int v, Boolean visited[]); //邻接表广度优先遍历：g:图  v:初始点  visited:标记数组

/*======================深度优先遍历(非连通图遍历)======================*/
void NonUnicomDFS(GraphMtx* g, int v, Boolean visited[]);
void NonUnicomBFS(GraphMtx* g, int v, Boolean visited[]);

void NonUnicomDFS_adj(AdjGraph* g, int v, Boolean visited[]);
void NonUnicomBFS_adj(AdjGraph* g, int v, Boolean visited[]); 

/*======================队列结构与函数声明======================*/
/* 循环队列的顺序存储结构 */
typedef struct Queue
{
	int data[MAXSIZE];
	int front;    	/* 头指针 */
	int rear;		/* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
}Queue;

typedef struct Queue Queue;
Status InitQueue(Queue* Q);	/* 初始化一个空队列Q */
Status QueueEmpty(Queue Q);	/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status EnQueue(Queue* Q, int e); /* 若队列未满，则插入元素e为Q新的队尾元素 */
Status DeQueue(Queue* Q, int* e); /* 若队列不空，则删除Q中队头元素，用e返回其值 */


#endif // !_GRAPH_H_
