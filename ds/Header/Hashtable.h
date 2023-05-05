#include "Dictionary.h"
#include "Bitmap.h"
#include "Entry.h"

typedef int Rank; //秩
static size_t hashCode ( char c ) { return ( size_t ) c; } //字符
static size_t hashCode ( int k ) { return ( size_t ) k; } //整数以及长长整数
static size_t hashCode ( long long i ) { return ( size_t ) ( ( i >> 32 ) + ( int ) i ); }
static size_t hashCode ( char s[] ) { //生成字符串的循环移位散列码（cyclic shift hash code）
   int h = 0; //散列码
   for ( size_t n = strlen ( s ), i = 0; i < n; i++ ) //自左向右，逐个处理每一字符
      { h = ( h << 5 ) | ( h >> 27 ); h += ( int ) s[i]; } //散列码循环左移5位，再累加当前字符
   return ( size_t ) h; //如此所得的散列码，实际上可理解为近似的“多项式散列码”
} //对于英语单词，"循环左移5位"是实验统计得出的最佳值


template <typename K, typename V>
class Hashtable:public Dictionary<K,V>
{
private:
	entry<K,V>** ht;
	int M;
	int N;
	Bitmap* lazyRemoval;
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval ->set(x))
protected:
	int probe4Hit( const K& k );
	int probe4Free (const K& k);
	void rehash();
public:
	Hashtable( int c = 5 );
	~Hashtable();
	int size() const{return N;}
	bool put(K, V);
	V* get(K k);
	bool remove(K k);
		
};
template <typename T>
void releases(T& e) {
	e = NULL;
}

int primeNLT ( int c, int n, char* file ) { //根据file文件中的记录，在[c, n)内取最小的素数
   Bitmap B ( file, n ); //file已经按位图格式，记录了n以内的所有素数，因此只要
   while ( c < n ) //从c开始，逐位地
      if ( B.test ( c ) ) c++; //测试，即可
      else return c; //返回首个发现的素数
   return c; //若没有这样的素数，返回n（实用中不能如此简化处理）
}

template <typename K, typename V> Hashtable<K,V>::Hashtable(int c)
{
	char text[] = "../data/_prime.txt";
	char* ch = text;
 
 
    M = primeNLT ( c, 104729, ch ); //不小于c的素数M
    N = 0; ht = new entry<K, V>*[M]; //开辟桶数组（假定成功

	memset(ht,0,sizeof(entry<K,V>*) *M);
	lazyRemoval = new Bitmap(M);
}

template <typename K,typename V> Hashtable<K,V>::~Hashtable()
{
	for(int i=0;i<M;i++)
	{
		if(ht[i])
			releases(ht[i]);
	}
	releases( ht );
	releases( lazyRemoval );
//	delete[] lazyRemoval;
}

template <typename K, typename V>
V* Hashtable<K,V>::get(K k)
{
	int r = probe4Hit(k);
	return ht[r] ?& (ht[r]->value) :NULL; 
}
template <typename K, typename V>
int Hashtable<K,V>::probe4Hit(const K& k)
{
	int r = hashCode(k) % M;
	while( (ht[r]&&(k!= ht[r]->key))||(!ht[r] && lazilyRemoved(r)))
		r = (r + 1) % M;
	return r;
}
template <typename K, typename V>
int Hashtable<K,V>::probe4Free(const K& k)
{
	int r = hashCode(k) % M;
	while(ht[r])
		r = (r + 1) % M;
	return r;
}
template <typename K, typename V>
bool Hashtable<K,V>::remove(K k)
{
	int r = probe4Hit(k);
	if(!ht[r])
		return false;
	releases( ht[r]);
	ht[r] = NULL;
	markAsRemoved(r);
	N--;
	return true;
}

template <typename K, typename V> bool Hashtable<K, V>::put( K k, V v ) { //散列表词条插入
	if ( ht[ probe4Hit( k ) ] ) return false; //雷同元素不必重复插入
	Rank r = probe4Free( k ); //为新词条找个空桶（只要装填因子控制得当，必然成功）
	ht[ r ] = new entry<K, V>( k, v ); ++N; //插入
	if ( N *2 > M ) rehash(); //若装填因子高于50%，重散列
return true;
}
template <typename K, typename V>
void Hashtable<K,V>::rehash()
{
	char text[] = "../data/_prime.txt";
	char* ch = text;
	int old_capacity = M;
	entry<K,V>** old_ht = ht;
	M = primeNLT(2*M, 104729,ch);
	N = 0; ht = new entry<K,V>*[M];
	memset(ht, 0, sizeof(entry<K,V>*) *M);
	releases(lazyRemoval);
//	delete[] lazyRemoval;
	lazyRemoval = new Bitmap (M);
	for(int i = 0; i < old_capacity; i++)
		if( old_ht[i] )
			put(old_ht[i]->key,old_ht[i]->value);
	releases(old_ht);
//	delete old_ht;
}





