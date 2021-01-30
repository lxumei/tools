#include<iostream>
#include<string>
using namespace std;

class Student{
    private:
        string name;
        int age;
    public:
        Student();
        Student(string name, int age);
        void show();
};

Student::Student(){

}

Student::Student(string name, int age){
    this->name = name;
    this->age = age;
}

void Student::show(){
    cout<<"student name: "<<name<<endl;
    cout<<"student age: "<<age<<endl;
}

int main(){

    Student stu("slei",25);  
    stu.show();
    return 0;
}
