## 二叉树part05

#### 找到树左下角的值
递归：核心：
``` CPP
class Solution {
public:
    int maxDepth = INT_MIN;
    int result;
    void traversal(TreeNode* root, int depth) {
        if (root->left == NULL && root->right == NULL) {
            if (depth > maxDepth) {
                maxDepth = depth;
                result = root->val;
            }
            return;
        }
        if (root->left) {
            depth++;
            traversal(root->left, depth);
            depth--; // 回溯
        }
        if (root->right) {
            depth++;
            traversal(root->right, depth);
            depth--; // 回溯
        }
        return;
    }
    int findBottomLeftValue(TreeNode* root) {
        traversal(root, 0);
        return result;
    }
};
```

树的最左下角的值可以使用层序遍历，记录下最后一行的i==0的元素就可以得到
code:
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
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*>  que;
        if(root!=nullptr) que.push(root);
        int result = 0;
        while(!que.empty()){
            int size = que.size();
            for(int i =0;i<size;i++){
                TreeNode* node = que.front();
                que.pop();
                if(i==0) result = node->val;
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
        }
        return result;

    }
};
```


#### 路径总和
递归方法：
递归函数什么时候需要返回值？什么时候不需要返回值？这里总结如下三点：

如果需要搜索整棵二叉树且不用处理递归返回值，递归函数就不要返回值。（这种情况就是本文下半部分介绍的113.路径总和ii）
如果需要搜索整棵二叉树且需要处理递归返回值，递归函数就需要返回值。 （这种情况我们在236. 二叉树的最近公共祖先 (opens new window)中介绍）
如果要搜索其中一条符合条件的路径，那么递归一定需要返回值，因为遇到符合条件的路径了就要及时返回。（本题的情况）

确定终止条件（使用计数器）

不要去累加然后判断是否等于目标和，那么代码比较麻烦，可以用递减，让计数器count初始为目标和，然后每次减去遍历路径节点上的数值。
如果最后count == 0，同时到了叶子节点的话，说明找到了目标和。
如果遍历到了叶子节点，count不为0，就是没找到。

确定单层的递归函数的逻辑
终止条件是判断叶子结点，所以在递归的过程中不能让空节点进入递归
递归函数是有返回值的，如果递归函数返回true，说明找到了合适的路径，应该立刻返回。


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

bool traversal(TreeNode* cur,int count){
    if(!cur->left&&!cur->right&&count==0) return true;
    if(!cur->left&&!cur->right) return false;
    
    if(cur->left){
        count-=cur->left->val;
        if(traversal(cur->left,count)) return true;
        count+=cur->left->val;
    }
    if(cur->right){
        count-=cur->right->val;
        if(traversal(cur->right,count)) return true;
        count+=cur->right->val;
    }
    return false;
}
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root==NULL) return false;
        return traversal(root,targetSum-root->val);

    }
};
```


#### 从前序和中序遍历序列构建二叉树
核心：
从后序找到中序的分割节点
中序分割，后利用中序的元素数量对后序进行分割
步骤：

第一步：如果数组大小为零的话，说明是空节点了。

第二步：如果不为空，那么取后序数组最后一个元素作为节点元素。

第三步：找到后序数组最后一个元素在中序数组的位置，作为切割点

第四步：切割中序数组，切成中序左数组和中序右数组 （顺序别搞反了，一定是先切中序数组）

第五步：切割后序数组，切成后序左数组和后序右数组

第六步：递归处理左区间和右区间

https://programmercarl.com/0106.%E4%BB%8E%E4%B8%AD%E5%BA%8F%E4%B8%8E%E5%90%8E%E5%BA%8F%E9%81%8D%E5%8E%86%E5%BA%8F%E5%88%97%E6%9E%84%E9%80%A0%E4%BA%8C%E5%8F%89%E6%A0%91.html#%E6%80%9D%E8%B7%AF



code
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
private:
    TreeNode* traversal(vector<int>& inorder, vector<int>& postorder) {
        if(postorder.size()==0) return nullptr;

        int rootValue = postorder[postorder.size()-1];
        TreeNode* root = new TreeNode(rootValue);

        if(postorder.size()==1) return root;

        int delimiterIndex;
        for(delimiterIndex = 0 ;delimiterIndex<inorder.size();delimiterIndex++){
            if(inorder[delimiterIndex]==rootValue) break;

        }

        vector<int> leftInorder(inorder.begin(),inorder.begin()+delimiterIndex);
        vector<int> rightInorder(inorder.begin()+delimiterIndex+1,inorder.end());

        postorder.resize(postorder.size()-1);

        vector<int> leftPostorder(postorder.begin(),postorder.begin()+leftInorder.size());
        vector<int> rightPostorder(postorder.begin()+leftInorder.size(),postorder.end());

        root->left = traversal(leftInorder, leftPostorder);
        root->right = traversal(rightInorder, rightPostorder);

        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0 || postorder.size() == 0) return NULL;
        return traversal(inorder, postorder);
    }
    
};
```