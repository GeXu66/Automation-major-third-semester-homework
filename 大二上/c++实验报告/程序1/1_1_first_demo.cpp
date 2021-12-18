#include <iostream>
#include <string>

using namespace std;

//Swap values of two value
#define my_swap(a, b) {a=a+b;b=a-b;a=a-b;}

/*inline my_swap1(int a, int b)
{
    a=a+b;
    b=a-b;
    a=a-b;
}*/

/*template <typename T>
void my_swap2(T &a, T &b)
{
    a=a+b;
    b=a-b;
    a=a-b;
}*/

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

    //my_swap(a1,c1);
    //cout<<a1<<" "<<c1<<endl<<endl;


    return 0;
}
