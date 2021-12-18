#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Matrix_4x4
{
private:
    double matrix[4][4];
public:
    //Ĭ�Ϲ��캯��
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
    //���ι��캯��
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
    //�������캯��
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
    //���� = �����������Ϊ�������
    Matrix_4x4 const & operator = (Matrix_4x4 const &m);
    //���� = �����������Ϊһ��4x4�Ķ�ά����
    Matrix_4x4 const & operator = (const double m[4][4]);
    //������������� + - *
    friend Matrix_4x4 operator + (Matrix_4x4 const &m1,Matrix_4x4 const &m2);
    friend Matrix_4x4 operator - (Matrix_4x4 const &m1,Matrix_4x4 const &m2);
    friend Matrix_4x4 operator * (Matrix_4x4 const &m1,Matrix_4x4 const &m2);
    //���� ^ �����Ϊ�����i���ݣ����iΪ��������δ�����
    friend Matrix_4x4 operator ^ (Matrix_4x4 m1,int i);
    //���� [] �������ʵ��˫�±귽ʽ���ʾ���Ԫ��
    const double * operator[] (const int i) const {return matrix[i];}
    double * operator[] (const int i){return matrix[i];}
    // ��������<< ����� >>
    friend ostream& operator <<(ostream& out_put, const Matrix_4x4 &m);
    friend istream& operator >>(istream& in_put, Matrix_4x4 &m);
    Matrix_4x4 inverse();   //�������棬���ı䵱ǰ����ֵ�����������
    Matrix_4x4 transpose(); //����ת�ã����ı䵱ǰ����ֵ������ת�þ���
    double determinant();//����������ʽ�����ı䵱ǰ����ֵ����������ʽ��ֵ
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
    Matrix_4x4 t(matrix);//��ʱ����
    Matrix_4x4 B;//�����
    //��A����������ʱ����t[n][n]��
    //��ʼ��B����Ϊ��λ��
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            B[i][j] = (i == j) ? 1 : 0;
        }
    }
    for (i = 0; i < 4; i++)
    {
        //Ѱ����Ԫ
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
        //�����Ԫ�����в��ǵ�i�У������н���
        if (k != i)
        {
            for (j = 0; j < 4; j++)
            {
                temp = t[i][j];
                t[i][j] = t[k][j];
                t[k][j] = temp;
                //B���潻��
                temp = B[i][j];
                B[i][j] = B[k][j];
                B[k][j] = temp;
            }
        }
        //�ж���Ԫ�Ƿ�Ϊ0, ����, �����A�������Ⱦ���,�����������
        if (t[i][i] == 0)
        {
            cout << "There is no inverse matrix!";
            return B;
        }
        //��ȥA�ĵ�i�г�ȥi������ĸ���Ԫ��
        temp = t[i][i];
        for (j = 0; j < 4; j++)
        {
            t[i][j] = t[i][j] / temp;        //���Խ����ϵ�Ԫ�ر�Ϊ1
            B[i][j] = B[i][j] / temp;        //�������
        }
        for (j = 0; j < 4; j++)        //��0��->��n��
        {
            if (j != i)                //���ǵ�i��
            {
                temp = t[j][i];
                for (k = 0; k < 4; k++)        //��j��Ԫ�� - i��Ԫ��*j��i��Ԫ��
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
    int num1,num2,index; // ��ʼ��
    double det=1;
    double total=1;
    int temp[5];
    //ѭ�������Խ�Ԫ
    for(int i = 0; i < 4; i++)
    {
        index = i; // ��ʼ������
        //��Ѱ��0ֵ����
        while(matrix[index][i] == 0 && index < 4)
        {
            index++;
        }
        if(index == 4) // �������û�з�0Ԫ
        {
            // ����ʽΪ0
            continue;
        }
        if(index != i)
        {
            //������
            for(int j = 0; j < 4; j++)
            {
                swap(matrix[index][j],matrix[i][j]);
            }
                //����ʽ��������������������
            det = det*pow(-1,index-i);
       }
       for(int j = 0; j < 4; j++)
       {
           temp[j] = matrix[i][j];
       }
       //����ÿһ��
       for(int j = i+1; j < 4; j++)
       {
           num1 = temp[i]; //�Խ�Ԫ��ֵ
           num2 = matrix[j][i]; //��һ�е�ֵ
           for(int k = 0; k < 4; k++)
           {
               matrix[j][k] = (num1 * matrix[j][k]) - (num2 * temp[k]);
           }
           total = total * num1; // Det(kA)=kDet(A);
        }
    }
    //�������Խ�Ԫ
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
