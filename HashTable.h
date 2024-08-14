//用来声明哈希
 
#include "common.h"
 
//哈希表：底层维护的两个空间一个是存储当前字符下标的head指向的空间，另一个是存储哈希冲突的空间
//prev指向的空间。
class HashTable
{
public:
	HashTable();
	~HashTable();
	//插入：
	void InsertString(ush& hashAddr, uch ch, ush pos, ush& macthHead);
	//获取前一个匹配串
	ush GetPrevMatch(ush &MathcHead);
	//更新哈希表：
	void updatahash();
private:
	//哈希函数：
	void HashFunc(ush& hashAddr, uch ch);
	ush H_SHIFT();
 
	ush* _prev;
	ush* _head;
	// 哈希桶的个数为2^15=32*1024:就是head或者prev空间的大小
	const ush HASH_BITS = 15;
	// 哈希表的大小=32K
	const ush HASH_SIZE = (1 << HASH_BITS);
	// 哈希掩码：主要作用是将右窗数据往左窗搬移时，用来更新哈希表中数据
	//当文件超过32k才会用到
	const ush HASH_MASK = HASH_SIZE - 1;
};