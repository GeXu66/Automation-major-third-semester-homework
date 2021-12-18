#include <iostream>
using namespace std;

template <class T>
class vector_ss
{
public:
    vector_ss()
    {
        vsize=10;
        buf=new T[10];
    }

    vector_ss(int n)
    {
        vsize=n;
        buf=new T[n];
    }

    ~vector_ss()
    {
        if (buf)
        {
            delete []buf;
        }
    }

    void set_val(int n, T a)
    {
        buf[n]=a;
    }

    void display()
    {
        for (int i=0;i<vsize;i++)
            cout<<buf[i]<<" ";
        cout<<endl;
    }

private:
    T *buf;
    int vsize;
};

int main()
{
    vector_ss<int> v1;
    vector_ss<char> v2;

    for (int i=0;i<10;i++)
    {
        v1.set_val(i,i+1);
        v2.set_val(i,'a'+i);
    }

    v1.display();
    v2.display();

    return 0;
}
