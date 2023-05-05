#include "BinNode.h" //引用二叉树结点模板类
#include "Stack.h"
#include "queue.h"

template <typename T> class BinTree {
	protected:
		int _size; //规模
		BinNodePosi(T) _root; //根节点
		virtual int updateHeight(BinNodePosi(T) x); //更新当前节点高度
		void updateHeightAbove(BinNodePosi(T) x); //更新所有祖先节点高度
	public:
		/*--构造与析构函数--*/
		BinTree(): _size(0), _root(NULL) {}
		~BinTree() {
			if (_size > 0) remove(_root);
		}
		/*--常用接口--*/
		int size() const {
			return _size;    //规模
		}
		bool empty() const {
			return !_root;    //判空
		}
		
		BinNodePosi(T) root() const {
			return _root;    //取根
		}
		
		BinNodePosi(T)  insertAsRoot(T const &e); //插入根节点
		BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e); //作为左孩子节点插入
		BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e); //作为右孩子节点插入
		BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S); //作为左子树插入
		BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S); //作为右子树插入
		int remove(BinNodePosi(T) x); //删除以x节点为根的子树，返回子树原先的规模
		BinTree<T>* secede(BinNodePosi(T) x); //删除子树，并将其转化为独立子树
		/*--遍历接口--*/
		template <typename VST>
		void travLevel(VST&visit) { //层次遍历
			if (_root) _root->travLevel(visit);
		}

		template <typename VST>
		void travPre(VST&visit) { //先序遍历
			if (_root) _root->travPre(visit);
		}

		template <typename VST>
		void travIn(VST&visit) { //中序遍历
			if (_root) _root->travIn(visit);
		}

		template <typename VST>
		void travPost(VST&visit) { //后序遍历
			if (_root) _root->travPost(visit);
		}

		/*--判断器、比较器--*/

		bool operator>(BinTree<T> const& t) {
			return _root && t._root && lt(_root, t._root);
		}

		bool operator<(BinTree<T> const& t) {
			return _root && t._root && lt(_root, t._root);
		}

		bool operator==(BinTree<T> const& t) {
			return _root && t._root && (_root == t._root);
		}

		bool operator!=(BinTree<T> const& t) {
			return _root && t._root && (_root != t._root);
		}

		bool operator>=(BinTree<T> const& t) {
			return _root && t._root && (_root >= t._root);
		}

		bool operator<=(BinTree<T> const& t) {
			return _root && t._root && (_root <= t._root);
		}

};

//—————————————————————————————————————————
template <typename T> int BinTree<T>::updateHeight( BinNodePosi(T) x ) {
	return x->height = 1 + max( stature (x -> lc), stature (x -> rc));
}
template <typename T> void BinTree<T>::updateHeightAbove( BinNodePosi(T) x ) {
	while(x) {
		updateHeight (x);
		x = x->parent;
	}
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e) {
	_size ++;    //将ｅ当作根节点插入空的二叉树
	return _root = new BinNode<T>(e);
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e) {
	_size ++;    //ｅ插入为ｘ的左孩子
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lchild;
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e) {
	_size ++;    //ｅ插入为ｘ的右孩子
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rchild;
}

template <typename T>//作为左子树
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) {//子树接入

	if ( x->lc = S->_root ) 
		x->lc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	delete S;
	//release(S);
	S = NULL;
	return x;

}
template <typename T>//as right child tree
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S) {
	if ( x->rc = S->_root ) 
		x->rc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	delete S;
	//release(S);
	S = NULL;
	return x;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}
//________________________________________________________warning!!!!!!!!!!!!!!!
template <typename T>
static int removeAt(BinNodePosi(T) x) {
	if (!x) return 0;
	int n = 1 + removeAt(x->lc) +  removeAt(x->rc);
	//release(x->data);
	//release(x);
	//delete x->data;
	delete x;
	return n;
}

template <typename T>//子树分离，将其封装为一棵独立子树返回
BinTree<T>* BinTree<T>::secede ( BinNodePosi(T) x ) {
	FromParentTo( *x ) = NULL;
	updateHeightAbove( x->parent );
	BinTree<T>* S = new BinTree<T>;
	S->_root = x;
	x->parent = NULL;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}

template <typename T, typename VST>//first
void travPre_R( BinNodePosi(T) x, VST& visit ) {
	if( !x ) return;
	visit( x->data );
	travPre_R( x->lc, visit);
	travPre_R( x->rc, visit);
}

template <typename T, typename VST>
void travPost_R( BinNodePosi(T) x, VST& visit) {//后序 
	if( !x ) return;
	travPost_R( x->lc, visit );
	travPost_R( x->rc, visit );
	visit( x->data );
}


template <typename T, typename VST>
void travIn_R( BinNodePosi(T) x, VST& visit) {//中序 
	if( !x ) return;
	travIn_R( x->lc, visit );
	visit( x->data );
	travIn_R( x->rc, visit );
}

template <typename T, typename VST>
static void visitAlongLeftBranch( BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)>& S) {
	while( x ) {
		visit( x->data );
		S.push( x->rc );
		x = x->lc;
	}
}

template <typename T, typename VST>
void travPre_I2( BinNodePosi(T) x, VST& visit ) {
	Stack<BinNodePosi(T)> S;
	while(true) {
		visitAlongLeftBranch(x, visit, S);
		if( S.empty() ) break;
		x = S.pop();
	}
}


template <typename T>
static void goAlongLeftBranch( BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
	while( x ) {
		S.push( x );
		x = x->lc;
	}
}

template <typename T, typename VST>
void travIn_I1 (BinNodePosi(T) x, VST& visit)//迭代版中序遍历 
{
	Stack<BinNodePosi(T)> S;//support stack
	while( true )
	{
		goAlongLeftBranch( x, S );
		if( S.empty() ) break;
		x = S.pop();
		visit ( x->data );
		x = x->rc;
	}
}

template <typename T, typename VST>
void travIn_I2 (BinNodePosi(T) x, VST& visit)//迭代版中序遍历 
{
	Stack<BinNodePosi(T)> S;//support stack
	while( true )
	
		if( x ){
			S.push( x );
			x = x->lc;
		} else if( !S.empty() ){
			x = S.pop();
			visit( x->data );
			x = x->rc;
		} else 
			break;
	
}

template <typename T, typename VST>
void travIn_I3 (BinNodePosi(T) x, VST& visit)//迭代版中序遍历 
{
	bool backtrack = false;
	while( true )
		if( !backtrack && HasLChild( *x ) )
			x = x->lc;
		else{
			visit(x->data);
			if(HasRChild(*x)){
				x = x->rc;
				backtrack = false;
			}else{
				if(!(x = x->succ())) break;
				backtrack = true;
			}
		}
}


template <typename T>
static void gotoHLVFL (Stack<BinNodePosi(T)>& S) 
{
	while( BinNodePosi(T) x = S.top())
		if( HasLChild( *x )){
			if( HasRChild( *x ) ) S.push( x->rc );
			S.push( x->lc );
		} else
			S.push( x->rc );
	S.pop();
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST& visit){
	Stack<BinNodePosi(T)> S;
	if( x ) S.push( x );
	while( !S.empty( ) ){
		if(S.top()!=x->parent)
			gotoHLVFL( S );
		x = S.pop(); visit( x-> data);
	}
}

template <typename T> template<typename VST>
void BinNode<T>::travLevel( VST& visit ){
	Queue<BinNodePosi(T)> Q;
	Q.enqueue( this );
	while( !Q.empty()){
		BinNodePosi(T) x = Q.dequeue();
		visit(x->data);
		if(HasLChild (*x))
			Q.enqueue( x->lc );
		if(HasRChild(*x))
			Q.enqueue( x->rc );
	}
}




