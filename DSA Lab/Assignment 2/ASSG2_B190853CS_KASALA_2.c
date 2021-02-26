#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct node{
	char* word;
	struct node* next;
}node;


typedef struct queue{
	struct node* head;
}queue;


node* createNode(int len){
	node* newNode;
	newNode = (node*)malloc(sizeof(node));
	char* word = (char*)malloc(sizeof(char)*len);
	newNode->next = NULL;
	newNode->word = word;
	return newNode;
}


queue* createHashTable(queue* hashTable,int m){
	for(int i=0; i<m; i++){
		queue* newQueue = (queue*)malloc(sizeof(queue));
		newQueue->head = NULL;
		*(hashTable+i) = *newQueue;
	}
	return hashTable;
}


void hashTableImplementation(char s[500], queue* A,int size){
	int i = 0;
	int j = 0;
	char* token = strtok(s, " ");
	int len = strlen(token);
	node* newNode = createNode(len);
	strcpy(newNode->word,token);
	while(token != NULL){
		len = strlen(token);
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
			newNode = createNode(len);
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
		int len = strlen(token);
		newNode = createNode(len);
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
	queue* hashTable = (queue*)malloc(sizeof(queue));
	hashTable = createHashTable(hashTable,size);
	hashTableImplementation(s,hashTable,size);
}
