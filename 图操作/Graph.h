#ifndef _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define GRAPH_INFINITY 65535 /* ��65535������� */
#define Default_Vertex_Size  10	/*����Ĭ�ϵĶ������*/
#define MAXSIZE 10 /* ����洢�ռ��ʼ������ */


typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef char VertexType; /* ��������Ӧ���û�����  */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */
typedef int Boolean; /* Boolean�ǲ�������,��ֵ��TRUE��FALSE */


/*======================�ڽӾ���ṹ�뺯������======================*/
typedef struct GraphMtx GraphMtx;  /*�����ڽӾ���*/
void InitGraph(GraphMtx* g);  /*�ڽӾ����ʼ��*/
int GetVertexPos(GraphMtx* g, VertexType v); /*�ڽӾ����ȡ�����λ��*/
void ShowGraph(GraphMtx g);		/*�ڽӾ����ӡͼ��Ϣ*/
void InsertVertex(GraphMtx* g, VertexType v);		/*�ڽӾ�����붥��*/
void RemoveEdge(GraphMtx* g, VertexType v1, VertexType v2);  /*�ڽӾ���ɾ����*/
void RemoveVertex(GraphMtx* g, VertexType v);	 /*�ڽӾ���ɾ������*/
int  GetFirstNeighbor(GraphMtx* g, VertexType v);  /*�ڽӾ����ȡv��һ���ڽӶ���*/
int  GetNextNeighbor(GraphMtx* g, VertexType v, VertexType w);/*�ڽӾ����ȡ��һ���ڽӶ���(�±�)����ȡ����v��һ���ڽӶ���w���ڽӶ���*/
void DestroyGraph(GraphMtx* g);	 /*�����ڽӾ���*/
VertexType GetVertexValue(GraphMtx* g, int v);  /*���ʶ����ȡֵ*/

/*======================�ڽӱ�ṹ�뺯������======================*/
//typedef struct EdgeNode EdgeNode; //�߽ṹ
//typedef struct VerNode VerNode, * Vertex;	//����ṹ
//typedef struct AdjGraph AdjGraph;	//�ڽӱ�(����ͼ)
//void InitAdjGraph(AdjGraph* g);		/*�ڽӱ��ʼ��*/
//�߽ṹ
typedef struct EdgeNode {
	int dest;//��Ŷ����±�
	struct EdgeNode* next; //ָ���¸��߽ṹָ��
	//EdgeType weight; //Ȩ,������
}EdgeNode;

//����ṹ
typedef struct VerNode {
	VertexType data; //��������
	EdgeNode* firstArc;  //ָ��߽ṹָ��
}VerNode, * Vertex;

//�ڽӱ�(����ͼ)
typedef struct AdjGraph {
	int MaxVertices; //��󶥵����
	int NumVertices; //ʵ�ʶ������
	int NumEdges;  //�ߵ�����

	Vertex adjList; //ָ�򶥵�ṹ��
}AdjGraph;

int GetVerNodePos(AdjGraph* g, VertexType v);  /*��ȡ����λ��*/
void ShowAdjGraph(AdjGraph g);		/*��ӡͼ*/
void InsertAdjVertex(AdjGraph* g, VertexType v);	/*���붥��*/
void InsertAdjEdge(AdjGraph* g, VertexType v1, VertexType v2);		/*����ߣ��ڶ���vertex1��vertex2֮�����һ����*/
void removeAdjEdge(AdjGraph* g, VertexType v1, VertexType v2);		/*ɾ����,ɾ������v1�Ͷ���v2֮��ı�*/
int GetFirstAdjNeighbor(AdjGraph* g, VertexType v);		/*��ȡ��һ���ڽӶ���*/
int GetNextAdjNeighbor(AdjGraph* g, VertexType v1, VertexType v2);	/*��ȡ�ڽӶ������һ�����㣺��ȡ����v1���ڽӶ��㣬���ڽӶ�����v1���ڽӶ���v2����һ��*/
void DestroyAdjGraph(AdjGraph* g);		/*����ͼ*/
VertexType GetVerNodeValue(AdjGraph* g, int v);   /*��ȡ����ֵ*/
/* ****************************************************** */

/*======================������ȱ���(��ͨͼ����)======================*/
void DFS(GraphMtx* g, int v, Boolean visited[]);	//�ڽӾ���������ȱ���:  g:ͼ  v:��ʼ��    visited:�������
void BFS(GraphMtx* g, int v, Boolean visited[]);	//�ڽӾ��������ȱ�����g:ͼ  v:��ʼ��  visited:�������

void DFS_adj(AdjGraph* g, int v, Boolean visited[]); //�ڽӱ�������ȱ���������������ͼg����ʼ����v
void BFS_adj(AdjGraph* g, int v, Boolean visited[]); //�ڽӱ������ȱ�����g:ͼ  v:��ʼ��  visited:�������

/*======================������ȱ���(����ͨͼ����)======================*/
void NonUnicomDFS(GraphMtx* g, int v, Boolean visited[]);
void NonUnicomBFS(GraphMtx* g, int v, Boolean visited[]);

void NonUnicomDFS_adj(AdjGraph* g, int v, Boolean visited[]);
void NonUnicomBFS_adj(AdjGraph* g, int v, Boolean visited[]); 

/*======================���нṹ�뺯������======================*/
/* ѭ�����е�˳��洢�ṹ */
typedef struct Queue
{
	int data[MAXSIZE];
	int front;    	/* ͷָ�� */
	int rear;		/* βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ�� */
}Queue;

typedef struct Queue Queue;
Status InitQueue(Queue* Q);	/* ��ʼ��һ���ն���Q */
Status QueueEmpty(Queue Q);	/* ������QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
Status EnQueue(Queue* Q, int e); /* ������δ���������Ԫ��eΪQ�µĶ�βԪ�� */
Status DeQueue(Queue* Q, int* e); /* �����в��գ���ɾ��Q�ж�ͷԪ�أ���e������ֵ */


#endif // !_GRAPH_H_
