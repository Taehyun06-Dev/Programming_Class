#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

const int PRICE  = 3500;

typedef struct _BAL {
	int K_50;
	int K_10;
	int K_5;
	int K_1;
	int H_5;
}BAL;

void waitScreen(BAL* L) {
	system("cls");
	printf("\n처음부터 다시시도하세요.\n아무키나 누르면 처음으로 돌아갑니다.");
	char input = _getch();
	printScreen(L);
}

void purchase(BAL* L) {
	system("cls");
	printf("먼저, 원하는 식권의 갯수를 입력하십시오(최대 10개): ");
	int input;
	scanf_s("%d", &input);
	if (!(0 < input <= 10)) {
		waitScreen(L);
	}
	printf("\n총 가격은 %d원 [ %d (원) X %d (장) ] 입니다.\n", PRICE * input, PRICE, input);
	printf("지불 방법을 5만원권 1만원권 5천원권 1천원권 500원권 순으로 띄어서 입력하십시오.\n");
	int input_50k, input_10k, input_5k, input_1k, input_5h;
	scanf_s("%d %d %d %d %d", &input_50k, &input_10k, &input_5k, &input_1k, &input_5h);
	int totalprice = input_50k * 50000 + input_10k * 10000 + input_5k * 5000 + input_1k * 1000 + input_5h * 500;
	int totalbal = 3500 * input;
	int totalminus = totalprice - totalbal;
	int m_50k = totalminus / 50000;
	totalminus -= (m_50k * 50000);
	int m_10k = totalminus / 10000;
	totalminus -= (m_10k * 10000);
	int m_5k = totalminus / 5000;
	totalminus -= (m_5k * 5000);
	int m_1k = totalminus / 1000;
	totalminus -= (m_1k * 1000);
	int m_5h = totalminus / 500;
	if (m_50k > L->K_50 || m_10k > L->K_10 || m_5k > L->K_5 || m_1k > L->K_1 || m_5h > L->H_5 || totalminus > 0) {
		printf("\n거슬러 줄 수 없음!");
		Sleep(2000);
		waitScreen(L);
	}
	else {
		L->K_50 += input_50k - m_50k;
		L->K_10 += input_10k - m_10k;
		L->K_5 += input_5k - m_5k;
		L->K_1 += input_1k - m_1k;
		L->H_5 += input_5h - m_5h;
		printf("\n식권 지급완료!");
		Sleep(2000);
		waitScreen(L);
	}
}

void printScreen(BAL* L){
	printf("\n거스름돈 현황: \n5만원권: %d개, 1만원권: %d개, 5천원권: %d개, 1천원권: %d개, 500원권: %d개\n", L->K_50, L->K_10, L->K_5, L->K_1, L->H_5);
	printf("\n식권을 구입하시려면 아무키나 누르십시오.\n");
	char input = _getch();
	purchase(L);
}

void main() {
	BAL* bal = (BAL*)malloc(sizeof(BAL));
	bal->K_50 = 0;
	bal->K_10 = 10;
	bal->K_5 = 10;
	bal->K_1 = 10;
	bal->H_5 = 10;
	printScreen(bal);
}
