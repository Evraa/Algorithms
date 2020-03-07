import numpy as np

#Like the chain stairs problem disccused befors
# if given N=4 and x=[1,2,3] how many ways to construct N
# ans = (1,1,1,1) (1,1,2) (1,2,1) (2,1,1) (2,2) (1,3) (3,1)


x =[1,2,3]
N = 4

def solve_rec(n):
    if n==0:
        return 1
    total = 0
    for i in range (len(x)):
        if (x[i] <= n):
            total += solve_rec(n-x[i])
    return total

#print (solve_rec(N))


dp = np.zeros([N+1])
dp[0] = 1
def solve_dp(n):
    if dp[n] != 0:
        return dp[n]
    total = 0
    for i in range (len(x)):
        if (x[i] <= n):
            total += solve_dp(n-x[i])
    dp[n] = total
    return dp[n]

#print (int(solve_dp(N)))

#Another approach of the problem, if arrangement doesnt matter
# if given N=4 and x=[1,2,3] how many ways to construct N
# ans = (1,1,1,1) (1,1,2) (2,2) (1,3)
dp = np.zeros([N+1,len(x)+1])
def solve2(n, lastidx):
    if n==0:
        return 1
    if (n<0 or lastidx >= len(x)):
        return 0
    if dp[n,lastidx] != 0:
        return dp[n,lastidx]

    ans = solve2(n-x[lastidx] , lastidx) + solve2 (n,lastidx+1) 
    dp[n,lastidx] = ans
    return dp[n,lastidx]   
    
print(solve2(N,0))
