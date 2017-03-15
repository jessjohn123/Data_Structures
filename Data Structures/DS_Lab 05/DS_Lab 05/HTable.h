#pragma once
#include "SLList.h"
template<typename Type>
class HTable
{
private:
	unsigned int (*m_hash)(const Type &v);
	unsigned int buckets;
	SLList<Type>*arr;
public:
	HTable(unsigned int numOfBuckets, unsigned int(*hfunction) (const Type &v));
	~HTable();
	HTable<Type>& operator=(const HTable<Type>& that);
	HTable(const HTable<Type>& that);
	void insert(const Type& v);
	bool findAndRemove(const Type& v);
	void clear();
	int find(const Type& v) const;
};

template<typename Type>
HTable <Type>::HTable(unsigned int numOfBuckets, unsigned int(*hfunction) (const Type &v))
{
	buckets = numOfBuckets;
	m_hash = hfunction;
	arr = new SLList<Type>[numOfBuckets];
}

template<typename Type>
HTable<Type>::~HTable()
{
	delete[]arr;
}
template<typename Type>
HTable <Type>::HTable(const HTable<Type>& that)
{
	buckets = that.buckets;
	m_hash = that.m_hash;
	arr = new SLList<Type>[buckets];
	for (unsigned int i = 0; i < buckets; i++)
	{
		arr[i] = that.arr[i];
	}
}

template<typename Type>
HTable<Type>& HTable<Type>::operator=(const HTable<Type>& that)
{
	if (this != &that)
	{
		delete[] arr;
		buckets = that.buckets;
		m_hash = that.m_hash;
		arr = new SLList<Type>[buckets];
		for (unsigned int i = 0; i < buckets; i++)
		{
			arr[i] = that.arr[i];
		}

	}
	return *this;
}

template<typename Type>
void HTable<Type>::insert(const Type& v)
{
	arr[m_hash(v)].addHead(v);
}

template<typename Type>
int HTable<Type>::find(const Type& v) const
{
	 arr[m_hash(v)];
	 int num = m_hash(v);
	SLLIter<Type> iter(arr[m_hash(v)]);
	for (iter.begin(); !iter.end(); iter.operator++())
	{
		if (iter.current() == v)
			return num;
	}
		return -1;
}

template<typename Type>
bool HTable<Type>::findAndRemove(const Type& v)
{
	SLLIter<Type> iter(arr[m_hash(v)]);
	for (iter.begin(); !iter.end(); iter.operator++())
	{
		if (iter.current() == v)
		{
			arr[m_hash(v)].remove(iter);
			return true;
		}
	}
		return false;
}

template<typename Type>
void HTable<Type>::clear()
{
	for (unsigned int i = 0; i < buckets; i++)
	{
		arr[i].clear();
	}

}