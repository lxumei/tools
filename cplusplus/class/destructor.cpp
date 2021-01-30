#include<iostream>
using namespace std;

class Box{
    public:
        int flag;
        double lenght;
        double breadth;
        double height;
        Box(int f);
        ~Box();
};

Box::Box(int f):flag(f){
}

Box::~Box(){
    cout<<flag<<endl;
}

Box b3(3);

void fun(){
    Box b4(4);
}

int main(){
    Box b1(1);
    Box *b2 = new Box(2);
    fun();
    cout<<"main"<<endl;
    return 0;
}
