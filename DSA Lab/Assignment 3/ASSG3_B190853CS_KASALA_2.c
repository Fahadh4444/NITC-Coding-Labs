#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int key;
	int height;
	int count;
	struct node* left;
	struct node* right;
}node;

typedef struct avlTree{
	struct node* root;
}avlTree;


node* createNode(int key){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->key = key;
	newNode->count = 1;
	newNode->left = newNode->right = NULL;
	newNode->height = 1;
	return newNode;
}


int max(int a, int b){
	return ((a>b)?a:b);
}


int height(node* n){
	if(n == NULL){
		return 0;
	}
	return n->height;
}


node* avlSearch(node* T,int k){
	if(T == NULL){
		return T;
	}
	if(T->key == k){
		return T;
	}else if(k < T->key){
		return avlSearch(T->left,k);
	}else if(k > T->key){
		return avlSearch(T->right,k);
	}
}


int avlBalanceFactor(node* T,int k){
	node* requiredNode = avlSearch(T,k);
	return (height(requiredNode->left) - height(requiredNode->right));
}


node* leftRotation(node* n){
	node* temp = n->right;
	node* trace = temp->left;
	temp->left = n;
	n->right = trace;
	n->height = max(height(n->left),height(n->right)) + 1;
	temp->height = max(height(temp->left),height(temp->right)) + 1;
	return temp;
}


node* rightRotation(node* n){
	node* temp = n->left;
	node* trace = temp->right;
	temp->right = n;
	n->left = trace;
	n->height = max(height(n->left),height(n->right)) + 1;
	temp->height = max(height(temp->left),height(temp->right)) + 1;
	return temp;
}


node* avlInsert(node* T,int k){
	if(T == NULL){
		return createNode(k);
	}
	if(k < T->key){
		T->left = avlInsert(T->left,k);
	}else if(k > T->key){
		T->right = avlInsert(T->right,k);
	}else{
		T->count = T->count + 1;
		return T;
	}
	
	T->height = max(height(T->left),height(T->right)) + 1;
	
	int bf;
	if(T == NULL){
		bf = 0;
	}else{
		bf = avlBalanceFactor(T,T->key);
	}
	
	//LL
	if(bf > 1 && k < T->left->key){
		return rightRotation(T);
	}else if(bf > 1 && k > T->left->key){
		T->left = leftRotation(T->left);
		return rightRotation(T);
	}else if(bf < -1 && k > T->right->key){
		return leftRotation(T);
	}else if(bf < -1 && k < T->right->key){
		T->right = rightRotation(T->right);
		return leftRotation(T);
	}
	
	return T;
}


void printing(node* n){
	for(int i=0; i<n->count;i++){
		printf("%d ",n->key);
	}
}


void print(node* n){
	if(n != NULL){
		print(n->left);
		printing(n);
		print(n->right);
	}
}


//`i', `d', `s', `b', `p' and `e'
int main(){
	avlTree* avl = (avlTree*)malloc(sizeof(avlTree));
	avl->root = NULL;
	int n,m;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&m);
		avl->root = avlInsert(avl->root,m);
	}
	print(avl->root);
	return 0;
}
