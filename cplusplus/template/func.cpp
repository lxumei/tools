#include<iostream>
using namespace std;

template<typename T> void Swap(T *a, T*b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int n1 = 100, n2 = 200;
    Swap(&n1, &n2);
    cout<<n1<<" "<<n2<<endl;

    float f1 = 12.5, f2 = 12.6;
    Swap(&f1, &f2);
    cout<<f1<<" "<<f2<<endl;

    return 0;
}
