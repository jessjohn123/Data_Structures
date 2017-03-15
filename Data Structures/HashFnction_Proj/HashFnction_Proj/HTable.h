#pragma once
#include "SLList.h"
using namespace std;

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
	void printSomeStuff(const char* tilePath = "hashdata.txt");
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

template<typename Type>
void HTable<Type>::printSomeStuff(const char* filePath = "hashdata.txt")
{
	ofstream outFile(filePath);

	if (outFile.is_open())
	{
		unsigned int empty = 0;
		unsigned int totalCount = 0;
		unsigned int loIndex = 0;

		unsigned int hiIndex = 0;

		for (unsigned int i = 0; i < buckets; ++i)
		{
			totalCount += arr[i].size();
			outFile << i << " : " << arr[i].size() << '\n';
			if (arr[i].size() == 0)
				++empty;

			if (arr[i].size() < arr[loIndex].size())
				loIndex = i;
			else if (arr[i].size() > arr[hiIndex].size())
				hiIndex = i;
		}

		outFile << '\n' << totalCount << " Total items stored in " << buckets << " buckets\n";
		outFile << '\n' << empty << " Buckets are empty\n\n";

		unsigned int Low = arr[loIndex].size();
		unsigned int range = arr[hiIndex].size() - Low + 1;

		outFile << "each bucket contains between " << Low << " and " << Low + range - 1 << " items.\n\n";

		unsigned int* arr_wds = new unsigned int[range];
		for (unsigned int j = 0; j < range; ++j)
			arr_wds[j] = 0;

		for (unsigned int k = 0; k < buckets; ++k)
			++arr_wds[arr[k].size() - Low];

		for (unsigned int p = 0; p < range; ++p)
			outFile << arr_wds[p] << " buckets have " << p + Low << " items\n";

		delete[] arr_wds;
	}
}

