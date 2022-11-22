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

void printAll(linkedList* L) {

	printf("\n");
	node* p = L->head;
	while (p != NULL) {
		printf("학번: %d, 성적: %d\n", p->num, p->score);
		p = p->next;
	}

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
	if (L->head == NULL) {
		addData(L, num, score);
		return;
	}
	node* newNode = (node*)malloc(sizeof(node));
	newNode->num = num;
	newNode->score = score;
	newNode->next = NULL;
	node* p = L->head;
	while (p != NULL) {
		if (p->score < score) {
			printf("ang");
			newNode->next = p->next;
			p = newNode;
			return;
		}
		p = p->next;
	}
	addData(L, num, score);
}

void delMember() {

}

void main() {

	linkedList* L = initList();
	while (1) {
		printf("\n[메뉴] 1.추가   2.삭제   3.출력\n");
		char input = _getch();
		switch (input) {
		case '1':
			addMember(L);
			break;
		case '2':
			delMember();
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
