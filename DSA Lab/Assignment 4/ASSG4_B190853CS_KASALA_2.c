#include<stdio.h>
#include<stdlib.h>

typedef struct edge{
	int source;
	int destination;
	int weight;
}edge;

typedef struct node{
	int vertex;
	struct node* next;
}node;

typedef struct graph{
	int vertices;
	int edges;
	node** listArray;
}graph;

typedef struct subset{
	int parent;
	int rank;
}subset;

graph* createGraph(int v){
	graph* newGraph = (graph*)malloc(sizeof(graph));
	newGraph->vertices = v;
	newGraph->listArray = malloc(v*sizeof(node));
	for(int i=0; i<v; i++){
		newGraph->listArray[i] = NULL;
	}
	return newGraph;
}

node* createNode(){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->next = NULL;
	return newNode;
}


int addEdges(graph* graph){
	int e = 0;
	int v = graph->vertices;
	for(int i=0; i<v; i++){
		char ch;
		int x;
		node* n;
		scanf("%d%c",&x,&ch);
		while(ch != '\n'){
			node* newNode = createNode();
			e++;
			newNode->vertex = x;
			if(graph->listArray[i] == NULL){
				graph->listArray[i] = newNode;
				n = graph->listArray[i]; 
			}else{
				n->next = newNode;
				n = n->next;
			}
			scanf("%d%c",&x,&ch);
		}
		node* newNode = createNode();
		newNode->vertex = x;
		if(graph->listArray[i] == NULL){
			graph->listArray[i] = newNode;
			n = graph->listArray[i]; 
		}else{
			n->next = newNode;
			n = n->next;
		}
		
	}
	return e;
}

void sort(edge edges[], int e){
	int min = 0;
	int index = 0;
	for(int i=0;i<e-1;i++){
		index = i;
		min = edges[i].weight;
		for(int j=i+1; j<e; j++){
			if(min > edges[j].weight){
				index = j;
				min = edges[j].weight;
			}
		}
		
		if(index != i){
			int src = edges[i].source;
			int dest = edges[i].destination;
			int wgt = edges[i].weight;
			edges[i].source = edges[index].source;
			edges[i].destination = edges[index].destination;
			edges[i].weight = edges[index].weight;
			edges[index].source = src;
			edges[index].destination = dest;
			edges[index].weight = wgt;
		}
	}
}

int findSet(subset subsets[], int v){
	if(subsets[v].parent != v){
		subsets[v].parent = findSet(subsets,subsets[v].parent);
	}
	return subsets[v].parent;
}

void Union(subset subsets[], int x, int y){
	int a = findSet(subsets,x);
	int b = findSet(subsets,y);
	if(subsets[a].rank < subsets[b].rank){
		subsets[a].parent = b;
	}else if(subsets[a].rank > subsets[b].rank){
		subsets[b].parent = a;
	}else{
		subsets[b].parent = a;
		subsets[a].rank++;
	}
}

int kruskal(graph* graph){
	int v = graph->vertices;
	int e = 0;
	int flag = 1;
	edge edges[graph->edges];
	for(int i=0; i<v; i++){
		node* n = graph->listArray[i]->next;
		int waste;
		scanf("%d",&waste);
		while(n){
			int wt;
			scanf("%d",&wt);
			for(int j=0; j<e; j++){
				if(edges[j].source == n->vertex && edges[j].destination == i){
					flag = 0;
					break;
				}
			}
			if(flag == 1){
				edges[e].source = i;
				edges[e].destination = n->vertex;
				edges[e].weight = wt;
				e = e + 1;
				n = n->next;
			}else{
				flag = 1;
				n = n->next;
			}
		}
	}
	sort(edges,graph->edges);
	
	subset subsets[v];
	for(int i=0;i<v;i++){
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}
	e = 0;
	int i = 0;
	int sumOfWeightsMST = 0;
	while(e < v-1 && i < graph->edges){
		int x = findSet(subsets, edges[i].source);
		int y = findSet(subsets, edges[i].destination);
		if(x != y){
			sumOfWeightsMST = sumOfWeightsMST + edges[i].weight;
			Union(subsets,x,y);
			e++;
			i++;
		}else{
			i++;
		}
	}
	printf("%d",sumOfWeightsMST);
	
}


int minKey(int key[], int set[], int v){
	int min = INT_MAX;
	int index;
	for(int i=0; i<v; i++){
		if(set[i] == 0 && key[i] < min){
			min = key[i];
			index = i;
		}
		
	}
	return index;
}


int prim(graph* graph){
	int v = graph->vertices;
	int e = 0;
	int num = graph->edges;
	edge edges[num];
	for(int i=0; i<v; i++){
		node* n = graph->listArray[i]->next;
		int waste;
		scanf("%d",&waste);
		while(n != NULL){
			edges[e].source = i;
			edges[e].destination = n->vertex;
			int wt;
			scanf("%d",&wt);
			edges[e].weight = wt;
			e++;
			n = n->next;
		}
		
	}
//	for(int i=0;i<e;i++)
//	{
//		printf("%d %d %d",edges[i].source,edges[i].destination,edges[i].weight);
//		printf("\n");
//	}
	e = num;
	int set[v];
	int key[v];
	for(int i=0;i<v;i++){
		set[i] = 0;
		key[i] = 2147483647;
	}
	key[0] = 0;
	for(int i=0;i<v-1;i++){
		int u = minKey(key,set,v);
		set[u] = 1;
		for(int j=0;j<e;j++){
			if( (edges[j].source == u) && ( set[edges[j].destination] == 0 ) && ( key[edges[j].destination] > edges[j].weight ) ){
				key[edges[j].destination] = edges[j].weight;
			}
		}
	}
	int sumOfWeightsMST = 0;
	for(int i=0; i<v; i++){
//		printf("%d\n",key[i]);
		sumOfWeightsMST = sumOfWeightsMST + key[i];
	}
	printf("%d",sumOfWeightsMST);
}


int main(){
	int v;
	int e;
	char ch;
	scanf("%c",&ch);
	scanf("%d",&v);
	graph* graph = createGraph(v);
	e = addEdges(graph);
	switch(ch){
		case 'a':
			graph->edges = e/2;
			kruskal(graph);
			return 0;
		case 'b':
			graph->edges = e;
			prim(graph);
			return 0;
	}
	
	
	
}
