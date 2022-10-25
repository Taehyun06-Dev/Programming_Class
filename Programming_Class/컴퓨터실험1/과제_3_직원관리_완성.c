#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

void printMainWindow();
void printWaitWindow_MW();

const char* DATA_PATH = "C:\\Users\\bkcha\\Desktop\\data_2.txt";

typedef struct{
	int address;
	char name[11];
	int number;
	int date;
}WORKER;

static WORKER WORKER_LIST[10];


void fileRead() {
    FILE* dataFile = NULL;
    if (!(0 == fopen_s(&dataFile, DATA_PATH, "r+"))) {
        printf("\a\n%s경로의 파일에 접근할 수 없습니다.\n", DATA_PATH); //참고: '\a'는 윈도우상의 경고음이 들리게 해준다.
        printWaitWindow_MW();
        return;
    }
    int count = 0;
    while (!feof(dataFile)) {
        char name[11] = "";
        int date = 0;
        int num = 0;
        int addr = 0;
        fscanf_s(dataFile, "%d %s %d %d\n", &addr, name, sizeof(name), &num, &date);
        strcpy_s(WORKER_LIST[count].name, 11, name);
        WORKER_LIST[count].address = addr;
        WORKER_LIST[count].number = num;
        WORKER_LIST[count].date = date;
        count++;
    }
    printf("\n[정보] %d개의 파일 데이터를 로딩하였습니다.\n", count);
    fclose(dataFile);

    printWaitWindow_MW();
}

void fileSave() {
    int nResult = remove(DATA_PATH);
    if (nResult == -1) {
        printf("\a\n%s경로의 파일을 삭제할 수 없습니다.\n", DATA_PATH); //참고: '\a'는 윈도우상의 경고음이 들리게 해준다.
        printWaitWindow_MW();
        return;
    }
    FILE* dataFile = NULL;
    if (!(0 == fopen_s(&dataFile, DATA_PATH, "w+"))) {
        printf("\a\n%s경로의 파일에 작성할 수 없습니다.\n", DATA_PATH); //참고: '\a'는 윈도우상의 경고음이 들리게 해준다.
        printWaitWindow_MW();
        return;
    }
    for (int a = 0; a < 10; a++) {
        if (WORKER_LIST[a].address > 0) {
            fprintf(dataFile, "%d %s %d %d\n", WORKER_LIST[a].address, WORKER_LIST[a].name, WORKER_LIST[a].number, WORKER_LIST[a].date);
        }
    }
    fclose(dataFile);
}


void searchByAddr() {
    system("cls");
    printf("───────────────────────────────────── [ WORKER INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 검색할 사원번호를 입력하고 엔터를 누르십시오.\n");
    printf("\n");
    printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
    int tempInput;
    scanf_s("%d", &tempInput);
    for (int a = 0; a < 9; a++) {
        if (WORKER_LIST[a].address == tempInput) {
            system("cls");
            printf("───────────────────────────────────── [ WORKER INFO ]─────────────────────────────────────\n");
            printf("\n");
            printf("☞ 검색 결과:\n");
            printf("\n ");
            printf("%d: 사번: %d, 이름: %s, 전화번호: %d, 생년월일: %d\n", a, WORKER_LIST[a].address, WORKER_LIST[a].name, WORKER_LIST[a].number, WORKER_LIST[a].date);
            printf("\n");
            printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
            printWaitWindow_MW();
            return;
        }
    }
    system("cls");
    printf("───────────────────────────────────── [ WORKER INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 검색 결과가 없습니다.\n");
    printf("\n");
    printf("─────────────────────────────────────────────────────────────────────────────────────────\n");
    printWaitWindow_MW();
}

void addWorker() {
    system("cls");
    printf("───────────────────────────────────── [ WORKER INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 추가할 사원번호를 입력하고 엔터를 누르십시오.\n");
    printf("\n");
    printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
    int tempInput;
    scanf_s("%d", &tempInput);
    for (int a = 0; a < 9; a++) {
        if (WORKER_LIST[a].address == tempInput) {
            system("cls");
            printf("───────────────────────────────────── [ WORKER INFO ]─────────────────────────────────────\n");
            printf("\n");
            printf("☞ 이미 있는 사원 입니다.\n");
            printf("\n");
            printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
            printWaitWindow_MW();
            return;
        }
    }
    system("cls");
    printf("───────────────────────────────────── [ WORKER INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 다음의 형식으로 입력하십시오.\n");
    printf("☞ 이름 전화번호 생년월일\n");
    printf("☞ 예시) 홍길동 01012345678 20020102\n");
    printf("\n");
    printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
    char name[11];
    int num;
    int date;
    scanf_s("%s %d %d", name, sizeof(name), &num, &date);
    for (int a = 0; a < 9; a++) {
        if (WORKER_LIST[a].address >= 1) {
            continue;
        }
        WORKER_LIST[a].address = tempInput;
        WORKER_LIST[a].number = num;
        WORKER_LIST[a].date = date;
        strcpy_s(WORKER_LIST[a].name, 11, name);
        printf("\n[정보] 사번: %d, 이름: %s, 전화번호: %d, 생년월일: %d 이(가) 추가되었습니다.\n", tempInput, name, num, date);
        printWaitWindow_MW();
        return;
    }
    printf("\n[정보] 자리가 꽉 찼습니다!\n");
    printWaitWindow_MW();
    return;
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

void printAllData() {

    system("cls");
    printf("───────────────────────────────────── [ WORKER LIST ]─────────────────────────────────────\n");
    printf("\n");
    for (int a = 0; a < 9; a++) {
        printf("%d: 사번: %d, 이름: %s, 전화번호: %d, 생년월일: %d\n",a, WORKER_LIST[a].address, WORKER_LIST[a].name, WORKER_LIST[a].number, WORKER_LIST[a].date);
    }
    printf("\n");
    printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
    printWaitWindow_MW();
}

void printErrorWindow_MW() {
    system("cls");
    printf("───────────────────────────────────── [ WORKER INFO ]─────────────────────────────────────\n");
    printf("\n");
    printf("\n");
    printf("☞ 잘못 누르셨습니다. 처음부터 다시 시도하시려면 아무키나 누르십시오.\n");
    printf("\n");
    printf("\n");
    printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
    char tempReulst = _getch();
    printMainWindow();
}

void printMainWindow() {
    system("cls");
    printf("───────────────────────────────────── [ WORKER DEMO ]─────────────────────────────────────\n");
    printf("\n");
    printf("☞ 작업을 선택하십시오.\n");
    printf("\n");
    printf("1 : 모든 정보 조회 - 개발&테스트용\n");
    printf("2 : 사원 번호로 정보 조회\n");
    printf("\n");
    printf("3 : 사원 추가하기\n");
    printf("\n");
    printf("4: 저장 및 종료하기\n");
    printf("\n");
    printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
    char tempReulst = _getch();
    switch (tempReulst) {
    case '1':
        printAllData();
        break;
    case '2':
        searchByAddr();
        break;
    case '3':
        addWorker();
        break;
    case '4':
        fileSave();
        break;
    default:
        printErrorWindow_MW();
        break;
    }

}


void main() {
    fileRead();
    printMainWindow();
}
