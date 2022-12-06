#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void printScreen();
void printWaitScreen();


typedef struct _room {
	int number;
	long int enterDate;

}ROOM;

static ROOM* ROOM_LIST[50];

void green() {
	printf("\033[0;32m");
}

void yellow() {
	printf("\033[0;33m");
}

void reset() {
	printf("\033[0m");
}

void exitRoom() {
	system("cls");
	printf("────────────────────────────── [ ROOM EXIT ]──────────────────────────────\n\n");
	printf("☞    퇴실처리를 원하는 방 번호를 입력하십시오: ");
	int input;
	scanf_s("%d", &input);
	if (ROOM_LIST[input - 1]->number > 0) {
		
		//숙박일 처리
		long int interval = (long int)(time(NULL)) - ROOM_LIST[input - 1]->enterDate;
		int day = 0;
		if (interval <= 86400) {
			day = 1;
		}else {
			day = interval / 86400;
		}

		//인원수 처리
		int num = ROOM_LIST[input - 1]->number;
		int exceed = 0;
		if (num > 2) {
			exceed = num - 2;
		}

		//요금 처리
		int priceday = 50000 + exceed * 20000;
		int total = priceday * day;

		printf("\n\n☞    총 숙박 인원: %d명(기본 2인 + 추가 %d인)\n", num, exceed);
		printf("☞    1일당 요금: %d원(50000 + 20000 x %d)\n", priceday, exceed);
		printf("☞    총 숙박 일: %d일\n", day);
		printf("\n\n☞    총 요금: %d원(%d원 x %d일)\n\n", total, priceday, day);
		ROOM_LIST[input - 1]->number = 0;
		printf("☞%d번방 퇴실처리가 완료되었습니다.", input);

	}else {
		printf("\n\n☞    예약되지 않은 방 입니다.\n");
	}
	printWaitScreen();
}

void cancelRoom() {
	system("cls");
	printf("────────────────────────────── [ ROOM CANCEL ]──────────────────────────────\n\n");
	printf("☞    예약취소를 원하는 방 번호를 입력하십시오: ");
	int input;
	scanf_s("%d", &input);
	if (ROOM_LIST[input - 1]->number > 0) {
		ROOM_LIST[input - 1]->number = 0;
		printf("\n\n☞    %d번방 예약이 취소처리 되었습니다.\n", input);
	}else {
		printf("\n\n☞    예약되지 않은 방 입니다.\n");
	}
	printWaitScreen();
}

void printWaitScreen() {
	printf("\n☞    아무키나 누르시면 메인으로 돌아갑니다.\n");
	char temp = _getch();
	printScreen();
}

void bookRoom() {
	system("cls");
	printf("────────────────────────────── [ ROOM BOOKING ]──────────────────────────────\n\n");
	printf("☞    예약을 원하는 방 번호를 입력하십시오: ");
	int input;
	scanf_s("%d", &input);
	if (ROOM_LIST[input - 1]->number > 0) {
		printf("\n\n☞    %d번 방은 이미 예약되어 있습니다.\n", input);
	}else {
		int inputN;
		printf("\n☞    인원을 입력하십시오: ");
		scanf_s("%d", &inputN);
		ROOM_LIST[input - 1]->number = inputN;
		ROOM_LIST[input - 1]->enterDate = (long int)(time(NULL));
		system("cls");
		printf("────────────────────────────── [ ROOM BOOKING ]──────────────────────────────\n\n");
		printf("\n☞    %d번방, %d명 예약이 완료되었습니다.\n\n", input, inputN);
		printWaitScreen();
	}
	printWaitScreen();
}

void checkStatus() {
	system("cls");
	printf("────────────────────────────── [ ROOM STATUS ]──────────────────────────────\n\n");
	printf("                       ");
	green();
	printf("■ 예약 가능       ");
	yellow();
	printf("■ 예약 불가\n\n\n");
	reset();
	for (int i = 0; i < 50; i++) {
		if (ROOM_LIST[i]->number > 0) {
			yellow();
		}else {
			green();
		}
		if (i >= 9) {
			printf("Room %d       ", i + 1);
		}else {
			printf("Room %d        ", i + 1);
		}
		reset();
		if ((i + 1) % 5 == 0 && i > 0) {
			printf("\n\n");
		}
	}
	printWaitScreen();
}

void printScreen() {
	system("cls");
	printf("────────────────────────────── [ MENU ]──────────────────────────────\n\n");
	printf("\n\n  [1]      예약현황");
	printf("\n\n  [2]      예약하기");
	printf("\n\n  [3]      예약취소");
	printf("\n\n\n  [4]      정산하기\n\n\n\n");
	printf("────────────────────────────── [ MENU ]──────────────────────────────\n\n");
	char temp = _getch();
	switch (temp) {
		case '1':
			checkStatus();
			break;
		case '2':
			bookRoom();
			break;
		case '3':
			cancelRoom();
			break;
		case '4':
			exitRoom();
			break;
		default:
			printf("\n☞    잘 못 누르셨습니다.\n");
			printWaitScreen();
			break;
	}
}

void main() {
	for (int i = 0; i < 50; i++) {
		ROOM_LIST[i] = (ROOM*)malloc(sizeof(ROOM));
	}
	printScreen();
}
