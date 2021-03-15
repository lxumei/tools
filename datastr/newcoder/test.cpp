#include<iostream>
using namespace std;

int main(){

    int a[] = {1, 2, 3, 4};
    int *b = a;
    cout<<*b++<<endl;
    cout<<a<<endl;
    cout<<b<<endl;
    for(int i = 0; i < 4; i++)
        cout<<a[i]<<endl;
    return 0;
}
