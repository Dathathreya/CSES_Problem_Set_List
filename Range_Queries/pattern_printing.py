#User function Template for python3
import sys

class Solution:
    def printTriangle(self, N):
        # Code here
        n,m,i,j = (2*N-1,2*N-1,0,0)
        z=N
        while i<n:
            j=0
            z=N
            while j<m:
                sys.stdout.write(str(z)+" ")
                if(i<N):
                    if(i>j):
                        z-=1
                    elif (2*N-2-i<=j):
                        z+=1
                else:
                    if(2*N-2-i>j):
                        z-=1
                    if (j>=i):
                        z+=1
                    # elif (i>=j):
                    #     z+=1
                j+=1
               
            sys.stdout.write("\n")    
            i+=1    

#{ 
 # Driver Code Starts
#Initial Template for Python 3

if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        N = int(input().strip())
        ob = Solution()
        ob.printTriangle(N)
# } Driver Code Ends