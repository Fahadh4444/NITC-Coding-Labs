#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Nodes
typedef struct node{
	int key;
	struct node* left;
	struct node* right;
	struct node* parent;
	
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
	return newNode;
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
					n->parent = temp;
					return;
				}else{
					temp = temp->left;
					
				}
			}else if(temp->key < n->key){
				if(temp->right == NULL){
					temp->right = n;
					n->parent = temp;
					return;
				}else{
					temp = temp->right;
				}
			}
		}
	}
}


node* minValue(tree* bst){
	node* temp = bst->root;
	while(1){
		if(temp->left == NULL){
			return temp;
		}
		temp = temp->left;
	}
}


node* maxValue(tree* bst){
	node* temp = bst->root;
	while(1){
		if(temp->right == NULL){
			return temp;
		}
		temp = temp->right;
	}
}


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


node* Predecessor(tree* bst,int k){
	tree* subBST = (tree*)malloc(sizeof(tree));
	subBST->root = NULL;
	node* temp = Search(bst,k);
	if(temp == NULL){
		return NULL;
	}
	node* parentNode = temp->parent;
	if(temp->left != NULL){
		subBST->root = temp->left;
		return maxValue(subBST);
	}else{
		while(1){
			if(parentNode->parent == NULL || temp != parentNode->left){
				free(subBST);
				return parentNode;
			}
			temp = parentNode;
			parentNode = parentNode->parent;
			
		}
	}
}


node* Successor(tree* bst,int k){
	tree* subBST = (tree*)malloc(sizeof(tree));
	subBST->root = NULL;
	node* temp = Search(bst,k);
	if(temp == NULL){
		return NULL;
	}
	node* parentNode = temp->parent;
	if(temp->right != NULL){
		subBST->root = temp->right;
		return minValue(subBST);
	}else{
		while(1){
			if(parentNode->parent == NULL || temp != parentNode->right){
				free(subBST);
				return parentNode;
			}
			temp = parentNode;
			parentNode = parentNode->parent;
			
		}
	}
}


void transplant(tree* bstt, node *u, node *v){	
  if(u->parent == NULL){              //u is root
    	bstt->root = v;
	}else if(u == u->parent->left){   //u is left child
    	u->parent->left = v;
	}else{ 							  //u is right child
    	u->parent->right = v;
	}
  if(v != NULL)
    v->parent = u->parent;
    
}


void Delete(tree* bst, int key){
	node* n = Search(bst,key);
	if(n != NULL){
		printf("%d\n",n->key);
	}else{
		printf("-1\n");
		return;
	}
	
	tree* subBST = (tree*)malloc(sizeof(tree));
	subBST->root = NULL;	
	if(n->left == NULL){
    	transplant(bst, n, n->right);
    	free(n);
  	}else if(n->right == NULL){
    	transplant(bst, n, n->left);
    	free(n);
  	}else{
  		subBST->root = n->right;
    	node* min = minValue(subBST); //minimum element in right subtree
    if(min->parent != n){
	    transplant(bst, min, min->right);
	    min->right = n->right;
	    min->right->parent = min;
    }
    	 transplant(bst, n, min);
    	min->left = n->left;
    	min->left->parent = min;
    	free(n);
  }
}


int Level(tree* bst,int k){
	node* temp = bst->root;
	int level = 1;
	while(1){
		if(temp->key == k){
			return level;
		}else{
			if(temp->key > k){
				if(temp->left == NULL){
					return level;
				}
				temp = temp->left;
				level++;
			}else if(temp->key < k){
				if(temp->right == NULL){
					return level;
				}
				temp = temp->right;
				level++;
			}
		}
		if(temp->left == NULL && temp->right == NULL){
			if(temp->key == k){
				return level;
			}else{
				return 0;
			}
		}
	}
}


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


void Preorder(tree* bst){
	node* n = bst->root;
  if(n != NULL) {
	tree* subBSTLeft = (tree*)malloc(sizeof(tree));
	subBSTLeft->root = bst->root->left;
	tree* subBSTRight = (tree*)malloc(sizeof(tree));
	subBSTRight->root = bst->root->right;
  	printf("%d ", n->key);
    Preorder(subBSTLeft);
    Preorder(subBSTRight);
    free(subBSTLeft);
    free(subBSTRight);
  }
}


void Postorder(tree* bst){
	node* n = bst->root;
  if(n != NULL) {
	tree* subBSTLeft = (tree*)malloc(sizeof(tree));
	subBSTLeft->root = bst->root->left;
	tree* subBSTRight = (tree*)malloc(sizeof(tree));
	subBSTRight->root = bst->root->right;
    Postorder(subBSTLeft);
    Postorder(subBSTRight);
    printf("%d ", n->key);
    free(subBSTLeft);
    free(subBSTRight);
  }
}


//`a', `d', `s', `l', `m', `x', `r', `u', `i', `p', `t' or `e'
//Main function
void main(){
	tree* bst = (tree*)malloc(sizeof(tree));
	bst->root = NULL;
	char ch;
	int key;
	node* requiredNode;
	while(1){
		scanf("%c",&ch);
		switch(ch){
			case 'a':
				scanf("%d",&key);
				node* newNode = createNode(key);
				Insert(bst,newNode);
				break;
			case 'd':
				scanf("%d",&key);
				Delete(bst,key);
				break;
			case 's':
				scanf("%d",&key);
				requiredNode = Search(bst,key);
				if(requiredNode == NULL){
					printf("-1\n");
				}else{
					printf("1\n");
				}
				break;
			case 'l':
				scanf("%d",&key);
				int requiredLevel = Level(bst,key);
				if(requiredLevel == 0){
					printf("-1\n");
				}else{
					printf("%d\n",requiredLevel);
				}
				break;
			case 'm':
				requiredNode = minValue(bst);
				printf("%d\n",requiredNode->key);
				break;
			case 'x':
				requiredNode = maxValue(bst);
				printf("%d\n",requiredNode->key);
				break;
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
			case 'p':
				Preorder(bst);
				printf("\n");
				break;
			case 't':
				Postorder(bst);
				printf("\n");
				break;
			case 'e':
				exit(0);
		}
	}
	
}
