#include<iostream>
using namespace std;

int main(){

    string *str = new string[10];
    int *arr = new int[10];

    delete [] str;
    delete [] arr;

    return 0;
}
