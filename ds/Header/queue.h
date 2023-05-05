#ifndef QUEUE
#define QUEUE

#include "List.h"
#include <stdlib.h>
using namespace std;

template <typename T> 
class Queue:public List<T>{
public: 
	void enqueue( T const& e){
		insertAsLast( e );
	}
	T dequeue(){
		return remove( this->first() );
	}
	T& front(){
		return this->first()->data;
	}
//    queue(){	//初始化
//        front=0;
//        back=-1;
//        count=0;
//    }
//    bool isEmpty(){	//判空
//        if(count==0){
////            cout<<"queue is empty.\n";
//            return true;
//        }
//        return false;
//    }
//    bool isFull(){	//判满
//        if(count==MAXSIZE||back==MAXSIZE-1){
////            cout<<"queue is full.\n";
//            return true;
//        }
//        return false;
//    }
//    int getFront(){	//取队头
//        if(isEmpty()){
//            return -1;
//        }
//        return data[front];
//    }
//    int getBack(){	//取队尾
//        if(isEmpty()){
//            return -1;
//        }
//        return data[back];
//    }
//    bool push(int num){	//入队
//        if(isFull()){
//            return false;
//        }
//        back++;
//        data[back]=num; 
//        count++;
//        return true;
//    }
//    bool pop(){	//出队
//        if(isEmpty()){
//            return false;
//        }
//        front++;
//        count--;
//        return true;
//    }
//    bool pop2(){	//出队
//        if(isEmpty()){
//            return false;
//        }
//        back--;
//        count--;
//        return true;
//    }
//    int getLength(){	//得到队列长度
//        return count;
//    }
//private:
//    int front;
//    int back;
//    int count;
//    int data[MAXSIZE];
};
#endif

