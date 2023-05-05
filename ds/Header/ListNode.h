#ifndef LISTNODE
#define LISTNODE
#include <cstddef>

#define ListNodePosi(T) ListNode<T>*
typedef int Rank;

template <typename T>
struct ListNode	{
	
	T data;                                                   //数据域 
	ListNodePosi(T) pred;                                     //直接前驱指针 
	ListNodePosi(T) succ;                                     //直接后继指针 
	
	ListNode() {}                                             //默认构造函数 针对header和trailer节点的构造 默认为NULL 
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
		:data(e), pred(p), succ(s) {}
	
	ListNodePosi(T) insertAsPred(T const& e);                 //在当前节点前插入新节点 
	ListNodePosi(T) insertAsSucc(T const& e);                 //在当前节点后插入新节点 
	
};

#endif 

