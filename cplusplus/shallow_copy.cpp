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
    Test t1(10);
    for(int i = 0; i < 10; i++){
        t1[i] = i;
    }
    cout<<"t1:";
    display(t1);

    Test t2 = t1;
    t2[0] = 100;
    cout<<"t1:";
    display(t1);
    cout<<"t2:";
    display(t2);

    Test *p_t1 = new Test(10);
    for(int i = 0; i < 10; i++){
        (*p_t1)[i] = i;
    }
    display(*p_t1);

    Test t3 = *p_t1;
    display(t3);
    t3[1] = 100;
    display(*p_t1);
    return 0;
}

