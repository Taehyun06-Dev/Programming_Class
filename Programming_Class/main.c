#include <stdio.h>
#include <stdlib.h> //동적 메모리 관련 라이브러리 불러오기.
#include <string.h> //동적 메모리 관련 strcopy 함수 사용을 위한 라이브러리.

//202202177 차태현

// 1번 문제 시작
char* get_bloodPressure(int var){ //혈압 수치에 따라 고혈압, 정상혈압, 저혈압 중 하나를 return 하는 함수.
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
        if(nYear % 2 == 0){
            strcpy(if_odd, "짝수"); //동적 메모리와 관련하여 직접 값을 입력하지 않는다.(이하동일)
        }else{
            strcpy(if_odd, "홀수");
        }
        //윤년 판별 구문
        if((nYear % 4 == 0) && (nYear % 100 != 0)){ //nYear변수가 4의 배수이고, 100의 배수가 아니라면~ 구문.
            strcpy(if_leap, "윤년");
        }else if (nYear % 400 == 0){ //nYear변수가 400의 배수라면~ 구문.
            strcpy(if_leap, "윤년");
        }else{
            strcpy(if_leap, "평년");
        }
        printf("%d은 %s, %s\n", nYear, if_odd, if_leap);
    }
    free(if_leap);
    free(if_odd);
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

void main(){
    //하나씩 주석처리 풀면서 실행누르기.
    //func_bloodPressureProblem();
    func_ChangeStrIntProblem();
    //func_nYearProblem();
    //func_GradeProblem();
}
