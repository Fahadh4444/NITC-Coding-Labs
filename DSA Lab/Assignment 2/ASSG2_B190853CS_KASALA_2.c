#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct node{
	char word[500];
	struct node* next;
}node;


typedef struct queue{
	struct node* head;
}queue;


node* createNode(){
	node* newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode->next = NULL;
	return newNode;
}


queue* createHashTable(queue* A,int m){
	for(int i=0; i<m; i++){
		queue* newQueue = (queue*)malloc(sizeof(queue));
		newQueue->head = NULL;
		A[i] = *newQueue;
	}
	return A;
}


void hashTableImplementation(char s[500], queue* A,int size){
	int i = 0;
	int j = 0;
	char* token = strtok(s, " ");
	node* newNode = createNode();
	strcpy(newNode->word,token);
	while(token != NULL){
		int len = strlen(token);
		char check[500];
		strcpy(check,token);
		int index = (len*len)%size;
//		printf("%s\n",token);
		if(A[index].head == NULL){
			newNode->next = NULL;
			A[index].head = newNode;
		}else if(strcmp(A[index].head->word, check) == 0){
			token = strtok(NULL, " ");
			if(token == NULL){
				break;
			}
			newNode = createNode();
			strcpy(newNode->word,token);
			continue;
		}else{
			node* temp = A[index].head;
			while(1){
				if(temp->next == NULL){
					newNode->next = NULL;
					temp->next = newNode;
					break;
				}else{
					if(strcmp(temp->next->word, check) == 0){
						break;
					}else{
						temp = temp->next;
					}
				}
			}
		}
		token = strtok(NULL, " ");
		if(token == NULL){
			break;
		}
		newNode = createNode();
		strcpy(newNode->word,token);
	}
	
	for(int k=0; k<size; k++){
		printf("%d:",k);
		if(A[k].head == NULL){
			printf("null\n");
			continue;
		}else{
			printf("%s",A[k].head->word);
			node* temp = A[k].head;
			while(1){
				if(temp->next != NULL){
					printf("-%s",temp->next->word);
					temp = temp->next;
				}else{
					break;
				}
				
			}
		}
		printf("\n");
	}
}


void main(){
	int size;
	scanf("%d",&size);
	char s[500];
	getchar();
	gets(s);
	queue List[size];
	queue* hashTable;
	hashTable = createHashTable(List,size);
	hashTableImplementation(s,hashTable,size);
}
