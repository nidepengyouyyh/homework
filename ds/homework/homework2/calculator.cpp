#include <iostream>
#include "../../Header/Stack.h"
#include <string>
#include <cmath>
#include <string.h>
#include "../../Header/Complex.h"
#include <iomanip>
#include <cstdlib>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
Complex evaluter(char *s);
int flag(char optr, Complex opnd);
typedef enum { ADD, SUB, MUI, DIV, POW, FAC, L_P, R_P, EOE ,COM, SIN, COS, TAN, LOG} Operator;//0-8
const char pri[14][14] = {
	//优先级关系 
//       +   -   *   /   ^   !   (   )   /0  i  sin cos tan  e
/* + */	'>','>','<','<','<','<','<','>','>','<','<','<','<','<',
/* - */	'>','>','<','<','<','<','<','>','>','<','<','<','<','<',
/* * */	'>','>','>','>','<','<','<','>','>','<','<','<','<','<',
/* / */	'>','>','>','>','<','<','<','>','>','<','<','<','<','<',
/* ^ */	'>','>','>','>','>','<','<','>','>','<','<','<','<','<',
/* ! */	'>','>','>','>','>','>',' ','>','>','>','<','<','<','>',
/* ( */	'<','<','<','<','<','<','<','=',' ','<','<','<','<','<',
/* ) */	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
/* 0 */	'<','<','<','<','<','<','<',' ','=','<','<','<','<','<',
/* i */	'>','>','>','>','>','>',' ','>','>','>','<','<','<',' ',
/* s */	'>','>','>','>','>','>','<','>','>',' ',' ',' ',' ','<',
/* c */	'>','>','>','>','>','>','<','>','>',' ',' ',' ',' ','<',
/* t */	'>','>','>','>','>','>','<','>','>',' ',' ',' ',' ','<',
/* e */	'>','>','>','>','>','<','<','>','>',' ',' ',' ',' ','<',	
};
int change(char c) {//储存运算符 
	switch (c)
	{
	case '+':return ADD; 
	case '-':return SUB; 
	case '*':return MUI; 
	case '/':return DIV; 
	case '^':return POW;
	case '!':return FAC; 
	case '(':return L_P;
	case ')':return R_P; 
	case '\0':return EOE;
	case 'i':return COM;
	case 's':return SIN;
	case 'c':return COS;
	case 't':return TAN;
	case 'e':return LOG;
	}
}

Complex readNumber(char* &S, Stack<Complex> &opnd) {
	Complex X;
	float x = 0.0;
	bool point=false;//判断是否为小数
	int i = 0;//计小数点后的位数
	while (isdigit(*S)||*S=='.') {
		if (*S != '.') {
			if (point == false) 	
				x = x * 10 + (*(S++) - 48);//减去48,ASCII转成数字
			if (point == true) 	
			{ x = x * 10 + (*(S++) - 48);
				 i++; }
		}
		else { S++; point = true; }
	}
	int temp = 1;
	for (int j = 0; j < i; j++) temp *= 10;
	x = x / temp;
	X.read_Real(double(x));
	opnd.push(X);//压入操作数栈
	return X;
}

Complex fac(Complex n) {	return (2 > n) ? 1 : n * fac(n - 1);}//自然数的阶乘(小数的阶乘呢???不会实现...)
Complex calcu(char optr, Complex opnd) {//单元运算 
	double a;
	if (optr == '!') return fac(opnd);
	else if(optr == 'i'){ 
		a=opnd.imag()*-1; 
		opnd.read_Imaginary(opnd.real())  ;
		opnd.read_Real(a * -1); 
		return opnd;} 
	else if(optr == 's'){
		a=opnd.real()*1;
		return sin(a);
	}
	else if(optr == 'c'){
		a=opnd.real()*1;
		return cos(a);
	}
	else if(optr == 't'){
		a=opnd.real()*1;
		return tan(a);
	}
	else if(optr == 'e'){//e为底的对数 
		a=opnd.real()*1;
			return log(a);
	}
}
int flag(char optr, Complex opnd)
{
	int f = 1;
	double a;
	if(optr == 'e'){
		a = opnd.real()*1;
		if(a<=0){
			cout<<endl<<"ERROR!对数越界";
			return f*(-1);
		}
	}
	return f;
}
Complex calcu(Complex opnd1, char op, Complex opnd2) {//重载双元运算符 
	Complex result = 1;
	Complex c;
	c.m_imag=1;//载入复数运算 
	switch (op) //判断运算符
	{
	case '+': {result = opnd1 + opnd2; return result; }
	case '-': {result = opnd1 - opnd2; return result; }
	case '*': {result = opnd1 * opnd2; return result; }
	case '/': {result = opnd1 / opnd2; return result; }
	case '^': {for (int i = 0; i < opnd2; i++) 
	result *= opnd1; 
	return result; }
	}//switch
}
char orderBetween(char c1, char c2) {
	return pri[change(c1)][change(c2)];
}
Complex evaluter(char* s)
{
    Stack<Complex> opnd;//运算数栈
    Stack<char> optr;//运算符栈
    optr.push('\0');//先将尾哨兵推入栈中
    while(!optr.empty()){
        if(isdigit(*s)){ //若为操作数，存在读入连续数字的情况
            readNumber(s,opnd); //则读入操作数 
            //append(RPN,opnd.top());
        }else{
        if(*s == 's'&& *(s+1) == 'i'&& *(s+2) == 'n')
			{ 
				s++;s++; *s = 's';}
        else if(*s == 'c'&& *(s+1) == 'o'&& *(s+2) == 's')
			{ 
				s++;s++; *s = 'c';}
        else if(*s == 't'&& *(s+1) == 'a'&& *(s+2) == 'n')
			{ 
				s++;s++; *s = 't';}
		else if(*s == 'l'&& *(s+1) == 'o'&& *(s+2) == 'g')
		{
			s++;s++; *s = 'e';
		}
		switch(orderBetween(optr.top(),*s)){//分别处理 
            case '<'://栈顶运算符优先级低 
                optr.push(*s);s++;break;
            case '='://优先级相等（当前运算符为右括号或者是尾哨兵） 
                optr.pop();s++;break;//脱括号，接收下一个字符
            case '>':{//运算时机到了 
                char op = optr.top(); optr.pop();
			if ('!' == op||'i'== op||'s' == op||'c' == op||'t' == op||'e' == op) {
				//stack.h 中pop函数的返回值为void,所以需要在pop之前先通过top函数取栈顶(top函数返回值为栈顶元素)然后再pop出栈
				Complex pOpnd = opnd.top(); opnd.pop();
				if(flag(op,pOpnd) == 1){
					opnd.push(calcu(op, pOpnd));//实施一元运算
				}
				else 
					cout<<" ";
			}
			else {
				Complex pOpnd2 = opnd.top(); opnd.pop();
				Complex pOpnd1 = opnd.top(); opnd.pop();
				opnd.push(calcu(pOpnd1, op, pOpnd2));//实施二元运算
			}
			break;
            }
            default: cout<<"请合理使用计算机";exit(-1);
        }
    }
    }
    return opnd.pop();
}

int main(int argc, char** argv) {
	char S1[] = "(5i+4)*(4i+3)"; cout << "(5i+4)*(4i+3)=" ; evaluter(S1).display(); 
	cout<<endl;
	char S2[] = "7.3i-3.5"; cout << "7.3i-3.5=" ;evaluter(S2).display() ;
	cout<<endl;
	char S3[] = "log3!"; cout << "log3!=" ;evaluter(S3).display() ;
	cout<<endl;
	char S7[] = "3i+4i"; cout << "3i+4i=" ;evaluter(S7).display() ;
	cout<<endl;
	char S4[] = "log(sin(3))"; cout << "log(sin(3))=" ;evaluter(S4).display() ;
	cout<<endl;
	char S5[] = "log(sin(5))"; cout << "log(sin(5))=" ;evaluter(S5).display() ;
	cout<<endl;
	char S6[] = "log(sins(5))"; cout << "log(sins(5))=" ;evaluter(S6).display() ;
	
//	char S5[] = "(2+3)+3!*6!i"; cout << "(2+3)+3!*6!i=" ;evaluter(S5).display();

}
