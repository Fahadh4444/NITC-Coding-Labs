#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int key;
	char color;
	struct node* left;
	struct node* right;
}node;

typedef struct rbTree{
	struct node* root;
}rbTree;


 node* createNode(int key, node* N){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->key = key;
	newNode->color = 'R';
	newNode->left = newNode->right = N;
	return newNode;
}



node* leftRotation(node* n){
	node* temp = n->right;
	node* trace = temp->left;
	temp->left = n;
	n->right = trace;
	return temp;
}


node* rightRotation(node* n){
	node* temp = n->left;
	node* trace = temp->right;
	temp->right = n;
	n->left = trace;
	return temp;
}


node* rbInsert(node* T,node* x, node* N){
	if(T == N){
		return x;
	}else{
		if(x->key < T->key){
			T->left = rbInsert(T->left,x,N);
			if(T->left->color == 'R'){
				if(T->left->left->color == 'R' || T->left->right->color == 'R'){
					if(T->right->color != 'R'){
						if(T->left->left->color == 'R'){
							T = rightRotation(T);
							T->right->color = 'R';
							T->color = 'B';
							return T;
						}else{
							T->left = leftRotation(T->left);
							T = rightRotation(T);
							T->right->color = 'R';
							T->color = 'B';
							return T;
						}
					}else if(T->right->color == 'R'){
						T->left->color = 'B';
						T->right->color = 'B';
						T->color = 'R';
						return T;
					}
				}
			}
			return T;
		}else{
			T->right = rbInsert(T->right,x,N);
			if(T->right->color == 'R'){
				if(T->right->left->color == 'R' || T->right->right->color == 'R'){
					if(T->left->color != 'R'){
						if(T->right->right->color == 'R'){
							T = leftRotation(T);
							T->left->color = 'R';
							T->color = 'B';
							return T;
						}else{
							T->right = rightRotation(T->left);
							T = leftRotation(T);
							T->left->color = 'R';
							T->color = 'B';
							return T;
						}
					}else if(T->left->color == 'R'){
						T->left->color = 'B';
						T->right->color = 'B';
						T->color = 'R';
						return T;
					}
				}
			}
		}
		return T;
	}
	return T;
}




//Print
void print(node* n, node* N){
	if(n != NULL && n != N){
		printf("( %d %c ",n->key,n->color);
		print(n->left,N);
		print(n->right,N);
		printf(") ");
	}else{
		printf("( ) ");
	}
}


//`i', `d', `s', `b', `p' and `e'
int main(){
	rbTree* T = (rbTree*)malloc(sizeof(rbTree));
	node* N = (node*)malloc(sizeof(node));
	N->color = 'B';
	N->left = N->right = NULL;
	T->root = N;
	int x;
	node* newNode;
	while(scanf("%d",&x) != 0){
		newNode = createNode(x,N);
		T->root = rbInsert(T->root,newNode,N);
		if(T->root->color == 'R'){
			T->root->color = 'B';
		}
		print(T->root,N);
		printf("\n");
	}
	exit(0);
	return 0;
}
