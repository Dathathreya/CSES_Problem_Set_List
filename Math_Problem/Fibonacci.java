import java.util.*;
import java.io.*;
import java.math.*;

class Pair {
        public long f;
        public long s;
        public Pair(long f,long s){
            this.f=f;this.s=s;
        }
    }

public class Fibonacci{
    public static final long  mod = (long)1e9+7;
    
    static Pair fib(long n)
    {
       if(n==0){
          return new Pair(0,1);
       }
       // f(n)=f(n), f(0)=f(1)=1,f(2)=1,f(3)=2,f(4)=3
       // f(n)=f(n-1)+f(n-2)
       // f(n+1)=f(n)+f(n-1)
       // f(n+2)=f(n+1)+f(n)
       // f(n+3)=f(n+1)+f(n+2)
       // f(n+3)=f(n)+f(n-1) +f(n)+f(n-1)+f(n)
       // f(n+3)=3*f(n)+2*f(n-1)
       // f(n+3)=f(4)*f(n)+f(3)*f(n-1)
       // f(n+3)=f(3+1)*f(n)+f(3)*f(n-1) // replace 3 as (n-1)
       // f(n+n-1)=f(n)*f(n)+f(n-1)*f(n-1)
       // f(2*n-1)=f(n-1)*f(n-1)+f(n)*f(n) ---part2---
       // f(n+n-2)=f(n-1)*f(n)+f(n-2)*f(n-1)=f(n-1)*(f(n)+f(n-2))=f(n-1)*(f(n)+f(n)-f(n-1))
       // f(2n-2)=f(n-1)*(2*f(n)-f(n-1)) ----part1---
       // f(2*n)=f(2*n-2)+f(2*n-1) // even no.
       // f(2*n+1)=f(2*n-1)+f(2*n) // odd no.
       
       Pair P = fib(n>>1);
       long part1 = P.f*(2*P.s-P.f)%mod;
       long part2 = (P.f*P.f + P.s*P.s)%mod;

       if(n%2==1){ // odd no. 
            return new Pair(part2,part1+part2);
       } 
       return new Pair(part1,part2);
    }

    public static void solve(Reader sc,FastWriter out){
        long n=sc.nextLong();
        System.out.println(fib(n).F);
    }

    public static void main(String[] args){
          int tt=1;
        // Scanner sc = new Scanner(System.in);
        Reader sc = new Reader();
        FastWriter wr= new FastWriter();
        while((tt--)>0){
              solve(sc,wr);  
        }
        wr.close();
    }

      static class FastWriter{
        private BufferedWriter bw;
        public FastWriter(){
            this.bw= new BufferedWriter(new OutputStreamWriter(System.out));
        }
        public void print(Object object) throws  IOException {
               bw.append(""+object);            
        }
        public void println(Object object) throws IOException{
               print(object);
               bw.append("\n");            
        }
        public void close() throws IOException{
            bw.close();
        }
    }

    static class Reader {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;
  
        public Reader()
        {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
  
        public Reader(String file_name) throws IOException
        {
            din = new DataInputStream(
                new FileInputStream(file_name));
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
  
        public String readLine() throws IOException
        {
            byte[] buf = new byte[64]; // line length
            int cnt = 0, c;
            while ((c = read()) != -1) {
                if (c == '\n') {
                    if (cnt != 0) {
                        break;
                    }
                    else {
                        continue;
                    }
                }
                buf[cnt++] = (byte)c;
            }
            return new String(buf, 0, cnt);
        }
  
        public int nextInt() throws IOException
        {
            int ret = 0;
            byte c = read();
            while (c <= ' ') {
                c = read();
            }
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
  
            if (neg)
                return -ret;
            return ret;
        }
  
        public long nextLong() throws IOException
        {
            long ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
            if (neg)
                return -ret;
            return ret;
        }
  
        public double nextDouble() throws IOException
        {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
  
            do {
                ret = ret * 10 + c - '0';
            } while ((c = read()) >= '0' && c <= '9');
  
            if (c == '.') {
                while ((c = read()) >= '0' && c <= '9') {
                    ret += (c - '0') / (div *= 10);
                }
            }
  
            if (neg)
                return -ret;
            return ret;
        }
  
        private void fillBuffer() throws IOException
        {
            bytesRead = din.read(buffer, bufferPointer = 0,
                                 BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }
  
        private byte read() throws IOException
        {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }
  
        public void close() throws IOException
        {
            if (din == null)
                return;
            din.close();
        }
    }
}