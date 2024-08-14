//实现哈希
#include "HashTable.h"
 
//构造函数
//哈希表：底层维护的两个空间一个是存储当前字符下标的head指向的空间，另一个是存储哈希冲突的空间
//prev指向的空间。
HashTable::HashTable()
:_prev(new ush[2 * WSIZE])
,_head(_prev+WSIZE)
{
	memset(_prev, 0,sizeof(ush)* 2 * WSIZE);
}
 
//析构函数
HashTable::~HashTable()
{
	delete[] _prev;
	_prev = _head = nullptr;
}
 
// hashAddr: 上一个字符串计算出的哈希地址
// ch：当前字符
// 本次的哈希地址是在前一次哈希地址基础上，再结合当前字符ch计算出来的
// HASH_MASK为WSIZE-1，&上掩码主要是为了防止哈希地址越界
void HashTable::HashFunc(ush& hashAddr, uch ch) 
{
	hashAddr = (((hashAddr) << H_SHIFT()) ^ (ch)) & HASH_MASK;
}
ush HashTable::H_SHIFT()
{
	return (HASH_BITS + MIN_MATCH - 1) / MIN_MATCH;
}
 
//插入：
// hashAddr：上一次哈希地址 
//ch：当前要插入的三个字符的第三个字符，因为我们将上一个哈希地址传入，那么上一个哈希地址的计算是通过当前三个
//字符的前两个字符和上一个三个字符的第一个字符计算得出，那么这里我们只需要将当前的三个字符的最后一个字符传入
//然后计算出当前三个字符的哈希地址即可。//那假如要插入的字符串是第一个字符串那么第一个哈希地址从哪里来？？？？？
// pos：当前三个字符的首字符的地址。
//matchHead：如果匹配，保存上一个在存储在当前哈希地址的三个元素的首地址。例如当前三号位置保存的是19当前要插入3号位置的
//三个字符串首地址是24那么macthhead保存的就是19。//这里为啥要保存？？？？？？？？？？？因为这里要在后面文件压缩的时候
//获取macthHead通过判断macthHead是否为0判断当前字符串是否有匹配串。
void HashTable::InsertString(ush& hashAddr, uch ch, ush pos, ush& macthHead)
{
	//1.计算当前要插入的三个字符串的哈希地址：
	HashFunc(hashAddr, ch);
	//2.将hashaddr位置存储的前文中的匹配字符串的位置搬移到prev的pos的位置
	_prev[pos & HASH_MASK] = _head[hashAddr];
	//3.保存当前将前文中找到的最近一个匹配串通过macthhead带出去
	macthHead = _head[hashAddr];///这里取hashaddr中的macthhead的时候要不要给macthead与上掩码？？？？？？？？？？？？这里其实不用与因为我们在获取上一个match的时候就对macthhead与掩码处理过。
	//4.将当前哈希地址存入当前字符串的首地址
	_head[hashAddr] = pos;
}
 
ush HashTable::GetPrevMatch(ush &MathcHead)
{
	MathcHead = _prev[MathcHead & HASH_MASK];
	return MathcHead;
}
//将数据搬移之后我们需要将哈希表更新：因为右窗的数据都搬移到了左窗那么此时哈希表中存放的地址都改变了
//所以我们需要将哈希表中的每个地址都减去WSIZE，对于哈希表中小于WSIZE的数据就相当于被覆盖了属于无效地址
//那么我们就将其置为0
void HashTable::updatahash()
{
	//更新head
	for (ush i = 0; i < HASH_SIZE; i++)
	{
		if (_head[i] < WSIZE)
		{
			_head[i] = 0;
		}
		else
		{
			_head[i] -= WSIZE;
		}
	}
	//更新prev
	for (ush i = 0; i < HASH_SIZE; i++)
	{
		if (_prev[i] < WSIZE)
		{
			_prev[i] = 0;
		}
		else
		{
			_prev[i] -= WSIZE;
		}
	}
}