#include <iostream>
#include <string>
#include <math.h>

using namespace std;

template<typename T>
struct stackNode
{
    T data;//存储的具体元素
    stackNode* next;//指向下一个节点的指针
};

template<typename T>
class MyStack
{
private:
    unsigned int count;//计数目前stack中存储的元素个数
    unsigned int maxSize;//stack中最大存储的元素个数
    stackNode<T>* top;//stack头节点的指针
public:
    MyStack();//默认构造函数，创建最多容纳10个元素的stack
    MyStack(unsigned int ms);//自定义容纳个数
    ~MyStack();//析构函数
    void Push(T data);//压栈
    T Pop(void);//出栈
    T Top(void);//获取栈顶元素
    bool isEmpty(void);//检查是否为空
    bool notEmpty(void);
    bool isfull(void);//经检查是否已满
};


template<typename T>
MyStack<T>::MyStack()
{
    count = 0;
    maxSize = 30;
    top = NULL;
}

template<typename T>
MyStack<T>::MyStack(unsigned int ms)
{
    count = 0;
    maxSize = ms;
    top = NULL;
}

template<typename T>
MyStack<T>::~MyStack()
{
    stackNode<T>* p = new stackNode<T>;
    for (unsigned int i = count; i >0; i--)
    {
        p = top;
        top = p->next;
        delete p;
    }
}

template<typename T>
void MyStack<T>::Push(T data)
{
    count++;
    if (isfull())
    {
        cout << "Error: This Stack is full" << endl;
        cout << "File Path =" << __FILE__ << endl;
        cout << "Function Name =" << __FUNCTION__ << endl;
        cout << "Line =" << __LINE__ << endl;
    }
    stackNode<T>* node = new stackNode<T>;
    node->data = data;
    node->next = top;
    top = node;
}

template<typename T>
T MyStack<T>::Pop(void)
{
    T nowdata;
    if (isEmpty())
    {
        cout << "Error: Stack is empty" << endl;
        cout << "File Path =" << __FILE__ << endl;
        cout << "Function Name =" << __FUNCTION__ << endl;
        cout << "Line =" << __LINE__ << endl;
        return 1;
    }
    stackNode<T>* p = top;
    nowdata=top->data;
    top = top->next;
    delete p;
    count--;
    return nowdata;
}

template<typename T>
T MyStack<T>::Top(void)
{
    return top->data;
}

template<typename T>
bool MyStack<T>::isEmpty(void)
{
    return count == 0 ? true : false;
}

template<typename T>
bool MyStack<T>::notEmpty(void)
{
    return count == 0 ? false : true;
}

template<typename T>
bool MyStack<T>::isfull(void)
{
    return count > maxSize ? true : false;
}

int compare(char top,char now)
{
    int toplevel=0;
    int nowlevel=0;
    if(top=='+'||top=='-')
    {
        toplevel=1;
    }
    else if(top=='*'||top=='/')
    {
        toplevel=2;
    }
    if(now=='+'||now=='-')
    {
        nowlevel=1;
    }
    else if(now=='*'||now=='/')
    {
        nowlevel=2;
    }
    if(nowlevel>toplevel)
    {
        return 2;
    }
    else if(nowlevel==toplevel)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool notdod(char c)
{
    if((int)c>=48&&(int)c<=57)
    {
        return false;
    }
    else if(c=='.')
    {
        return false;
    }
    else
    {
        return true;
    }
}

double calculate(double num1,char op,double num2)
{
    if(op=='+')
        return num1+num2;
    else if(op=='-')
        return num1-num2;
    else if(op=='*')
        return num1*num2;
    else
        return num1/num2;
}

int main()
{
    MyStack<char> C;//字符模板栈
    MyStack<double> D;//数值模板栈
    int flag=0;//标志变量
    int con=0;//除以10的倍数
    int asc=0;//当前字符的asc码
    double num=0;//储存当前数字
    string expression="null";
    char s;
    cout<<"please enter :"<<endl;
    cin>>expression;
    for(unsigned int i=0;i<sizeof(expression);i++)
    {
        s=expression[i];
        asc=(int)s;
        if(asc>=48&&asc<=57)//对数字进行处理
        {
            if(flag==0)
            {
                num=num*10+asc-48;
            }
            else
            {
                num=num+(float)(asc-48)/pow(10,con);
                con++;
            }
            if(notdod(expression[i+1]))
            {
                D.Push(num);
                num=0;
                con=0;
                flag=0;
            }
        }
        else if(asc==46)//遇到小数点进入除法模式
        {
            flag=1;
            con++;
        }
        else if(s=='(')
        {
            C.Push(s);
        }
        else if(s==')')
        {
            if(C.Top()=='(')//遇到左括号弹出
                C.Pop();
            else
            {
                do{
                    D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));//将数字弹出
                    if(C.isEmpty())//若空则弹出
                    {
                        cout<<"匹配错误"<<endl;
                        break;
                    }
                }while(C.Top()!='(');
                if(C.Top()=='(')//弹出括号
                    C.Pop();
            }
        }
        else if(s=='+')
        {
            if(C.isEmpty())
                C.Push(s);
            else if(C.Top()=='(')
                C.Push(s);
            else
            {
                do{
                    D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));
                    if(C.isEmpty())
                    {
                        break;
                    }
                }while(C.Top()!='(');
                C.Push(s);
            }

        }
        else if(s=='-')
        {
            if(C.isEmpty())
                C.Push(s);
            else if(C.Top()=='(')
                C.Push(s);
            else
            {
                do{
                    D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));
                    if(C.isEmpty())
                    {
                        break;
                    }
                }while(C.Top()!='(');
                C.Push(s);
            }
        }
        else if(s=='*')
        {
            if(C.isEmpty())
                C.Push(s);
            else if(C.Top()=='(')
                C.Push(s);
            else if(compare(C.Top(),s)==1)
            {
                D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));
                C.Push(s);
            }
            else if(compare(C.Top(),s)==2)
                C.Push(s);
        }
        else if(s=='/')
        {
            if(C.isEmpty())
                C.Push(s);
            else if(C.Top()=='(')
                C.Push(s);
            else if(compare(C.Top(),s)==1)
            {
                D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));
                C.Push(s);
            }
            else if(compare(C.Top(),s)==2)
                C.Push(s);
        }
    }

    if(C.notEmpty())
    {
        while(C.Top()!='(')
        {
            D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));
            if(C.isEmpty())
            {
                break;
            }
        }
        if(C.notEmpty())
        {
            cout<<"匹配错误"<<endl;
            return 0;
        }

    }
    num=D.Pop();
    cout<<"answer:"<<num<<endl;
    return 0;
}
