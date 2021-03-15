#include<iostream>
#include<string>
#include<exception>
using namespace std;

void test1(){
    string str = "slei is a graduate student of OUC";
    try{
        char ch1 = str[100];
        cout<<ch1<<endl;
    }catch(exception e){
        cout<<"[1]out of bound!"<<endl;
    }

    try{
        char ch2 = str.at(100);
        cout<<ch2<<endl;
    }catch(exception &e){
        cout<<"[2]out of bound!"<<endl;
    }

    try{
        throw "Unknown Exception";
        cout<<"This statement will not be executed."<<endl;
    }catch(const char* &e){
        cout<<"In catch: "<<e<<endl;
    }
}

void func_inner(){
    throw "Unknown Exception";
    cout<<"[1]This statement will not be executed."<<endl;
}

void func_outer(){
    func_inner();
    cout<<"[2]This statement will not be executed."<<endl;
}

void test2(){
    try{
        func_outer();
        cout<<"[3] This statement will not be executed."<<endl;
    }catch(const char *&e){
        cout<<"In catch 3: "<<e<<endl;
    }
}

int main(){
    test2();
    return 0;
}
