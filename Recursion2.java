public class Recursion2{
    
    public static void main(String [] args){
       
    }
    
    public static int length(string str){
        if (str.equals(""))
            return 0;
        else
            return 1 + length(str.substring(l));  //원래 문자열에서 맨앞 문자열을 제거한 문자열 만들어줌
    }   
    
    public static void printChars(String str){
        if(str.length() == 0)
            return;
        else{
            System.out.print(str.charAt(0));
            printChars(str.substring(1));
        }
    }
    
    public static void printCharsReverse(String str){
        if(str.length() == 0)
            return;
        else{
            printCharsReverse(str.substring(1));
            System.out.print(str.charAt(0));
        }
    }
    
    public static int sum(int n, int [] data){
        if (n <= 0)
            return 0;
        else
            return sum(n-1, data) + data[n-1];
    }
    
    //데이터파일로 부터 n개의 정수 읽어오기
    public void readFrom(int n, int[] data, Scanner in){
        if(n == 0)
            return;
        else{
            readFrom(n-1, data, in);
            data[n-1] = in.nextInt();
        }
    }
}