#include<iostream>
using namespace std;

class People{
    public:
        void setname(string name);
        void setage(int age);
        void sethobby(string hobby);
        string getname();
        int getage();
        string gethobby();
    protected:
        string name;
        int age;
    private:
        string hobby;
};

void People::setname(string name){
    this->name = name;
}

void People::setage(int age){
    this->age = age;
}

void People::sethobby(string hobby){
    this->hobby = hobby;
}

string People::getname(){
    return name;
}

int People::getage(){
    return age;
}

string People::gethobby(){
    return hobby;
}

class Student: public People{
    public:
        void setid(int id);
        int getid();
        void show();
    private:
        int id;
};

void Student::setid(int id){
    this->id = id;
}

int Student::getid(){
    return id;
}

void Student::show(){
    cout<<name<<","<<age<<","<<gethobby()<<","<<id<<endl;
}

int main(){
    Student stu;
    stu.setname("slei");
    stu.setage(25);
    stu.setid(100);
    stu.sethobby("computer");
    stu.show();
    return 0;
}
