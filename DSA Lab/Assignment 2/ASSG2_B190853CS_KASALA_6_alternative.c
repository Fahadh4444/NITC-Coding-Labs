#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Nodes
typedef struct node{
	int key;
	struct node* left;
	struct node* right;
}node;


typedef struct qNode{
	int data;
	struct qNode* next;
}qNode;


typedef struct queue{
	qNode* next;
}queue;


//tree
typedef struct tree{
	struct node* root;
}tree;


//Function to create node
node* createNode(int key){
	node* newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}


qNode* createqNode(int key){
	qNode* newNode;
	newNode = (qNode*)malloc(sizeof(qNode));
	newNode->data = key;
	newNode->next = NULL;
}


void enqueue(queue* q,qNode* n ){
	qNode* temp;
	if(q->next == NULL){
		q->next = n;
	}else{
		temp = q->next;
		while(1){
			if(temp->next == NULL){
				temp->next = n;
				return;
			}else{
				temp = temp->next;
			}
		}
	}
}


int dequeue(queue* Q){
	qNode* headNode= Q->next;
	Q->next = Q->next->next;
	headNode->next = NULL;
	return headNode->data;
}


//Function to insert Nodes to BST
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


// Function to print BST
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


//Function to find path queue
void pathQueue(tree* bst,int a,queue* Q){
	node* temp = bst->root;
	while(1){
		if(temp->key == a){
			qNode* newNode = createqNode(temp->key);
			enqueue(Q,newNode);
			return;
		}else if(temp->key != a){
			qNode* newNode = createqNode(temp->key);
			enqueue(Q,newNode);
		}
		if(temp->key > a){
			temp = temp->left;
		}else if(temp->key < a){
			temp = temp->right;
		}
	}
}


//Function to find max value in two paths
void pathMax(tree* bst,int a,int b){
	queue* Q1 = (queue*)malloc(sizeof(queue));
	Q1->next = NULL;
	queue* Q2 = (queue*)malloc(sizeof(queue));
	Q2->next = NULL;
	pathQueue(bst,a,Q1);
	pathQueue(bst,b,Q2);
	int max;
	int x,y;
	while(1){
		if(Q1->next != NULL && Q2->next != NULL){
			x = dequeue(Q1);
			y = dequeue(Q2);	
		}
		else{
			break;
		}
		if(x != y){
			if(x > max){
				max = x;
			}
			if(y > max){
				max = y;
			}
			break;
		}else{
			max = x;
		}
	}
	while(1){
		if(Q1->next != NULL && Q2->next != NULL){
			x = dequeue(Q1);
			y = dequeue(Q2);
			if(x > max){
				max = x;
			}
			if(y > max){
				max = y;
			}
		}else if(Q1->next != NULL && Q2->next == NULL){
			x = dequeue(Q1);
			if(x > max){
				max = x;
			}
		}else if(Q1->next == NULL && Q2->next != NULL){
			y = dequeue(Q2);
			if(y > max){
				max = y;
			}
		}else{
			printf("%d",max);
			exit(0);
		}
	}	
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


// i p e
//Main function
void main(){
	tree* bst = (tree*)malloc(sizeof(tree));
	bst->root = NULL;
	node* newNode;
	int minus = 1;
	char s[1000000];
	gets(s);
	int i = 0;
	while(s[i] != '\0'){
		if(s[i] == '-'){
			minus = -1;
			i++;
		}
		char y = s[i];
		int num1 = y - '0';
		while(1){
			if(s[i+1] != ' ' && s[i+1] != '\0'){
				i++;
				char x = s[i];
				int num2 = x - '0';
				num1 = concat(num1,num2);
			}else{
				break;
			}	
		}
		newNode = createNode((minus*num1));
		Insert(bst,newNode);
		if(s[i+1] == '\0'){
			break;
		}
		i = i + 2;
	}
//	print(bst->root);
	int a,b;
	scanf("%d",&a);
	scanf("%d",&b);
	pathMax(bst,a,b);
}
