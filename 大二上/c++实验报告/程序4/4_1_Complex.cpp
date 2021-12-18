#include <iostream>
using namespace std;

class Complex
{
private:
    double r,i;

public:

    Complex(double x=0, double y=0): r(x),i(y){};

    Complex(const Complex &c): r(c.r),i(c.i){};

    Complex add(const Complex &c)
    {
        Complex temp;

        temp.r=r+c.r;
        temp.i=i+c.i;

        return temp;
    }


    Complex sub(const Complex &c)
    {
        r-=c.r;
        i-=c.i;

        return *this;
    }


    void display()
    {
        cout<<r<<"+"<<i<<"i"<<endl;
    }

};

int main()
{
    Complex c1,c2(1),c3(3,3);
    c1=c1+c2;
    c1=c2.add(c3);
    c1.display();
    c1=c2.sub(c3);
    c1.display();
}
