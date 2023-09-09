import java.io.FileInputStream;
import java.io.IOException;
import java.io.DataInputStream;
import java.util.StringTokenizer;
import java.io.BufferedReader;

public class FastIO {
    public static class FastReader
    {
        final private  int BUFFER_SIZE= 1<<16;
        private int bytesread=0,bufferpointer=0;
        private DataInputStream din;
        private byte[] buffer;

        public FastReader(){
            buffer= new byte[BUFFER_SIZE];
            din = new DataInputStream(System.in);
            bytesread=bufferpointer=0;
        }        
        public String readLine() throws Exception {
            byte buf[]=new byte[64];
            int c,cnt=0;
            while((c=read())!=-1){
                 if(c=='\n'){
                    if(cnt!=0){
                       break;     
                    }   
                    else {
                        continue;
                    } 
                 }  
                 buf[cnt++]=(byte)c;   
            }
            return new String(buf,0,cnt);
        }
        public int nextInt() throws Exception{
            int ret=0;
            byte c=read();
            while(c<=' '){
                c=read();    
            }
            boolean neg=(c=='-');
            if(neg){
                c=read();
            }
            do{
                ret=((ret*10)+(c-'0'));
            }while(((c=read()) >='0')&&(c <='9'));
            if(neg)
                return -ret;
            return ret;
        }
        public long nextLong() throws Exception{
            long ret=0;
            byte c=read();
            while(c<=' '){
                c=read();    
            }
            boolean neg=(c=='-');
            if(neg){
                c=read();
            }
            do{
                ret=((ret*10)+(c-'0'));
            }while(((c=read()) >='0')&&(c <='9'));
            if(neg) 
                return -ret;
            return ret;
        }
        public double nextDouble() throws Exception{
            double ret=0;
            double div=1;
            byte c=read();
            while(c <= ' '){
                c=read();
            }
            boolean neg = (c=='-');
            if(neg){
                c=read();
            }
            do{
                ret = ret*10 + (c-'0'); 
            }while((c=read())>='0' && (c)<='9');

            if(c =='.'){
                while((c=read())>='0' && c<='9'){
                    ret+=(c-'0')/(div*=10);
                }
            }
            if(neg) 
               return -ret; 
            return ret;
        }
        public void fillBuffer() throws Exception{
            bytesread = din.read(buffer,bufferpointer=0,BUFFER_SIZE);
            if(bytesread==-1)
                buffer[0]= -1 ;
        }
        public byte read() throws Exception{
            if(bytesread==bufferpointer){
                fillBuffer();
            }
            return buffer[bufferpointer++];
        }
        public void close() throws Exception{
            if(din==null)
                return;
            din.close();    
        } 
    }
    // Buffered/Printer/PrintWriter
    public static void main(String[] args) throws Exception
    {
        FastReader sc = new FastReader();
        int tt=sc.nextInt();
        double dd=sc.nextDouble();
        long lt=sc.nextLong();
        System.out.printf("%d %f %d",tt,dd,lt);
        // double/int --> int 
        // double/double --> double 
    }
}