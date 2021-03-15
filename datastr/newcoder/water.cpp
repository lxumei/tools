#include<iostream>
using namespace std;

int main(){
    int n;
    while(cin>>n){
        if(n == 0)
            continue;
        int empty = n;
        int tmp = 0;
        int res = 0;
        while(empty > 2){
            tmp = empty / 3;
            res += tmp;
            empty = tmp + empty % 3;
        }
        if(empty == 2)
            res++;
        cout<<res<<endl;
    }

    return 0;
}
