## 二叉树part09

#### 修剪二叉搜索树



#### 将有序数组转换为二叉搜索树
核心：使用二叉搜索树和有序数组之间的关系进行构建相应关系

递归三大件：
- 递归函数的参数
- 递归函数的结束条件
- 递归函数的单层循环逻辑
code

```CPP
class Solution {
private:
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = left + ((right - left) / 2);
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = traversal(nums, left, mid - 1);
        root->right = traversal(nums, mid + 1, right);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = traversal(nums, 0, nums.size() - 1);
        return root;
    }
};
```



#### 把二叉搜索树转换为累加树  

核心：双指针方法
遍历整棵树就不需要返回值


