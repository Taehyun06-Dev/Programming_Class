#include <stdio.h>
#include <stdlib.h> //동적 메모리 관련 라이브러리 불러오기.
#include <string.h> //동적 메모리 관련 strcopy 함수 사용을 위한 라이브러리.

//202202177 차태현

// 1번 문제 시작
char* get_bloodPressure(int var){ //혈압 수치에 따라 고혈압, 정상혈압, 저혈압 중 하나를 return 하는 함수. 포인터를 이용해 문자열을 리턴한다.

    if(var > 120){
        return "고혈압";
    }
    if(var >= 80){
        return "정상혈압";
    }
    return "저혈압";

}

void func_bloodPressureProblem(){ //메인 함수.

    int bloodPressure;

    while(1) {
        scanf_s("%d", &bloodPressure, sizeof(bloodPressure));
        if(bloodPressure <= 0){
            printf("종료합니다.");
            break; //0이하 값이 입력되면 while 문을 빠져나간다.
        }
        printf("%d은 %s\n",bloodPressure, get_bloodPressure(bloodPressure)); //get_bloodPressure 함수를 호출하여 수치에 따른 문자열 값을 구해온다.
    }

}
// 1번 문제 종료

// 2번 문제 시작
void func_ChangeStrIntProblem(){ //메인 함수.
    char cData[128] = {'A'}; //배열을 초기화 하지 않으면 정크값이 들어가므로 배열을 초기화한다.(이하 모든 배열변수 동일)
    int sum;

    while(1) {
        sum = 0;
        scanf_s("%s", cData, sizeof(cData));
        for (int i = 0; cData[i] != '\0'; i++) {
            int x = cData[i] - '0';
            if (x >= 49) { //문자(char)을 제시된 방법으로 바꾸니 49 이상의 값이 나와 해당 값을 continue로 거름. 즉, 문자를 거름.
                continue;
            }
            sum += x; //숫자만 더하기
        }
        if (sum == 0) {
            printf("숫자 문자 개수 : 0\n종료합니다.");
            return;
        }
        printf("숫자 문자 합계(sum)  : %d\n", sum);
    }

}
//2번 문제 종료

//3번 문제 시작
void func_nYearProblem(){

    char* if_odd = malloc(sizeof(char)*2); //"홀수", "짝수"라는 문자열을 저장하기 위해 동적 메모리를 할당한다.
    char* if_leap = malloc(sizeof(char)*2); //"윤년", "평년"이라는 문자열을 저장하기 위해 동적 메모리를 할당한다.
    int nYear;

    while(1) {
        scanf_s("%d", &nYear, sizeof(nYear));

        if(nYear <= 0){ //0이하 값이 입력되면 종료
            printf("종료합니다.\n");
            free(if_leap); //동적 메모리를 해제한다.
            free(if_odd); //동적 메모리를 해제한다.
            return;
        }

        //짝홀 판별 구문
        if(nYear % 2 == 0){
            strcpy(if_odd, "짝수"); //동적 메모리와 관련하여 직접 값을 입력하지 않는다.(이하동일)
        }else{
            strcpy(if_odd, "홀수");
        }

        //윤년 판별 구문
        if(((nYear % 4 == 0) && (nYear % 100 != 0)) || (nYear % 400 == 0)){ //(nYear변수가 4의 배수이고, 100의 배수가 아니다) 또는 (400의 배수이다)구문.
            strcpy(if_leap, "윤년");
        }else{
            strcpy(if_leap, "평년");
        }
        printf("%d은 %s, %s\n", nYear, if_odd, if_leap);

    }

}
//3번 문제 종료

//4번 문제 시작
char get_Grade(int val){ //점수별 학점(등급)을 받아오는 함수.

    if(val >= 90){
        return 'A';
    }
    if(val >= 80){
        return 'B';
    }
    if(val >= 70){
        return 'C';
    }
    if(val >= 60){
        return 'D';
    }
    return 'F';

}

//4번 문제의 첫번째 풀이. for문을 2개 사용한다.
void func_GradeProblem(){ //메인 함수.

    int nScore;
    int nData[20] = {0};
    int count = -1;

    while(1){
        scanf_s("%d", &nScore, sizeof(nScore));
        if(nScore <= 0){
            printf("종료합니다.\n"); //0이하 값이 입력되면 종료.
            break;
        }
        count ++;
        nData[count] = nScore;
        printf("점수 %d, 학점 %c\n", nScore, get_Grade(nScore));
    }

    printf("점수: ");
    int sum = 0;
    for(int i = 0; nData[i] != '\0'; i++){ //해당 for문에서 전체 합계와 숫자 점수들을 출력한다.
        sum += nData[i];
        printf("%d, ", nData[i]);
    }
    count++;
    printf("입력한 개수: %d,  합계: %d,  평균: %.3f\n학점: ", count, sum, (float)sum / (float)count); //float형태에서 소수점 3자리 까지만 출력을 위해 .3f를 사용한다.
    for(int i = 0; nData[i] != '\0'; i++){
        printf("%c", get_Grade(nData[i])); //해당 for문에서 학점(등급)을 출력한다. get_Grade()함수에서 등급을 받아온다.
    }

}

//4번 문제의 2번째 풀이. 학점 문자열을 하나의 for문에서 처리하면서 for문을 하나 줄인다.
void func_GradeProblem_with_stringbuilder(){

    int nScore;
    int nData[20] = {0};
    int count = -1;

    while(1){
        scanf_s("%d", &nScore, sizeof(nScore));
        if(nScore <= 0){
            printf("종료합니다.\n"); //0이하 값이 입력되면 종료.
            break;
        }
        count ++;
        nData[count] = nScore;
        printf("점수 %d, 학점 %c\n", nScore, get_Grade(nScore));
    }

    printf("점수: ");
    int sum = 0;
    char* string_builder = malloc(sizeof(char)*21); //전체 학점 문자열을 담아낼 변수를 만들기 위해 동적 메모리를 사용한다.
    strcpy(string_builder, ""); //string_builder 변수에 빈값을 입력한다.

    for(int i = 0; nData[i] != '\0'; i++){ //해당 for문에서 전체 합계와 숫자 점수들을 출력한다.
        sum += nData[i];
        size_t len = strlen(string_builder); //string_builder 변수의 크기를 len 변수에 저장한다.
        string_builder[len] = get_Grade(nData[i]); //string_builder 변수에 학점을 계속 추가(append)해준다.
        string_builder[len+1] = '\0'; //string_builder 변수의 끝에 NULL값을 추가해준다.
        printf("%d, ", nData[i]);
    }
    count++;
    printf("입력한 개수: %d,  합계: %d,  평균: %.3f\n학점: %s", count, sum, (float)sum / (float)count, string_builder); //float형태에서 소수점 3자리 까지만 출력을 위해 .3f를 사용한다.
    free(string_builder); //동적 메모리 해제.

}

//4번 문제의 3번째 풀이. 구조체 배열을 활용한다.
void func_GradeProblem_with_structure(){

    typedef struct struct_Score{ //구조체를 typedef를 활용하여 선언한다.
        int score; //정수 형태의 점수 저장.
        char grade; //char 형태의 학점 저장.
    }Scr;

    Scr nData[20] = { 0, }; //구조체 배열을 선언과 동시에 초기화함.
    int nScore;
    int count = -1;

    while(1){
        scanf_s("%d", &nScore, sizeof(nScore));
        if(nScore <= 0){
            printf("종료합니다.\n"); //0이하 값이 입력되면 종료.
            break;
        }
        count ++;
        nData[count].score = nScore;
        nData[count].grade = get_Grade(nScore);
        printf("점수 %d, 학점 %c\n", nScore, get_Grade(nScore));
    }

    printf("점수: ");
    int sum = 0;
    char* string_builder = malloc(sizeof(char)*21); //전체 학점 문자열을 담아낼 변수를 만들기 위해 동적 메모리를 사용한다.
    strcpy(string_builder, ""); //string_builder 변수에 빈값을 입력한다.

    for(int i = 0; nData[i].score != 0; i++){ //해당 for문에서 전체 합계와 숫자 점수들을 출력한다.
        sum += nData[i].score;
        size_t len = strlen(string_builder); //string_builder 변수의 크기를 len 변수에 저장한다.
        string_builder[len] = nData[i].grade; //string_builder 변수에 학점을 계속 추가(append)해준다.
        string_builder[len+1] = '\0'; //string_builder 변수의 끝에 NULL값을 추가해준다.
        printf("%d, ", nData[i].score);
    }

    count++;
    printf("입력한 개수: %d,  합계: %d,  평균: %.3f\n학점: %s", count, sum, (float)sum / (float)count, string_builder); //float형태에서 소수점 3자리 까지만 출력을 위해 .3f를 사용한다.
    free(string_builder); //동적 메모리 해제.

}
//4번 문제 종료

void main(){
    //하나씩 주석처리 풀면서 실행누르기.
    //func_bloodPressureProblem();
    //func_ChangeStrIntProblem();
    //func_nYearProblem();
    //func_GradeProblem();
    //func_GradeProblem_with_stringbuilder();
    //func_GradeProblem_with_structure();
}
