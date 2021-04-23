#include<stdio.h>
#include<stdlib.h>

typedef struct edge{
	int s;
	int d;
	int w;
}E;

typedef struct graph{
	int vertex;
	int edges;
	E* Eds;
}G;


G* createGraph(int v, int e){
	G* newGraph = (G*)malloc(sizeof(G));
	newGraph->edges = e;
	newGraph->vertex = v;
	newGraph->Eds = malloc(e * sizeof(E));
	return newGraph;
}

void addEdges(G* Graph){
	int x, y, z;
	int e = Graph->edges;
	for(int i = 0; i < e; i++){
		scanf("%d %d %d",&x,&y,&z);
		Graph->Eds[i].s = x;
		Graph->Eds[i].d = y;
		Graph->Eds[i].w = z;
	}
}


void bellomFord(G* Graph ,int src){
	int v = Graph->vertex;
	int e = Graph->edges;
	int d[v];
	for(int i=0; i<e; i++){
		d[i] = 2147483647;
	}
	d[src] = 0;
	for(int i=0; i<v; i++ ){
		for(int j=0; j<e; j++){
			int source = Graph->Eds[j].s;
			int destination = Graph->Eds[j].d;
			int weight = Graph->Eds[j].w;
			if(d[source] != 2147483647 && d[source] + weight < d[destination]){
				d[destination] = d[source] + weight;
			}
		}
	}
	for(int i=0; i<e; i++){
		int source = Graph->Eds[i].s;
		int destination = Graph->Eds[i].d;
		int weight = Graph->Eds[i].w;
		if(d[source] != 2147483647 && d[source] + weight < d[destination]){
			printf("1");
			return;
		}
	}
	printf("-1");
	
	
}



int main(){
	
	int v,e;
	scanf("%d %d",&v,&e);
	G* Graph = createGraph(v, e);
	addEdges(Graph);
	bellomFord(Graph, 0);
	return 0;
}
