
//对词条的操作
template<typename K, typename V> struct Dictionary
{
	virtual int size() const = 0;   //返回当前词条总数
	virtual bool put(K k, V v) = 0;  //插入词条
	virtual V* get(K k) = 0;       //读取指定词条的数据项
	virtual bool remove(K k) = 0;    //删除词条
};
