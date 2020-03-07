import numpy as np

weights = [1,2,4,5]
values = [5,3,5,2]

c = 2
n = len(weights)
#Recursive solution
def knapsack_rec (idx , weight):
    if idx == n :
        return 0
    
    #ELSE: You have two ways, 1-leave it, 2-if you can, take it

    ans = knapsack_rec(idx+1,weight)
    if(weights[idx] <= weight):
        ans = max(ans , values[idx] + knapsack_rec(idx+1,weight-weights[idx]))
    return ans
#print (knapsack_rec(0,c))




#Memoized Solution
dp = np.zeros([n+1,c+1])

def knapsack_dp (idx , weight):
    if idx == n :
        return 0
    #ELSE: You have two ways, 1-leave it, 2-if you can, take it
    if dp[idx,weight] != 0:
        return dp[idx,weight]

    ans = knapsack_dp(idx+1,weight)

    if(weights[idx] <= weight):
        ans = max(ans , values[idx] + knapsack_dp(idx+1,weight-weights[idx]))
    dp[idx,weight] = ans

    return dp[idx,weight]
    
print (knapsack_dp(0,c))