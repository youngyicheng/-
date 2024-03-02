### 题目
## 四数之和
找到a+b+c+d=0
采用分而治之思想，先计算出a+b的数值 然后采用使用另外一个遍历，在上一个map当中找到0-(c+d)的数值；如果没有找到，就证明不存在这种相加方式，如果找到，就使用count进行相加；
核心：使用unordered_map 此处key存储a+b的value value存储为出现次数

```CPP
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {

        unordered_map<int,int> un_map;
        for(int a:nums1){
            for(int b : nums2){
                un_map[a+b]++;
            }
        }
        int count = 0;
        for (int c:nums3){
            for(int d:nums4){
                if(un_map.find(0-(c+d))!=un_map.end()){
                    count+=un_map[0-(c+d)];
                }
            }
        }
        return count;

    }
};
```


## 赎金信  
建议：本题 和 242.有效的字母异位词 是一个思路 ，算是拓展题 
使用map key为字符串 value为出现个数，从而可以判断是否可以组成和出现


## 三个数字之和
核心：采用双指针，重点是非重复，从而需要特殊处理

```CPP
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {


        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        for(int i ;i<nums.size();i++){
            if(nums[i]>0){
                return result;
            }

            if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
            }

            int left = i+1;
            int right = nums.size()-1;
            while(right>left){
                if (nums[i] + nums[left] + nums[right] > 0) right--;
                else if (nums[i] + nums[left] + nums[right] < 0) left++;
                else{
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});

                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;

                    right--;
                    left++;
                }


            }

        }
    return result; 
    }
};



class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        // 找出a + b + c = 0
        // a = nums[i], b = nums[left], c = nums[right]
        for (int i = 0; i < nums.size(); i++) {
            // 排序之后如果第一个元素已经大于零，那么无论如何组合都不可能凑成三元组，直接返回结果就可以了
            if (nums[i] > 0) {
                return result;
            }
            // 错误去重a方法，将会漏掉-1,-1,2 这种情况
            /*
            if (nums[i] == nums[i + 1]) {
                continue;
            }
            */
            // 正确去重a方法
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while (right > left) {
                // 去重复逻辑如果放在这里，0，0，0 的情况，可能直接导致 right<=left 了，从而漏掉了 0,0,0 这种三元组
                /*
                while (right > left && nums[right] == nums[right - 1]) right--;
                while (right > left && nums[left] == nums[left + 1]) left++;
                */
                if (nums[i] + nums[left] + nums[right] > 0) right--;
                else if (nums[i] + nums[left] + nums[right] < 0) left++;
                else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    // 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;

                    // 找到答案时，双指针同时收缩
                    right--;
                    left++;
                }
            }

        }
        return result;
    }
};
```





## 四数之和
四数之和总结：
核心：采用双指针方法可以将暴力求解所需要的时间复杂度降低，一般都可以降低一个层次（n)

双指针法将时间复杂度：O(n^2)的解法优化为 O(n)的解法。也就是降一个数量级，题目如下：

27.移除元素(opens new window)
15.三数之和(opens new window)
18.四数之和(opens new window)
链表相关双指针题目：

206.反转链表(opens new window)
19.删除链表的倒数第N个节点(opens new window)
面试题 02.07. 链表相交(opens new window)
142题.环形链表II


code:

``` CPP
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int k = 0; k < nums.size(); k++) {
            // 剪枝处理
            if (nums[k] > target && nums[k] >= 0) {
            	break; // 这里使用break，统一通过最后的return返回
            }
            // 对nums[k]去重
            if (k > 0 && nums[k] == nums[k - 1]) {
                continue;
            }
            for (int i = k + 1; i < nums.size(); i++) {
                // 2级剪枝处理
                if (nums[k] + nums[i] > target && nums[k] + nums[i] >= 0) {
                    break;
                }

                // 对nums[i]去重
                if (i > k + 1 && nums[i] == nums[i - 1]) {
                    continue;
                }
                int left = i + 1;
                int right = nums.size() - 1;
                while (right > left) {
                    // nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
                    if ((long) nums[k] + nums[i] + nums[left] + nums[right] > target) {
                        right--;
                    // nums[k] + nums[i] + nums[left] + nums[right] < target 会溢出
                    } else if ((long) nums[k] + nums[i] + nums[left] + nums[right]  < target) {
                        left++;
                    } else {
                        result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                        // 对nums[left]和nums[right]去重
                        while (right > left && nums[right] == nums[right - 1]) right--;
                        while (right > left && nums[left] == nums[left + 1]) left++;

                        // 找到答案时，双指针同时收缩
                        right--;
                        left++;
                    }
                }

            }
        }
        return result;
    }
};



```