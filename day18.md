## 二叉树 part07
#### 二叉搜索树的最小绝对差 
核心：二叉搜索树的中序遍历是有序数组，从而求相邻两节点的最小值就是求这个数组的两节点间的最小值

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
int result =INT_MAX;
TreeNode* pre = nullptr;
void traversal(TreeNode* cur){
    if(cur == nullptr) return;
    traversal(cur->left);
    if(pre!=nullptr){
        result = min(result,cur->val-pre->val);
    }
    pre = cur;
    traversal(cur->right);
}
public:
    int getMinimumDifference(TreeNode* root) {
        traversal(root);
        return result;

    }
};
```
note: 遇到在二叉搜索树上求什么最值，求差值之类的，都要思考一下二叉搜索树可是有序的，要利用好这一特点。

同时要学会在递归遍历的过程中如何记录前后两个指针，这也是一个小技巧，学会了还是很受用的。


#### 二叉搜索树中的众数
核心：
- 不是二叉搜索树 遍历+map统计频率，直接选择频率最高的几个元素
- 二叉搜索树 中序遍历为有序数组，有序数组的最大众数只能是相邻的两个数字
  


```CPP
class Solution {
private:
    int maxCount = 0; // 最大频率
    int count = 0; // 统计频率
    TreeNode* pre = NULL;
    vector<int> result;
    void searchBST(TreeNode* cur) {
        if (cur == NULL) return ;

        searchBST(cur->left);       // 左
                                    // 中
        if (pre == NULL) { // 第一个节点
            count = 1;
        } else if (pre->val == cur->val) { // 与前一个节点数值相同
            count++;
        } else { // 与前一个节点数值不同
            count = 1;
        }
        pre = cur; // 更新上一个节点

        if (count == maxCount) { // 如果和最大值相同，放进result中
            result.push_back(cur->val);
        }

        if (count > maxCount) { // 如果计数大于最大值频率
            maxCount = count;   // 更新最大频率
            result.clear();     // 很关键的一步，不要忘记清空result，之前result里的元素都失效了
            result.push_back(cur->val);
        }

        searchBST(cur->right);      // 右
        return ;
    }

public:
    vector<int> findMode(TreeNode* root) {
        count = 0;
        maxCount = 0;
        pre = NULL; // 记录前一个节点
        result.clear();

        searchBST(root);
        return result;
    }
};
```


#### 二叉树的最近公共祖先
核心：自底向上的来查找，从而来找到公共祖先
回溯算法就是自底向上的来查找（后序遍历）
多看代码复习这道题


code
```CPP
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==q || root ==p||root==NULL) return root;
        TreeNode* left = lowestCommonAncestor(root->left,p,q);
        TreeNode* right = lowestCommonAncestor(root->right,p,q);
        if(left!=NULL && right ==NULL) return left;
        else if(left==NULL && right !=NULL) return right;
        else if (left!=NULL && right !=NULL) return root;
        else return NULL;
    }
};
```