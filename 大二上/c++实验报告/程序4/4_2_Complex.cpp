#include<iostream>
using namespace std;

class Complex
{
private:
    double r,i;

public:

    //Complex(){};

    Complex(double x=0, double y=0): r(x),i(y){};

    Complex(const Complex &c): r(c.r),i(c.i){};

    void display()
    {
        cout<<r<<"+"<<i<<"i"<<endl;
    }


    Complex operator +(const Complex &c)
    {
        Complex tmp_c;

        tmp_c.i=i+c.i;
        tmp_c.r=r+c.r;

        return tmp_c;
    }

    Complex add(const Complex &c)
    {
        Complex temp;

        temp.r=r+c.r;
        temp.i=i+c.i;

        return temp;
    }

    Complex operator-(const Complex &c)
    {
        Complex tmp_c;

        tmp_c.i=i-c.i;
        tmp_c.r=r-c.r;

        return tmp_c;
    }

    ostream& operator <<(this,ostream& out_put)  //ÖØÔØÊäÈëÔËËã·û
    {
        out_put<<r<<"+"<<i<<"i";

        return out_put;
    }
    istream& operator >>(istream& in_put)
    {
        in_put>>r>>i;

        return in_put;
    }



};

int main()
{
    Complex c1,c2,c3(3,3);
    c1=c2+c3;
    c1=c2.add(c3);
    c1.display();
    c1=c2-c3;
    c1.display();

    c1=1+c3;
    //c1.display();

    //cout<<c1<<endl<<c2<<endl;
    cout<<c2<<endl;
    //c1<<cout<<endl;
    c2>>cin;
    //c2<<cout<<endl;
}
