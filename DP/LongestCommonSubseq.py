#find the length of the longest common subsequence between two strings
# with relative positions
import numpy as np

str1 = "ABDEF"
str2 = "ANDBD"
n = len(str1)
m = len(str2)


#Recursive solution, complexity 2^(N || M)
def solve(i,j):
    if(i == n or j == m):
        return 0

    if str1[i] == str2[j]:
        return 1 + solve(i+1,j+1)
    
    return max (solve(i+1,j) , solve(i,j+1) )

#print (solve (0,0))




#DP solution, complexity O(N)
dp = np.zeros([n,m])
def solve_dp(i,j):
    if(i == n or j == m):
        return 0

    if dp[i,j] != 0:
        return dp[i,j]

    if str1[i] == str2[j]:
        dp[i,j] =  1 + solve(i+1,j+1)
        return dp[i,j]
    dp[i,j] = max (solve_dp(i+1,j) , solve_dp(i,j+1) )
    return dp[i,j]

print (int(solve_dp (0,0)))



    