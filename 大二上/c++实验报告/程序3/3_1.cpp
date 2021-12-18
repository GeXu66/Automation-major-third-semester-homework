#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    void set_stu(int stu_num, string stu_name)
    {
        num=stu_num;
        name=stu_name;
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
    Student st;

    st.set_stu(1,"Xiaohua");
    st.display_stu();

    return 0;
}
