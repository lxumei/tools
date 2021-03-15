#include<iostream>
#include<string>
using namespace std;

int main(){
    string str = "123";
    cout<<str<<endl;
    cout<<str.substr(3, -1)<<endl;
    cout<<str.substr(1,1)<<endl;
    return 0;
}
