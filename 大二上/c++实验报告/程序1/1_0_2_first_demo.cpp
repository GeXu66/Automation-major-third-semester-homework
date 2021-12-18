#include <iostream>
//#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

const double pi=3.14;

/*double volumn()
{
    return pi*1*1;
}

double volumn(double r)
{
    return pi*r*r*1;
}

double volumn(double r, double h)
{
    return pi*r*r*h;
}*/

class student
{

public:
    student(int n ,char s,char *nam):num(n),sex(s)
    {
        cout<<&nam<<endl;
        strcpy(name,nam);
    }
    void display()
    {
        cout<<name<<endl;
    }
private:
    int num;
    char sex;
    char *name;
};

double volumn(double r=1, double h=1)
{
    return pi*r*r*h;
}

int main()
{
    cout<< volumn()<<endl;

    cout<< volumn(2)<<endl;

    cout<< volumn(2,2)<<endl;

    cout<<"/*a+b*/+c"<<endl;

    int a=3;
    int *p;
    *p=a;

    //char *name="lll";
    //cout<<name<<endl;
    //cout<<*name<<endl;
    cout<<p<<endl;
    cout<<*p<<endl;

    student lzh(20,'m',"lzh");
    lzh.display();
    return 0;
}

//double volumn(double r, double h)
//{
//    return pi*r*r*h;
//}



















