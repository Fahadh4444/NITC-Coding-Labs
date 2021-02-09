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


//void print(node* n){
//	if(n != NULL){
//		printf("( %d ",n->key);
//		print(n->left);
//		print(n->right);
//		printf(") ");
//	}else{
//		printf("( ) ");
//	}
//}


void kthSmallestValue(tree* bst,int k){
	node* n = bst->root;
	static int temp = 0;
	if(n != NULL) {
		tree* subBSTLeft = (tree*)malloc(sizeof(tree));
		subBSTLeft->root = bst->root->left;
		tree* subBSTRight = (tree*)malloc(sizeof(tree));
		subBSTRight->root = bst->root->right;
		kthSmallestValue(subBSTLeft,k);
		if(k != (temp)){
			temp++;
		}
		if(temp == k){
			printf("%d",n->key);
			exit(0);
		}
		kthSmallestValue(subBSTRight,k);
		free(subBSTLeft);
		free(subBSTRight);
	}
}


// i p e
//Main function
void main(){
	tree* bst = (tree*)malloc(sizeof(tree));
	bst->root = NULL;
	char s[1000000];
	int number;
	gets(s);
	treeConstruction(bst,s);
//	print(bst->root);
	scanf("%d",&number);
	kthSmallestValue(bst,number);
}
