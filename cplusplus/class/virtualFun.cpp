#include<iostream>
#include<string>
using namespace std;

class People{
    public:
        People(string name, int age);
        virtual void display();
    protected:
        string name;
        int age;
};

People::People(string name, int age){
    this->name = name;
    this->age = age;
}

void People::display(){
    cout<<name<<","<<age<<",do nothing"<<endl;
}

class Teacher: public People{
    public:
        Teacher(string name, int age, int salary);
        void display();
    private:
        int salary;
};

Teacher::Teacher(string name, int age, int salary):People(name, age){
    this->salary = salary;
}

void Teacher::display(){
    cout<<name<<","<<age<<","<<salary<<endl;
}

int main(){
    People *p = new People("slei", 25);
    p->display();

    p = new Teacher("casper", 24, 300000);
    p->display();

    People pp = Teacher("lxumei", 24, 300000);
    pp.display();
    return 0;
}

