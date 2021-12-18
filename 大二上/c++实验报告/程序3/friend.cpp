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

    //friend void display(vector_ss const &v);

private:
    int *buf;
    int vsize;
};

void display(vector_ss const &v)
{
    for (int i=0;i<v.vsize;i++)
        cout<<v.buf[i]<<" ";
    cout<<endl;
}

int main()
{
    vector_ss v1,v2;

    for (int i=0;i<10;i++)
    {
        v1.set_val(i,i+1);
        v2.set_val(i,-i-1);
    }

    display(v1);
    display(v2);


    return 0;
}
