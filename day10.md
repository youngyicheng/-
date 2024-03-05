## 栈和队列的练习

#### 有效括号
核心：分析好对应括号不匹配的问题
- 字符串的左方向的括号多余了，所以不匹配
- 括号没有实现多余，但是括号的类型没有匹配上
- 字符串的右边括号多余了

使用栈的上下匹配进行对比从来来确定好括号的匹配

```CPP
class Solution {
public:
    bool isValid(string s) {
        if(s.size() % 2!=0) return false;
        stack<char> st;
        for(int i=0;i<s.size();i++){
            if(s[i]=='(') st.push(')');
            else if(s[i]=='{') st.push('}');
            else if(s[i]=='[') st.push(']');
            else if(st.empty()||st.top()!=s[i]) return false;
            else st.pop();
        }
        return st.empty();

    }
};
```

#### 删除字符串的重复部分
核心：使用栈来进行重复的字符匹配
每次push的时候判断是不是top与相同，如果相同就实行pop操作

code：
```CPP
class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        for(char s : s){
            if(st.empty()||s!=st.top()){
                st.push(s);
            }
            else{
                st.pop();
            }
        }
        string res = "";
        while(!st.empty()){
            res+=st.top();
            st.pop();
        }
        reverse(res.begin(),res.end());
        return res;


    }
};
```

**逆波兰表达式**
核心：看懂运算要求，每次遇到运算符才开始操作，然后不断弹出最上面的两个数字，生成数字后进行push（同样是使用栈进行操作）
```CPP
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        for(int i=0;i<tokens.size();i++){
            if(tokens[i]=="+"||tokens[i]=="-"||tokens[i]=="*"||tokens[i]=="/"){
                long long num1 = st.top();
                st.pop();
                long long num2 = st.top();
                st.pop();
                if(tokens[i] == "+") st.push(num2+num1);
                if(tokens[i] == "-") st.push(num2-num1);
                if(tokens[i] == "*") st.push(num2*num1);
                if(tokens[i] == "/") st.push(num2/num1);
            }
            else{
                st.push(stoll(tokens[i]));
            }
        }

        int result = st.top();
        st.pop(); // 把栈里最后一个元素弹出（其实不弹出也没事）
        return result;

    }
};
```







