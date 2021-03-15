#include<iostream>
using namespace std;

class Line{
    public:
        Line(float len);
        virtual float area() = 0;
        virtual float volume() = 0;
    protected:
        float m_len;
};

Line::Line(float len):m_len(len){}

class Rec: public Line{
    public:
        Rec(float len, float width);
        float area();
    protected:
        float m_width;
};

Rec::Rec(float len, float width):Line(len), m_width(width){}

float Rec::area(){
    return m_len * m_width;
}

class Cuboid: public Rec{
    public:
        Cuboid(float len, float width, float height);
        float area();
        float volume();
    protected:
        float m_height;
};

Cuboid::Cuboid(float len, float width, float height):Rec(len, width), m_height(height){}

float Cuboid::area(){
    return 2 * (m_len * m_width + m_len * m_height + m_width * m_height);
}

float Cuboid::volume(){
    return m_len * m_width * m_height;
}

class Cube: public Cuboid{
    public:
        Cube(float len);
        float area();
        float volume();
};

Cube::Cube(float len):Cuboid(len, len, len){}

float Cube::area(){
    return 6 * m_len * m_len;
}

float Cube::volume(){
    return m_len * m_len * m_len;
}

int main(){
    Line *p = new Cuboid(10, 20, 30);
    cout<<"Cuboid's area = "<<p->area()<<endl;
    cout<<"Cuboid's volume = "<<p->volume()<<endl;

    p = new Cube(15);
    cout<<"Cube's area = "<<p->area()<<endl;
    cout<<"Cube's volume = "<<p->volume()<<endl;

    return 0;
}
