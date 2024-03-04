## 栈和队列

#### 栈

栈提供push 和 pop 等等接口，所有元素必须符合先进后出规则，所以栈不提供走访功能，也不提供迭代器(iterator)。 不像是set 或者map 提供迭代器iterator来遍历所有元素。container adapter
栈是可插拔的（可以自由控制不同容器来实现栈的功能）
使用方法：push pop top
常用的SGI STL，如果没有指定底层实现的话，默认是以deque为缺省情况下栈的底层结构。
deque是一个双向队列，封住一端打开另一端就可以实现栈的逻辑

#### 使用栈来模拟队列
核心：使用两个stackin 和 stackout两个栈来进行处理

```Cpp
class MyQueue {
public:
    stack<int> stIn;
    stack<int> stOut;
    /** Initialize your data structure here. */
    MyQueue() {

    }
    /** Push element x to the back of queue. */
    void push(int x) {
        stIn.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        // 只有当stOut为空的时候，再从stIn里导入数据（导入stIn全部数据）
        if (stOut.empty()) {
            // 从stIn导入数据直到stIn为空
            while(!stIn.empty()) {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }

    /** Get the front element. */
    int peek() {
        int res = this->pop(); // 直接使用已有的pop函数
        stOut.push(res); // 因为pop函数弹出了元素res，所以再添加回去
        return res;
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return stIn.empty() && stOut.empty();
    }
};

```






#### 使用队列来模拟栈
核心：使用一个队列就可以开始来模拟栈了
对于先进先出来说 一个队列可以将头部元素（除了最后一个元素）重新全部塞回头部 然后实现先进后出的效果
code
```CPP
class MyStack {
public:
    queue<int> que;

    MyStack() {

    }
    
    void push(int x) {
        que.push(x);

    }
    
    int pop() {
        int size = que.size();
        size--;
        while(size--){
            que.push(que.front());
            que.pop();

        }
        int result = que.front();
        que.pop();
        return result;

    }
    
    int top() {
        return que.back();

    }
    
    bool empty() {
        return que.empty();

    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
```