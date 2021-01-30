#include<iostream>
using namespace std;

class Student{
    private:
        static int s_total;
        const string class_name;
        string name;
        int age;
    public:
        Student();
        Student(string name, int age, string str);
        string getName() const;
        int getAge() const;
        void show() const;
};

int Student::s_total = 0;

Student::Student(){
    s_total++;
}

Student::Student(string name, int age, string str):class_name(str){
    this->name = name;
    this->age = age;
    s_total++;
}

string Student::getName() const{
    return name;
}

int Student::getAge() const{
    return age;
}

void Student::show() const{
    cout<<class_name<<":"<<name<<","<<age<<"    "<<s_total<<endl;
}
int main(){
    Student stu1("slei", 25, "stu1");
    stu1.show();
    Student stu2("lxumei", 24, "stu2");
    stu2.show();
    const Student stu3("casper", 25, "stu3");
    stu3.show();
    return 0;
}
