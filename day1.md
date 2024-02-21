1. 数组是存放在连续内存空间上的相同类型数据的集合。
2. 数组下标从0开始 内存空间地址连续
3. 因为是连续的，所以在增加和删除的时候需要移动其他元素的地址
4. 如果对于C++来说，需要注意vector和array的区别，vector的底层实现为array，为容器不是数组
5. **数组的元素是不能删除的，只能够进行覆盖**
6. 在cpp当中，二维数组的地址也是连续的
7. java不存在指针，寻址操作完全交给虚拟机（定义方式：

```java
int [][] rating = new int [3][4];
```

**二分法**

前提：有序数组

二分查找涉及很多边界条件，需要考虑到left<= right 还是left<right

1. 二分法第一种：闭区间（[left,right])

区间的定义这就决定了二分法的代码应该如何写，**因为定义target在[left, right]区间，所以有如下两点：**

* while (left <= right) 要使用 <= ，因为left == right是有意义的，所以使用 <=
* if (nums[middle] > target) right 要赋值为 middle - 1，因为当前这个nums[middle]一定不是target，那么接下来要查找的左区间结束下标位置就是 middle - 1

2. 二分法第二种：开区间（[left,right)

**因为定义target在[left, right)区间，所以有如下两点：**

* while (left < right) 要使用 <= ，因为left == right是没有意义的，所以使用 <>
* if (nums[middle] > target) right 要赋值为 middle ，因为当前这个nums[middle]可能是target，那么接下来要查找的左区间结束下标位置就是 middle

**删除元素**
核心为使用双指针，通过快指针找到需要删除的元素从而对low进行赋值，从而返回low 为不同元素的长度

```python
class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        slow = 0
        fast = 0
        while fast<len(nums):
            if nums[fast]!=val:
                nums[slow] = nums[fast]
                slow+=1
            fast+=1
        return slow
```
