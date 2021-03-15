#include<iostream>
using namespace std;

class People{
    public:
        void show();
        People(string name, int age);
    protected:
        string name;
        int age;
};

void People::show(){
    cout<<name<<","<<age<<endl;
}

People::People(string name, int age){
    this->name = name;
    this->age = age;
}

class Student : public People{
    public:
        void show();
        using People::name;
        using People::age;
        Student(string name, int age, int id);
    private:
        int id;
};

Student::Student(string name, int age, int id):People(name, age){
    this->id = id;
}

void Student::show(){
    cout<<name<<","<<age<<","<<id<<endl;
}

int main(){
    Student stu1("slei", 25, 100);
    stu1.show();
    return 0;
}

