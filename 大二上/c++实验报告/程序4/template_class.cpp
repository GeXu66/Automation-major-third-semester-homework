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

    vector_ss(vector_ss const &v)
    {
        cout<<"Copy Constructor"<<endl;
        vsize=v.vsize;
        buf=new T[vsize];
        for (int i=0;i<vsize;i++)
            buf[i]=v[i];
    }

    ~vector_ss()
    {
        if (buf)
        {
            delete []buf;
        }
    }


    vector_ss const & operator = (vector_ss const &v);

public:
    T & operator [] (int i) const
    {
        return buf[i];
    };

    void display() const
    {
        for (int i=0;i<vsize;i++)
            cout<<buf[i]<<" ";
        cout<<endl;
    }

private:
    T *buf;
    int vsize;
};

template <class T>
vector_ss<T> const & vector_ss<T>::operator = (vector_ss<T> const &v)
{
    cout<<"Operator ="<<endl;
    vsize=v.vsize;
    buf=new T[vsize];
    for (int i=0;i<vsize;i++)
        buf[i]=v[i];

    return *this;
}

int main()
{
    vector_ss<int> v1;
    vector_ss<char> v2;

    for (int i=0;i<10;i++)
    {
        v1[i]=i+1;
        v2[i]='a'+i;
    }
    v1.display();
    v2.display();

    vector_ss<int> v3=v1,v4;
    v4=v3=v1;
    v4.display();

    return 0;
}
