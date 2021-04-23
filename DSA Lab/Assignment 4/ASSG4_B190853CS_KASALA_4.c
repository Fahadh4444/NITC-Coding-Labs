#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int vertex;
	struct node* next;
}node;

typedef struct queue{
	struct node* head;
}queue;

typedef struct graph{
	int numVertices;
	int *visitedNodes;
	struct node** adjLists;
}graph;

node* createNode(int v){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

graph* createGraph(int v){
	graph* G = (graph*)malloc(sizeof(graph));
	G->numVertices = v;
	G->adjLists = malloc(v*sizeof(node*));
	G->visitedNodes = malloc(v*sizeof(int));
	for(int i = 0; i < v; i++){
		G->adjLists[i] = NULL;
		G->visitedNodes[i] = 0;
	}
	return G;
}

void enqueueBack(queue *L, node* n){
	n->next = NULL;
	if(L->head == NULL){
		L->head = n;
	}else{
		node* temp = L->head;
		while(temp->next != NULL){
			temp = temp->next;
			
		}
		temp->next = n;
		return;
	}
}

node* dequeue(queue* L){
	node* headNode = L->head;
	L->head = L->head->next;
	headNode->next = NULL;
	return headNode;
}

void BFS(graph* G, int v){
	queue* L = (queue*)malloc(sizeof(queue));
	L->head = NULL;
	node* temp = createNode(v);
	L->head = temp;
	while(L->head != NULL){
		node* n = dequeue(L);
		G->visitedNodes[n->vertex] = 1;
		printf("%d ",n->vertex);
		node* trace = G->adjLists[n->vertex];
		while(trace != NULL){
			temp = createNode(trace->vertex);
			if(G->visitedNodes[temp->vertex] == 0){
				G->visitedNodes[temp->vertex] = 1;
				enqueueBack(L,temp);	
			}
			trace = trace->next;
		}
	}	
}

void DFS(graph* G, int v){
	node* temp = G->adjLists[v];
	 G->visitedNodes[v] = 1;
	 printf("%d ",v);
	 
	 while(temp != NULL){
	 	int requiredVertex = temp->vertex;
	 	if(G->visitedNodes[requiredVertex] == 0){
	 		DFS(G,requiredVertex);
		 };
		temp = temp->next;  
	 }
}

int main(){
	int vertices, edges;
	scanf("%d %d",&vertices,&edges);
	graph* G = createGraph(vertices);
	int s,d;
	queue* Q = (queue*)malloc(sizeof(queue));
	for(int i = 0; i < edges; i++){
		scanf("%d %d",&s,&d);
		node* requiredNode = createNode(d);
		Q->head = G->adjLists[s];
		enqueueBack(Q,requiredNode);
		G->adjLists[s] = Q->head;
	}
	int start;
	scanf("%d",&start);
	BFS(G,start);
	printf("\n");
	for(int i = 0; i < vertices; i++){
		G->visitedNodes[i] = 0;
	}
	DFS(G,start);
	
	return 0;
}
