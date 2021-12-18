#include <iostream>
using namespace std;

class vector_ss
{
public:
    vector_ss()//:asize(10)
    {
        vsize=10;
        buf=new int[10];
        cnt++;
    }

    ~vector_ss()
    {
        if (buf)
        {
            delete []buf;
        }
        cnt--;
    }

    int cnt_val()
    {
        return cnt;
    }

private:
    int *buf;
    int vsize;
    static int cnt;
};

int vector_ss::cnt=0;

int main()
{
    vector_ss v1;
    cout<<v1.cnt_val()<<endl;
    {
        vector_ss v2;
        cout<<v2.cnt_val()<<endl;
    }
    cout<<v1.cnt_val()<<endl;
    vector_ss *v3=new vector_ss;
    cout<<v1.cnt_val()<<endl;
    delete v3;
    cout<<v1.cnt_val()<<endl;

    return 0;
}
