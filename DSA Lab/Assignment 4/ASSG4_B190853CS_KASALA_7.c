#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int k;
	int R;
	struct node* parent;
	struct node* next;
}node;

int c1 = 0;
int c2 = 0;
int c3 = 0;
int c4 = 0;

node makeSet(node a, int n){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->k = n;
	newNode->parent = newNode;
	newNode->R = 0;
	newNode->next = NULL;
	a.next = newNode;
	return a;
}


node* find(node* n, int c){
	if(c == 1){
		c1++;
	}
	if(c == 2){
		c2++;
	}
	if(n->parent == n){
		return n;
	}else{
		return find(n->parent,c);
	}
}


node* find_ByPC(node* n, int c){
	if(c == 3){
		c3++;
	}
	if(c == 4){
		c4++;
	}
	if(n->parent != n){
		n->parent = find_ByPC(n->parent, c);
	}
	return n->parent;
}


node* unionOne(node* a, node* b, int c){
	a = find(a, c);
	b = find(b, c);
	if(a == b){
		return a;
	}else{
		b->parent = a;
		return a;
	}
}

node* unionTwo(node* a, node* b, int c){
	a = find(a, c);
	b = find(b, c);
	if(a == b){
		return a;
	}else{
		if(a->R >= b->R){
			b->parent = a;
			if(a->R == b->R){
				a->R = a->R + 1;
			}
			return a;
		}else{
			a->parent = b;
			return b;
		}
	}
}

node* unionThree(node* a, node* b, int c){
	a = find_ByPC(a, c);
	b = find_ByPC(b, c);
	if(a == b){
		return a;
	}else{
		b->parent = a;
		return a;
	}
}

node* unionFour(node* a, node* b, int c){
	a = find_ByPC(a, c);
	b = find_ByPC(b, c);
	if(a == b){
		return a;
	}else{
		if(a->R >= b->R){
			b->parent = a;
			if(a->R == b->R){
				a->R = a->R + 1;
			}
			return a;
		}else{
			a->parent = b;
			return b;
		}
	}	
}

int main(){
	int a,b;
	node a1[50];
	node a2[50];
	node a3[50];
	node a4[50];
	for(int i = 0; i<50; i++){
		a1[i].next = NULL;
		a2[i].next = NULL;
		a3[i].next = NULL;
		a4[i].next = NULL;
	}
	char ch;
	int x, y;
	int c;
	node* p;
	node* q;
	node* r;
	node* s;
	while(1){
		scanf("%c",&ch);
		switch(ch){
			case 'm':
				scanf("%d",&x);
				if(a1[x].next != NULL){
					printf("-1\n");
					continue;
				}
				a1[x] = makeSet(a1[x], x);
				a2[x] = makeSet(a2[x], x);
				a3[x] = makeSet(a3[x], x);
				a4[x] = makeSet(a4[x], x);
				printf("%d\n",a1[x].next->k);
				break;
			case 'u':
				scanf("%d",&x);
				scanf("%d",&y);
				if(a1[x].next == NULL || a2[y].next == NULL){
					printf("-1\n");
					continue;
				}
				c = 1; 
				p = unionOne(a1[x].next,a1[y].next, c);
				c = 2;
				q = unionTwo(a2[x].next,a2[y].next, c);
				c = 3;
				r = unionThree(a3[x].next,a3[y].next, c);
				c = 4;
				s = unionFour(a4[x].next,a4[y].next, c);
				printf("%d %d %d %d\n",p->k,q->k,r->k,s->k);
				break;
			case 'f':
				scanf("%d",&x);
				if(a1[x].next == NULL){
					printf("-1\n");
					continue;
				}
				c = 1; 
				p = find(a1[x].next, c);
				c = 2;
				q = find(a2[x].next, c);
				c = 3;
				r = find_ByPC(a3[x].next, c);
				c = 4;
				s = find_ByPC(a4[x].next, c);
				printf("%d %d %d %d\n",p->k,q->k,r->k,s->k);
				break;
			case 's':
				printf("%d %d %d %d",c1, c2, c3, c4);
				exit(0);
		}
	}
	
	
	return 0;
}
