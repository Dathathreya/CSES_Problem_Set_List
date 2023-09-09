import java.util.*;
import java.io.*;
import java.util.function.*;


public class Forest_QueriesII 
{
    static class FastReader
    {
    StringTokenizer st; //= new StringTokenize();
    BufferedReader bf;
    public FastReader(){
        bf= new BufferedReader(new InputStreamReader(System.in));
    }
    public String next()
    {
        while(st==null || !st.hasMoreTokens() ){
            try {
                st= new StringTokenizer(bf.readLine());
            }
            catch(IOException ex)
            {
                   ex.printStackTrace(); 
            }
        }
        return st.nextToken();
    }
    public int nextInt(){
        return Integer.parseInt(next());
    } 
    public long nextLong()
    {
        return Long.parseLong(next());
    }   
    public double nextDouble(){
        return Double.parseDouble(next());
    }
    public String nextLine()
    {
        String str="";
        try {
            if(st.hasMoreTokens()){
                str+=st.nextToken("\n");
            }
            else {
                str=bf.readLine();
            }
        }
        catch(IOException ex)
        {
            ex.printStackTrace();
        }
        return str; 
    }
    }
    public static void main(String []args) throws Exception
    {
        //Scanner sc = new Scanner(System.in);
        FastReader sc = new FastReader();
        int tt=sc.nextInt();
        System.out.printf("%d\n",tt);
    }
}