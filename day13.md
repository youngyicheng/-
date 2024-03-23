## 二叉树part2

#### 层序遍历

核心：使用队列 的先进先出的原则

```CPP
 vector<vector<int>> levelOrder(TreeNode* root) {
    queue<TreeNode* > que;
    if(root!=NULL) { que.push(root)};
    vector<vector<int>> res;
    while(!que.empty()){
        int size = que.size();
        vector<int> vec;
        for(int i:size){
            TreeNode * node = que.front();
            que.pop();
            vec.push_back(node->val);
            if(node->left){que.push(node->left)};
            if(node->right){que.push(node->right)};
        }
        res.push_back(vec);
    }
    return res;
    }

```
#### 翻转二叉树

直接对于根节点的两个子树进行翻转，然后得出对应的效果就可以

```CPP
TreeNode* invertTree(TreeNode* root){
    if(root ==NULL){return root;}
    swap(root->left,root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

```

#### 对称二叉树
判断对称二叉树的是说明为镜像的两个节点，并不是左右的两个子节点，所以要分为外侧和里侧的两种情况
- 函数的参数（对于树来说就是root节点）
- 函数的终止条件（需要将大部分情况考虑清楚）
- 函数的单层循环条件（对于左右节点都不为空，并且数值都相同的情况）
  
  




