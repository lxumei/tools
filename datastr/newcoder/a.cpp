#include<iostream>
using namespace std;

int main(){
    string str;
    while(cin>>str){
        int len = str.size();
        int plus = 1;
        int res = 0;
        for(int i = len - 1; i > 1; i--){
            char c = str[i];
            if(c >= '0' && c <= '9')
                res += (c - '0') * plus;
            else
                res += (c - 'A' + 10) * plus;
            plus *= 16;
        }
        cout<<res<<endl;
                                                            }
}
