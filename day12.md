## 二叉树part1

二叉树的种类：1.满二叉树；2.完全二叉树
满二叉树：度只有0和2 深度为k 有$2^{k-1}$个节点；
完全二叉树：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层（h从1开始），则该层包含 1~ 2^(h-1) 个节点。

优先队列是一个堆，堆是一个完全二叉树，保证父子节点的顺序关系

二叉搜索树

前面介绍的树，都没有数值的，而二叉搜索树是有数值的了，二叉搜索树是一个有序树。

若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
它的左、右子树也分别为二叉排序树

平衡二叉搜索树（AVL树）
性质：

- 一颗空树或者左右两个子树的高度差绝对值不超过1，左右两颗子树都是一颗平衡二叉搜索树

**C++中map、set、multimap，multiset的底层实现都是平衡二叉搜索树**，所以map、set的增删操作时间时间复杂度是logn，注意我这里没有说unordered_map、unordered_set，unordered_map、unordered_set底层实现是哈希表。

因为为平衡二叉树，所以增删的操作时间复杂度为 log（n)

所以大家使用自己熟悉的编程语言写算法，一定要知道常用的容器底层都是如何实现的，最基本的就是map、set等等，否则自己写的代码，自己对其性能分析都分析不清楚！

#### 二叉树的存储方式

- 链式存储
- 顺序存储（遍历方式需要注意 如果父节点的下标为i 那么左孩子为2i+1;右孩子为2i+2；
  大多都是使用链式存储二叉树

#### 二叉树的遍历

- 深度优先dfs
  - 前序遍历（迭代，递归）
  - 中序遍历（迭代，递归）
  - 后序遍历（迭代，递归）
- 广度优先dfs
  - 层次遍历（迭代）

前中后遍历其实指的是中间节点的遍历顺序（只需要记住为中间节点的遍历顺序就可以）
前序遍历：中左右
中序遍历：左中右
后序遍历：左右中

广度优先遍历需要使用队列来进行实现，深度优先遍历使用栈来实现

```CPP
struct TreeNode{
    int val;
    TreeNode * lhs;
    TreeNode * rhs;
    TreeNode(int x):val(x),lhs(NULL),rhs(NULL){}
};
```

### 二叉树的递归遍历

每次写递归，都按照这三要素来写，可以保证大家写出正确的递归算法！

- 确定递归函数的参数和返回值： 确定哪些参数是递归的过程中需要处理的，那么就在递归函数里加上这个参数， 并且还要明确每次递归的返回值是什么进而确定递归函数的返回类型。
- 确定终止条件： 写完了递归算法, 运行的时候，经常会遇到栈溢出的错误，就是没写终止条件或者终止条件写的不对，操作系统也是用一个栈的结构来保存每一层递归的信息，如果递归没有终止，操作系统的内存栈必然就会溢出。
- 确定单层递归的逻辑： 确定每一层递归需要处理的信息。在这里也就会重复调用自己来实现递归的过程。

前序遍历（其他两个遍历方式 只需要更改插入值的顺序就可以）

```CPP
class Solution {
public:
    void traversal(TreeNode* cur, vector<int>& vec) {
        if (cur == NULL) return;
        vec.push_back(cur->val);    // 中
        traversal(cur->left, vec);  // 左
        traversal(cur->right, vec); // 右
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};
```

#### 二叉树的迭代遍历

递归的实现就是：每一次的递归调用就是把函数的局部变量、参数值和返回地址来压入调用的栈中，然后返回的时候不断从栈顶来弹出上一次递归的各种参数；

**前序遍历**（非递归方法）

```CPP
vector<int> preorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    vector<int> res;
    if(root == null) return ;
    st.push(root);
    while(!st.empty()){
        TreeNode * node = st.top();
        st.pop();
        res.push_back(node->val);
        if(node->right) st.push(node->right);
        if(node->left) st.push(node->left);

    }
    return res;


}

```

**中序遍历**

```CPP
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur != NULL || !st.empty()) {
            if (cur != NULL) { // 指针来访问节点，访问到最底层
                st.push(cur); // 将访问的节点放进栈
                cur = cur->left;                // 左
            } else {
                cur = st.top(); // 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
                st.pop();
                result.push_back(cur->val);     // 中
                cur = cur->right;               // 右
            }
        }
        return result;
    }
};
```

**后序遍历**

```CPP
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> result;
        if (root == NULL) return result;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            result.push_back(node->val);
            if (node->right) st.push(node->right); // 相对于前序遍历，这更改一下入栈顺序 （空节点不入栈）
            if (node->left) st.push(node->left); // 空节点不入栈
        }
        reverse(result.begin(), result.end()); // 将结果反转之后就是左右中的顺序了
        return result;
    }
}
```
