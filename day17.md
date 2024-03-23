## 二叉树part06
#### 最大二叉树
递归分为三步：
- 确定递归函数的参数值和返回值
- 确定递归函数的终止条件
- 确定单层递归的递归逻辑
```CPP
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {

        // 确定结束的条件
        TreeNode* node = new TreeNode(0);
        if(nums.size()==1){
            node->val = nums[0];
            return node;
        }
        int maxValue = 0;
        int maxValueIndex=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]>maxValue){
                maxValue = nums[i];
                maxValueIndex=i;
            }


        }

        node ->val = maxValue;
        if(maxValueIndex>0){
            vector<int> newVec(nums.begin(),nums.begin()+maxValueIndex);
            node->left=constructMaximumBinaryTree(newVec);
        }
        if(maxValueIndex<(nums.size()-1)){
            vector<int> newVec(nums.begin()+maxValueIndex+1,nums.end());
            node->right=constructMaximumBinaryTree(newVec);
        }

        return node;
    }
};
```


#### 合并二叉树（也还是递归）
- 确定递归函数的参数和返回值
合并两个二叉树，传入两个二叉树的节点
参考使用前序遍历的递归模版就ok
```CPP
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == NULL) return t2; // 如果t1为空，合并之后就应该是t2
        if (t2 == NULL) return t1; // 如果t2为空，合并之后就应该是t1
        // 修改了t1的数值和结构
        t1->val += t2->val;                             // 中
        t1->left = mergeTrees(t1->left, t2->left);      // 左
        t1->right = mergeTrees(t1->right, t2->right);   // 右
        return t1;
    }
};
```