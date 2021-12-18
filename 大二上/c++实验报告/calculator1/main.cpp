#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Node
{
    char date;//节点数据
    Node *pNext;//指向下一个节点的指针
    friend class Stack;//友元类
};

class Stack
{
public:
    Stack()//构造器
    {
        pTop = new Node;
        pBottom = pTop;
        pBottom->pNext = NULL;

    }
   ~Stack()//析构器
    {
        delete pTop;
    }

    void push(char val)//压栈
    {
        Node *pNew = new Node;
        pNew->date=val;
        pNew->pNext=pTop;
        pTop = pNew;
    }

    void traverse()//遍历
    {
        Node *p=pTop;
        while(p!=pBottom)
        {
           cout<<p->date<<endl;
           p=p->pNext;
        }
    }

    bool isempty()//判空
    {
        if(pTop==pBottom)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    char top()//顶部出栈
    {
        char s;
        if(isempty())
        {
            return false;
        }
        else
        {
            Node *p=pTop;
            s = p->date;
            pTop = p->pNext;
            delete p;
            p=NULL;

            return s;
        }
    }

    void clearall()//清空栈数据
    {
        Node *p=pTop;
        Node *q=NULL;

        while(p!=pBottom)
        {
            q=p->pNext;
            delete p;
            p = q;
        }
        pTop=pBottom;
    }

private:
    Node *pTop;//栈顶
    Node *pBottom;//栈底


};


int main()
{
    Stack A;
    string expression="null";
    char s;
    char s1;
    double num=0;
    int con=0;
    int flag=0;//定义flag标志变量检查是小数点前还是小数点后
    cout << "please enter:" << endl;
    cin>>expression; //输入表达式
    for(unsigned int i=0;i<sizeof(expression);i++)//遍历每一个字符
    {
        s=expression[i];//保存当前字符
        switch((int)s)//检索asc||码
        {
        case 40:
            //(
            cout<<"操作符：左小括号"<<endl;
            A.push(s);
            num=0;//读取到操作符将之前读取到的数据清零
            con=0;//读取到操作符将小数点后除的倍数清零
            break;
        case 41:
            //)
            cout<<"操作符：右小括号"<<endl;
            if(A.isempty())
            {
                cout<<"匹配错误"<<endl;
                return 0;
            }
            else
            {
                s1=A.top();
                if(s1!='(')
                {
                    cout<<"匹配错误"<<endl;
                    return 0;
                }
                num=0;
                con=0;
            }
            flag=0;
            break;
        case 91:
            //[
            cout<<"操作符：左中括号"<<endl;
            A.push(s);
            num=0;
            con=0;
            flag=0;
            break;
        case 93:
            //]
            cout<<"操作符：右中括号"<<endl;
            if(A.isempty())
            {
                cout<<"匹配错误"<<endl;
                return 0;
            }
            else
            {
                s1=A.top();
                if(s1!='[')
                {
                    cout<<"匹配错误"<<endl;
                    return 0;
                }
                num=0;
                con=0;
            }
            flag=0;
            break;
        case 123:
            //{
            cout<<"操作符：左大括号"<<endl;
            A.push(s);
            num=0;
            con=0;
            flag=0;
            break;
        case 125:
            //}
            cout<<"操作符：右大括号"<<endl;
            if(A.isempty())
            {
                cout<<"匹配错误"<<endl;
                return 0;
            }
            else
            {
                s1=A.top();
                if(s1!='{')
                {
                    cout<<"匹配错误"<<endl;
                    return 0;
                }
                num=0;
                con=0;
            }
            flag=0;
            break;
        case 42:
            //*
            cout<<"操作符：乘号"<<endl;
            num=0;
            con=0;
            flag=0;
            break;
        case 43:
            //+
            cout<<"操作符：加号"<<endl;
            num=0;
            con=0;
            flag=0;
            break;
        case 45:
            //-
            cout<<"操作符：减号"<<endl;
            num=0;
            con=0;
            flag=0;
            break;
        case 47:
            // /
            cout<<"操作符：除号"<<endl;
            num=0;
            con=0;
            flag=0;
            break;
        case 48:
            //0
            if(flag==0)
            {
             num=num*10+0;
            }
            else
            {
                num=num+(float)0/pow(10,con);
                con++;//下一次多除以10
            }
            //如果下一个是操作符直接输出数值
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 49:
            //1
            if(flag==0)
            {
             num=num*10+1;
            }
            else
            {
                num=num+(float)1/pow(10,con);
                con++;
            }
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 50:
            //2
            if(flag==0)
            {
             num=num*10+2;
            }
            else
            {
                num=num+(float)2/pow(10,con);
                con++;
            }
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 51:
            //3
            if(flag==0)
            {
             num=num*10+3;
            }
            else
            {
                num=num+(float)3/pow(10,con);
                con++;
            }
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 52:
            //4
            if(flag==0)
            {
             num=num*10+4;
            }
            else
            {
                num=num+(float)4/pow(10,con);
                con++;
            }
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 53:
            //5
            if(flag==0)
            {
             num=num*10+5;
            }
            else
            {
                num=num+(float)5/pow(10,con);
                con++;
            }
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 54:
            //6
            if(flag==0)
            {
             num=num*10+6;
            }
            else
            {
                num=num+(float)6/pow(10,con);
                con++;
            }
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 55:
            //7
            if(flag==0)
            {
             num=num*10+7;
            }
            else
            {
                num=num+(float)7/pow(10,con);
                con++;
            }
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 56:
            //8
            if(flag==0)
            {
             num=num*10+8;
            }
            else
            {
                num=num+(float)8/pow(10,con);
                con++;
            }
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 57:
            //9
            if(flag==0)
            {
             num=num*10+9;
            }
            else
            {
                num=num+(float)9/pow(10,con);
                con++;
            }
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"操作数："<<num<<endl;
            }
            break;
        case 46:
            //.
            flag=1;
            con++;
            break;
        }
    }

    if(A.isempty()==0)
    {
        cout<<"非空，错误"<<endl;
    }
    return 0;
}
