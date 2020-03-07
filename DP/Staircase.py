#Stair case problem

# find number of ways to climb a stair, when you're only allowed to climb x ={array of steps}
#ex: x = [1,2] and n = 4 --> ans  = 5 --> (1,1,1,1) and (1,1,2) and (2,2) and (1,2,1) and (2,1,1) and (2,1,1)
import numpy as np

#This solution for only 1 or 2 steps, using top-down approach and memoization
x = [1,2]
n = 4
dp = np.zeros([n+1])
dp[1] = 1
dp[2] = 2
def num_ways (n):
    if dp[n] != 0:
        return dp[n]

    dp[n] = num_ways(n-1) + num_ways(n-2)
    return dp[n]

#print (num_ways (n))

#A bottom-up approach
nums = np.zeros([n+1])
nums[0] = 1
nums[1] = 1
def num_ways_bottom_up (n):
    for i in range (2,n+1):
        nums[i] = nums[i-1] + nums[i-2]
    return nums[n]
#print (num_ways_bottom_up (n))

#Another approach of the problem, where you're allowed to take some kind of steps
#x = [1,3,5] and n = 4 --> ans = 3 --> (1,1,1,1) and (1,3) and (3,1)
x = [1,3,5]
n = 4
size_x = len(x)
#Recursive solution
def num_ways_x (n):
    if n == 0:
        return 1
    if n == 1:
        return 1
    total = 0
    
    for i in range(size_x):
        if x[i] <= n:
            total += num_ways_x(n-x[i])
    return total
    
#print (num_ways_x (n))

#Using DP

x = [1,3,5]
n = 4
size_x = len(x)
dp = np.zeros([n+1])
dp[0] = 1
dp[1] = 1
#Recursive solution
def num_ways_x_dp (n):
    if dp[n] != 0:
        return dp[n]
    total = 0
    
    for i in range(size_x):
        if x[i] <= n:
            total += num_ways_x_dp(n-x[i])
    dp[n] = total
    return dp[n]
    
#print (int(num_ways_x_dp (n)))


x = [1,3,5]
n = 4
size_x = len(x)
nums = np.zeros([n+1])
nums[0] = 1

#Bottom_up
def num_ways_x_bottom_up (n):
    for i in range (1,n+1):
        total = 0
        for j in range (size_x):
            if i-x[j] >= 0:
                total += nums[i-x[j]]
        nums[i] = total
    return nums[n]
print (int(num_ways_x_bottom_up (n)))