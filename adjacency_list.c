#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct GraphNode
{
	int vertex;
	struct GraphNode *link;
}GraphNode;

typedef struct GraphType
{
	int n; //정점의 개수
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for(v = 0; v < MAX_VERTICES; v++)
	{
		g->adj_list[v] = NULL;
	}
}

void insert_vertex(GraphType *g, int v)
{
	if((g->n) + 1 > MAX_VERTICES)
	{
		fprintf(stderr,"그래프 정점 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node;
	if(u >= g->n || v >= g->n)
	{
		fprintf(stderr,"그래프:정점 번호 오류");
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node->link;
}

//리스트로 구현한 깊이 우선 탐색 
void dfs_list(GraphType *g, int v)
{
	GraphNode *w;
	visited[v] = TRUE;
	printf("%d", v);
	for(w = g->adj_list[v]; w; w=w->link)
		if(!visited[w->vertex])
			dfs_list(g, w->vertex);
}