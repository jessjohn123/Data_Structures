#pragma once
#include "DynArray.h"
template<typename Type> 
class BinaryHeap : protected DynArray<Type>
{

public:
	void enqueue(const Type &v);
	Type dequeue();
	Type& operator[] (int index);
	void clear();
	unsigned int size();

};

/////////////////////////////////////////////////////////////////////////////
// Function : enqueue
// Parameters : v - the item to add to the heap
// Notes : after the new item is added, this function ensures that the 
//	smallest value in the heap is in [0]
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void BinaryHeap <Type>::enqueue(const Type &v)
{
	this->append(v);
	for (unsigned int i = this->size() - 1 ; i > 0;)
	{
		if (this->arr[i] < this->arr[(i - 1)/ 2])
		{
			swap(this->arr[i], this->arr[(i - 1)/ 2]);
			i = (i - 1) / 2;//if(arr[i] < i -1 /2
			//i++;
		}
		else
		{
			break;
		}

	}
}

template<typename Type>
Type BinaryHeap <Type>::dequeue()
{
	if (arr_size)
	{
		Type returning = arr[0];
		arr_size--;
		arr[0] = arr[arr_size];
		unsigned curr = 0, left, right;
		while (curr < arr_size)
		{
			left = (curr << 1) + 1;
			right = left + 1;
			if (left >= arr_size)
				return returning;
			if (right < arr_size)
				if (arr[left] > arr[right]) left = right;
			if (arr[left] < arr[curr])
			{
				swap(arr[left], arr[curr]);
				curr = left;
			}
			else
				return returning;
		}
		//for (unsigned int i = 0; i < arr_size; i++)
		//{
		//	if ((arr[i * 2 + 1] < arr[i * 2 + 2]) && (arr[i] > arr[i * 2 + 1]))
		//	{
		//		swap(arr[i], arr[i * 2 + 1]);
		//		//arr[i] = arr[i * 2 + 1];
		//		i = i * 2 + 1;
		//	}
		//	else if ((arr[i * 2 + 2] < arr[i * 2 + 1]) && (arr[i] > arr[i * 2 + 2]))
		//	{
		//		swap(arr[i], arr[i * 2 + 2]);
		//		//arr[i] = arr[i * 2 + 2];
		//		i = i * 2 + 2;
		//	}
		//	if (i > size())
		//	{
		//		break;
		//	}
		//	if (i * 2 + 2 > size())
		//	{
		//		break;
		//	}
		//	if (i * 2 + 1 > size())
		//	{5
		//		break;
		//	}
		//}
		return returning;
	}
	else
		return Type();
}

template<typename Type>
//Type& DynArray<Type>::operator[](const unsigned int index)
Type& BinaryHeap<Type>::operator[](int index)
{
	return DynArray<Type>::operator[](index);
}


template<typename Type>
void BinaryHeap <Type>::clear()
{
	DynArray<Type>::clear();
}

template<typename Type>
unsigned int BinaryHeap<Type>::size()
{
	return arr_size;
}