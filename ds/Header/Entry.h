
 
//词条类
template<typename K, typename V> struct entry
{
	K key;      //关键码
	V value;    //数据项
 
	//构造函数
	entry(K k = K(), V v = V()) :key(k), value(v) {}   
	entry(const entry<K, V>& e) :key(e.key), value(value) {}
	bool operator<(const entry<K, V>& e);
	bool operator>(const entry<K, V>& e);
	bool operator==(const entry<K, V>& e);
	bool operator!=(const entry<K, V>& e);
};
 
template<typename K, typename V> bool entry<K,V>::operator<(const entry<K, V>& e)
{
	return this->key < e.key;
}
 
template<typename K, typename V> bool entry<K, V>::operator>(const entry<K, V>& e)
{
	return this->key > e.key;
}
 
template<typename K, typename V> bool entry<K, V>::operator==(const entry<K, V>& e)
{
	return this->key == e.key;
}
 
template<typename K, typename V> bool entry<K, V>::operator!=(const entry<K, V>& e)
{
	return this->key != e.key;
}
