//排序 
#include<iostream>
#include <stdlib.h>
#include<cstdio>
#include "../../complex/Complex.h"
#include "../../vector/vector.h"
using namespace std;
 
int main(){
	Complex A[10];
	cout << "随机生成无序复数向量" <<endl; 
	for (int j = 0; j < 10; j++){
	   A[j].read_Real(rand() % 200 / 10.0);
	   A[j].read_Imaginary(rand() % 200 / 10.0);
	   A[j].read_modulus();
       A[j].display();//在屏幕上显示 
    }//生成复数 
    cout << endl;
    Vector<Complex>v(A, 10);
//    //______________________________________________
//    int n;
//    n = v.disordered();//有序性甄别 
//    cout << "无序数为" << n << endl;
//    //getchar();
//    v.bubbleSort(0,10); 
//    n = v.disordered();
//    cout << "排序后" <<endl;
//    for (int j = 0; j < 10; j++){
//	   v._elem[j].display();
//    }
//    cout<<endl;
//    cout << "无序数为" << n << endl;
//    //getchar();
//    //________________________________________________________排序 
	//置乱
	v.unsort(0,10);
	cout << "置乱后" << endl;
	for(int i=0;i<10;i++)
		v[i].display();
	
	//查找
	cout<<endl<<"查找"<<endl;
	int c;
	c = v.find(A[8]);
	cout<<"A[8]此时的位置为"<<c<<endl;
	//插入
	cout<<"插入后"<<endl;
	v.insert(10, A[4]);
	for(int i=0;i<11;i++)
		v[i].display(); 
	cout<<endl;
 	cout<<"删除8后"<<endl;
	//删除
	v.remove(8);
	for(int i=0;i<10;i++)
		v[i].display();
	cout<<endl;
	cout<<"唯一化"<<endl;
	//唯一化
	c = v.deduplicate();
	cout << "重复复数的个数为" << c << endl <<"唯一化后："<< endl;
	for(int i=0;i<9;i++)
		v[i].display();
	
	 
}

 

