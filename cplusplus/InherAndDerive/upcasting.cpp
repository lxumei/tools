#include<iostream>
using namespace std;

class A{
    public:
        A(int a);
        virtual void display();
        int m_a;
};

A::A(int a):m_a(a){
}

void A::display(){
    cout<<"class A: m_a = "<<m_a<<endl;
}

class B: public A{
    public:
        B(int a, int b);
        void display();
        int m_b;
};

B::B(int a, int b):A(a), m_b(b){
}

void B::display(){
    cout<<"Class B: m_a = "<<m_a<<", m_b = "<<m_b<<endl;
}

class C{
    public:
        C(int c);
    public:
        void display();
    protected:
        int m_c;
};

C::C(int c):m_c(c){
}

void C::display(){
    cout<<"Class C: m_c = "<<m_c<<endl;
}

class D: public B, public C{
    public:
        D(int a, int b, int c, int d);
    public:
        void display();
    private:
        int m_d;
};

D::D(int a, int b, int c, int d):B(a, b), C(c), m_d(d){}

void D::display(){
    cout<<"Class D: m_a = "<<m_a<<", m_b = "<<m_b<<" , m_c = "<<m_c<<", m_d = "<<m_d<<endl;
}

int main(){
    A a(10);
    B b(66, 99);
    a.display();
    b.display();

    cout<<"--------------------"<<endl;
    a = b;
    a.display();
    b.display();

    cout<<"--------------------"<<endl;
    A *pa = new A(1);
    B *pb = new B(2, 20);
    C *pc = new C(3);
    D *pd = new D(4, 40, 400, 4000);

    pa = pd;
    pa->display();

    pb = pd;
    pb->display();

    pc = pd;
    pc->display();

    cout<<"pa = "<<pa<<endl;
    cout<<"pb = "<<pb<<endl;
    cout<<"pc = "<<pc<<endl;
    cout<<"pd = "<<pd<<endl;

    return 0;
}
