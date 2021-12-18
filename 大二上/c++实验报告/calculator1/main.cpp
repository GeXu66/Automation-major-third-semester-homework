#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Node
{
    char date;//�ڵ�����
    Node *pNext;//ָ����һ���ڵ��ָ��
    friend class Stack;//��Ԫ��
};

class Stack
{
public:
    Stack()//������
    {
        pTop = new Node;
        pBottom = pTop;
        pBottom->pNext = NULL;

    }
   ~Stack()//������
    {
        delete pTop;
    }

    void push(char val)//ѹջ
    {
        Node *pNew = new Node;
        pNew->date=val;
        pNew->pNext=pTop;
        pTop = pNew;
    }

    void traverse()//����
    {
        Node *p=pTop;
        while(p!=pBottom)
        {
           cout<<p->date<<endl;
           p=p->pNext;
        }
    }

    bool isempty()//�п�
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

    char top()//������ջ
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

    void clearall()//���ջ����
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
    Node *pTop;//ջ��
    Node *pBottom;//ջ��


};


int main()
{
    Stack A;
    string expression="null";
    char s;
    char s1;
    double num=0;
    int con=0;
    int flag=0;//����flag��־���������С����ǰ����С�����
    cout << "please enter:" << endl;
    cin>>expression; //������ʽ
    for(unsigned int i=0;i<sizeof(expression);i++)//����ÿһ���ַ�
    {
        s=expression[i];//���浱ǰ�ַ�
        switch((int)s)//����asc||��
        {
        case 40:
            //(
            cout<<"����������С����"<<endl;
            A.push(s);
            num=0;//��ȡ����������֮ǰ��ȡ������������
            con=0;//��ȡ����������С�������ı�������
            break;
        case 41:
            //)
            cout<<"����������С����"<<endl;
            if(A.isempty())
            {
                cout<<"ƥ�����"<<endl;
                return 0;
            }
            else
            {
                s1=A.top();
                if(s1!='(')
                {
                    cout<<"ƥ�����"<<endl;
                    return 0;
                }
                num=0;
                con=0;
            }
            flag=0;
            break;
        case 91:
            //[
            cout<<"����������������"<<endl;
            A.push(s);
            num=0;
            con=0;
            flag=0;
            break;
        case 93:
            //]
            cout<<"����������������"<<endl;
            if(A.isempty())
            {
                cout<<"ƥ�����"<<endl;
                return 0;
            }
            else
            {
                s1=A.top();
                if(s1!='[')
                {
                    cout<<"ƥ�����"<<endl;
                    return 0;
                }
                num=0;
                con=0;
            }
            flag=0;
            break;
        case 123:
            //{
            cout<<"���������������"<<endl;
            A.push(s);
            num=0;
            con=0;
            flag=0;
            break;
        case 125:
            //}
            cout<<"���������Ҵ�����"<<endl;
            if(A.isempty())
            {
                cout<<"ƥ�����"<<endl;
                return 0;
            }
            else
            {
                s1=A.top();
                if(s1!='{')
                {
                    cout<<"ƥ�����"<<endl;
                    return 0;
                }
                num=0;
                con=0;
            }
            flag=0;
            break;
        case 42:
            //*
            cout<<"���������˺�"<<endl;
            num=0;
            con=0;
            flag=0;
            break;
        case 43:
            //+
            cout<<"���������Ӻ�"<<endl;
            num=0;
            con=0;
            flag=0;
            break;
        case 45:
            //-
            cout<<"������������"<<endl;
            num=0;
            con=0;
            flag=0;
            break;
        case 47:
            // /
            cout<<"������������"<<endl;
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
                con++;//��һ�ζ����10
            }
            //�����һ���ǲ�����ֱ�������ֵ
            if(((int)expression[i+1]<46)||((int)expression[i+1]>57))
            {
                cout<<"��������"<<num<<endl;
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
                cout<<"��������"<<num<<endl;
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
                cout<<"��������"<<num<<endl;
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
                cout<<"��������"<<num<<endl;
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
                cout<<"��������"<<num<<endl;
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
                cout<<"��������"<<num<<endl;
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
                cout<<"��������"<<num<<endl;
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
                cout<<"��������"<<num<<endl;
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
                cout<<"��������"<<num<<endl;
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
                cout<<"��������"<<num<<endl;
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
        cout<<"�ǿգ�����"<<endl;
    }
    return 0;
}
