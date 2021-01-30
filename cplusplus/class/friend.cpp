#include<iostream>
using namespace std;

class Address;

class Student{
    public:
        Student(string name, int age);
        void show(Address *addr);
        friend void show(Student *stu);
    private:
        string name;
        int age;
};

class Address{
    private:
        string province;
        string city;
    public:
        Address(string province, string city);
        friend void Student::show(Address *addr);
};

Student::Student(string name, int age){
    this->name = name;
    this->age = age;
}

void Student::show(Address *addr){
    cout<<name<<","<<age<<","<<endl;
    cout<<"address: "<<addr->province<<","<<addr->city<<endl;
}

Address::Address(string province, string city){
    this->province = province;
    this->city = city;
}

void show(Student *stu){
    cout<<stu->name<<","<<stu->age<<","<<endl;
}

int main(){
    Student stu1("slei", 25);
    Address addr("Shandong", "Zouchen");
    stu1.show(&addr);
    show(&stu1);

    return 0;
}
