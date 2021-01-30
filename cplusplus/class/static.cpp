#include<iostream>
#include<string.h>
using namespace std;

class Student{
    private:
        string name;
        int age;
        static int s_total;
    public:
        Student();
        Student(string name, int age);
        void show();
        static void showStuNumber();
};

int Student::s_total = 0;

Student::Student(){
    s_total++;
}

Student::Student(string name, int age){
    this->name = name;
    this->age = age;
    s_total++;
}

void Student::show(){
    cout<<"Student name: "<<name<<" Student age: "<<age<<" Student number: "<<s_total<<endl;
}

void Student::showStuNumber(){
    cout<<"Student number: "<<s_total<<endl;
}

int main(){
    Student stu1("slei", 25);
    stu1.show();
    Student stu2("lxumei", 24);
    stu2.show();
    Student::showStuNumber();
    return 0;
}
