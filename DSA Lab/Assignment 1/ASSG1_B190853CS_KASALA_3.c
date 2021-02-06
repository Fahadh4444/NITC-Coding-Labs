#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Nodes
typedef struct node{
	int key;
	struct node* left;
	struct node* right;
	struct node* parent;
	struct node* next;
	struct node* after;
	
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
	newNode->parent = NULL;
	newNode->next = NULL;
	newNode->after = NULL;
	return newNode;
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


//Function to add node at head position using after pointer
void enqueueBackByAfter(queue *L, node* n){
	n->after = NULL;
	if(L->head == NULL){
		L->head = n;
	}else{
		node* temp = L->head;
		while(temp->after != NULL){
			temp = temp->after;
			
		}
		temp->after = n;
		return;
	}
}


//Function to remove node from head position using next pointer
node* dequeue(queue* L){
	node* headNode = L->head;
	L->head = L->head->next;
	headNode->next = NULL;
	return headNode;
}


//Function to remove node from head position using after pointer
node* dequeueAfterNode(queue* L){
	node* headNode = L->head;
	L->head = L->head->after;
	headNode->after = NULL;
	return headNode;
}


//Function to concat to integers
int concat(int a, int b){ 
    char s1[20]; 
    char s2[20]; 
  
    // Convert both the integers to string 
    sprintf(s1, "%d", a); 
    sprintf(s2, "%d", b); 
  
    // Concatenate both strings 
    strcat(s1, s2); 
  
    // Convert the concatenated string 
    // to integer 
    int c = atoi(s1); 
  
    // return the formed integer 
    return c; 
}


//Function to implement(construct) tree
void treeConstruction(tree* binaryTree, char s[1000000]){
	node* temp = NULL;
	int minus = 1;
	int i = 0;
	while(s[i] != '\0'){
		minus = 1;
		if(s[i] == '('){
			i = i+2;
			if(s[i] == ')'){
				if(s[i+1] == '\0'){
					i++;
				}else{
					i = i+2;
				}
				continue;
			}else{
				if(s[i] == '-'){
					minus = -1;
					i++;
				}
				char y = s[i];
				int num1 = y - '0';
				while(1){
					if(s[i+1] != ' '){
						i++;
						char x = s[i];
						int num2 = x - '0';
						num1 = concat(num1,num2);
					}else{
						break;
					}	
				}
				node* newNode = createNode((minus*num1));
				if(temp == NULL){
					binaryTree->root = newNode;
					temp = binaryTree->root;
				}
				else if(temp->left == NULL){
					temp->left = newNode;
					newNode->parent = temp;
					temp = newNode;
				}else if(temp->right == NULL){
					temp->right = newNode;
					newNode->parent = temp;
					temp = newNode;
				}
				i = i+2;
				continue;	
			}
		}else if(s[i] == ')'){
			if(temp->parent != NULL){
				temp = temp->parent;
			}
			if(s[i+1] == '\0'){
				i++;
			}else{
				i = i+2;
			}
			continue;
		}
	}
}


//Function to fillQueue
void fillQueue(queue* L,node* n){
	queue* lOne = (queue*)malloc(sizeof(queue));
	lOne->head = NULL;
	queue* lTwo = (queue*)malloc(sizeof(queue));
	lTwo->head = NULL;
	int x = 1;
	int y = 0;
	while(1){
		if(x == 1){
			if(lOne->head == NULL){
				lOne->head = n;
			}else{
				node* dequeuedNode = dequeue(lOne);
				dequeuedNode->next = NULL;
				enqueueBack(L,dequeuedNode);
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
				}
			}
		}else if(y == 1){
			if(lTwo->head  == NULL){
				lTwo->head = n;
			}else{
				node* dequeuedNode = dequeue(lTwo);
				dequeuedNode->next = NULL;
				enqueueBack(L,dequeuedNode);
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
				}
			}
		}
		if(lOne->head == NULL && lTwo->head == NULL){
			free(lOne);
			free(lTwo);
			return;
		}
	}
}


//Function to fillSubTreeNodesQueue
void fillSubTreeNodesQueue(queue* L,node* n){
	queue* lOne = (queue*)malloc(sizeof(queue));
	lOne->head = NULL;
	queue* lTwo = (queue*)malloc(sizeof(queue));
	lTwo->head = NULL;
	int x = 1;
	int y = 0;
	while(1){
		if(x == 1){
			if(lOne->head == NULL){
				lOne->head = n;
			}else{
				node* dequeuedNode = dequeueAfterNode(lOne);
				dequeuedNode->after = NULL;
				enqueueBackByAfter(L,dequeuedNode);
				if(dequeuedNode->left != NULL){
					dequeuedNode->left->after = NULL;
					enqueueBackByAfter(lTwo,dequeuedNode->left);
				}
				if(dequeuedNode->right != NULL){
					dequeuedNode->right->after = NULL;
					enqueueBackByAfter(lTwo,dequeuedNode->right);
				}
				if((lOne->head == NULL || lTwo->head == NULL) && (dequeuedNode->left != NULL || dequeuedNode->right != NULL)){
					int m;
					m = x;
					x = y;
					y = m;
				}
			}
		}else if(y == 1){
			if(lTwo->head  == NULL){
				lTwo->head = n;
			}else{
				node* dequeuedNode = dequeueAfterNode(lTwo);
				dequeuedNode->after = NULL;
				enqueueBackByAfter(L,dequeuedNode);
				if(dequeuedNode->left != NULL){
					dequeuedNode->left->after = NULL;
					enqueueBackByAfter(lOne,dequeuedNode->left);
				}
				if(dequeuedNode->right != NULL){
					dequeuedNode->right->after = NULL;
					enqueueBackByAfter(lOne,dequeuedNode->right);
				}
				if((lOne->head == NULL || lTwo->head == NULL) && (dequeuedNode->left != NULL || dequeuedNode->right != NULL)){
					int m;
					m = x;
					x = y;
					y = m;
				}
			}
		}
		if(lOne->head == NULL && lTwo->head == NULL){
			free(lOne);
			free(lTwo);
			return;
		}
	}
}


//Function to check whether each node BST root node or not
int checkCondition(node* n,int num){
	int sum = 0;
	queue* subTreeNodesQueue = (queue*)malloc(sizeof(queue));
	subTreeNodesQueue->head = NULL;
	fillSubTreeNodesQueue(subTreeNodesQueue,n);
	if(subTreeNodesQueue->head->left == NULL && subTreeNodesQueue->head->right == NULL){
		if(num == subTreeNodesQueue->head->key){
			return 1;
		}else{
			return 0;
		}
	}
	while(1){
		if(subTreeNodesQueue->head == NULL){
			break;
		}
		if(subTreeNodesQueue->head->left == NULL && subTreeNodesQueue->head->right == NULL){
			sum = sum + subTreeNodesQueue->head->key;
			node* temp = subTreeNodesQueue->head;
			subTreeNodesQueue->head = subTreeNodesQueue->head->after;
			temp->after = NULL;
			continue;
		}
		if(((subTreeNodesQueue->head->key) > (subTreeNodesQueue->head->left->key)) && ((subTreeNodesQueue->head->key) < (subTreeNodesQueue->head->right->key))){
			sum = sum + subTreeNodesQueue->head->key;
			node* temp = subTreeNodesQueue->head;
			subTreeNodesQueue->head = subTreeNodesQueue->head->after;
			temp->after = NULL;
			continue;
		}else{
			while(1){
				node* temp = subTreeNodesQueue->head;
				if(subTreeNodesQueue->head != NULL){
					subTreeNodesQueue->head = subTreeNodesQueue->head->after;
					temp->after = NULL;
				}else{
					break;
				}
			}
			return 0;
		}
	}
	if(num != sum){
		return 0;
	}
	return 1;
}


//Function to count requuired nodes
void countBST(tree* binaryTree,int num){
	int count = 0;
	int n;
	queue* nodesQueue = (queue*)malloc(sizeof(queue));
	nodesQueue->head = NULL;	
	fillQueue(nodesQueue,binaryTree->root);
	while(nodesQueue->head != NULL){
		if(checkCondition(nodesQueue->head,num)){
			count++;
		}
		node* trace;
		trace = nodesQueue->head;
		nodesQueue->head = nodesQueue->head->next;
		trace->next = NULL;
	}
	if(count == 0){
		printf("-1");
		return;
	}
	printf("%d",count);
}


// i p e
//Main function
void main(){
	tree* binaryTree = (tree*)malloc(sizeof(tree));
	binaryTree->root = NULL;
	char s[1000000];
	int number;
	gets(s);
	treeConstruction(binaryTree,s);
	int k;
	scanf("%d",&k);
	countBST(binaryTree,k);
}
