#include<stdio.h>
#include<stdlib.h>


typedef struct node{
	int key;
	int deg;
	struct node* sib;
	struct node* parent;
	struct node* child;	
}node;


typedef struct heap{
	node* root;
}_heap;


node* createNode(int k){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->child = newNode->parent = newNode->sib = NULL;
	newNode->deg = 0;
	newNode->key = k;
	return newNode;
}


_heap* createHeap(){
	_heap* newHeap = malloc(sizeof(_heap));
	newHeap->root = NULL;
	return newHeap;
}


int printing(node* n,int l){
	if(n == NULL){
		return 0;
	}
	if(l == 1){
		node* temp = n;
		while(temp != NULL){
			printf("%d ",temp->key);
			temp = temp->sib;	
		}
		return 1;
	}
	int m = printing(n->child,l-1);
	node* temp = n->sib;
	while(temp != NULL){
		printing(temp->child,l-1);
		temp = temp->sib;
	}
	return m;
}


void level(node* n){
	int l = 1;
	printf("%d ",n->key);
	while(printing(n->child,l)){
		l++;
	}
}


void print(node* n){
	node* temp = n;
	while(temp != NULL){
		level(temp);
		temp = temp->sib;
	}
}


node* mergeHeaps(_heap* heap, _heap* newHeap){
	if(heap->root == NULL){
		return newHeap->root;
	}
	if(newHeap->root == NULL){
		return heap->root;
	}
	
	node* head;
	node* tail;
	node* traceHeap = heap->root;
	node* traceNewHeap = newHeap->root;
	
	if(heap->root->deg <= newHeap->root->deg){
		head = heap->root;
		traceHeap = traceHeap->sib;
	}else{
		head = newHeap->root;
		traceNewHeap = traceNewHeap->sib;
	}
	tail = head;
	
	while(traceHeap != NULL && traceNewHeap != NULL){
		if(traceHeap->deg <= traceNewHeap->deg){
			tail->sib = traceHeap;
			traceHeap = traceHeap->sib;
		}else{
			tail->sib = traceNewHeap;
			traceNewHeap = traceNewHeap->sib;
		}
		tail = tail->sib;
	}
	if(traceHeap == NULL){
		tail->sib = traceNewHeap;
	}else{
		tail->sib = traceHeap;
	}
	return head;
}


node* heapsUnion(_heap* heap, _heap* newHeap){
	node* requiredNode = mergeHeaps(heap,newHeap);
	heap->root = NULL;
	newHeap->root = NULL;
	
	if(requiredNode == NULL){
		return NULL;
	}
	
	node* prev = NULL;
	node* n = requiredNode;
	node* next = requiredNode->sib;
	
	while(next != NULL){
		if((n->deg != next->deg) || ((next->sib != NULL) && (next->sib->deg == n->deg))){
			prev = n;
			n = next;
		}else{
			if(n->key < next->key){
				n->sib = next->sib;
				next->parent = n;
				next->sib = n->child;
				n->child = next;
				n->deg = n->deg + 1;
			}else{
				if(prev == NULL){
					requiredNode = next;
				}else{
					prev->sib = next;
				}
				n->parent = next;
				n->sib = next->child;
				next->child = n;
				next->deg = next->deg + 1;
				n = next;
			}
		}
		next = n->sib;
	}
	return requiredNode;
}


void bHInsert(_heap* heap,_heap* newHeap){
	heap->root = heapsUnion(heap,newHeap);
	free(newHeap);
}


void heapRemove(_heap* heap, node* n, node* nb){
	if(n == heap->root){
		heap->root = n->sib;
	}else{
		nb->sib = n->sib;
	}
	
	node* newRoot = NULL;
	node* childNode = n->child;
	
	while(childNode != NULL){
		node* next = childNode->sib;
		childNode->sib = newRoot;
		childNode->parent = NULL;
		newRoot = childNode;
		childNode = next;
	}
	_heap* newHeap = createHeap();
	newHeap->root = newRoot;
	heap->root = heapsUnion(heap, newHeap);
	free(newHeap);
}



node* extractMin(_heap* heap, int x){
	if(heap->root == NULL){
		return NULL;
	}
	node* min = heap->root;
	node* minPrev = NULL;
	node* next = min->sib;
	node* nextPrev = min;
	
	while(next != NULL){
		if(next->key < min->key){
			min = next;
			minPrev = nextPrev;
		}
		nextPrev = next;
		next = next->sib;
	}
	if(x == 1){
		heapRemove(heap, min, minPrev);
	}
	return min;
}


node* find(node* n, int x){
	node* a = n;
	node* b = NULL;
	if(n->key == x){
		b = n;
		return b;
	}
	
	if(a->child != NULL && b == NULL){
		b = find(a->child, x);
	}
	
	if(a->sib != NULL && b == NULL){
		b = find(a->sib, x);
	}
	return b;
}


int decreaseKey(_heap* heap, int n, int m){
	node* requiredNode = find(heap->root, n);
	if(requiredNode == NULL){
		return 0;
	}
	requiredNode->key = m;
	node* a = requiredNode;
	node* b = requiredNode->parent;
	
	while(b != NULL && a->key < b->key){
		int i = a->key;
		a->key = b->key;
		b->key = i;
		a = b;
		b = b->parent;
	}
	return 1;
}


int bHDelete(_heap* heap, int x){
	int n = decreaseKey(heap,x,-1000000);
	if(n == 0){
		return 0;
	}
	extractMin(heap,1);
	return 1;
}


//imxrde
int main(){
	_heap* heap =  createHeap();
	heap->root = NULL;
	char ch;
	int x;
	int y;
	int r;
	node* requiredNode;
	node* resultNode;
	while(1){
		scanf("%c",&ch);
		switch(ch){
			case 'i':// insert key
				scanf("%d",&x);
				requiredNode = createNode(x);
				_heap* newHeap = createHeap();
				newHeap->root = requiredNode;
				bHInsert(heap,newHeap);
				break;
			case 'm'://print min
				resultNode = extractMin(heap,0);
				printf("%d\n",resultNode->key);
				break;
			case 'x'://extract min
				resultNode = extractMin(heap,1);
				printf("%d\n",resultNode->key);
				break;
			case 'r':// decrease key
				scanf("%d",&x);
				scanf("%d",&y);
				r = decreaseKey(heap,x,y);
				if(r == 0){
					printf("-1\n");
				}else{
					printf("%d\n",y);	
				}
				break;
			case 'd':// delete
				scanf("%d",&x);
				r = bHDelete(heap, x);
				if(r == 0){
					printf("-1\n");
				}else{
					printf("%d\n",x);	
				}
				break;
			case 'p'://print binomial heap
				print(heap->root);
				printf("\n");
				break;
			case 'e':
				exit(0);
			
		}
	}
	return 0;
}
