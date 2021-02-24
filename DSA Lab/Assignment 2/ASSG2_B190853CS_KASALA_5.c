#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Nodes
typedef struct node{
	int key;
	struct node* left;
	struct node* right;
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
	return newNode;
}


//Function to find parent Node
node* findingParentNode(tree* bst,int k){
	node* temp = bst->root;
	node* parent= NULL;
	while(1){
		if(temp->key == k){
			return parent;
		}else{
			if(temp->key > k){
				parent = temp;
				temp = temp->left;
			}else if(temp->key < k){
				parent = temp;
				temp = temp->right;
			}
		}
		if(temp->left == NULL && temp->right == NULL){
			if(temp->key == k){
				return parent;
			}
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
					temp = newNode;
				}else if(temp->right == NULL){
					temp->right = newNode;
					temp = newNode;
					high = 1;
				}
				i = i+2;
				continue;	
			}
		}else if(s[i] == ')'){
			node* parentNode;
			parentNode = findingParentNode(binaryTree,temp->key);
			if(parentNode != NULL){
				temp = parentNode;
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


//Function to find minValue
node* minValue(tree* bst){
	node* temp = bst->root;
	while(1){
		if(temp->left == NULL){
			return temp;
		}
		temp = temp->left;
	}
}
//Function to find maxValue
node* maxValue(tree* bst){
	node* temp = bst->root;
	while(1){
		if(temp->right == NULL){
			return temp;
		}
		temp = temp->right;
	}
}


//Function to find node in bst
node* Search(tree* bst,int k){
	node* temp = bst->root;
	while(1){
		if(temp->key == k){
			return temp;
		}else{
			if(temp->key > k){
				if(temp->left == NULL){
					return NULL;
				}
				temp = temp->left;
			}else if(temp->key < k){
				if(temp->right == NULL){
					return NULL;
				}
				temp = temp->right;
			}
		}
		if(temp->left == NULL && temp->right == NULL){
			if(temp->key == k){
				return temp;
			}else{
				return NULL;
			}
		}
	}
}


//Function to find predecessor
node* Predecessor(tree* bst,int k){
	tree* subBST = (tree*)malloc(sizeof(tree));
	subBST->root = NULL;
	node* temp = Search(bst,k);
	if(temp == NULL){
		return NULL;
	}
	node* parentNode;
	node* grandParentNode;
	parentNode = findingParentNode(bst,temp->key);
	if(parentNode != NULL){
		grandParentNode = findingParentNode(bst,parentNode->key);	
	}
	if(temp->left != NULL){
		subBST->root = temp->left;
		return maxValue(subBST);
	}else{
		while(1){
			if(grandParentNode == NULL || temp != parentNode->left){
				free(subBST);
				return parentNode;
			}
			temp = parentNode;
			parentNode = grandParentNode;
			
		}
	}
}


//Function to find successor
node* Successor(tree* bst,int k){
	tree* subBST = (tree*)malloc(sizeof(tree));
	subBST->root = NULL;
	node* temp = Search(bst,k);
	if(temp == NULL){
		return NULL;
	}
	node* parentNode;
	node* grandParentNode;
	parentNode = findingParentNode(bst,temp->key);
	if(parentNode != NULL){
		grandParentNode = findingParentNode(bst,parentNode->key);
	}
	if(temp->right != NULL){
		subBST->root = temp->right;
		return minValue(subBST);
	}else{
		while(1){
			if(grandParentNode == NULL || temp != parentNode->right){
				free(subBST);
				return parentNode;
			}
			temp = parentNode;
			parentNode = grandParentNode;
			
		}
	}
}


int kthSmallestValue(tree* bst,int k, int* tempPointer,int* checkPointer){
	node* n = bst->root;
	if(n != NULL) {
		tree* subBSTLeft = (tree*)malloc(sizeof(tree));
		subBSTLeft->root = bst->root->left;
		tree* subBSTRight = (tree*)malloc(sizeof(tree));
		subBSTRight->root = bst->root->right;
		*checkPointer = kthSmallestValue(subBSTLeft,k,tempPointer,checkPointer);
		if(*checkPointer == 1){
			return 1;
		}
		if(k != (*tempPointer)){
			*tempPointer = *tempPointer + 1;
		}
		if(*tempPointer == k){
			printf("%d\n",n->key);
			return 1;
		}
		*checkPointer = kthSmallestValue(subBSTRight,k,tempPointer,checkPointer);
		if(*checkPointer == 1){
			return 1;
		}
		free(subBSTLeft);
		free(subBSTRight);
	}
	if(*checkPointer != 1){
		return 0;
	}
}


int kthLargestValue(tree* bst,int k, int* tempPointer,int* checkPointer){
	node* n = bst->root;
	if(n != NULL) {
		tree* subBSTLeft = (tree*)malloc(sizeof(tree));
		subBSTLeft->root = bst->root->left;
		tree* subBSTRight = (tree*)malloc(sizeof(tree));
		subBSTRight->root = bst->root->right;
		*checkPointer = kthLargestValue(subBSTRight,k,tempPointer,checkPointer);
		if(*checkPointer == 1){
			return 1;
		}
		if(k != (*tempPointer)){
			*tempPointer = *tempPointer + 1;
		}
		if(*tempPointer == k){
			printf("%d\n",n->key);
			return 1;
		}
		*checkPointer = kthLargestValue(subBSTLeft,k,tempPointer,checkPointer);
		if(*checkPointer == 1){
			return 1;
		}
		free(subBSTLeft);
		free(subBSTRight);
	}
	if(*checkPointer != 1){
		return 0;
	}
}



// Inorder
void Inorder(tree* bst){
	node* n = bst->root;
  if(n != NULL) {
	tree* subBSTLeft = (tree*)malloc(sizeof(tree));
	subBSTLeft->root = bst->root->left;
	tree* subBSTRight = (tree*)malloc(sizeof(tree));
	subBSTRight->root = bst->root->right;
    Inorder(subBSTLeft);
    printf("%d ", n->key);
    Inorder(subBSTRight);
    free(subBSTLeft);
    free(subBSTRight);
  }
}


//Print
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



//`r', `u', `i', `l' `s' 'e'
//Main function
void main(){
	tree* bst = (tree*)malloc(sizeof(tree));
	bst->root = NULL;
	char s[1000000];
	gets(s);
	treeConstruction(bst,s);
//	print(bst->root);
	char ch;
	int key;
	int temp = 0;
	int check = 0;
	node* requiredNode;
	while(1){
		scanf("%c",&ch);
		switch(ch){
			case 'r':
				scanf("%d",&key);
				requiredNode = Predecessor(bst,key);
				if(requiredNode != NULL){
					printf("%d\n",requiredNode->key);
				}else{
					printf("-1\n");
				}
				break;
			case 'u':
				scanf("%d",&key);
				requiredNode = Successor(bst,key);
				if(requiredNode != NULL){
					printf("%d\n",requiredNode->key);
				}else{
					printf("-1\n");
				}
				break;
			case 'i':
				Inorder(bst);
				printf("\n");
				break;
			case 'l':
				scanf("%d",&key);
				kthLargestValue(bst,key,&temp,&check);
				temp = 0;
				check =0;
				break;
			case 's':
				scanf("%d",&key);
				kthSmallestValue(bst,key,&temp,&check);
				temp = 0;
				check = 0;
				break;
			case 'e':
				exit(0);
		}
	}
//( 25 ( 13 ( ) ( 18 ( ) ( ) ) ) ( 50 ( 45 ( ) ( ) ) ( 55 ( ) ( ) ) ) )
}
