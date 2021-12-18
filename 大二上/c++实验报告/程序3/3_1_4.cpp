#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    //Constructor
    Student()
    {
        cout<<"Student()"<<endl;
    };

    Student(int stu_num, string stu_name)//:num(stu_num),name(stu_name)
    {
        num=stu_num;
        name=stu_name;
        cout<<"Student(int, string)"<<endl;
    }

    ~Student()
    {
        cout<<"~Student"<<endl;
    }

    void display_stu()
    {
        cout<<"Studeng  Num is : "<<num<<endl;
        cout<<"Student Name is : "<<name<<endl;
    }
private:
    int num;
    string name;
};


int main()
{
    Student st(1,"Xiaohua");
    st.display_stu();

    Student st2;
    st2.display_stu();

    return 0;
}
