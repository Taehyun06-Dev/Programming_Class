#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX 30 //테스트 데이터의 갯수를 정한다. 
const int DUMMY_SIZE = 30; //C++은 가능하지만, C언어는 const의 선언 순서가 달라 MAX로 데이터 갯수를 한번 더 지정함.

void printMainWindow();
void printAskWindow();

typedef struct {
	int x;
	int y; 
	int z;
} TRI_VALUE;

static TRI_VALUE TRI_VALUE_LIST[MAX];


//방법 2로 구현 - 프로그램 1
void Solution_1() {
	for (int i = 0; i < DUMMY_SIZE; i++) {
		int x = TRI_VALUE_LIST[i].x;
		int y = TRI_VALUE_LIST[i].y;
		int z = TRI_VALUE_LIST[i].z;
		if (!(x < y + z)) {
			printf("%d, %d, %d 으(로) 이루어진 도형은 삼각형이 아닙니다. [X]\n", x, y, z);
			continue;
		}
		if (!(y < x + z)) {
			printf("%d, %d, %d 으(로) 이루어진 도형은 삼각형이 아닙니다. [X]\n", x, y, z);
			continue;
		}
		if (!(z < x + y)) {
			printf("%d, %d, %d 으(로) 이루어진 도형은 삼각형이 아닙니다. [X]\n", x, y, z);
			continue;
		}
		printf("%d, %d, %d 으(로) 이루어진 도형은 삼각형이 입니다.   [O]\n", x, y, z);
	}
	printAskWindow();
}

//방법 3으로 구현 - 프로그램 2
void Solution_2() {
	for (int i = 0; i < DUMMY_SIZE; i++) {
		int x = TRI_VALUE_LIST[i].x;
		int y = TRI_VALUE_LIST[i].y;
		int z = TRI_VALUE_LIST[i].z;
		if (!(x >= y)) {
			int temp = x;
			x = y;
			y = temp;
		}
		if (!(x >= z)) {
			int temp = x;
			x = z;
			z = temp;
		}
		if (x < y + z) {
			printf("%d, %d, %d 으(로) 이루어진 도형은 삼각형이 입니다.   [O]\n", x, y, z);
			continue;
		}
		printf("%d, %d, %d 으(로) 이루어진 도형은 삼각형이 아닙니다. [X]\n", x, y, z);
	}
	printAskWindow();
}

void createDummyData() {
	for (int i = 0; i < DUMMY_SIZE; i++) { 
		TRI_VALUE_LIST[i].x = rand() % 9 + 1;
		TRI_VALUE_LIST[i].y = rand() % 9 + 1;
		TRI_VALUE_LIST[i].z = rand() % 9 + 1;
	}
}

void printAskWindow() {
	printf("\n\n아무 키나 누르면 메인으로 이동합니다.\n\n");
	char tempReulst = _getch();
	printMainWindow();
}

void printMainWindow() {
	system("cls");
	printf("───────────────────────────────────── [ TRI DEMO ]──────────────────────────────────────\n");
	printf("\n");
	printf("☞ 작업을 선택하십시오. 본 시스템은 데모 데이터를 이용하여 운영됩니다.\n");
	printf("\n");
	printf("1 : 방법2 (프로그램 1)\n");
	printf("2 : 방법3 (프로그램 2)\n");
	printf("────────────────────────────────────────────────────────────────────────────────────────\n");
	char tempReulst = _getch();
	switch (tempReulst) {
	case '1':
		Solution_1();
		break;
	case '2':
		Solution_2();
		break;
	default:
		printf("\n잘못 눌렀습니다. 프로그람을 다시 키십시오. 신중히 누르십시오.");
		exit(1);
	}
}

void main() {
	createDummyData();
	printMainWindow();
}
