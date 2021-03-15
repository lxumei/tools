#include<iostream>
#include<cstdlib>
using namespace std;

class OutOfRange{
    public:
        OutOfRange():m_flag(1){};
        OutOfRange(int len, int index):m_len(len), m_index(index), m_flag(2){};
    public:
        void what() const;
    private:
        int m_flag;
        int m_len;
        int m_index;
};

void OutOfRange::what() const{
    if(m_flag == 1)
        cout<<"Error: empty array, no elements to pop."<<endl;
    else if(m_flag == 2)
        cout<<"Error: out of range (array length "<<m_len<<", access index "<<m_index<<")"<<endl;
    else
        cout<<"Unknown exception."<<endl;
}

class Array{
    public:
        Array();
        ~Array(){free(m_p);}
    public:
        int operator[](int i) const;
        int push(int ele);
        int pop();
        int length() const {return m_len;}
    private:
        int m_len;
        int m_capacity;
        int *m_p;
    private:
        static const int m_stepSize = 50;
};

Array::Array(){
    m_p = (int *)malloc(sizeof(int) * m_stepSize);
    m_capacity = m_stepSize;
    m_len = 0;
}

int Array::operator[] (int index) const{
    if(index < 0 || index >= m_len){
        throw OutOfRange(m_len, index);
    }

    return *(m_p + index);
}

int Array::push(int ele){
    if(m_len >= m_capacity){
        m_capacity += m_stepSize;
        m_p = (int *)realloc(m_p, sizeof(int) * m_capacity);
    }

    *(m_p + m_len) = ele;
    m_len++;
    return m_len - 1;
}

int Array::pop(){
    if(m_len == 0)
        throw OutOfRange();
    m_len--;
    return *(m_p + m_len);
}

void printArray(Array &arr){
    int len = arr.length();
    if(len == 0){
        cout<<"Empty array! No elements to print."<<endl;
        return;
    }

    for(int i = 0; i < len; i++){
        if(i == len - 1){
            cout<<arr[i]<<endl;
        }else{
            cout<<arr[i]<<" ";
        }
    }
}

int main(){
    Array nums;
    
    for(int i = 0; i < 10; i++){
        nums.push(i);
    }
    printArray(nums);

    try{
        cout<<nums[20]<<endl;
    }catch(OutOfRange &e){
        e.what();
    }

    try{
        for(int i = 0; i < 20; i++)
            nums.pop();
    }catch(OutOfRange &e){
        e.what();
    }

    printArray(nums);

    return 0;
}
