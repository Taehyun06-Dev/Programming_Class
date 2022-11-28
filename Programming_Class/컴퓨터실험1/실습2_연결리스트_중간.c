#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct _list {
	struct _node* head;
	struct _node* tail;
} linkedList;

typedef struct _node {
	int num;
	int score;
	struct _node* next;
} node;

/*
void addData(linkedList* L, int n, int m) {

	node* newNode = (node*)malloc(sizeof(node));

	newNode->num = n;
	newNode->score = m;
	newNode->next = NULL;

	if (L->head == NULL && L->tail == NULL) {
		L->head = L->tail = newNode;
	}
	else {
		L->tail->next = newNode;
		L->tail = newNode;
	}

}
*/


void printAll(linkedList* L) {

	printf("\n");
	node* p = L->head;
	double sum = 0;
	double counter = 0;
	while (p != NULL) {
		sum += p->score;
		counter++;
		printf("학번: %d, 성적: %d\n", p->num, p->score);
		p = p->next;
	}
	printf("\n평균: %.2f", sum / counter);

}


linkedList* initList() {

	linkedList* L = (linkedList*)malloc(sizeof(linkedList));
	L->head = NULL;
	L->tail = NULL;
	return L;

}


void addMember(linkedList* L) {

	printf("\n학번과 점수를 입력하십시오.");
	int num, score;
	scanf_s("%d %d", &num, &score);
	node* p = L->head;
	node* insert = NULL;
	char comp = 'f';

	node* newNode = (node*)malloc(sizeof(node));
	newNode->num = num;
	newNode->score = score;
	newNode->next = NULL;

	while (p != NULL && p->next != NULL) {
		if (p->score < score) {
			insert = p;
		}
		p = p->next;
		if (p->score >= score && insert != NULL) {
			node* temp = insert->next;
			newNode->next = temp;
			insert->next = newNode;
			comp = 't';
			break;
		}
	}

	if (comp == 'f') {

		if (L->head == NULL) {
			L->head = newNode;
		}
		else  if (L->tail == NULL) {
			L->head->next = L->tail = newNode;
		}
		else {
			L->tail->next = newNode;
		}


	}

}

void delMember(linkedList* L) {
	
	printf("\n삭제할 학번을 입력하십시오.");
	int num;
	scanf_s("%d", &num);
	char comp = 'f';
	node* p = L->head;

	if (p->num == num) {
		L->head = p->next;
		comp = 't';
		printf("삭제완료.\n");
	}
	
	while (p != NULL&&comp=='f') {
		if (p->next->num == num) {
			node* temp = p->next;
			if (temp->next != NULL) {
				p->next = temp->next;
			}else {
				p->next = NULL;
			}
			comp = 't';
			printf("삭제완료.\n");
			break;
		}
		p = p->next;
	}

	if (comp == 'f') {
		printf("에러: 일치하는 학번이 없습니다.\n");
	}

}

void main() {

	linkedList* L = initList();
	while (1) {
		printf("\n[메뉴] 1.추가   2.삭제   3.출력\n");
		char input = _getch();
		switch (input) {
		case '0':
			printf("종료합니다.\n");
			exit(1);
		case '1':
			addMember(L);
			break;
		case '2':
			delMember(L);
			break;
		case '3':
			printAll(L);
			break;
		default:
			printf("처음부터 다시 시도하십시오.\n");
			break;
		}
	}

}
