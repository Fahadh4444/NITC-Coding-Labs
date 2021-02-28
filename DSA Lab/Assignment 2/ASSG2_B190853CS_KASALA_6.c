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


node* commonPoint(node* n, int a, int b){
	node* temp = n;
		if(temp->key<a && temp->key<b){
			temp = commonPoint(temp->right,a,b);
		}
		else if(temp->key>a && temp->key>b){
			temp = commonPoint(temp->left,a,b);
		}
		else{
			return temp;	
		}
}

int pathMax(node* n,int a,int b){
	
	int max = INT_MIN;
	while(n->key != a){
		if(n->key > a){
			if(n->key > max && n->key != b){
				max = n->key;
			}
			n = n->left;
		}else{
			if(n->key > max && n->key != b){
				max = n->key;
			}
			n = n->right;
		}
	}
	return max;
}


void totalPathMax(node* n, int a, int b){
	node* common = commonPoint(n,a,b);
//	printf("%d\n",common->key);
	int aMax = pathMax(common,a,b);
	int bMax = pathMax(common,b,a);
//	printf("%d\n",aMax);
//	printf("%d\n",bMax);
	if(aMax>=bMax){
		printf("%d",aMax);
	}else{
		printf("%d",bMax);
	}
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
	totalPathMax(bst->root,a,b);

}
