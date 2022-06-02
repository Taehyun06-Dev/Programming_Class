#include <stdio.h>
#include <conio.h> //_getch() 함수를 사용하기 위해 선언
#include <string.h> //strtok() 함수를 사용하기 위해 선언
#include <stdlib.h>  //동적할당을 사용하기 위해 선언
#include <math.h> //제곱과 같은 연산자를 사용하기 위해 선언

#define firstFileLine "sepal.length | sepal.width | petal.length | petal.width | variety\n" //파일의 첫줄을 hard coding한다. 이유는 writeOriginalData() 함수 주석에 나와있다.
#define maxStrLength 15 //각 데이터의 최대 길이를 지정
#define putAndPrint(a) printf(##a); fputs(##a, writeFile); //전처리기를 활용하여 fprintf()과 printf()구문을 동시에 사용한다.
//line 141의 출력문을 보면 인자 갯수가 다 같지 않다. 따라서 각 인자 갯수별로 define 함수를 여러개 선언한다.
#define putAndPrint_2(a,b,c,d) printf(##a,b,c,d); fprintf(writeFile, ##a,b,c,d);   //인자 갯수가 다르므로 새 define을 선언
#define putAndPrint_3(a,b,c,d,e) printf(##a,b,c,d,e); fprintf(writeFile, ##a,b,c,d,e);  //인자 갯수가 다르므로 새 define을 선언 

const char* filePath = "C:\\Users\\bkcha\\Desktop\\iris.csv"; //불러올 데이터 파일 위치 (프로그램 실행시 도스창에서 타 경로로 지정가능)
const char* savePath = "C:\\Users\\bkcha\\Desktop\\result.txt"; //저장할 데이터 파일 위치

void initPath(); //함수 순서 문제를 해결하기 위해 컴파일러에게 해당 함수가 있음을 알려줌
void writeOriginalData(FILE* inputFile);  //함수 순서 문제를 해결하기 위해 컴파일러에게 해당 함수가 있음을 알려줌

//데이터 파일의 정보를 담아내기 위한 구조체
struct irisDataStruct {
    float sepalLength;
    float sepalWidth;
    float petalLength;
    float petalWidth;
    int variety; //메모리 절약을 위해 Setosa -> 1, Versicolor -> 2, Virginica -> 3 로 구분한다.
};

//꽃별로 꽃잎, 꽃 받침대의 가로세로 합을 모아둔 구초제 배열
//변수뒤에 _sl이 붙은것은 sepal.length(꽃잎 가로길이), _sw가 붙은것은 sepal.width(꽃잎 세로길이)...을 의미한다.
//_swc, _plc 처럼 c가 추가로 붙은것은 표준편차 관련 변수이다.
struct irisSumDataStruct {
    float sum_sl;
    float sum_sw;
    float sum_pl;
    float sum_pw;
    float sum_count;
};

//출력용 결과 데이터를 모아둔 구조체(전체)
struct irisDataTotal {
    float avg_total_sl;
    float avg_total_sw;
    float avg_total_pl;
    float avg_total_pw;
};

//출력용 결과 데이터를 모아둔 구조체 배열(꽃별로)
struct irisVarietyDataTotal {
    float favg_total_sl;
    float favg_total_sw;
    float favg_total_slc;
    float favg_total_swc;
    float favg_total_pl;
    float favg_total_plc;
    float favg_total_pw;
    float favg_total_pwc;
    float favg_count;
};

//모든 함수에서 접근이 가능하도록 정적 변수로 선언한다.
static struct irisSumDataStruct SUMDATA[3]; //순서대로 Setosa, Versicolor, Virginica의 성분별 합산 정보및 갯수를 담는다.
static struct irisDataTotal AVGDATA; //전체 평균의 정보를 담는다.
static struct irisVarietyDataTotal LASTDATA[3]; //순서대로 Setosa, Versicolor, Virginica의 성분별 평균, 표준편차 정보를 담는다.
static struct irisDataStruct sData[155]; //전체 파일 데이터가 담김
static int sizeTotal; //전체 데이터의 개수를 담는 변수
static char* saveFilePath; //저장 파일의 경로를 담는 변수

char* dataParse(char* inputText) { //inputText를 가공하는 함수

    int countNum = 0;
    char(*strArr)[maxStrLength] = (char(*)[maxStrLength])malloc(5 * 15 * sizeof(char)); //문자열 배열에 동적 할당
    char* context = NULL;
    char* ptr = strtok_s(inputText, ",", &context); //","를 기준으로 문자열을 쪼갠다.
    while (ptr != NULL) {
        countNum++;
        strcpy_s(strArr[countNum - 1], sizeof(strArr[countNum - 1]), ptr); //동적할당한 변수에 값을 대입한다.
        ptr = strtok_s(NULL, ",", &context);
    };
    return strArr;

}

int deterVariety(char* inputText) { //꽃의 종류를 판별하는 함수. Setosa -> 1, Versicolor -> 2, Virginica -> 3 로 값이 반환된다.

    char* ptr;
    ptr = strstr(inputText, "\"Setosa\""); //문자열에 공백이 포함되어 있다. 따라서 문자열을 비교하지 않고 포함하는지 확인한다.
    if (ptr) {
        return 1;
    }
    ptr = strstr(inputText, "\"Versicolor\"");
    if (ptr) {
        return 2;
    }
    ptr = strstr(inputText, "\"Virginica\"");
    if (ptr) {
        return 3;
    }
    //개인적으로 좋아하는 return 형 함수에서 if문 작성방법. else나 else if를 사용하지 않는다.(어차피 return에서 종료되므로)
    printf("\a\n\nnon-existing flower variety!! name: %s\n\n", inputText); //없는 꽃 종류라면 오류를 표시한다. 참고: '\a'는 윈도우 경고음을 출력한다.
    exit(1);

}

void setDataSum(float sl, float sw, float pl, float pw, int var) { //값들을 합산하는 함수

    SUMDATA[var - 1].sum_sl += sl;
    SUMDATA[var - 1].sum_sw += sw;
    SUMDATA[var - 1].sum_pl += pl;
    SUMDATA[var - 1].sum_pw += pw;
    SUMDATA[var - 1].sum_count++;
    LASTDATA[var - 1].favg_count++;

}

void resultPrint() { //결과 출력 함수
    Sleep(3200);
    system("cls");
    FILE* writeFile = NULL;
    if (!(0 == fopen_s(&writeFile, saveFilePath, "w"))) {
        printf("\a\n%s경로의 파일에 작성할 수 없습니다.\n", saveFilePath); //참고: '\a'는 윈도우상의 경고음이 들리게 해준다.;
        exit(1);
    }
    writeOriginalData(writeFile); //파일에 원래의 변수들을 작성하는 함수
    printf("\n☞ 3초뒤 결과창이 출력 됩니다.");
    Sleep(500);
    system("color 1");
    Sleep(500);
    system("color 2");
    printf("\r☞ 3초뒤 결과창이 출력 됩니다.");
    Sleep(500);
    system("color 3");
    Sleep(500);
    system("color 4");
    printf(" \r☞ 2초뒤 결과창이 출력 됩니다.");
    Sleep(500);
    system("color 5");
    Sleep(500);
    system("color 6");
    printf(" \r☞ 1초뒤 결과창이 출력 됩니다.");
    Sleep(1000);
    system("cls");
    system("color 7");
    putAndPrint("────────────────────────────────────────────────────────────────\n");
    putAndPrint("│                             [꽃잎]                           \n");
    putAndPrint("│                                                              \n");
    putAndPrint("│              Setosa     Versicolor    Virginica     전체     \n");
    putAndPrint("│                                                              \n");
    putAndPrint_3("│  가로평균    %.3f      %.3f         %.3f         %.3f    \n", LASTDATA[0].favg_total_sl, LASTDATA[1].favg_total_sl, LASTDATA[2].favg_total_sl, AVGDATA.avg_total_sl);
    putAndPrint("│                                                              \n");
    putAndPrint_2("│  표준편차    %.3f      %.3f         %.3f         ---      \n", LASTDATA[0].favg_total_slc, LASTDATA[1].favg_total_slc, LASTDATA[2].favg_total_slc);
    putAndPrint("│                                                              \n");
    putAndPrint_3("│  세로평균    %.3f      %.3f         %.3f         %.3f    \n", LASTDATA[0].favg_total_sw, LASTDATA[1].favg_total_sw, LASTDATA[2].favg_total_sw, AVGDATA.avg_total_sw);
    putAndPrint("│                                                              \n");
    putAndPrint_2("│  표준편차    %.3f      %.3f         %.3f         ---      \n", LASTDATA[0].favg_total_swc, LASTDATA[1].favg_total_swc, LASTDATA[2].favg_total_swc);
    putAndPrint("│                                                              \n");
    putAndPrint("────────────────────────────────────────────────────────────────\n");
    putAndPrint("│                            [꽃받침]                          \n");
    putAndPrint("│                                                              \n");
    putAndPrint("│              Setosa     Versicolor    Virginica     전체     \n");
    putAndPrint("│                                                              \n");
    putAndPrint_3("│  가로평균    %.3f      %.3f         %.3f         %.3f    \n", LASTDATA[0].favg_total_pl, LASTDATA[1].favg_total_pl, LASTDATA[2].favg_total_pl, AVGDATA.avg_total_pl);
    putAndPrint("│                                                              \n");
    putAndPrint_2("│  표준편차    %.3f      %.3f         %.3f         ---      \n", LASTDATA[0].favg_total_plc, LASTDATA[1].favg_total_plc, LASTDATA[2].favg_total_plc);
    putAndPrint("│                                                              \n");
    putAndPrint_3("│  세로평균    %.3f      %.3f         %.3f         %.3f    \n", LASTDATA[0].favg_total_pw, LASTDATA[1].favg_total_pw, LASTDATA[2].favg_total_pw, AVGDATA.avg_total_pw);
    putAndPrint("│                                                              \n");
    putAndPrint_2("│  표준편차    %.3f      %.3f         %.3f         ---      \n", LASTDATA[0].favg_total_pwc, LASTDATA[1].favg_total_pwc, LASTDATA[2].favg_total_pwc);
    putAndPrint("│                                                              \n");
    putAndPrint("────────────────────────────────────────────────────────────────\n");
    fclose(writeFile);


}

void cleanDataSum() { //전체 데이터를 계산하는 함수

    //전체 데이터를 기준으로 꽃잎, 꽂받침의 가로, 세로 길이 평균 계산
    AVGDATA.avg_total_sl = (SUMDATA[0].sum_sl + SUMDATA[1].sum_sl + SUMDATA[2].sum_sl) / sizeTotal;
    AVGDATA.avg_total_sw = (SUMDATA[0].sum_sw + SUMDATA[1].sum_sw + SUMDATA[2].sum_sw) / sizeTotal;
    AVGDATA.avg_total_pl = (SUMDATA[0].sum_pl + SUMDATA[1].sum_pl + SUMDATA[2].sum_pl) / sizeTotal;
    AVGDATA.avg_total_pw = (SUMDATA[0].sum_pw + SUMDATA[1].sum_pw + SUMDATA[2].sum_pw) / sizeTotal;


    //꽃별로 꽃잎, 꽃 받침대의 가로, 세로 길이 평균 계산
    for (int i = 0; i < 3; i++) {
        LASTDATA[i].favg_total_sl = SUMDATA[i].sum_sl / SUMDATA[i].sum_count;
        LASTDATA[i].favg_total_sw = SUMDATA[i].sum_sw / SUMDATA[i].sum_count;
        LASTDATA[i].favg_total_pl = SUMDATA[i].sum_pl / SUMDATA[i].sum_count;
        LASTDATA[i].favg_total_pw = SUMDATA[i].sum_pw / SUMDATA[i].sum_count;
    }

    //꽃별로 꽃잎, 꽃 받침대의 가로, 세로 길이 분산 계산
    for (int i = 2; i < sizeTotal; i++) {
        int var = sData[i].variety - 1;
        LASTDATA[var].favg_total_slc += (float)((pow((sData[i].sepalLength - LASTDATA[var].favg_total_sl), 2)) / LASTDATA[var].favg_count);
        LASTDATA[var].favg_total_swc += (float)((pow((sData[i].sepalWidth - LASTDATA[var].favg_total_sw), 2)) / LASTDATA[var].favg_count);
        LASTDATA[var].favg_total_plc += (float)((pow((sData[i].petalLength - LASTDATA[var].favg_total_pl), 2)) / LASTDATA[var].favg_count);
        LASTDATA[var].favg_total_pwc += (float)((pow((sData[i].petalWidth - LASTDATA[var].favg_total_pw), 2)) / LASTDATA[var].favg_count);
    }

    //한번에 제곱근 처리
    for (int var = 0; var < 3; var++) {  
        float tempf;
        tempf = LASTDATA[var].favg_total_slc;
        LASTDATA[var].favg_total_slc = sqrt(tempf);
        tempf = LASTDATA[var].favg_total_swc;
        LASTDATA[var].favg_total_swc = sqrt(tempf);
        tempf = LASTDATA[var].favg_total_plc;
        LASTDATA[var].favg_total_plc = sqrt(tempf);
        tempf = LASTDATA[var].favg_total_pwc;
        LASTDATA[var].favg_total_pwc = sqrt(tempf);
    }

    resultPrint();
}



void readData(char* path) { //파일을 읽는 주 함수

    FILE* dataFile = NULL;
    char line[255];

    if (0 == fopen_s(&dataFile, path, "rb")) { //해당 경로에 있는 파일을 정상적으로 열 수 있나 확인한다.
        
        int lineCount = 0;
        char(*lineData)[maxStrLength] = NULL; //dataParse() 함수 사용으로 첫줄을 배열로 직접 받아 올 수 있어 2차원 배열(header)을 활용하지 않고 lineData 변수에 값을 할당하였습니다.

        while (fgets(line, sizeof(line), dataFile) != NULL) {

            lineCount++;
            lineData = dataParse(line);

            if (lineCount == 1) { //첫번째 줄을 읽는 구문
                printf("첫줄 읽어오기: ");
                for (int i = 0; i < 5; i++) {
                    printf("%s ", lineData[i]);
                }
                printf("\n\n☞ 결과창 준비중입니다... 잠시 기다려주십시오."); //결과는 이미 나왔지만, 화려하게 보여주기 위해 약간의 양념을 친다.
            }else {
                sData[lineCount].sepalLength = atof(lineData[0]);
                sData[lineCount].sepalWidth = atof(lineData[1]);
                sData[lineCount].petalLength = atof(lineData[2]);
                sData[lineCount].petalWidth = atof(lineData[3]);
                sData[lineCount].variety = deterVariety(lineData[4]);
                setDataSum(sData[lineCount].sepalLength, sData[lineCount].sepalWidth, sData[lineCount].petalLength, sData[lineCount].petalWidth, sData[lineCount].variety);
            }
        }
        sizeTotal = lineCount - 1;
        cleanDataSum();
        fclose(dataFile);
        free(lineData); //동적할당 해제
        free(saveFilePath); //동적할당 해제
    }
    else { //만약 해당 경로에 파일이 존재하지 않다면, initPath() 함수로 돌아간다.
        printf("\a\n%s경로에 파일이 존재하지 않습니다.\n", path); //참고: '\a'는 윈도우상의 경고음이 들리게 해준다.
        printf("\n☞ 경로 설정창을 여시겠습니까? Y/N: \n");
        if (_getch() == 'y') {
            initPath();
        }else { //개인적으로 좋아하는 if-else문 작성방법. if가 끝나는 중괄호에 else를 붙인다.
            return;
        }
    }


}

void writeOriginalData(FILE* writeFile) {
    
    //원본 데이터의 첫줄을 그대로 가져오려면 새로운 정적 함수나 인자를 주는 방법을 활용해야 하는데,
    //해당 방법은 여기서는 메모리 낭비일 뿐이다. 따라서 첫줄은 hard coding으로 프로그램 내에 직접 작성한다.
    fprintf(writeFile, firstFileLine); 
    fprintf(writeFile, "──────────────────────────────────────────────────────────────────\n");
    for (int i = 2; i < 155; i++) { //구조상 데이터는 인자 2부터 저장되므로 for문을 2부터 시작한다.
        if (sData[i].variety != NULL) {
            fprintf(writeFile, "    %.1f      |     %.1f     |     %.1f      |     %.1f     | ", sData[i].sepalLength, sData[i].sepalWidth, sData[i].petalLength, sData[i].petalWidth);
            switch (sData[i].variety) { //저장할때 메모리 절약 차원으로 Setosa -> 1, Veriscolor -> 2, Vriginica -> 3으로 저장했으므로 데이터를 쓸때는 역으로 복구한다.
                case 1:
                    fprintf(writeFile, "%s\n", "Setosa");
                    break;
                case 2:
                    fprintf(writeFile, "%s\n", "Versicolor");
                    break;
                case 3:
                    fprintf(writeFile, "%s\n", "Virginica");
                    break;
            }
        }
    }
    fprintf(writeFile, "──────────────────────────────────────────────────────────────────\n"); //파일에 구분선 그리기
    
}


void initPath() { //나름대로의 그래픽으로 시각화한 경로 설정창. 파일 경로를 지정한다.
   
    int inputNum;
    system("cls");
    printf("─────────────────────────────────────[ 경로 설정창 ]─────────────────────────────────────\n");
    printf("\n");
    printf("[추천] 1: %s\n", filePath);
    printf("[추천] 2: iris.csv\n");
    printf("[일반] 3: 직접 입력\n");
    printf("\n");
    printf("───────────────────────────────────────────────────────────────────────────────────────────\n");
    printf("\n");
    printf("☞ 읽어올 파일 경로를 선택하십시오. 저장 경로도 동일하게 지정됩니다.:  ");
    scanf_s("%d", &inputNum, sizeof(inputNum));
    printf("\n\n☞ %d번 경로를 선택하셨습니다.\n\n", inputNum);
    saveFilePath = malloc(sizeof(char) * 40); //동적할당을 사용한다.
    switch (inputNum) {
        case 1:
            strcpy_s(saveFilePath, sizeof(char) * 40, savePath);
            readData(filePath);
            break;
        case 2:
            strcpy_s(saveFilePath, sizeof(char) * 40, "iris.csv");
            readData("iris.csv");
            break;
        case 3:
            printf("\n\n☞ 파일 경로를 직접 입력하십시오: ");
            char inputText[40];
            scanf_s("%s", inputText, sizeof(inputText));
            strcpy_s(saveFilePath, sizeof(char) * 40, inputText);
            readData(inputText);
            break;
        default:
            system("cls");
            initPath();
            break;
    }

}


void main() {initPath();} //선호하는 코딩 방법. 이와 같이 구문이 매우 짧을때는 한줄로 만들어 버린다.



