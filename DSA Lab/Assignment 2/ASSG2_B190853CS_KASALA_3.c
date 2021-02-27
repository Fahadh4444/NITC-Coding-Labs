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
		hashTable[i] = *newQueue;
	}
	return hashTable;
}



int Pow(int base,int expo){
	if(expo == 0){
		return 1;
	}
	int result = 1;
	for(int i=0; i<expo; i++){
		result = result*base;
	}
	return result;
}


int Index(char* word,int len){
	int arr[8];
	for(int i=0; i<8; i++){
		arr[i] = 0;
	}
	int j=0;
	while(j<len){
		if(word[j] == 'a'){
			arr[0] = 1;
			j++;
			continue;
		}else if(word[j] == 'b'){
			arr[1] = 1;
			j++;
			continue;	
		}else if(word[j] == 'c'){
			arr[2] = 1;
			j++;
			continue;	
		}else if(word[j] == 'd'){
			arr[3] = 1;
			j++;
			continue;	
		}else if(word[j] == 'e'){
			arr[4] = 1;
			j++;
			continue;	
		}else if(word[j] == 'f'){
			arr[5] = 1;
			j++;
			continue;	
		}else if(word[j] == 'g'){
			arr[6] = 1;
			j++;
			continue;	
		}else if(word[j] == 'h'){
			arr[7] = 1;
			j++;
			continue;	
		}
	}
	int num = 0;
	for(int i=0; i<8; i++){
		int power = Pow(2,i);
		num = num + (power*arr[i]);
	}
	return num;
//	for(int i=0; i<8; i++){
//		printf("%d",arr[i]);
//	}
//	printf("\n");
//	printf("%d\n",num);
}


queue* Insert(queue* hashTable, char* word){
	int len = strlen(word);
//	printf("%d",len);
	int index = Index(word,len);
	if(hashTable[index].head == NULL){
		node* newNode = createNode(len);
		strcpy(newNode->word,word);
		hashTable[index].head = newNode;
		return hashTable;
	}
	else if(strcmp(hashTable[index].head->word, word) >= 0){
		node* newNode = createNode(len);
		strcpy(newNode->word,word);
		node* temp = hashTable[index].head;
		hashTable[index].head = newNode;
		newNode->next = temp;
		return hashTable;
	}else{
		node* temp = hashTable[index].head;
		while(1){
				if(temp->next == NULL){
						node* newNode = createNode(len);
						strcpy(newNode->word,word);
						temp->next = newNode;
						return hashTable;
				}else if(strcmp(temp->next->word, word) >= 0){
						node* newNode = createNode(len);
						strcpy(newNode->word,word);
						node* check = temp->next;
						temp->next = newNode;
						newNode->next = check;
						return hashTable;
				}else{
						temp = temp->next;
					}
				}
		}
	}






void main(){
	queue* hashTable;
	queue List[255];
	hashTable = createHashTable(List,255);
	int size;
	scanf("%d",&size);
	char word[50];
	for(int i=0; i<size; i++){
        scanf("%s",word);
		hashTable = Insert(hashTable,word);
	}
	for(int k=0; k<255; k++){
		if(hashTable[k].head == NULL){
			continue;
		}else{
			node* temp = hashTable[k].head;
			printf("%s ",temp->word);
			while(1){
				if(temp->next != NULL){
					printf("%s ",temp->next->word);
					temp = temp->next;
				}else{
					break;
				}
				
			}
		}
		printf("\n");
	}
	
}
