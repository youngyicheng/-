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


#### 二叉树当中的搜索树


二叉搜索树是一个有序树：

- 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
- 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
- 它的左、右子树也分别为二叉搜索树


code:
```CPP
// 递归方法
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if (root == NULL || root->val == val) return root;
        TreeNode* result = NULL;
        if (root->val > val) result = searchBST(root->left, val);
        if (root->val < val) result = searchBST(root->right, val);
        return result;
    }
};
// 迭代方法
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while(root!=NULL){
            if(root->val>val) root = root->left;
            else if(root->val<val) root = root->right;
            else return root;
        }
        return NULL;
    }
};
```


#### 验证二叉搜索树
核心：对于二叉搜索树来说，使用中序遍历所输出的序列应该是有序的，所以从而可以从这个方面来进行验证


```CPP
class Solution {
private:
    vector<int> vec;
    void traversal(TreeNode* root) {
        if (root == NULL) return;
        traversal(root->left);
        vec.push_back(root->val); // 将二叉搜索树转换为有序数组
        traversal(root->right);
    }
public:
    bool isValidBST(TreeNode* root) {
        vec.clear(); // 不加这句在leetcode上也可以过，但最好加上
        traversal(root);
        for (int i = 1; i < vec.size(); i++) {
            // 注意要小于等于，搜索树里不能有相同元素
            if (vec[i] <= vec[i - 1]) return false;
        }
        return true;
    }
};

```





