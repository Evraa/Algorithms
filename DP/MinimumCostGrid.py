#Minimum cost grid, given an nXm grid, with starting point at the top left
#and ending point at the bottom right
#with movement only in the rgiht/down/right-down directions
#return the minimum cost allowed

import numpy as np
from random import seed
from random import randint
seed(1)
n = 2
m = 2
max_int = 1e9
grid = np.zeros([n,m])
dp = np.zeros([n,m])
for i in range (n):
    for j in range (m):
        value = randint(0, 10)
        grid[i,j] = value
        dp[i,j] = -1
print (grid)



def min_trip (i,j):
    if (i == n-1 and j == m-1):
        return grid[i,j] 

    if dp[i,j] != -1:
        return dp[i,j]

    if i >= n or j>= m:
        return max_int 


    dp[i,j] = grid[i,j] + min(min_trip(i+1,j), min_trip(i,j+1) ,min_trip(i+1,j+1))
    return dp[i,j]

print (min_trip(0,0))