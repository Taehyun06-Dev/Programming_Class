#include <stdio.h>
#include <stdlib.h>

typedef struct _list {
	struct _node* cur;
	struct _node* head;
	struct _node* tail;
} linkedList;

typedef struct _node {
	int num;
	int mid;
	int final;
	struct _node* next;
} node;

void addData(linkedList* L, int n, int m, int f) {
	
	node* newNode = (node*)malloc(sizeof(node));
	
	newNode->num = n;
	newNode->mid = m;
	newNode->final = f;
	newNode->next = NULL;
	
	if (L->head == NULL && L->tail == NULL) {
		L->head = L->tail = newNode;
	}else{
		L->tail->next = newNode;
		L->tail = newNode;
	}
	L->cur = newNode;

}

void printAll(linkedList* L) {
	
	printf("\n");
	node* p = L->head;
	while (p != NULL) {
		printf("학번: %d, 중간: %d, 기말: %d \n", p->num, p->mid, p->final);
		p = p->next;
	}

}

int* getInput(linkedList* L) {
    
	static int inputList[3];
    	printf("학번 중간 기말점수 순으로 입력하십시오: ");
   	scanf_s("%d %d %d", &inputList[0], &inputList[1], &inputList[2]);
	return inputList;

}

linkedList* initList() {
	
	linkedList* L = (linkedList*)malloc(sizeof(linkedList));
	L->cur = NULL;
	L->head = NULL;
	L->tail = NULL;
	return L;

}

void main() {
	
	linkedList* L = initList();
	printf("종료는 0 0 0 을 입력하십시오.\n");

	while (1) {
		int* tempList = getInput(L);
		if (tempList[0] == 0) {
			printAll(L);
			exit(1);
		}
		addData(L, tempList[0], tempList[1], tempList[2]);
	}

}
