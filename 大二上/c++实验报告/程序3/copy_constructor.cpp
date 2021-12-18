#include <iostream>
using namespace std;

class vector_ss
{
public:
    vector_ss()
    {
        vsize=10;
        buf=new int[10];
    }

    vector_ss(int n)
    {
        vsize=n;
        buf=new int[n];
    }

    vector_ss(const vector_ss &v)
    {
        vsize=v.vsize;
        buf=new int[vsize];
        for(int i=0;i<vsize;i++)
            buf[i]=v.buf[i];
    }

    ~vector_ss()
    {
        if (buf)
        {
            delete []buf;
        }
    }

    void set_val(int n, int a)
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
    int *buf;
    int vsize;
};

int main()
{
    vector_ss v1;

    for (int i=0;i<10;i++)
    {
        v1.set_val(i,i+1);
    }

    vector_ss v2(v1);

    v1.display();
    v2.display();

    return 0;
}
