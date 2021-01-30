#include<iostream>
#include<string>
using namespace std;

class Box{
    string creater; //defalut access level is private
    public: //access specifier
        double length;
        double breadth;
        double height;
        Box(){}
        Box(double len, double bre);
        Box(double len, double bre, double hei);
        double get(void);
        void set(double len, double bre, double hei);
        void setCreater(string str);
};

Box::Box(double len, double bre, double hei){
    length = len;
    breadth = bre;
    height = hei;
}

Box::Box(double len, double bre):length(len), breadth(bre){
    height = 0;
    cout<<breadth<<" "<<length<<endl;
}

double Box::get(void){
    return length * breadth * height;
}

void Box::set(double len, double bre, double hei){
    length = len;
    breadth = bre;
    height = hei;
}

void Box::setCreater(string str){
    creater = str;
    cout<<"creater = "<<creater<<endl;
}

int main(){
    cout<<"create a Box object:\n";
    Box b1;
    b1.set(3, 4, 5);
    cout<<"get(): "<<b1.get()<<endl;
    b1.setCreater("lxumei");

    cout<<endl;
    cout<<"creater a object pointer\n";
    Box *b2 = new Box;
    b2->set(3, 3, 3);
    cout<<"b2->get():"<<b2->get()<<endl;
    b2->setCreater("lxumei");
    delete(b2);
    
    cout<<endl;
    cout<<"Constructor"<<endl;
    Box b3(2, 2, 2);
    cout<<"b3.get():"<<b3.get()<<endl;

    cout<<endl;
    cout<<"Constructor"<<endl;
    Box *b4 = new Box(1, 2, 2);
    cout<<"b4->get():"<<b4->get()<<endl;

    cout<<endl;
    cout<<"Constructor"<<endl;
    Box *b5 = new Box(1, 2);
    cout<<"b5->get():"<<b5->get()<<endl;
    return 0;
}
