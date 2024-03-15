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




