## 二叉树part03
#### 二叉树的最大深度
根节点的高度就是树的深度
- 后序遍历求的是根节点的高度（树的深度）
- 使用层序遍历，每次遍历过一次队列之后depth++

code
```CPP
class solution {
public:
    int getdepth(TreeNode* node) {
        if (node == NULL) return 0;
        int leftdepth = getdepth(node->left);       // 左
        int rightdepth = getdepth(node->right);     // 右
        int depth = 1 + max(leftdepth, rightdepth); // 中
        return depth;
    }
    int maxDepth(TreeNode* root) {
        return getdepth(root);
    }
};
int maxDepth(TreeNode* root){
    if(root==null) return 0;
    int depth = 0
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty()){
        int size = que.size();
        depth++;
        for(int i =0;i<size;i++){
            TreeNode * node = que.front();
            que.pop();
            if(node->left) que.push(node->left);
            if(node->right) que.push(node->right);

        }
    }
}
```

#### 二叉树的最小深度
最小的节点为左右孩子都为空（所以根节点不应该是最小的孩子）
- 求二叉树的最小深度和求二叉树的最大深度的差别主要在于处理左右孩子不为空的逻辑。(为的是处理左右孩子都不为空的逻辑)

如果使用非递归遍历的话，求深度都使用层序遍历方法，当左右两个孩子都为空的时候，说明是到了最低的一层了 然后进行退出（框架都是用层序遍历的框架 然后进行修改）




#### 完全二叉树的节点个数
- 只要使用一个遍历方法（后序遍历即可 左右中）
以下为非递归写法：

```CPP

class Solution {
public:
    int countNodes(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);
        int result = 0;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                result++;   // 记录节点数量
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
        }
        return result;
    }
};

```
