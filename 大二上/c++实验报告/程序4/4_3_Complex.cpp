#include<iostream>
using namespace std;

class Complex
{
private:
    double r,i;

public:

    //Complex(){};
    Complex(double x=0, double y=0):r(x),i(y)
    {cout<<"Default Complex("<<r<<","<<i<<")"<<endl;};//:{cout<<"r="<<r<<" i="<<i<<endl;};

    Complex(const Complex &c): r(c.r),i(c.i)
    {cout<<"Copy Complex("<<r<<","<<i<<")"<<endl;};

    void display() {cout<<r<<"+"<<i<<"i"<<endl;};

    const Complex& operator=(const Complex &c)
    {
        i=c.i;
        r=c.r;

        cout<<"Operator = ("<<r<<","<<i<<")"<<endl;

        return *this;
    };

    friend Complex operator+(const Complex &c1, const Complex &c2);
    friend Complex operator-(const Complex &c1, const Complex &c2);

    friend ostream& operator <<(ostream& out_put, const Complex &c);  //重载输入运算符
    friend istream& operator >>(istream& in_put, Complex &c);

};

Complex operator+(const Complex &c1, const Complex &c2)
{
    Complex tmp_c;

    tmp_c.i=c1.i+c2.i;
    tmp_c.r=c1.r+c2.r;

    return tmp_c;
}
Complex operator-(const Complex &c1, const Complex &c2)
{
    Complex tmp_c;

    tmp_c.i=c1.i-c2.i;
    tmp_c.r=c1.r-c2.r;

    return tmp_c;
}
ostream& operator <<(ostream& out_put, const Complex &c) //重载输入运算符
{
    out_put<<c.r<<"+"<<c.i<<"i";

    return out_put;
}
istream& operator >>(istream& in_put, Complex &c)
{
    in_put>>c.r>>c.i;

    return in_put;
}

int main()
{

    Complex c1,c2(1),c3(3,3);

    cin>>c1;
    cout<<"c1="<<c1<<endl;

    Complex c4=c2;
    c4=c2;
    cout<<endl<<"c4=c2"<<endl;


    cout<<endl<<"cout<<1+c3<<endl"<<endl;
    cout<<1+c3<<endl;

    //cout<<endl<<"cout<<c1<<endl"<<endl;
    //cout<<c1<<endl;


}
