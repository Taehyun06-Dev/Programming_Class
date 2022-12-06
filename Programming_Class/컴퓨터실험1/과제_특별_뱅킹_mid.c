#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

typedef struct _room {
	int number;
	long enterDate;
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

}

void cancelRoom() {

}

void printBookComplete(int roomNum) {

}

void bookRoom() {
	system("cls");
	printf("────────────────────────────── [ ROOM BOOKING ]──────────────────────────────\n\n");
	printf("☞    예약을 원하는 방 번호를 입력하십시오: ");
	int input;
	scanf_s("%d", &input);
	if (ROOM_LIST[input - 1]->number > 0) {
		printf("\n\n☞    %d번 방은 이미 예약되어 있습니다.\n ", input);
		printf("☞    다른 방을 선택하시려면 [1], 메인으로 돌아가려면 아무키나 누르십시오\n");
		char inputC = _getch();
		if (inputC == '1') {
			bookRoom();
			return;
		}
			printScreen();
			return;
		int inputN;
		printf("☞    인원을 입력하십시오.");
		scanf_s("%d", &inputN);
		ROOM_LIST[input - 1]->number = inputN;
		printBookComplete(input - 1);
	}
}

void checkStatus() {
	system("cls");
	printf("────────────────────────────── [ ROOM STATUS ]──────────────────────────────\n\n");
	printf("☞                      ");
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
		if ((i+1) % 5 == 0 && i > 0) {
			printf("\n\n");
		}
	}
}

void printScreen() {

}

void main() {
	for (int i = 0; i < 50; i++) {
		ROOM_LIST[i] = (ROOM*)malloc(sizeof(ROOM));
	}
	checkStatus();
}
