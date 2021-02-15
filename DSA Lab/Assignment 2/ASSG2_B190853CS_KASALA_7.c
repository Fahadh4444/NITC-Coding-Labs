#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Nodes
typedef struct node{
	int key;
	struct node* left;
	struct node* right;
	struct node* next;
}node;


//tree
typedef struct tree{
	struct node* root;
}tree;

//queue used in finding cousind
typedef struct queue{
	struct node* head;
}queue;


//Function to create node
node* createNode(int key){
	node* newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->next = NULL;
	return newNode;
}


node* dequeue(queue* L){
	node* headNode = L->head;
	L->head = L->head->next;
	headNode->next = NULL;
	return headNode;
}


//Function to add node at head position using next pointer
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


//18 20 24 30 36 50 51
node* treeImplementation(node* rootNode,int n,int m,int array[m]){
	if(n<m){
		int mid = (n+m)/2;
		rootNode = createNode(array[mid]);
		rootNode->left = treeImplementation(rootNode->left,n,mid,array);
		rootNode->right = treeImplementation(rootNode->right,mid+1,m,array);
		return rootNode;
	}
	return NULL;
}


void Insert(tree* bst,node* n){
	if(bst->root == NULL){
		bst->root = n;
		return;
	}else{
		node* temp = bst->root;
		while(1){
			if(temp->key > n->key){
				if(temp->left == NULL){
					temp->left = n;
					return;
				}else{
					temp = temp->left;	
				}
			}else if(temp->key < n->key){
				if(temp->right == NULL){
					temp->right = n;
					return;
				}else{
					temp = temp->right;
				}
			}
		}
	}
}


//Function to fillQueue
void levelSum(tree* bst){
	queue* lOne = (queue*)malloc(sizeof(queue));
	lOne->head = NULL;
	queue* lTwo = (queue*)malloc(sizeof(queue));
	lTwo->head = NULL;
	int x = 1;
	int y = 0;
	int sum = 0;
	while(1){
		if(x == 1){
			if(lOne->head == NULL){
				lOne->head = bst->root;
			}else{
				node* dequeuedNode = dequeue(lOne);
				dequeuedNode->next = NULL;
				sum = sum + dequeuedNode->key;
				if(dequeuedNode->left != NULL){
					dequeuedNode->left->next = NULL;
					enqueueBack(lTwo,dequeuedNode->left);
				}
				if(dequeuedNode->right != NULL){
					dequeuedNode->right->next = NULL;
					enqueueBack(lTwo,dequeuedNode->right);
				}
				if((lOne->head == NULL || lTwo->head == NULL) && (dequeuedNode->left != NULL || dequeuedNode->right != NULL)){
					int m;
					m = x;
					x = y;
					y = m;
					printf("%d ",sum);
					sum = 0;
				}
			}
		}else if(y == 1){
			if(lTwo->head  == NULL){
				lTwo->head = bst->root;
			}else{
				node* dequeuedNode = dequeue(lTwo);
				dequeuedNode->next = NULL;
				sum = sum + dequeuedNode->key;
				if(dequeuedNode->left != NULL){
					dequeuedNode->left->next = NULL;
					enqueueBack(lOne,dequeuedNode->left);
				}
				if(dequeuedNode->right != NULL){
					dequeuedNode->right->next = NULL;
					enqueueBack(lOne,dequeuedNode->right);
				}
				if((lOne->head == NULL || lTwo->head == NULL) && (dequeuedNode->left != NULL || dequeuedNode->right != NULL)){
					int m;
					m = x;
					x = y;
					y = m;
					printf("%d ",sum);
					sum = 0;
				}
			}
		}
		if(lOne->head == NULL && lTwo->head == NULL){
			printf("%d",sum);
			free(lOne);
			free(lTwo);
			return;
		}
	}
}


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
//Main function
void main(){
	tree* bst = (tree*)malloc(sizeof(tree));
	bst->root = NULL;
	queue* L = (queue*)malloc(sizeof(queue));
	L->head = NULL;
	int size;
	scanf("%d",&size);
	int arr[size];
	for(int i = 0; i<size; i++){
		scanf("%d",&arr[i]);
	}
	bst->root = treeImplementation(bst->root,0,size-1,arr);
	node* n = createNode(arr[size-1]);
	Insert(bst,n);
	print(bst->root);
	printf("\n");
	levelSum(bst);
}
