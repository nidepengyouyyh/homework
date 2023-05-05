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
	double time=0;  
    double counts=0;  
    LARGE_INTEGER nFreq;  
    LARGE_INTEGER nBeginTime;  
    LARGE_INTEGER nEndTime;  
	Complex B[10];
	Complex A[10];
	cout << "随机生成无序复数向量" <<endl; 
	for (int j = 0; j < 10; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
       A[j].display();//在屏幕上显示 
    }//生成复数 
    cout << endl;
    for(int i=0;i<10;i++)
    {
    	B[i].m_real=A[i].m_real;
    	B[i].m_imag=A[i].m_imag;
    	B[i].m_modulus=A[i].m_modulus;
	}
    Vector<Complex>v(A, 10);
    Vector<Complex>v1(B, 10);
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
    cout << "排序后" <<endl;
    for (int j = 0; j < 10; j++){
	   v[j].display();
    }
    cout<<endl;
    cout<<"乱序冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
        cout<<"乱序归并执行时间："<<time*1000<<"ms"<<endl;
    
    
    QueryPerformanceFrequency(&nFreq);  
    QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
    cout<<"有序冒泡执行时间："<<time*1000<<"ms"<<endl;

    QueryPerformanceFrequency(&nFreq);  
        QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
    cout<<"有序归并执行时间："<<time*1000<<"ms"<<endl;
    
	v.bubbleSort(-1,0,10);
    v1.bubbleSort(-1,0,10);//倒序
	 
    QueryPerformanceFrequency(&nFreq);  
        QueryPerformanceCounter(&nBeginTime);
    v.bubbleSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
    cout<<"倒序冒泡执行时间："<<time*1000<<"ms"<<endl;
    
    QueryPerformanceFrequency(&nFreq);  
        QueryPerformanceCounter(&nBeginTime);
    v1.mergeSort(0,10); 
    QueryPerformanceCounter(&nEndTime);
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;//计算程序执行时间单位为s
    cout<<"倒序归并执行时间："<<time*1000<<"ms"<<endl;
    
	
    
}
