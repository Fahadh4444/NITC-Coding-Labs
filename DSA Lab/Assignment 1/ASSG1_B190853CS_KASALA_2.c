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
	return newNode;
}


//Function to add node at head position
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


//Function to remove node from head position
node* dequeue(queue* L){
	node* headNode = L->head;
	L->head = L->head->next;
	headNode->next = NULL;
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
	int high = 1;
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
					high = 0;
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
				else if(temp->left == NULL && high == 1){
					temp->left = newNode;
					newNode->parent = temp;
					temp = newNode;
				}else if(temp->right == NULL){
					temp->right = newNode;
					newNode->parent = temp;
					temp = newNode;
					high = 1;
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


//Functiom to return parent node of required(n) node
node* search(node* rootNode, node* n){
	queue* L = (queue*)malloc(sizeof(queue));
	L->head = NULL;
	while(1){
		if(L->head == NULL){
			enqueueBack(L,rootNode);
		}else{
			node* dequeuedNode = dequeue(L);
			if(dequeuedNode->left == NULL && dequeuedNode->right != NULL ){
				if(dequeuedNode->right->key == n->key){
					return dequeuedNode;
				}else{
					enqueueBack(L,dequeuedNode->right);
				}	
			}else if(dequeuedNode->left != NULL && dequeuedNode->right == NULL ){
				if(dequeuedNode->left->key == n->key){
					return dequeuedNode;
				}else{
					enqueueBack(L,dequeuedNode->left);
				}				
			}else{
				if(dequeuedNode->left->key == n->key || dequeuedNode->right->key == n->key){
					return dequeuedNode;
				}else{
					enqueueBack(L,dequeuedNode->left);
					enqueueBack(L,dequeuedNode->right);
				}
			}
		}
	}
	while(L->head != NULL){
		dequeue(L);
	}
}


//Function to print cousin nodes
void cousins(tree* binaryTree,int num){
	node* rootNode = binaryTree->root;
	node* level;
	if(binaryTree->root->key == num){
		printf("-1");
		return;
	}else{
		node* requiredParentNode = createNode(num);
		level = search(rootNode,requiredParentNode);
		if(level == binaryTree->root){
			printf("-1");
			return;
		}
	}
	queue* lOne = (queue*)malloc(sizeof(queue));
	lOne->head = NULL;
	queue* lTwo = (queue*)malloc(sizeof(queue));
	lTwo->head = NULL;
	int x = 1;
	int y = 0;
	int m = 0;
	while(1){
		if(x == 1){
			if(lOne->head == NULL){
				enqueueBack(lOne,rootNode);
			}else{
				node* dequeuedNode = dequeue(lOne);
				if(dequeuedNode->left == level || dequeuedNode->right == level){
					if(dequeuedNode->left != NULL){
						enqueueBack(lTwo,dequeuedNode->left);
					}
					if(dequeuedNode->right != NULL){
						enqueueBack(lTwo,dequeuedNode->right);
					}
					while(lOne->head != NULL){
						dequeuedNode = dequeue(lOne);
						if(dequeuedNode->left != NULL){
							enqueueBack(lTwo,dequeuedNode->left);
						}
						if(dequeuedNode->right != NULL){
							enqueueBack(lTwo,dequeuedNode->right);
						}
					}
					while(lTwo->head != NULL){
						dequeuedNode = dequeue(lTwo);
						if(dequeuedNode != level){
							if(dequeuedNode->left != NULL){
								m = 1;
								printf("%d ",dequeuedNode->left->key);
							}
							if(dequeuedNode->right != NULL){
								m = 1;
								printf("%d ",dequeuedNode->right->key);
							}
						}
						if(lTwo->head == NULL){
							if( m == 0){
								printf("-1");
							}
							return;
						}
					}
				}else{
					if(dequeuedNode->left != NULL){
						enqueueBack(lTwo,dequeuedNode->left);
					}
					if(dequeuedNode->right != NULL){
						enqueueBack(lTwo,dequeuedNode->right);
					}
				}
				if(lOne->head == NULL || lTwo->head == NULL){
					int m;
					m = x;
					x = y;
					y = m;
				}
			}
		}else if(y == 1){
			if(lTwo->head == NULL){
				enqueueBack(lTwo,rootNode);
			}else{
				node* dequeuedNode = dequeue(lTwo);
				if(dequeuedNode->left == level || dequeuedNode->right == level){
					if(dequeuedNode->left != NULL){
						enqueueBack(lOne,dequeuedNode->left);
					}
					if(dequeuedNode->right != NULL){
						enqueueBack(lOne,dequeuedNode->right);
					}
					while(lTwo->head != NULL){
						dequeuedNode = dequeue(lTwo);
					if(dequeuedNode->left != NULL){
						enqueueBack(lOne,dequeuedNode->left);
					}
					if(dequeuedNode->right != NULL){
						enqueueBack(lOne,dequeuedNode->right);
					}
					}
					
					while(lOne->head != NULL){
						dequeuedNode = dequeue(lOne);
						if(dequeuedNode != level){
							if(dequeuedNode->left != NULL){
								m = 1;
								printf("%d ",dequeuedNode->left->key);
							}
							if(dequeuedNode->right != NULL){
								m = 1;
								printf("%d ",dequeuedNode->right->key);
							}
						}
						if(lOne->head == NULL){
							if( m == 0){
								printf("-1");
							}
							return;
						}
					}
				}else{
					if(dequeuedNode->left != NULL){
						enqueueBack(lOne,dequeuedNode->left);
					}
					if(dequeuedNode->right != NULL){
						enqueueBack(lOne,dequeuedNode->right);
					}
				}
				if(lOne->head == NULL || lTwo->head == NULL){
					int m;
					m = x;
					x = y;
					y = m;
				}
			}
			
		}
	}
}


// i p e
//Main function
void main(){
	tree* binaryTree = (tree*)malloc(sizeof(tree));
	binaryTree->root = NULL;
	queue* L = (queue*)malloc(sizeof(queue));
	L->head = NULL;
	char s[1000000];
	int number;
	gets(s);
	treeConstruction(binaryTree,s);
	scanf("%d",&number);
	cousins(binaryTree,number);
}
