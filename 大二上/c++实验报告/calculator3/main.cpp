#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Matrix_4x4
{
private:
    double matrix[4][4];
public:
    //默认构造函数
    Matrix_4x4()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrix[i][j] = (i == j) ? 1 : 0;
            }
        }
    }
    //带参构造函数
    Matrix_4x4(const double m[4][4])
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                matrix[i][j]=m[i][j];
            }
        }
    }
    //拷贝构造函数
    Matrix_4x4(Matrix_4x4 const &m)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                matrix[i][j]=m[i][j];
            }
        }
    }
    //重载 = 运算符，参数为矩阵对象
    Matrix_4x4 const & operator = (Matrix_4x4 const &m);
    //重载 = 运算符，参数为一个4x4的二维数组
    Matrix_4x4 const & operator = (const double m[4][4]);
    //重载算术运算符 + - *
    friend Matrix_4x4 operator + (Matrix_4x4 const &m1,Matrix_4x4 const &m2);
    friend Matrix_4x4 operator - (Matrix_4x4 const &m1,Matrix_4x4 const &m2);
    friend Matrix_4x4 operator * (Matrix_4x4 const &m1,Matrix_4x4 const &m2);
    //重载 ^ 运算符为矩阵的i次幂（如果i为负数，如何处理？）
    friend Matrix_4x4 operator ^ (Matrix_4x4 m1,int i);
    //重载 [] 运算符，实现双下标方式访问矩阵元素
    const double * operator[] (const int i) const {return matrix[i];}
    double * operator[] (const int i){return matrix[i];}
    // 重载输入<< 和输出 >>
    friend ostream& operator <<(ostream& out_put, const Matrix_4x4 &m);
    friend istream& operator >>(istream& in_put, Matrix_4x4 &m);
    Matrix_4x4 inverse();   //矩阵求逆，不改变当前矩阵值，返回逆矩阵
    Matrix_4x4 transpose(); //矩阵转置，不改变当前矩阵值，返回转置矩阵
    double determinant();//矩阵求行列式，不改变当前矩阵值，返回行列式的值
};

Matrix_4x4 const & Matrix_4x4::operator = (Matrix_4x4 const &m)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            matrix[i][j]=m[i][j];
        }
    }
    return *this;
}

Matrix_4x4 const & Matrix_4x4::operator = (const double m[4][4])
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            matrix[i][j]=m[i][j];
        }
    }
    return *this;
}

Matrix_4x4 operator + (const Matrix_4x4 &m1,const Matrix_4x4 &m2)
{
    Matrix_4x4 temp;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            temp[i][j]=m1[i][j]+m2[i][j];
        }
    }
    return temp;
}

Matrix_4x4 operator - (const Matrix_4x4 &m1,const Matrix_4x4 &m2)
{
    Matrix_4x4 temp;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            temp[i][j]=m1[i][j]-m2[i][j];
        }
    }
    return temp;
}

Matrix_4x4 operator * (const Matrix_4x4 &m1,const Matrix_4x4 &m2)
{
    Matrix_4x4 temp;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            temp[i][j]=0;
            for(int n=0;n<4;n++)
            {
                temp[i][j]+=m1[i][n]*m2[n][j];
            }
        }
    }
    return temp;
}

Matrix_4x4 operator ^ (Matrix_4x4 m,int n)
{
    Matrix_4x4 temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = (i == j) ? 1 : 0;
        }
    }
    if(n==0)
    {
        return temp;
    }
    else if(n>0)
    {
        for(int i=0;i<n;i++)
        {
            temp=temp*m;
        }
    }
    else
    {
        for(int i=0;i<-n;i++)
        {
            temp=temp*m;
        }
        temp.inverse();
    }
    return temp;
}

ostream& operator <<(ostream& out_put, const Matrix_4x4 &m)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(m[i][j]>1e-6)
            {
                out_put<<m[i][j]<<"     ";
            }
            else
            {
                out_put<<0<<"     ";
            }
        }
        out_put<<endl;
    }
    return out_put;
}

istream& operator >>(istream& in_put, Matrix_4x4 &m)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            in_put>>m[i][j];
        }
    }
    return in_put;
}

Matrix_4x4 Matrix_4x4::inverse()
{
    int i, j, k;
    double max_, temp;
    Matrix_4x4 t(matrix);//临时矩阵
    Matrix_4x4 B;//逆矩阵
    //将A矩阵存放在临时矩阵t[n][n]中
    //初始化B矩阵为单位阵
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            B[i][j] = (i == j) ? 1 : 0;
        }
    }
    for (i = 0; i < 4; i++)
    {
        //寻找主元
        max_ = t[i][i];
        k = i;
        for (j = i+1; j < 4; j++)
        {
            if (fabs(t[j][i]) > fabs(max_))
            {
                max_ = t[j][i];
                k = j;
            }
        }
        //如果主元所在行不是第i行，进行行交换
        if (k != i)
        {
            for (j = 0; j < 4; j++)
            {
                temp = t[i][j];
                t[i][j] = t[k][j];
                t[k][j] = temp;
                //B伴随交换
                temp = B[i][j];
                B[i][j] = B[k][j];
                B[k][j] = temp;
            }
        }
        //判断主元是否为0, 若是, 则矩阵A不是满秩矩阵,不存在逆矩阵
        if (t[i][i] == 0)
        {
            cout << "There is no inverse matrix!";
            return B;
        }
        //消去A的第i列除去i行以外的各行元素
        temp = t[i][i];
        for (j = 0; j < 4; j++)
        {
            t[i][j] = t[i][j] / temp;        //主对角线上的元素变为1
            B[i][j] = B[i][j] / temp;        //伴随计算
        }
        for (j = 0; j < 4; j++)        //第0行->第n行
        {
            if (j != i)                //不是第i行
            {
                temp = t[j][i];
                for (k = 0; k < 4; k++)        //第j行元素 - i行元素*j列i行元素
                {
                    t[j][k] = t[j][k] - t[i][k]*temp;
                    B[j][k] = B[j][k] - B[i][k]*temp;
                }
            }
        }
    }
    return B;
}

Matrix_4x4 Matrix_4x4::transpose()
{
    for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			swap(matrix[i][j], matrix[j][i]);
		}
	}
	return matrix;
}

void swap(double &a, double &b)
{
	double temp = a;
	a = b;
	b = temp;
	return;
}

double Matrix_4x4::determinant()
{
    int num1,num2,index; // 初始化
    double det=1;
    double total=1;
    int temp[5];
    //循环遍历对角元
    for(int i = 0; i < 4; i++)
    {
        index = i; // 初始化索引
        //找寻非0值索引
        while(matrix[index][i] == 0 && index < 4)
        {
            index++;
        }
        if(index == 4) // 如果这里没有非0元
        {
            // 行列式为0
            continue;
        }
        if(index != i)
        {
            //交换行
            for(int j = 0; j < 4; j++)
            {
                swap(matrix[index][j],matrix[i][j]);
            }
                //行列式的正负会变如果交换两行
            det = det*pow(-1,index-i);
       }
       for(int j = 0; j < 4; j++)
       {
           temp[j] = matrix[i][j];
       }
       //遍历每一行
       for(int j = i+1; j < 4; j++)
       {
           num1 = temp[i]; //对角元的值
           num2 = matrix[j][i]; //下一行的值
           for(int k = 0; k < 4; k++)
           {
               matrix[j][k] = (num1 * matrix[j][k]) - (num2 * temp[k]);
           }
           total = total * num1; // Det(kA)=kDet(A);
        }
    }
    //乘起来对角元
    for(int i = 0; i < 4; i++)
    {
        det = det * matrix[i][i];
    }
    return (det/total); //Det(kA)/k=Det(A);
}

int main()
{
    double m[4][4]={{1,2,3,4},{8,6,7,9},{4,10,-4,12},{-13,14,45,28}};
    Matrix_4x4 a;
    Matrix_4x4 b(a);
    Matrix_4x4 c(m);
    Matrix_4x4 d;
    Matrix_4x4 e;
    double temp;

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            d[i][j]=m[i][j];
        }
    }

    cout<<"a:"<<endl<<a<<endl;
    cout<<"b(a)"<<endl<<b<<endl;
    cout<<"c(m)"<<endl<<c<<endl;
    cout<<"d"<<endl<<d<<endl;

    d=a+c;
    cout<<"d=a+c:"<<endl<<d<<endl;

    d=d-a;
    cout<<"d=d-a"<<endl<<d<<endl;

    e=d.inverse();
    cout<<"e:"<<endl<<e<<endl;

    d=d*e;
    cout<<"d:"<<endl<<d<<endl;

    d=a^3;
    cout<<"d=a^3"<<endl<<a<<endl;

    d=c.transpose();
    cout<<"d=c.transpose()"<<endl<<d<<endl;

    temp=c.determinant();
    cout<<"temp=c.determinant"<<endl<<temp<<endl;

    return 0;
}
