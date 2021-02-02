#include<stdio.h>
#include<stdlib.h>


typedef struct node{
	int key;
	struct node* parent;
	struct node* left;
	struct node* right;
	struct node* next;
}node;


typedef struct tree{
	struct node* root;
}tree;


typedef struct queue{
	struct node* head;
}queue;

// creating Node
node* createNode(int key){
	node* newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode->key = key;
	newNode->parent = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->next = NULL;
	return newNode;
}


//Function to Add Node to the end of the queue
void enqueueBack(queue *L, node* n){
	if(L->head == NULL){
		L->head = n;
	}else{
		node* temp = L->head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = n;
	}
}


// Function to Add Node to the front of the queue
void enqueueFront(queue* L,node* n){
	if(L->head == NULL){
		L->head = n;
	}else{
		node* temp;
		temp = L->head;
		L->head = n;
		n->next = temp;
	}
}


// Function to remove and return Node from Front
node* dequeue(queue* L){
	node* headNode = L->head;
	L->head = L->head->next;
	return headNode;
}


// Function to build Binary Tree in Level Order Transversal
void levelOrderInsertion(tree* binaryTree, node* n, queue* L){
	if(binaryTree->root == NULL){
		binaryTree->root = n;
		//Create Queue to keep tract of nodes
		enqueueBack(L,binaryTree->root);
		return;
	}else{
		while(1){
			node* dequeuedNode = dequeue(L);
			if(dequeuedNode->left != NULL && dequeuedNode->right != NULL){
				enqueueBack(L,dequeuedNode->left);
				enqueueBack(L,dequeuedNode->right);
				break;
			}else if(dequeuedNode->left == NULL){
				dequeuedNode->left = n;
				n->parent = dequeuedNode;
				enqueueFront(L,dequeuedNode);
				break;
			}else if(dequeuedNode->right == NULL){
				dequeuedNode->right = n;
				n->parent = dequeuedNode;
				enqueueBack(L,dequeuedNode->left);
				enqueueBack(L,dequeuedNode->right);
				break;
			}
		}
	}
}


// Function to print node keys of Binary Tree in Level Order Transversal
void print(node* n){
	if(n != NULL){
		printf("( %d ",n->key);
		print(n->left);
		print(n->right);
		printf(") ");
	}else{
		printf("( ) ");
	}
}


// i p e
void main(){
	tree* binaryTree = (tree*)malloc(sizeof(tree));
	binaryTree->root = NULL;
	queue* L = (queue*)malloc(sizeof(queue));
	L->head = NULL;
	node* newNode;
	node* rootNode;
	char c;
	int x;
	while(1){
		scanf("%c",&c);
		switch(c){
			case 'i':
				scanf("%d",&x);
				newNode = createNode(x);
				levelOrderInsertion(binaryTree,newNode,L);
				break;
			case 'p':
				rootNode = binaryTree->root;
				print(rootNode);
				printf("\n");
				break;
			case 'e':
				exit(0);
		}
	}
}
