import java.util.Scanner;

public class T_1 {

    public Boolean verifyCircle(int radius){
        if(radius <= 0){
            return false;
        }
        return true;
    }

    public Boolean verifyRectangle(int[][] coordList){
       if(coordList[0][0] == coordList[1][0] || coordList[0][1] == coordList[1][1]){
           return false;
       }
       return true;
    }

    public Boolean verifyTriangle(int[][] coordList){
        double tempList[] = new double[3];
        tempList[0] = Math.sqrt((coordList[0][0] - coordList[1][0])^2+(coordList[0][1] - coordList[1][1])^2);
        tempList[1] = Math.sqrt((coordList[1][0] - coordList[2][0])^2+(coordList[1][1] - coordList[2][1])^2);
        tempList[2] = Math.sqrt((coordList[0][0] - coordList[2][0])^2+(coordList[0][1] - coordList[2][1])^2);
        double tempMax = tempList[0];
        double tempSum = 0d;
        for(double a : tempList){
            if(a > tempMax){
                tempMax = a;
            }else{
                tempSum += a;
            }
        }
        if(tempMax < tempSum){
            return true;
        }
        return false;
    }

    public void drawCircle(int[][] coordCenter, int radius){
        if(!verifyCircle(radius)){
            System.out.println("[오잉?] 해당 원은 그릴 수 없습니다.");
            return;
        }
        System.out.println("요청된 좌표는 중심 ("+coordCenter[0][0]+", "+coordCenter[0][1]+"), 반지름 "+radius+" 입니다.");
    }
    public void drawRectangle(int[][] coordList){
        if(!verifyRectangle(coordList)){
            System.out.println("[오잉?] 해당 사각형은 그릴 수 없습니다.");
            return;
        }
        for(int a = 0; a < 2; a++){
            System.out.println("요청된 "+a+1+"번째 좌표는 ("+coordList[a][0]+", "+coordList[a][1]+") 입니다.");
        }
    }
    public void drawTriangle(int[][] coordList){
        if(!verifyTriangle(coordList)){
            System.out.println("[오잉?] 해당 삼각형은 그릴 수 없습니다.");
            return;
        }
        for(int a = 0; a < 3; a++){
            System.out.println("요청된 "+a+1+"번째 좌표는 ("+coordList[a][0]+", "+coordList[a][1]+") 입니다.");
        }

    }

    public void rotateShape(Object obj){
        //empty
    }

    public void startManager(){

        //Default
        int temp[][] = new int[3][2];
        String tempString[];
        Scanner scanner = new Scanner(System.in);

        try {
            //Circle
            System.out.println("[원 그리기 마법사]");
            System.out.print("중심 좌표를 입력하십시오(형식: a,b): ");
            tempString = scanner.next().split(",");
            temp[0][0] = Integer.parseInt(tempString[0]);
            temp[0][1] = Integer.parseInt(tempString[1]);
            System.out.print("반지름을 입력하십시오(형식: a): ");
            int tempRad = scanner.nextInt();
            drawCircle(temp, tempRad);

            //Triangle
            System.out.println("[삼각형 그리기 마법사]");
            for (int a = 0; a < 3; a++) {
                System.out.print(a+1 + "번째 좌표를 입력하십시오(형식: a,b): ");
                tempString = scanner.next().split(",");
                temp[a][0] = Integer.parseInt(tempString[0]);
                temp[a][1] = Integer.parseInt(tempString[1]);
            }
            drawTriangle(temp);

            //Rectangle
            System.out.println("[사각형 그리기 마법사]");
            for (int a = 0; a < 2; a++) {
                System.out.print(a+1 + "번째 좌표를 입력하십시오(형식: a,b): ");
                tempString = scanner.next().split(",");
                temp[a][0] = Integer.parseInt(tempString[0]);
                temp[a][1] = Integer.parseInt(tempString[1]);
            }
            drawRectangle(temp);

        }catch (Exception e){
            System.out.println("오류 발생! 처음부터 다시 시도하시오.");
        }
    }

    public static void main(String[] args){
        T_1 instance = new T_1();
        instance.startManager();
    }

}
