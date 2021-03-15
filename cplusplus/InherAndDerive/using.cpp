#include<iostream>
using namespace std;

class People{
    public:
        void show();
    protected:
        string name;
        int age;
};

void People::show(){
    cout<<name<<","<<age<<endl;
}

class Student : public People{
    public:
        void show();
    public:
        using People::name;
        using People::age;
};

void Student::show(){
    cout<<"this is student\n"<<endl;
}

int main(){
    Student stu1;
    stu1.name = "slei";
    stu1.age = 25;
    cout<<stu1.name<<endl;
    stu1.show();
    stu1.People::show();
    return 0;
}

