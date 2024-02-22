### Day2 leetcode task

#### 977.有序数组的平方 
核心：双指针法
因为本来就是个有序数组，所以如果平方的话肯定是从双边开始为最大的，所以我们只要从最大的开始遍历就可以，由此可以想到使用双指针，然后从右边开始赋值
[题目链接](https://leetcode.cn/problems/squares-of-a-sorted-array/)
**代码如下**
```python
class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        start = 0
        end = len(nums) - 1
        i = len(nums) - 1
        nums_lst = [float('inf')] * len(nums)
        while start<=end:
            if nums[start]**2<nums[end]**2:
                nums_lst[i]= nums[end]**2
                end-=1
            else:
                nums_lst[i]= nums[start]**2
                start+=1

            i-=1
        return (nums_lst)
```











#### 209.长度最小的子数组 
核心：滑动窗口
确定以下三点：
- 窗口内是什么
- 如何确定窗口开始位置
- 如何确定结束位置
 [题目链接](https://leetcode.cn/problems/minimum-size-subarray-sum/) 
```python class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        l = len(nums)
        left = 0
        right = 0
        min_len = float('inf')
        cur_sum = 0 #当前的累加值

        while right<l:
            cur_sum+=nums[right]
            while cur_sum>=target:
                min_len = min(min_len,right-left+1)
                cur_sum -= nums[left]
                left+=1
                

            right+=1
        return min_len if min_len != float('inf') else 0
```



#### 59.螺旋矩阵II 
核心：使用二分法当中的左闭右开原则，在每次的遍历过程中，需要判断出偏移量来确定每一行来遍历的最后位置，从而来达到完整遍历的效果
判断层数也是一个核心，根据层数来确定偏移量，循环几次就来确定几个offset
[题目链接](https://leetcode.cn/problems/spiral-matrix-ii/submissions/503824957/)

题解：
```python 
class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        nums = [[0] * n for _ in range(n)]
        startx, starty = 0, 0               # 起始点
        loop, mid = n // 2, n // 2          # 迭代次数、n为奇数时，矩阵的中心点
        count = 1                           # 计数

        for offset in range(1,loop+1):
            for i in range(starty,n-offset):
                nums[startx][i]=count
                count+=1
            for i in range(startx,n-offset):
                nums[i][n-offset]=count
                count+=1
            for i in range(n-offset,startx,-1):
                nums[n-offset][i]=count
                count+=1
            for i in range(n-offset,starty,-1):
                nums[i][startx]=count
                count+=1
            startx+=1
            starty+=1
        if n%2!=0:
            nums[mid][mid]=count

        return nums
            
```