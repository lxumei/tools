#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

void next(queue<int> train_in, stack<int> cur_train, vector<int> res){
    if(train_in.empty()){
        for(int i = 0; i < res.size(); i++)
            cout<<res[i]<<" ";
        
        while(!cur_train.empty()){
            int cur = cur_train.top();
            cout<<cur<<" ";
            cur_train.pop();
        }
        cout<<endl;
        return;
    }
    
    if(cur_train.empty()){
        cur_train.push(train_in.front());
        train_in.pop();
        next(train_in, cur_train, res);
    }else{
        int cur, front;
        while(!cur_train.empty()){
            //当前已经进站的车出站
            cur = cur_train.top();
            cur_train.pop();        //当前进站的车，将栈顶的车出栈
            res.push_back(cur);     //将出栈的车放在res中
            
            front = train_in.front();   //从未入栈的车中，按照输入顺序，选择第一辆车
            train_in.pop();     //
            cur_train.push(front);  //将选择的第一辆车进站
            next(train_in, cur_train, res);
            
            //当前已经进站的车不出站
            res.pop_back();
            cur_train.pop();    //pop front
            cur_train.push(cur);    
            cur_train.push(front);       
            next(train_in, cur_train, res);
        }
    }
    
}

int main(){
    int n;

    while(cin>>n){
        queue<int> train_in;
        stack<int> cur_train;
        vector<int> res;

        for(int i = 0; i < n; i++){
            int tmp;
            cin>>tmp;
            train_in.push(tmp);
        }
        next(train_in, cur_train, res);
    }
    
    return 0;
}
