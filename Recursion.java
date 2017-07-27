public class Recursion{
    
    public static void main(String [] args){
        int result = func(4);
        System.out.print(result);
    }
    
    public static int func(int n){
        if(n <= 0)
            return 0;
        else
            return n + func(n-1);
    }
    
    public static int factorial(int n)
    {
        if (n==0)
            return 1;
        else
            return n * factorial(n-1);
    }
    
    public static double power(double x, int n){
        if(n == 0)
          return 1;
        else
          return x * power(x, n-1);
    }
    
    public static fibonacci(int n){
        if( n < 2)
          return n;
        else
          return fibonacci(n-1) + fibonacci(n-2);
    }
    
    public static double gcd(int m, int n){
        if( m < n){
            int tmp = m; m = n; n = tmp;
        }
        m%n == 0 ? return n : return gcd(n,m%n);
    }
    
    public static double simple_gcd(int m, int n){
        n == 0 ? return m : return gcd(n, m%n);
    }
}
