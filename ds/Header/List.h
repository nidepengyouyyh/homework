#ifndef LIST
#define LIST
#include "listNode.h"
template <typename T> class List{//列表模板类 
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;//规模、头哨兵、尾哨兵
	
protected:
	void init();
	int clear();
	void copyNodes( ListNodePosi(T), int);
	void merge( ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
	void mergeSort(ListNodePosi(T)&, int);
	void selectionSort( ListNodePosi(T), int);
	void insertionSort(ListNodePosi(T), int); 

public:
//构造函数
	List(){ init(); }//默认
	List( List<T> const& L);
	List( List<T> const& L, Rank r, int n);
	List( ListNodePosi(T) p, int n);
//析构函数
	~List();//释放（包含头，尾哨兵在内的）所有节点
//只读访问接口
	Rank size() const {return _size;}//规模
	bool empty() const {return _size <= 0;}//判空
	T& operator[](Rank r) const;//重载，支持寻秩访问,效率较低
	ListNodePosi(T) first() const {return header->succ;}//首节点位置 
	ListNodePosi(T) last() const {return trailer->pred;}//尾节点位置 
	bool valid (ListNodePosi(T) p)
	{return p && (trailer != p) && (header != p);}//将头，尾节点等同于NULL
	int disordered() const;
	ListNodePosi(T) find (T const& e) const//无序列表查找
	{return find(e, _size, trailer);}
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;//无序区间查找 
	ListNodePosi(T) search (T const& e) const//有序列表查找 
	{return search(e, _size, trailer);}
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;//有序区间查找
	ListNodePosi(T) selectMax (ListNodePosi(T) p, int n);
	ListNodePosi(T) selectMax(){return selectMax(header->succ, _size);	}//整体最大者
//可写访问接口
	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);
	T remove(ListNodePosi(T) p);
	void merge(List<T>& L)
	{merge(first(), size, L, L.first(), L._size);}
	void sort(ListNodePosi(T) p, int n);
	void sort(){sort(first(), _size);}
	int deduplicate();
	int uniquify();
	void reverse();
//遍历
	void traverse(void(* )(T&));
	template <typename VST>
	void traverse(VST&); 
	 
};

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e){
	ListNodePosi(T) x = new ListNode(e,pred,this);
	pred->succ = x;
	pred = x;
	return x;
}

template <typename T> 
void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header -> succ = trailer;
	header -> pred = NULL;
	trailer -> pred = header;
	trailer -> succ = NULL;
	_size = 0;//记录规模 
}
template <typename T> 
T& List<T>::operator[]( Rank r) const{
	ListNodePosi(T) p = first();
	while(0 < r--) p = p->succ;
	return p->data;
}

template <typename T> //在无序列表内结点p （可能是trailer）的n个（真）前驱中，找到等于e的最后者
ListNodePosi(T) List<T>::find ( T const& e, int n, ListNodePosi(T) p ) const{
   while(0 < n--) 
      if(e == (p = p->pred)->data) return p; //逐一对比，存在则返回该结点
   return NULL ;  // 否则返回空
}

template <typename T> 
ListNodePosi(T) List<T>::insertAsFirst( T const& e){
   _size++; return header->insertAsSucc(e); //e当作首结点插入
}


template <typename T> 
ListNodePosi(T) List<T>::insertAsLast( T const& e){
   _size++; return trailer->insertAsPred(e); //e当作尾结点插入
}

template <typename T> 
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p , T const& e){
   _size++; return p->insertAsPred(e); //e当作p的前驱插入
}

template <typename T> 
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p , T const& e){
   _size++; return p->insertAsSucc(e); //e当作p的后继插入
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p){
   //删除合法位置p处的结点，并返回其数值
   T e = p->data; //备份删除结点的数值
   p->pred->succ = p->succ ; // 后继
   p->succ->pred = p->pred; // 前驱
   delete p; //删除结点
   _size--;
   return e;
}

template <typename T> 
int List<T>::deduplicate(){
   //剔除无序列表中的重复结点
   if(_size < 2) return 0; //平凡列表自然无重复
   int oldside = _size ;
   ListNodePosi(T) p = header ; Rank r = 0; //p 从首结点开始
   while(trailer != (p = p->succ)){ //依次直到末结点
      ListNodePosi(T) q = find(p->data ,r,p); //在p的r个前驱中查找雷同者
      q ? remove(q):r++; //若的确存在，删除，否则秩加一
   }
   return oldside - _size ; //返回删除的节点数
}

template <typename T>
void List<T>::traverse(void (*visit)(T&)){
   //利用函数指针机制的遍历
   for(ListNodePosi(T) p = header->succ ; p != trailer ; p = p->succ )
      visit(p->data);
}

template <typename T> template <typename VST> // 元素类型，迭代器
void List<T>::traverse(VST& visit){  //利用函数对象性质的遍历
   for(ListNodePosi(T) p = header->succ; p != trailer ; p = p->succ)
      visit(p->data);
}

template <typename T> 
int List<T>::uniquify(){
   //成批剔除重复元素，效率更高
   if(_size < 2) return 0; //平凡列表自然无重复
   int oldside = _size;
   ListNodePosi(T) p ;  ListNodePosi(T) q; //依次指向紧邻的各对节点
   for(p = header ,q = p->succ ; q != trailer ; p = q ,q = q->succ){ // 自左向右扫描
      if(p->data == q->data){ remove(q); q = p ;} //若pq雷同，删除后者
   }
   return (oldside-_size); 
}

template <typename T> //有序列表内结点p 的n个前驱中，找到不大于e的最后者（可能相等）
ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ){
   while(0 <= n--)
      if(((p = p->pred)->data) <= e) break;
   return p;
}

template <typename T> //插入排序
void List<T>::insertionSort(ListNodePosi(T) p ,int n){
   for(int r = 0 ; r < n ;r++){
      insertAfter(search(p->data ,r , p) , p->data);
      p = p->succ ; remove(p->pred);
   }
}


template <typename T> //返回起始p的n个后继中最大的
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p ,int n){
   ListNodePosi(T) max = p ; 
   for(ListNodePosi(T) cur = p ; 1 < n  ; n--)
      if((cur = cur->succ)->data  >= max->data)
         max = cur;
   return max; 
}

template <typename T> //选择排序
void List<T>::selectionSort(ListNodePosi(T) p ,int n){
   ListNodePosi(T) head = p->pred ; ListNodePosi(T) tail = p;
   for(int i = 0 ; i < n ; i++) tail = tail->succ;
   while(1 < n ){ //在至少还剩两个结点之前循环
      ListNodePosi(T) max = selectMax(head->succ ,n); //找出最大者
      insertBefore(tail ,remove(max)); //将其移动至tail 的末尾
      tail = tail->pred; n--;
   }
}

template <typename T> //归并算法
void List<T>::merge(ListNodePosi(T)& p, int n , List<T>& L, ListNodePosi(T) q, int m){
   //自p起的n个元素，自q起的m个元素归并
   ListNodePosi(T) pp = p->pred;
   while(0 < m) {
      if((0 < n) && (p->data <= q->data))
         {if (q == (p = p->succ)) break ; n--;}
      else
         {insertBefore(p,L.remove((q = q->succ)->pred)); m--;}
   }
   p = pp->succ;
}

template <typename T> //归并排序
void List<T>::mergeSort(ListNodePosi(T)& p , int n){
   if(n < 2) return;
   int m = n>>1;
   ListNodePosi(T) q = p ; for(int i = 0 ; i < m ; i++) q = q->succ;
   mergeSort(p,m);mergeSort(q,n-m);
   merge(p,m,*this , q , n-m);
}


template <typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}
template <typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while(0<_size)
		remove(header->succ);
	return oldSize;
}
#endif



