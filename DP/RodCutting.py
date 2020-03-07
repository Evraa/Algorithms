#Like the Staircase problem
# If given a rog with size N
# and array of all the cuts 1:M and the price of each cut
# find the MAX price of that rod
# given N = 4 x=[1,2,3,4] v=[2,5,6,3]
# ans (1,1,1,1) = 8
#     (1,1,2) = 9
#     (2,2) = 10
#     (1,3) = 8
#     (4) = 3
# max is 10

import numpy as np
x = [1,2,3,4,5]
v = [2,5,6,3,2]
m = len(x)
N = 4
def solve_rec(n):

    if n == 0:
        return 0
    val = -1
    for i in range (1,n+1):
        val = max (val ,v[i-1] + solve_rec(n-i))
    return val


#print(solve_rec(N))

dp= np.zeros(m+1)
def solve_dp(n):

    if n == 0:
        return 0
    if dp[n] != 0:
        return dp[n]
    val = -1
    for i in range (1,n+1):
        val = max (val ,v[i-1] + solve_dp(n-i))
    
    dp[n] = val
    return val


#print (int(solve_dp(N)))

#Yet cant get its bottom_up approach