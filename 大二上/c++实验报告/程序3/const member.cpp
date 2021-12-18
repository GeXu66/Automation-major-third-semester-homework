#include <iostream>
using namespace std;

class vector_ss
{
public:
    vector_ss()//:asize(10)
    {
        vsize=10;
        buf=new int[10];
        //asize=10;
    }

    vector_ss(int n)//:asize(10)
    {
        vsize=n;
        buf=new int[n];
    }

    vector_ss(const vector_ss &v)//:asize(v.asize)
    {
        vsize=v.vsize;
        buf=new int[vsize];
        for(int i=0;i<vsize;i++)
            buf[i]=v.buf[i];
            //buf[i]=v.val(i);

        //v.display();
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
        //display();
    }

    void display() const
    {
        for (int i=0;i<vsize;i++)
            cout<<buf[i]<<" ";
        cout<<endl;

        //set_val(1,20);
    }

    int val(int i)
    {
        return buf[i];
    }

private:
    int *buf;
    int vsize;
    //const int asize;
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

    //v1.val(1);
    //v1.display();


    return 0;
}
