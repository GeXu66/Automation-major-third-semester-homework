#include <iostream>
#include <string>
#include <math.h>

using namespace std;

template<typename T>
struct stackNode
{
    T data;//�洢�ľ���Ԫ��
    stackNode* next;//ָ����һ���ڵ��ָ��
};

template<typename T>
class MyStack
{
private:
    unsigned int count;//����Ŀǰstack�д洢��Ԫ�ظ���
    unsigned int maxSize;//stack�����洢��Ԫ�ظ���
    stackNode<T>* top;//stackͷ�ڵ��ָ��
public:
    MyStack();//Ĭ�Ϲ��캯���������������10��Ԫ�ص�stack
    MyStack(unsigned int ms);//�Զ������ɸ���
    ~MyStack();//��������
    void Push(T data);//ѹջ
    T Pop(void);//��ջ
    T Top(void);//��ȡջ��Ԫ��
    bool isEmpty(void);//����Ƿ�Ϊ��
    bool notEmpty(void);
    bool isfull(void);//������Ƿ�����
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
    MyStack<char> C;//�ַ�ģ��ջ
    MyStack<double> D;//��ֵģ��ջ
    int flag=0;//��־����
    int con=0;//����10�ı���
    int asc=0;//��ǰ�ַ���asc��
    double num=0;//���浱ǰ����
    string expression="null";
    char s;
    cout<<"please enter :"<<endl;
    cin>>expression;
    for(unsigned int i=0;i<sizeof(expression);i++)
    {
        s=expression[i];
        asc=(int)s;
        if(asc>=48&&asc<=57)//�����ֽ��д���
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
        else if(asc==46)//����С����������ģʽ
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
            if(C.Top()=='(')//���������ŵ���
                C.Pop();
            else
            {
                do{
                    D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));//�����ֵ���
                    if(C.isEmpty())//�����򵯳�
                    {
                        cout<<"ƥ�����"<<endl;
                        break;
                    }
                }while(C.Top()!='(');
                if(C.Top()=='(')//��������
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
            cout<<"ƥ�����"<<endl;
            return 0;
        }

    }
    num=D.Pop();
    cout<<"answer:"<<num<<endl;
    return 0;
}
