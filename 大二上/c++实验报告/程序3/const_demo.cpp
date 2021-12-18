#include <iostream>

using namespace std;

//在主程序中以各个变量为参数调用下列函数，查看编译器提示
void f1(int x){};
void f2(int const x){};
void f3(int &x){};
void f4(int const &x){};
void f5(int *x){};
void f6(int const *x){};
void f7(int* const x){};


int main()
{
    //编译程序并根据编译器的错误提示，修改程序至无语法错误，体会各种定义的使用方法
    int a1=10;
    int const a2=a1;
    //a1++;
    //a2++;

    // 分别将b1和b2初始化为a1和a2的引用，看编译器的提示
    int &b1=a1;
    int const &b2=a1; //将b2初始化为a1的引用，尝试改变a1的值以及b1的值并输出，查看运行结果

    //b2++;
    a1=5;
    cout<<b2<<endl;
    // 分别将下列指针初始化为a1和a2的地址，看编译器的提示
    int* p1=&a1;
    int const *p2=&a1; //将p2初始化为a1的地址，尝试改变a1的值以及p2的值并输出，查看运行结果
    int* const p3=&a1;  //将p3分别初始化为a1和a2的地址，查看编译器的提示

    //p2=&a2;
    //*p2=1;
    //p3=&a2;
    //*p3=2;
    //尝试将const变量放在等号的左边，看编译器的输出
    //a2=a1;

    return 0;
}
