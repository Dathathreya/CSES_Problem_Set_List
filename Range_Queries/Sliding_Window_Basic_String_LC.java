//1358. Number of Substrings Containing All Three Characters
// Accepted Solution
class Solution {
    public boolean all(int ch[],int size)
    {
        return (ch[0]>=1 && ch[1]>=1 && ch[2]>=1);
    }
    public int numberOfSubstrings(String s) {
        int first=0,last=0,n=s.length(),answer=0;
        int ch[]=new int[3];
        Arrays.fill(ch,0);
        for(;first+2<n;)
        {
            while(!all(ch,3) && last<n)
            {
                ch[s.charAt(last)-'a']+=1;
                last+=1;
            }
            if(all(ch,3)){
                answer+= (n-last+1);
            }
            ch[s.charAt(first)-'a']-=1;
            first+=1;
        }
        return answer;
    }
}