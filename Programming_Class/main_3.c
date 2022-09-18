#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#define MAX 30 //최대 계좌 생성 갯수를 정의함.
//C언어는 MAP을 사용할 수 없으므로 구조체 배열로 구현한다. 다만, index형 검색이 아니라 전체 배열에서 계좌 번호값을 검색하므로 검색 속도가 느리다.

void putDemoData();
void printMainWindow();
void printWaitWindow_MW();
char checkPass();

typedef struct {
    char userName[11];
    int userPassword;
    long userBalance;
    long userAddress;
} BANK_ACCOUNT;

static BANK_ACCOUNT BANK_ACCOUNT_LIST[MAX];


void transferBal() {
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 본인의 계좌번호를 입력하고 엔터를 누르십시오.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    long tempInput;
    scanf_s("%ld", &tempInput);
    for (int a = 0; a < 9; a++) {
        if (BANK_ACCOUNT_LIST[a].userAddress == tempInput) {
            system("cls");
            printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
            printf("\n");
            printf("☞ 본인 계좌의 다음 사항을 확인하십시오.\n");
            printf("\n");
            printf("   [본인] 고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
            printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
            printf("\n\n☞ 맞으면 Y, 아니면 아무키나 누르십시오.");
            char tempInput_s = _getch();
            if (tempInput_s == 'y' || tempInput_s == 'Y') {
                if (checkPass(BANK_ACCOUNT_LIST[a].userPassword) == 1) {
                    system("cls");
                    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                    printf("\n");
                    printf("☞ 이체할 계좌를 입력하고 엔터를 누르십시오.\n");
                    printf("\n");
                    printf("   [본인] 고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                    printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                    long tempInput_3;
                    scanf_s("%ld", &tempInput_3);
                    for (int b = 0; b < 9; b++) {
                        if (BANK_ACCOUNT_LIST[b].userAddress == tempInput_3) {
                            system("cls");
                            printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                            printf("\n");
                            printf("☞ 상대 계좌의 다음 사항을 확인하십시오.\n");
                            printf("\n");
                            printf("   [본인] 고객명: %s, 계좌번호: %ld\n\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                            printf("   [상대] 고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[b].userName, BANK_ACCOUNT_LIST[b].userAddress);
                            printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                            printf("\n\n☞ 맞으면 Y, 아니면 아무키나 누르십시오.");
                            tempInput_s = _getch();
                            if (tempInput_s == 'y' || tempInput_s == 'Y') {
                                system("cls");
                                printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                                printf("\n");
                                printf("☞ 다음 계좌에서 이체할 금액을 입력하고 엔터를 누르십시오.\n");
                                printf("\n");
                                printf("   [본인] 고객명: %s, 계좌번호: %ld\n\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                                printf("   [상대] 고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[b].userName, BANK_ACCOUNT_LIST[b].userAddress);
                                printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                                long tempInput_m23;
                                scanf_s("%ld", &tempInput_m23);
                                if (tempInput_m23 > BANK_ACCOUNT_LIST[a].userBalance) {
                                    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                                    printf("\n");
                                    printf("☞ 잔액이 부족합니다.\n");
                                    printf("\n");
                                    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
                                    printWaitWindow_MW();
                                    break;
                                }
                                system("cls");
                                printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                                printf("\n");
                                printf("☞ 해당 계좌로 다음 사항이 처리됩니다.\n");
                                printf("\n");
                                printf("   [본인] 고객명: %s, 계좌번호: %ld\n\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                                printf("   [상대] 고객명: %s, 계좌번호: %ld\n\n", BANK_ACCOUNT_LIST[b].userName, BANK_ACCOUNT_LIST[b].userAddress);
                                printf("\n");
                                printf("   거래명: 이체, 금액: %d원\n", tempInput_m23);
                                printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                                printf("\n\n☞ 맞으면 Y, 아니면 아무키나 누르십시오.");
                                char tempInput_h = _getch();
                                if (tempInput_h == 'y' || tempInput_h == 'Y') {
                                    BANK_ACCOUNT_LIST[a].userBalance -= tempInput_m23;
                                    BANK_ACCOUNT_LIST[b].userBalance += tempInput_m23;
                                    system("cls");
                                    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                                    printf("\n");
                                    printf("☞ 해당 거래가 처리되었습니다.\n");
                                    printf("\n");
                                    printf("   [본인] 고객명: %s, 계좌번호: %ld, 잔액: %ld\n\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress, BANK_ACCOUNT_LIST[a].userBalance);
                                    printf("   [상대] 고객명: %s, 계좌번호: %ld\n\n", BANK_ACCOUNT_LIST[b].userName, BANK_ACCOUNT_LIST[b].userAddress);
                                    printf("\n");
                                    printf("   거래명: 이체, 금액: %d원\n", tempInput_m23);
                                    printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                                    printWaitWindow_MW();
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 처음부터 다시 시도하십시오.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    printWaitWindow_MW();
}

void withdrawBal() {
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 출금할 계좌번호를 입력하고 엔터를 누르십시오.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    long tempInput;
    scanf_s("%ld", &tempInput);
    for (int a = 0; a < 9; a++) {
        if (BANK_ACCOUNT_LIST[a].userAddress == tempInput) {
            system("cls");
            printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
            printf("\n");
            printf("☞ 출금 계좌의 다음 사항을 확인하십시오.\n");
            printf("\n");
            printf("   고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
            printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
            printf("\n\n☞ 맞으면 Y, 아니면 아무키나 누르십시오.");
            char tempInput_s = _getch();
            if (tempInput_s == 'y' || tempInput_s == 'Y') {
                if (checkPass(BANK_ACCOUNT_LIST[a].userPassword) == 1) {
                    system("cls");
                    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                    printf("\n");
                    printf("☞ 다음 계좌에서 출금할 금액을 입력하고 엔터를 누르십시오.\n");
                    printf("\n");
                    printf("   고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                    printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                    long tempInput_m2;
                    scanf_s("%ld", &tempInput_m2);
                    system("cls");
                    if (tempInput_m2 > BANK_ACCOUNT_LIST[a].userBalance) {
                        printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                        printf("\n");
                        printf("☞ 잔액이 부족합니다.\n");
                        printf("\n");
                        printf("────────────────────────────────────────────────────────────────────────────────────────\n");
                        printWaitWindow_MW();
                        break;
                    }
                    else {
                        system("cls");
                        printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                        printf("\n");
                        printf("☞ 해당 계좌로 다음 사항이 처리됩니다.\n");
                        printf("\n");
                        printf("   고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                        printf("\n");
                        printf("   거래명: 출금, 금액: %d원\n", tempInput_m2);
                        printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                        printf("\n\n☞ 맞으면 Y, 아니면 아무키나 누르십시오.");
                        char tempInput_h = _getch();
                        if (tempInput_h == 'y' || tempInput_h == 'Y') {
                            BANK_ACCOUNT_LIST[a].userBalance -= tempInput_m2;
                            system("cls");
                            printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                            printf("\n");
                            printf("☞ 해당 거래가 처리되었습니다.\n");
                            printf("\n");
                            printf("   고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                            printf("\n");
                            printf("   거래명: 출금, 금액: %d원, 잔액: %d원\n", tempInput_m2, BANK_ACCOUNT_LIST[a].userBalance);
                            printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                            printWaitWindow_MW();
                            break;
                        }
                    }
                }
                else {
                    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                    printf("\n");
                    printf("☞ 비밀번호가 다릅니다.\n");
                    printf("\n");
                    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
                    printWaitWindow_MW();
                    break;
                }
               
            }
        }
    }
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 처음부터 다시 시도하십시오.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    printWaitWindow_MW();
}

void depositBal() {
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 입금할 계좌번호를 입력하고 엔터를 누르십시오.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    long tempInput;
    scanf_s("%ld", &tempInput);
    for (int a = 0; a < 9; a++) {
        if (BANK_ACCOUNT_LIST[a].userAddress == tempInput) {
            system("cls");
            printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
            printf("\n");
            printf("☞ 입금 계좌의 다음 사항을 확인하십시오.\n");
            printf("\n");
            printf("   고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);           
            printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
            printf("\n\n☞ 맞으면 Y, 아니면 아무키나 누르십시오."); 
            char tempInput_s = _getch();
            if (tempInput_s == 'y' || tempInput_s == 'Y') {
                system("cls");
                printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                printf("\n");
                printf("☞ 다음 계좌로 입금할 금액을 입력하십시오.\n");
                printf("\n");
                printf("   고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                long tempInput_m;
                scanf_s("%ld", &tempInput_m);
                system("cls");
                printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                printf("\n");
                printf("☞ 해당 계좌로 다음 사항이 처리됩니다.\n");
                printf("\n");
                printf("   고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                printf("\n");
                printf("   거래명: 입금, 금액: %d원\n", tempInput_m);
                printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                printf("\n\n☞ 맞으면 Y, 아니면 아무키나 누르십시오.");
                char tempInput_h = _getch();
                if (tempInput_h == 'y' || tempInput_h == 'Y') {
                    BANK_ACCOUNT_LIST[a].userBalance += tempInput_m;
                    system("cls");
                    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                    printf("\n");
                    printf("☞ 해당 거래가 처리되었습니다.\n");
                    printf("\n");
                    printf("   고객명: %s, 계좌번호: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userAddress);
                    printf("\n");
                    printf("   거래명: 입금, 금액: %d원, 잔액: %d원\n", tempInput_m, BANK_ACCOUNT_LIST[a].userBalance);
                    printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
                    printWaitWindow_MW();
                    break;
                }
            }
        }
    }
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 처음부터 다시 시도하십시오.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    printWaitWindow_MW();
}

void searchByName() {
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 검색할 고객명을 입력하고 엔터를 누르십시오.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    char tempInput[10];
    scanf_s("%s", &tempInput, 11);
    for(int a = 0; a < 9; a++) {
        if(strcmp(BANK_ACCOUNT_LIST[a].userName, tempInput) == 0){
            if (checkPass(BANK_ACCOUNT_LIST[a].userPassword) == 1) {
                system("cls");
                printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                printf("\n");
                printf("☞ 검색 결과:\n");
                printf("\n ");
                printf("   고객명: %s, 비밀번호: %d, 계좌번호: %ld, 잔액: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userPassword, BANK_ACCOUNT_LIST[a].userAddress, BANK_ACCOUNT_LIST[a].userBalance);
                printf("\n");
                printf("────────────────────────────────────────────────────────────────────────────────────────\n");
                printWaitWindow_MW();
                break;
            }else {
                printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                printf("\n");
                printf("☞ 비밀번호가 다릅니다.\n");
                printf("\n");
                printf("────────────────────────────────────────────────────────────────────────────────────────\n");
                printWaitWindow_MW();
                break;
            }
        }
    }
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 검색 결과가 없습니다.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    printWaitWindow_MW();
}

void searchByAddr() {
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 검색할 계좌번호를 입력하고 엔터를 누르십시오.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    long tempInput;
    scanf_s("%ld", &tempInput);
    for(int a = 0; a < 9; a++) {
        if(BANK_ACCOUNT_LIST[a].userAddress == tempInput) {
            if (checkPass(BANK_ACCOUNT_LIST[a].userPassword) == 1) {
                system("cls");
                printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                printf("\n");
                printf("☞ 검색 결과:\n");
                printf("\n ");
                printf("   고객명: %s, 비밀번호: %d, 계좌번호: %ld, 잔액: %ld\n", BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userPassword, BANK_ACCOUNT_LIST[a].userAddress, BANK_ACCOUNT_LIST[a].userBalance);
                printf("\n");
                printf("────────────────────────────────────────────────────────────────────────────────────────\n");
                printWaitWindow_MW();
                break;
            }else {
                printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
                printf("\n");
                printf("☞ 비밀번호가 다릅니다.\n");
                printf("\n");
                printf("────────────────────────────────────────────────────────────────────────────────────────\n");
                printWaitWindow_MW();
                break;
            }
        }
    }
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 검색 결과가 없습니다.\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    printWaitWindow_MW();
}

void printAllData() {
   
    system("cls");
    printf("───────────────────────────────────── [ BANK LIST ]─────────────────────────────────────\n");
    printf("\n");
    for(int a = 0; a < 9; a++) {
        printf("%d: %s, 비밀번호: %d, 계좌번호: %ld, 잔액: %ld\n", a, BANK_ACCOUNT_LIST[a].userName, BANK_ACCOUNT_LIST[a].userPassword, BANK_ACCOUNT_LIST[a].userAddress, BANK_ACCOUNT_LIST[a].userBalance);
    }
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    printWaitWindow_MW();
}

void createDemoData() {

    putDemoData(0, "홍길동", 1234, 0, 100100);
    putDemoData(1, "김길동", 1235, 100, 200200);
    putDemoData(2, "최길동", 1236, 200, 300300);
    putDemoData(3, "차길동", 1237, 300, 400400);
    putDemoData(4, "강길동", 1238, 400, 500500);
    putDemoData(5, "노길동", 1239, 500, 600600);
    putDemoData(6, "마길동", 1240, 600, 700700);
    putDemoData(7, "무길동", 1241, 700, 800800);
    putDemoData(8, "괙길동", 1242, 0, 900900);

}

void putDemoData(int index, char* name, int pass, long balance, long addr) {

    strcpy_s(BANK_ACCOUNT_LIST[index].userName, 11, name);
    BANK_ACCOUNT_LIST[index].userPassword = pass;
    BANK_ACCOUNT_LIST[index].userBalance = balance;
    BANK_ACCOUNT_LIST[index].userAddress = addr;

}

void printWaitWindow_MW() {
    printf("\n");
    printf("\n");
    printf("\n");
    printf("☞ 아무키나 누르시면 메인 화면으로 이동합니다.\n");
    printf("\n");
    printf("\n");
    char tempReulst = _getch();
    printMainWindow();
}

void printErrorWindow_MW() {
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("\n");
    printf("☞ 잘못 누르셨습니다. 처음부터 다시 시도하시려면 아무키나 누르십시오.\n");
    printf("\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    char tempReulst = _getch();
    printMainWindow();
}

void printGoodByeWindow() {
    system("cls");
    printf("\n");
    printf("\n");
    printf("                                                                                                         \n");
    printf("        ■■■■■    ■■■■■    ■■■■■    ■■■■     ■■■■      ■      ■    ■■■■■    \n");
    printf("        ■            ■      ■    ■      ■    ■      ■   ■      ■      ■  ■      ■            \n");
    printf("        ■    ■■    ■      ■    ■      ■    ■      ■   ■  ■■          ■        ■■■■■    \n");
    printf("        ■      ■    ■      ■    ■      ■    ■      ■   ■      ■        ■        ■            \n");
    printf("        ■■■■■    ■■■■■    ■■■■■    ■■■■     ■■■■          ■        ■■■■■    \n");
    printf("                                                                                                         \n");
    printf("\n");
    printf("\n");
    Sleep(300);
    system("color 1");
    Sleep(300);
    system("color 0");
    Sleep(300);
    system("color 2");
    Sleep(300);
    system("color 3");
    Sleep(300);
    system("color 4");
    Sleep(300);
    system("color 5");
    Sleep(300);
    system("color 3");
    Sleep(300);
    system("color 1");
    exit(1);
}

void printMainWindow() {
    system("cls");
    printf("───────────────────────────────────── [ BANK DEMO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 작업을 선택하십시오. 본 시스템은 데모 데이터를 이용하여 운영됩니다.\n");
    printf("☞ 숫자 입력란에는 숫자만 입력하시고, 꼬일시 껏다가 켜주시기 바랍니다.\n");
    printf("\n");
    printf("1 : 모든 정보 조회 - 개발&테스트용\n");
    printf("2 : 계좌 번호로 정보 조회(잔액조회)\n");
    printf("3 : 사용자명으로 정보 조회(잔액조회)\n");
    printf("\n");
    printf("4 : 입금\n");
    printf("5 : 출금\n");
    printf("6 : 이체\n");
    printf("\n");
    printf("7 : 종료 - 애니메이션 포함\n");
    printf("\n");
    printf("────────────────────────────────────────────────────────────────────────────────────────\n");
    char tempReulst = _getch();
    switch (tempReulst) {
    case '1':
        printAllData();
        break;
    case '2':
        searchByAddr();
        break;
    case '3':
        searchByName();
        break;
    case '4':
        depositBal();
        break;
    case '5':
        withdrawBal();
        break;
    case '6':
        transferBal();
        break;
    case '7':
        printGoodByeWindow();
        break;
    default:
        printErrorWindow_MW();
        break;
    }

}

char checkPass(int pass) {
    system("cls");
    printf("───────────────────────────────────── [ BANK INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 비밀번호 4자리를 입력하고 엔터를 누르십시오.\n");
    printf("\n────────────────────────────────────────────────────────────────────────────────────────\n");
    int tempInput_m;
    scanf_s("%d", &tempInput_m);
    if (tempInput_m == pass) {
        return 1;
    }
    return 0;
}

void main() {
    createDemoData();
    printMainWindow();
}

