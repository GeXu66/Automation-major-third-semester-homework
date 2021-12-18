#include <iostream>
#include <string>

using namespace std;

//Swap values of two int
void my_swap(int &a, int &b)
{
    int c;
    c=a;
    a=b;
    b=c;
}

//Swap values of two double
void my_swap(double &a, double &b)
{
    double c;
    c=a;
    a=b;
    b=c;
}

//Swap values of two char
void my_swap(char &a, char &b)
{
    char c;
    c=a;
    a=b;
    b=c;
}

//Swap values of two string
void my_swap(string &a, string &b)
{
    string c;
    c=a;
    a=b;
    b=c;
}

int main()
{
    int a1,a2;
    cin>>a1>>a2;
    my_swap(a1,a2);
    cout<<a1<<" "<<a2<<endl<<endl;

    double d1,d2;
    cin>>d1>>d2;
    my_swap(d1,d2);
    cout<<d1<<" "<<d2<<endl<<endl;

    char c1,c2;
    cin>>c1>>c2;
    my_swap(c1,c2);
    cout<<c1<<" "<<c2<<endl<<endl;

    string s1,s2;
    cin>>s1>>s2;
    my_swap(s1,s2);
    cout<<s1<<" "<<s2<<endl<<endl;

    //cin>>a1>>d1>>c1>>s1;
    //cout<<a1<<" "<<d1<<" "<<c1<<" "<<s1<<endl;

    return 0;
}
