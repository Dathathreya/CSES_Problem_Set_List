import java.util.*;
import java.io.*;

public class Exponentiation
{
    public static long MOD = (long)1e9+7;
    public static int psv[]=new int[1000007];
    public static long power (int a,int b)
    {
        if(b==0){
            return 1;
        }
        long ret=power(a,(b/2));
        ret%=MOD;
        // System.out.printf("ret:%d\t",ret);
        long answer=1;
        answer*=ret;
        answer%=MOD;
        answer*=ret;
        answer%=MOD;
        if((b%2)==1){
            answer*=a;
            answer%=MOD;
        }
        return answer;
        // 3 7 -> ((3*3)*3*(3*3)*3)*3
        // 3 3 -> (3*3)*3
        // 3 1 -> 3
        // 3 0
    }
    public static long pow(long a,long b)
    {
        long  answer=1;
        while(b>0)
        {
            if((b%2)==1) 
            {
               // answer%=MOD;
                answer*=a;
                answer%=MOD;
            }
            a=a*a;
            a%=MOD;
            b/=2;
        }
        return answer;
    }
    
    // 18 - 2 3 3 
    // 25 - 5 5
    // 24 - 2 2 2 3
    // 24 - (2+1)*(3+1)
    public static void psf(int sz){
        int i,j;
        for(i=1;i<=sz;i++){
               psv[i]=i; // before seive smallest divisor is itself 
        }
        for(i=2;i*i<=sz;i+=1){
            if(psv[i]==i){
                j=(i*i); 
                while(j<=sz)
                {
                    if(psv[j]==j) // not updated
                    {  // smallest divisor for current number
                        psv[j]=i;
                    }
                    j+=i;
                }   
            }
        }
    }
    
    public static void solve(Scanner sc)
    {
        long num;
        num=sc.nextLong();
        long ans=1;
        while(num!=1){
            int cnt=1;
            int smallest=psv[(int)num];
            while(num%smallest==0){
                cnt+=1;
                num/=smallest; // get rid of divisors
            }
            ans*=cnt;
        }
        System.out.println(ans);       
    } 
    public static void main(String []args)
    {
        //System.out.println(MOD);
        Scanner sc = new Scanner(System.in);
        int tt=Integer.parseInt(sc.next());
        psf(1000006);
        // for(int i=1;i<=100;i++)
        // {
        //     System.out.printf("%d ",psv[i]);
        // }
        while((tt--)>0)
        {
            solve(sc); 
        }
    }
}