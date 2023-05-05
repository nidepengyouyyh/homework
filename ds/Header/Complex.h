#include <iostream>
#include <cmath>
#ifndef COMPLEX
#define COMPLEX
using namespace std;
//复数类
class Complex{
public:  //构造函数
    Complex(double real = 0.0, double imag = 0.0): m_real(real), m_imag(imag){ }
public:  //运算符重载
    //以全局函数的形式重载
    friend Complex operator+(const Complex &c1, const Complex &c2);
    friend Complex operator-(const Complex &c1, const Complex &c2);
    friend Complex operator*(const Complex &c1, const Complex &c2);
    friend Complex operator/(const Complex &c1, const Complex &c2);
    friend bool operator> (const Complex &c1, const Complex &c2);
    friend bool operator< (const Complex &c1, const Complex &c2);
    friend bool operator==(const Complex &c1, const Complex &c2);
    friend bool operator!=(const Complex &c1, const Complex &c2);
    //以成员函数的形式重载
    Complex & operator+=(const Complex &c);
    Complex & operator-=(const Complex &c);
    Complex & operator*=(const Complex &c);
    Complex & operator/=(const Complex &c);
     void display ();
     double read_Real (double r);
     double read_Imaginary (double i);
     double read_modulus();
public:  //成员函数
    double real() const{ return m_real; }
    double imag() const{ return m_imag; }
    double modulus() const{ return m_modulus; } 
    double m_real;  //实部
    double m_imag;  //虚部
    double m_modulus;  //模长 
};
//重载+运算符
Complex operator+(const Complex &c1, const Complex &c2){
    Complex c;
    c.m_real = c1.m_real + c2.m_real;
    c.m_imag = c1.m_imag + c2.m_imag;
    return c;
}
//重载-运算符
Complex operator-(const Complex &c1, const Complex &c2){
    Complex c;
    c.m_real = c1.m_real - c2.m_real;
    c.m_imag = c1.m_imag - c2.m_imag;
    return c;
}
//重载*运算符  (a+bi) * (c+di) = (ac-bd) + (bc+ad)i
Complex operator*(const Complex &c1, const Complex &c2){
    Complex c;
    c.m_real = c1.m_real * c2.m_real - c1.m_imag * c2.m_imag;
    c.m_imag = c1.m_imag * c2.m_real + c1.m_real * c2.m_imag;
    return c;
}
//重载/运算符  (a+bi) / (c+di) = [(ac+bd) / (c2+d2)] + [(bc-ad) / (c2+d2)]i
Complex operator/(const Complex &c1, const Complex &c2){
    Complex c;
    c.m_real = (c1.m_real*c2.m_real + c1.m_imag*c2.m_imag) / (pow(c2.m_real, 2) + pow(c2.m_imag, 2));
    c.m_imag = (c1.m_imag*c2.m_real - c1.m_real*c2.m_imag) / (pow(c2.m_real, 2) + pow(c2.m_imag, 2));
    return c;
}
//重载==运算符
bool operator==(const Complex &c1, const Complex &c2){
    if( c1.m_real == c2.m_real && c1.m_imag == c2.m_imag ){
        return true;
    }else{
        return false;
    }
}
//重载> <运算符 
bool operator>(const Complex &c1, const Complex &c2){
    if( c1.m_modulus > c2.m_modulus ){
        return true;
    }else{
        return false;
    }
}
bool operator>(const Complex &c1, double m){
    if( c1.m_modulus > m*m){
        return true;
    }else{
        return false;
    }
}
bool operator<(const Complex &c1, const Complex &c2){
    if(c1.m_modulus < c2.m_modulus ){
        return true;
    }else{
        return false;
    }
}
bool operator<(const Complex &c1, double m){
    if(c1.m_modulus < m*m ){
        return true;
    }else{
        return false;
    }
}
bool operator<=(const Complex &c1, const Complex &c2){
    if(c1.m_modulus <= c2.m_modulus ){
        return true;
    }else{
        return false;
    }
}
bool operator<=(const Complex &c1, double m){
    if(c1.m_modulus <= m*m ){
        return true;
    }else{
        return false;
    }
}
bool operator>=(const Complex &c1, double m){
    if(c1.m_modulus >= m*m ){
        return true;
    }else{
        return false;
    }
}
//重载!=运算符
bool operator!=(const Complex &c1, const Complex &c2){
    if( c1.m_real != c2.m_real || c1.m_imag != c2.m_imag ){
        return true;
    }else{
        return false;
    }
}
//重载+=运算符
Complex & Complex::operator+=(const Complex &c){
    this->m_real += c.m_real;
    this->m_imag += c.m_imag;
    return *this;
}
//重载-=运算符
Complex & Complex::operator-=(const Complex &c){
    this->m_real -= c.m_real;
    this->m_imag -= c.m_imag;
    return *this;
}
//重载*=运算符
Complex & Complex::operator*=(const Complex &c){
    this->m_real = this->m_real * c.m_real - this->m_imag * c.m_imag;
    this->m_imag = this->m_imag * c.m_real + this->m_real * c.m_imag;
    return *this;
}
//重载/=运算符
Complex & Complex::operator/=(const Complex &c){
    this->m_real = (this->m_real*c.m_real + this->m_imag*c.m_imag) / (pow(c.m_real, 2) + pow(c.m_imag, 2));
    this->m_imag = (this->m_imag*c.m_real - this->m_real*c.m_imag) / (pow(c.m_real, 2) + pow(c.m_imag, 2));
    return *this;
}
//显示复数 
void Complex::display (){
	if ( m_real != 0 ){
		if  ( m_imag > 0 ){
			cout << m_real << "+" << m_imag << "i" << " "; 
		}
		else if(m_imag < 0) 
			cout << m_real << m_imag << "i" << " ";
		else
			cout << m_real << " "; 
	}
	else if( m_real == 0&& m_imag != 0)
		cout<< m_imag << "i"<< " ";
	else if (m_imag == 0)
		cout << 0;
}
//实部 虚部 模 
double Complex::read_Real (double r){
    m_real = r;		
}
double Complex::read_Imaginary (double i){
    m_imag = i;		
}
double Complex::read_modulus(){
	m_modulus = m_imag * m_imag + m_real*m_real;
}
#endif
