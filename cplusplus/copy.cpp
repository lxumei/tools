#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class Test{
    public:
        Test(int len);
        ~Test();
    public:
        int operator[](int i) const{
            return m_p[i];
        }
        int &operator[](int i){
            return m_p[i];
        }
        int length() const{
            return m_len;
        }
    private:
        int m_len;
        int *m_p;
};

Test::Test(int len):m_len(len){
    m_p = (int *)malloc(sizeof(int)*m_len);
}

Test::~Test(){
    free(m_p);
}

class Array{
    public:
        Array(int len);
        Array(Array &arr);
        ~Array();
    public:
        int operator[](int i) const{
            return m_p[i];
        }
        int &operator[](int i){
            return m_p[i];
        }
        int length() const{
            return m_len;
        }
        Array &operator=(const Array &arr);
    private:
        int m_len;
        int *m_p;
};

Array::Array(int len):m_len(len){
    m_p = (int *)malloc(sizeof(int)*m_len);
}

//copy constructor function 
Array::Array(Array &arr){
    m_len = arr.m_len;
    m_p = (int *)malloc(sizeof(int)*m_len);
    memcpy(m_p, arr.m_p, m_len * sizeof(int));
}

Array::~Array(){
    free(m_p);
}

Array &Array::operator=(const Array &arr){
    if(this!=&arr){
        m_len = arr.m_len;
        free(m_p);
        m_p = (int *)malloc(sizeof(int) * m_len);
        memcpy(m_p, arr.m_p, sizeof(int) * m_len);
    }

    return *this;
} 

void display(const Array &arr){
    int len = arr.length();
    for(int i = 0; i < len; i++){
        if(i == len - 1)
            cout<<arr[i]<<endl;
        else
            cout<<arr[i]<<" ";
    }
}

void display(const Test &arr){
    int len = arr.length();
    for(int i = 0; i < len; i++){
        if(i == len - 1)
            cout<<arr[i]<<endl;
        else
            cout<<arr[i]<<" ";
    }
}

int main(){

    Array arr1(10);
    for(int i = 0; i < 10; i++){
        arr1[i] = i;
    }

    Array arr2 = arr1;
    arr2[5] = 100;
    arr2[3] = 32;

    display(arr1);
    display(arr2);

    Array arr3(5);
    for(int i = 0; i < 5; i++){
        arr3[i] = i;
    }

    display(arr3);

    arr3 = arr2;
    display(arr3);

    Test t1(10);
    for(int i = 0; i < 10; i++){
        t1[i] = i;
    }
    display(t1);

    Test t2 = t1;
    t2[0] = 100;
    display(t1);
    display(t2);

    return 0;
}

