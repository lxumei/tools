#include<iostream>
using namespace std;

int main(){
    int a;
    const int* pa = &a;
    int &ra = a;
    cout<<&a<<endl;
    cout<<&pa<<endl;
    cout<<&ra<<endl;
    return 0;
}
