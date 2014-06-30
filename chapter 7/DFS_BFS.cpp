#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "MyHeader.h"

Boolean HaveVisited[MAX_VERTEX_NUM];
Status(*VisitFunc)(int v);


void DFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v)){
	// ��ͼG��������ȱ���
	int v;
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = FALSE;				// ���ʱ�־�����ʼ��
	for (v = 0; v < G.vexnum; ++v){
		if (!visited[v])
			DFS(G, v, visited, Visit);	// ��δ���ʵ��������DFS
	}
}// DFSTraverse

void DFS(ALGraph G, int v, Boolean visited[], Status(*Visit)(ALGraph G, int v)){
	// �ӵ�v����������ݹ��������ȱ���ͼG
	int w;
	visited[v] = TRUE;				// ���ʵ�v�����
	Visit(G, v);
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)){
		if (!visited[w]) DFS(G, w, visited, Visit);	// ��v����δ���ʵ��ڽӶ���w�ݹ����DFS
	}
}// DFS

void BFSTraverse(ALGraph G, Boolean visited[], Status(*Visit)(ALGraph G, int v)){
	// ��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited
	int v, w;
	QElemType u;
	LinkQueue Q;
	for (v = 0; v < G.vexnum; v++)
		visited[v] = FALSE;
	InitQueue(Q);					// �ÿյĸ�������Q
	for (v = 0; v < G.vexnum; v++){
		if (!visited[v]){			// v��δ����
			visited[v] = TRUE;
			Visit(G, v);
			EnQueue(Q, v);			// v�����
			while (!QueueEmpty(Q)){
				DeQueue(Q, u);		// ��ͷԪ�س��Ӳ���Ϊu
				for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)){
					if (!visited[w]){	// wΪu����δ���ʵ��ڽӶ���
						visited[w] = TRUE;
						Visit(G, w);
						EnQueue(Q, w);
					} // if
				} // for
			} // while
		} // if
	} // for
}// BFSTraverse

void DFSForest(ALGraph G, CSTree &T, Boolean visited[]){
	// ��������ͼG�������������ɭ�ֵģ����󣩺��ӣ��ң��ֵ�����T
	int v;
	CSTree p, q;
	q = NULL;
	T = NULL;
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = FALSE;
	for (v = 0; v < G.vexnum; ++v){
		if (!visited[v]){						// ��v����Ϊ�µ��������ĸ����
			p = (CSTree)malloc(sizeof(CSNode));	// ��������
			*p = { GetVex(G, v), NULL, NULL };	// ���ý�㸳ֵ
			if (!T){							// �ǵ�һ���������ĸ���T�ĸ���
				T = p;
			} else{
				q->nextsibling = p;			// �������������ĸ���ǰһ�õĸ��ġ��ֵܡ���
			}
			q = p;								// qָʾ��ǰ�������ĸ�
			DFSTree(G, v, p, visited);			// ������pΪ����������
		}
	}
}// DFSForest

void DFSTree(ALGraph G, int v, CSTree &T, Boolean visited[]){
	// �ӵ�v���������������ȱ���ͼG��������TΪ����������
	int w;
	bool first;
	CSTree p, q;
	q = NULL;
	visited[v] = TRUE;
	first = TRUE;
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)){
		if (!visited[w]){
			p = (CSTree)malloc(sizeof(CSNode));	// ���亢�ӽ��
			*p = { GetVex(G, w), NULL, NULL };
			if (first){							// w��v�ĵ�һ��δ�����ʵ��ڽӶ���
				T->lchild = p;					// �Ǹ�������
				first = FALSE;
			} else{								// w��v������δ�����ʵ��ڽӶ���
				q->nextsibling = p;				// ����һ�ڽӶ�������ֵܽ��
			}
			q = p;
			DFSTree(G, w, q, visited);	// �ӵ�w���������������ȱ���ͼG��������������q
		} // if
	} // for
}// DFSTree

void MiniSpanTree_PRIM(MGraph G, VertexType u){
	// ������ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ�����
	// ��¼�Ӷ��㼯 U �� V-U �Ĵ�����С�ıߵĸ������鶨��
	int i, j, k;
	lowedge closedge;
	k = LocateVex(G, u);
	for (j = 0; j < G.vexnum; ++j){
		if (j != k){						// ���������ʼ��
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arcs[k][j].adj;
		}
	}
	closedge[k].lowcost = 0;				// ��ʼ��U = {u}
	for (i = 1; i < G.vexnum; ++i){			// ѡ������G.vexnum - 1 ������
		k = minimum(closedge, G.vexnum);	// ���T����һ����㣺��k����
		printf("%c %c\n", closedge[k].adjvex, G.vexs[k]);		// ������������
		closedge[k].lowcost = 0;			// ��k���㲢��U��
		for (j = 0; j < G.vexnum; ++j){
			if (G.arcs[k][j].adj < closedge[j].lowcost){	// �¶��㲢��U������ѡ����С��
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
	}
}// MiniSpanTree_PRIM

int minimum(lowedge closedge, int len){
	int i, min;
	min = -1;
	for (i = 0; i < len; i++){
		if (closedge[i].lowcost){
			min = i;
			break;
		}
	}
	for (; i < len; i++){
		if (closedge[i].lowcost && closedge[i].lowcost < closedge[min].lowcost){
			min = i;
		}
	}
	return min;
}// minimum

Status display(ALGraph G, int v){
	// ��ӡͼG�ĵ�v������
	if (v >= G.vexnum)
		return ERROR;
	printf("%c ", G.vertices[v].data);
	return OK;
}// display