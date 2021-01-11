#include<iostream>
#include<algorithm>
#include<stack>
#include<map>
using namespace std;
 
map<char, int> mp;
 
int cal(int num1, int num2, char op){
    int res = 0;
    switch (op){
        case '+':
            res = num1 + num2;
            break;
        case '-':
            res = num1 - num2;
            break;
        case '*':
            res = num1 * num2;
            break;
        case '/':
            res = num1 / num2;
            break;
    }
 
    return res;
}
 
int main(){
 
    string str;
    cin>>str;
 
    stack<int> num;
    stack<char> op;
 
    int len = str.length();
    int val = 0, sign = 1, flag = 0;
     
    //注意优先级的设置，不要少了'('
    mp['$'] = -1;
    mp['('] = 0;
    mp['+'] = 1;
    mp['-'] = 1;
    mp['*'] = 2;
    mp['/'] = 2;
    op.push('$');
 
    for(int i = 0; i < len; i++){
        char cur = str[i];
        if(isdigit(cur)){
            //cout<<cur<<endl;
            val = val * 10 + (cur - '0');
            if(i == len-1 || !isdigit(str[i+1])){
                num.push(val * sign);
                val = 0;
                sign = 1;
            }
        }else if(cur == '{' || cur == '[' || cur == '('){
            op.push('(');
        }else if(cur == '}' || cur == ']' || cur == ')'){
            //cout<<cur<<endl;
            while(op.top() != '('){
                int num2 = num.top();
                num.pop();
                int num1 = num.top();
                num.pop();
                num.push(cal(num1, num2, op.top()));
                op.pop();
            }
            op.pop();
        }else{
            if(str[i] == '-'){ //注意，这里要处理负号的情况
                if(i == '0' || (isdigit(str[i+1]) && str[i-1] != ')' && !isdigit(str[i-1]))){
                    sign = -1;
                    continue;
                }
            }
            //cout<<cur<<" "<<mp[cur]<<" "<<mp[op.top()]<<endl;
            while(mp[cur] <= mp[op.top()]){
                int num2 = num.top();
                num.pop();
                int num1 = num.top();
                num.pop();
                num.push(cal(num1, num2, op.top()));
                op.pop();
            }
            op.push(cur);
        }
 
    }
 
    while(op.top() != '$'){
        int num2 = num.top();
        num.pop();
        int num1 = num.top();
        num.pop();
        num.push(cal(num1, num2, op.top()));
        op.pop();
    }
 
    //cout<<str<<"=";
    cout<<num.top()<<endl;
 
    return 0;
}

