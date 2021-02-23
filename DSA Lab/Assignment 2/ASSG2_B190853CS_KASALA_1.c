#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int* createHashTable(int* A,char type,int m){
	for(int i=0; i<m; i++){
		A[i] = 0;
	}
	return A;
}


int checkPrime(int num){
	int check = 1;
	for(int i=2; i<num-1; i++){
		if(num%i == 0){
			check = 0;
			return 0;
		}
	}
	if(check == 1){
		return 1;
	}
}


int hashIndex(char hashType, int x, int size, int i, int c1, int c2){
	if(hashType == 'a'){
		return ( ((x%size)+(i*c1)+(i*i*c2))%size );
	}else if(hashType == 'b'){
		int maxPrime;
		for(int j=size-1; j>0; j--){
			if(checkPrime(j)){
				maxPrime = j;
				break;
			}
		}
		return (((x%size) + i*(maxPrime-(x%maxPrime)))%size);
	}
}


int* hashTableInsert(char hashType,int* A, int x,int size,int c1, int c2){
	int index;
	for(int i=0; i<size; i++){
		if(hashType == 'a'){
			index = hashIndex(hashType,x,size,i,c1,c2);
		}else if(hashType == 'b'){
			index = hashIndex(hashType,x,size,i,c1,c2);
		}
		if(A[index] == 0 || A[index] == 2147483647 ){
			A[index] = x;
			return A;
		}
	}
}


int hashTableSearch(char hashType,int* A, int x, int size,int c1, int c2){
	int index;
	for(int i=0; i<size; i++){
		if(hashType == 'a'){
			index = hashIndex(hashType,x,size,i,c1,c2);
		}else if(hashType == 'b'){
			index = hashIndex(hashType,x,size,i,c1,c2);
		}
		if(A[index] == 0){
			printf("-1\n");
			return -1;
		}else if(A[index] == x){
			printf("1\n");
			return 1;
		}
	}
	printf("-1\n");
	return -1;
}


int* hashTableDelete(char hashType,int* A, int x, int size,int c1, int c2){
	int index;
	for(int i=0; i<size; i++){
		if(hashType == 'a'){
			index = hashIndex(hashType,x,size,i,c1,c2);
		}else if(hashType == 'b'){
			index = hashIndex(hashType,x,size,i,c1,c2);
		}
		if(A[index] == x){
			A[index] =2147483647;
			return A;
		}
	}
}


void printHashTable(int* A,int size){
	for(int i=0; i<size; i++){
		if(A[i] == 0 || A[i] == 2147483647){
			printf("%d ()\n",i);
		}else{
			printf("%d (%d)\n",i,A[i]);
		}
	}
}



//isdpt
void main(){
	char hashType;
	scanf("%c",&hashType);
	int size;
	scanf("%d",&size);
	int arr[size];
	int* hashTable;
	hashTable = createHashTable(arr,hashType,size);
	int c1,c2;
	if(hashType == 'a'){
		scanf("%d %d",&c1,&c2);
	}
	char ch;
	int x;
	while(1){
		scanf("%c",&ch);
		switch(ch){
			case 'i':
				scanf("%d",&x);
				hashTable = hashTableInsert(hashType,hashTable,x,size,c1,c2);
				break;
			case 's':
				scanf("%d",&x);
				hashTableSearch(hashType,hashTable,x,size,c1,c2);
				break;
			case 'd':
				scanf("%d",&x);
				hashTable = hashTableDelete(hashType,hashTable,x,size,c1,c2);
				break;
			case 'p':
				printHashTable(hashTable,size);
				break;
			case 't':
				exit(0);
		}
	}
	
	
	
	
	
	
	
}
