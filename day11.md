## 栈和队列的练习
#### 滑动窗口的最大值
核心：单调队列的实现
设计单调队列的时候，pop，和push操作要保持如下规则：

pop(value)：如果窗口移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作
push(value)：如果push的元素value大于入口元素的数值，那么就将队列入口的元素弹出，直到push元素的数值小于等于队列入口元素的数值为止
保持如上规则，每次窗口移动的时候，只要问que.front()就可以返回当前窗口的最大值。

如果使用了单调队列后找到最大元素只需要进行遍历这个deque就可以实现，从而直接不对原始的que进行操作 这个还是需要另一步处理的

code:
```CPP
class Solution {


private:


    class MyQueue{ //构建单调队列
        public:
        deque<int> que;
        void pop(int value){
            if(!que.empty() && value == que.front()){
                que.pop_front();
            }
        }
        void push(int value){
            while(!que.empty()&&value>que.back()){
                que.pop_back();
            }
            que.push_back(value);
        }
        int front(){
            return que.front();
        }

    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> res;
        for (int i=0;i<k;i++){
            que.push(nums[i]);
        }

        res.push_back(que.front());
        for(int i=k;i<nums.size();i++){
            que.pop(nums[i-k]);
            que.push(nums[i]);
            res.push_back(que.front());

        }
        return res;
    }
};
```








#### 前K个高频元素
设计三大问题：
1. 统计元素出现的频率（使用unodered_map)
2. 对频率进行排序（使用最小堆，每次pop出都是最小元素，从而k个留下来都是最大的元素）
3. 找出最大的k个元素（使用first进行调用）
核心：建议优先队列（使用的是最小堆：需要自定义比较条件）



注意：大家对这个比较运算在建堆时是如何应用的，为什么左大于右就会建立小顶堆，反而建立大顶堆比较困惑。

确实 例如我们在写快排的cmp函数的时候，return left>right 就是从大到小，return left<<right 就是从小到大。

优先级队列的定义正好反过来了，可能和优先级队列的源码实现有关（我没有仔细研究），我估计是底层实现上优先队列队首指向后面，队尾指向最前面的缘故！

code:
```CPP
class Solution {
public:
    class mycomparison{
        public:
        bool operator()(const pair<int,int>& lhs,const pair<int,int>& rhs){
            return lhs.second>rhs.second;
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int>map;
        for(int i=0;i<nums.size();i++){
            map[nums[i++]]++;
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,mycomparison> pri_que;
        for(unordered_map<int,int>::iterator it=map.begin();it!=map.end();it++){
            pri_que.push(*it);
            if(pri_que.size()>k){
                pri_que.pop();
            }

        }
        vector<int> res(k);
        for(int i =k-1;i>=0;i--){
            res[i] = pri_que.top().first;
            pri_que.pop();
        }
        return res;

    }
};
```