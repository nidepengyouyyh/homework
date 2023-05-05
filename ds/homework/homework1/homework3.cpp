//排序 
#include<windows.h> 
#include <ctime>
#include<iostream>
#include <stdlib.h>
#include<cstdio>
#include "../../complex/Complex.h"
#include "../../vector/vector.h"
using namespace std;
int main()
{
	double m1 = 10, m2 = 20;
	Complex A[10];
	Complex* B;
	cout << "随机生成无序复数向量，排序后显示:" <<endl; 
	for (int j = 0; j < 10; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
       //A[j].display();//在屏幕上显示 
    }//生成复数 
    Vector<Complex>v(A, 10);
    v.bubbleSort(0,10);
    for(int i=0; i<10; i++)
    {
    	v[i].display();
	}
	cout<<endl;
	cout<<"模在范围[10，20）间的复数如下："<<endl;
	
 //   Complex* B =new Complex[a]; 
    B=v.check(0,10,m1,m2);
    for(int i=0;i<sizeof(B);i++)
    {
    	v[i].display();
	}
    
}
