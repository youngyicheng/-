## 二叉树part04
#### 平衡二叉树
判断是否为高度平衡二叉树：一个二叉树的每个节点的左右两个子树的高度差的绝对值不能超过1

- 求深度为从上到下查，需要前序遍历
- 求高度为从下到上，为后序遍历

此题使用的是后序遍历（那么就是左右中）

**note**:
通过本题可以了解求二叉树深度 和 二叉树高度的差异，求深度适合用前序遍历，而求高度适合用后序遍历。

本题迭代法其实有点复杂，大家可以有一个思路，也不一定说非要写出来。

但是递归方式是一定要掌握的！


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
    int getHeight(TreeNode* root){
        if(root==nullptr){
            return 0;
        }
        int result =0;
        int leftHeight = getHeight(root->left);
        if(leftHeight==-1) return -1;
        int rightHeight = getHeight(root->right);
        if(rightHeight==-1) return -1;

        if(abs(leftHeight-rightHeight)>1){
            result = -1;
        }
        else{
            result = 1+max(leftHeight,rightHeight);
        }
        return result;
    }
    bool isBalanced(TreeNode* root) {
        int result = getHeight(root);
        return result==-1? false : true;



    }
};
```
#### 二叉树的所有路径
要求为从根节点到叶子节点的路径，所以需要前序遍历，方便让父节点指向孩子节点，找到对应的路径
核心：回溯算法
记录下路径，需要进行回溯来回退一个路径然后再进入另一个路径
递归和回溯是同一家的，本题也需要回溯（还未写完）

#### 左叶子之和


