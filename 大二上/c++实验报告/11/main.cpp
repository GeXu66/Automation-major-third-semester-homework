#include<windows.h>
#include<iostream>
#include<stdio.h>
#include<string>
#include<sstream>
#include <math.h>

using namespace std;

const char g_szClassName[] = "myWindowClass";
int x,y,key;
int draw;
string expre="";
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
int compare(char top,char now);
double calculate(double num1,char op,double num2);
bool notdod(char c);
// Step 4: the Window Procedure
void drawxy(int x,int y,HWND hwnd)
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<5; j++)
        {
            if((x>=15+j*150&&x<=155+j*150)&&(y>=200+i*90&&y<=280+i*90))
            {
                string _c[4][5]= {{"7","8","9","+","C"},{"4","5","6","-","B"},{"1","2","3","*","("},{".","0","=","/",")"}};
                HDC hdc=GetDC(hwnd);
                SetBkMode(hdc, TRANSPARENT);
                RECT _rect;
                SetRect(&_rect, 15+j*150, 200+i*90,155+j*150,280+i*90);
                HBRUSH _hbrush;
                _hbrush = CreateSolidBrush(RGB(150,150,150));
                FillRect(hdc, &_rect, _hbrush);
                TextOut(hdc,70+j*150,225+i*90,TEXT(_c[i][j].c_str()),1);
                TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
                ReleaseDC(hwnd,hdc);
            }
        }
    }
}
int calc(string &expre)
{
    MyStack<char> C;//字符模板栈
    MyStack<double> D;//数值模板栈
    stringstream numtemp;
    int flag=0;//标志变量
    int con=0;//除以10的倍数
    int asc=0;//当前字符的asc码
    double num=0;//储存当前数字
    //string expression="null";
    char s;
    //cout<<"please enter :"<<endl;
    //cin>>expression;
    for(unsigned int i=0; i<sizeof(expre); i++)
    {
        s=expre[i];
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
            if(notdod(expre[i+1]))
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
                do
                {
                    D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));//将数字弹出
                    if(C.isEmpty())//若空则弹出
                    {
                        cout<<"匹配错误"<<endl;
                        break;
                    }
                }
                while(C.Top()!='(');
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
                do
                {
                    D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));
                    if(C.isEmpty())
                    {
                        break;
                    }
                }
                while(C.Top()!='(');
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
                do
                {
                    D.Push(calculate(D.Pop(),C.Pop(),D.Pop()));
                    if(C.isEmpty())
                    {
                        break;
                    }
                }
                while(C.Top()!='(');
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
    //cout<<"answer:"<<num<<endl;
    numtemp<<num;
    numtemp>>expre;
    return 0;
}

void judgestr(string str,string &expre,HDC hdc)
{
    for(int i=0; i<10; i++)
    {
        stringstream Temp;
        Temp<<i;
        string j=Temp.str();
        if(str==j)
        {
            expre+=j;
            TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
        }
    }
    if(str=="+")
    {
        expre+="+";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(str=="-")
    {
        expre+="-";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(str=="*")
    {
        expre+="*";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(str=="/")
    {
        expre+="/";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(str==".")
    {
        expre+=".";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(str=="(")
    {
        expre+="(";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(str==")")
    {
        expre+=")";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(str=="C")
    {
        expre="";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(str=="B")
    {
        expre.erase(expre.end() - 1);
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(str=="=")
    {
        calc(expre);
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
}

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


void click(int x,int y,HWND hwnd)
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<5; j++)
        {
            if((x>=15+j*150&&x<=155+j*150)&&(y>=200+i*90&&y<=280+i*90))
            {
                string _c[4][5]= {{"7","8","9","+","C"},{"4","5","6","-","B"},{"1","2","3","*","("},{".","0","=","/",")"}};
                HDC hdc=GetDC(hwnd);
                SetBkMode(hdc, TRANSPARENT);
                RECT _rect;
                SetRect(&_rect, 15+j*150, 200+i*90,155+j*150,280+i*90);
                HBRUSH _hbrush;
                _hbrush = CreateSolidBrush(RGB(150,150,150));
                FillRect(hdc, &_rect, _hbrush);
                TextOut(hdc,70+j*150,225+i*90,TEXT(_c[i][j].c_str()),1);
                judgestr(_c[i][j],expre,hdc);
                ReleaseDC(hwnd,hdc);
            }
        }
    }
}

void keydown(int key,HWND hwnd)
{
    HDC hdc=GetDC(hwnd);
    stringstream alltemp;
    string temp;
    cout<<"key down????????"<<endl;
    cout<<"key:::"<<key<<endl;
    for(int i=48;i<=57;i++)
    {
        if(key==i)
        {
            alltemp<<(key-48);
            alltemp>>temp;
            expre+=temp;
            TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
        }
    }
    if(key==40)//(
    {
        expre+="(";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(key==41)//)
    {
        expre+=")";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(key==107)//小键盘上的加
    {
        expre+="+";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(key==109)//小键盘上的减
    {
        expre+="-";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(key==106)//小键盘上的乘
    {
        expre+="*";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(key==111)//小键盘上的除
    {
        expre+="/";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(key==67||key==99)// C
    {
        expre+="";
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(key==66||key==98)// B
    {
        expre.erase(expre.end() - 1);
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    if(key==187)
    {
        calc(expre);
        TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    }
    TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
    ReleaseDC(hwnd,hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CLOSE:
        cout<<" WM_CLOSE"<<endl;
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        cout<<" WM_DESTROY"<<endl;
        PostQuitMessage(0);
        break;

    case WM_CREATE:
        cout<<" WM_CREATE"<<endl;
        SetTimer(hwnd,1,100,NULL);
        draw=1;
        break;

    case WM_MOVE:
        cout<<" WM_MOVING"<<endl;
        break;

    case WM_SIZE:
        cout<<" WM_SIZE"<<endl;
        break;

    case WM_LBUTTONDOWN:
        x=LOWORD(lParam);
        y=HIWORD(lParam);
        drawxy(x,y,hwnd);
        click(x,y,hwnd);
        cout<<" WM_LBUTTONDOWN at "<<x<<" "<<y<<endl;
        break;

    case WM_LBUTTONUP:
        x=LOWORD(lParam);
        y=HIWORD(lParam);
        drawxy(x,y,hwnd);
        cout<<" WM_LBUTTONUP at "<<x<<" "<<y<<endl;
        break;

    case WM_MOUSEMOVE:
        x=LOWORD(lParam);
        y=HIWORD(lParam);
        drawxy(x,y,hwnd);
        cout<<" WM_MOUSEMOVE at "<<x<<" "<<y<<endl;
        break;

    case WM_RBUTTONDOWN:
        x=LOWORD(lParam);
        y=HIWORD(lParam);
        cout<<" WM_RBUTTONDOWN at "<<x<<" "<<y<<endl;
        break;

    case WM_KEYDOWN:
        key=wParam;
        keydown(key,hwnd);
        cout<<" WM_KEYDOWN : "<<key<<endl;
        //cout<<key<<endl;
        break;

    case WM_KEYUP:
        key=wParam;
        cout<<" WM_KEYUP : "<<key<<endl;
        break;

    case WM_TIMER:
        cout<<" WM_TIMER"<<endl;
        if(draw)
        {
            string c[4][5]= {{"7","8","9","+","C"},{"4","5","6","-","B"},{"1","2","3","*","("},{".","0","=","/",")"}};
            //int len=sprintf(c,"%d",ind);
            HDC hdc=GetDC(hwnd);
            SetBkMode(hdc, TRANSPARENT);
            HBRUSH hBrush;
            RECT rect;
            SetRect(&rect, 0, 0,800,600);
            hBrush = CreateSolidBrush(RGB(245,245,220));
            FillRect(hdc, &rect, hBrush);
            hBrush = NULL;

            for(int i=0; i<4; i++)
            {
                for(int j=0; j<5; j++)
                {
                    Rectangle(hdc, 15+j*150,200+i*90,155+j*150,280+i*90);
                    TextOut(hdc,70+j*150,225+i*90,TEXT(c[i][j].c_str()),1);
                    TextOut(hdc,20,130,TEXT(expre.c_str()),expre.length());
                }
            }
            Rectangle(hdc, 15,110,755,190);
            ReleaseDC(hwnd,hdc);
        }
        drawxy(x,y,hwnd);
        TextOut(GetDC(hwnd),20,130,TEXT(expre.c_str()),expre.length());
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
               WS_EX_CLIENTEDGE,
               g_szClassName,
               "The title of my window",
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT, 800,600,
               NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
