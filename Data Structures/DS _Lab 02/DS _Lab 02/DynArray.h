#pragma once
template<typename Type>
class DynArray
{
protected:
	unsigned int arr_size;
	unsigned int arr_capacity;
	Type* arr;

public:
	Type Getarr(int a) { return arr = a; }
	DynArray();
	~DynArray();
	DynArray(const DynArray<Type> & that);
	DynArray<Type>& operator=(const DynArray<Type>& that);
	Type& operator[] (const unsigned int index);
	const Type& operator[] (const unsigned int index) const;
	unsigned int size() const;
	unsigned int capacity() const;
	void clear();
	void append(const Type& item);
	void reserve(const unsigned int & newCap = 0);

};

template<typename Type>
DynArray <Type>::DynArray()
{
	arr = nullptr;
	arr_size = 0;
	arr_capacity = 0;

}

template<typename Type>
DynArray <Type>::~DynArray()
{
	clear();
}

template<typename Type>
DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& that)
{
	if (this != &that)
	{
		clear();
		for (unsigned int i = 0; i < that.arr_size; i++)
		{
			append(that.arr[i]);
		}
	}
	return *this;
}
template<typename Type>
DynArray <Type>::DynArray(const DynArray<Type>& that)
{
	arr_size = 0;
	arr_capacity = 0;
	arr = nullptr;
	for (int i = 0; i < that.arr_size; i++)
	{
		append(that.arr[i]);
	}
}

template<typename Type>
Type& DynArray<Type>::operator[](const unsigned int index)
{
	return arr[index];
}

template<typename Type>
const Type& DynArray <Type>::operator[](const unsigned int index)const
{
	return arr[index];
}

template<typename Type>
unsigned int DynArray <Type>::size()const
{
	return arr_size;
}

template<typename Type>
unsigned int DynArray <Type> ::capacity() const
{
	return arr_capacity;
}

template<typename Type>
 void DynArray <Type>::clear()
{
	 if (arr)
	 {
		delete[] arr;
		arr = nullptr;
	 }
	arr_size = 0;
	arr_capacity = 0;
}

template<typename Type>
void DynArray <Type>::append(const Type& item)
{
	// if the capacity is 0; set the capacity to 1
	if (arr_capacity == 0)
	{
		arr_capacity += 1;
		///creating new arr(assigning the capacity)
		arr = new Type[arr_capacity];
		//setting the first subindex to the data
		arr[0] = item;
		arr_size++;
	}
	//when the size and capacity are same, expand the capacity before resizing
	else if (arr_size == arr_capacity)
	{
		//in order not to generate an error in while resizing, 
		//its safe to create a temp variable to whom we assign our data of old array before overwriting the new 
		//assigning old data the new temporary variable
	Type* temp = new Type[arr_capacity];
	for (unsigned int i = 0; i < arr_size; i++)
	{
		temp[i] = arr[i];
	}
	// free the memory created for the old array
	delete[] arr;
	//doubling the capacity
	arr_capacity *= 2;
	//creating new array
	arr = new Type[arr_capacity];
	//assigning the previous plus new elements into the arr by restoring the data from the temp
	for (unsigned int i = 0; i < arr_size; i++)
	{
		arr[i] = temp[i];
	}
	arr[arr_size] = item;
	arr_size++;
	// free the memory created for the temp array
	delete[] temp;
	}
	else
	{
		arr[arr_size] = item;
		arr_size++;
	}
}

template<typename Type>
 void DynArray<Type>::reserve(const unsigned int & newCap = 0)
{
	 if (!newCap && !arr_capacity)
	 {
		 //this temporary array will hold the resized array before deleting the old array
		 Type* temp = new Type[arr_capacity];
		 for (int i = 0; i < arr_size; i++)
		 {
			 temp[i] = arr[i];
		 }
		 delete[] arr;
		 arr_capacity = 1;

		 arr = new Type[arr_capacity];

		 for (int i = 0; i < arr_size; i++)
		 {
			 // new array is assigned to the old pointer
			 arr[i] = temp[i];
		 }
		 delete[] temp;
	 }
	else if (newCap == 0)
	{
		Type* temp = new Type[arr_capacity];
		for (int i = 0; i < arr_size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr_capacity *= 2;

		arr = new Type[arr_capacity];

		for (int i = 0; i < arr_size; i++)
		{
			arr[i] = temp[i];
		}
		delete[] temp;
	}

	else if (newCap > arr_capacity)
	{
		Type* temp = new Type[arr_capacity];
		for (int i = 0; i < arr_size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr_capacity = newCap;
		arr = new Type[arr_capacity];

		for (int i = 0; i < arr_size; i++)
		{
			arr[i] = temp[i];
		}
		delete[] temp;
	}
	if (newCap < arr_capacity)
	{
		return;
	}
}

 /*template <typename Type>
 void DynArray<Type>::remove(const unsigned int index)
 {
	 for (int i = 0; i < arr_size; i++)
	 {
		 if (arr[i] == index)
			 continue;
		 temp[i] = arr[i];
	 }
	 delete[] arr;

	 arr = new Type[arr_capacity];
	 
	 for (int i = 0; i < arr_size; i++)
	 {
		 arr[i] = temp[i];
	 }
 }*/

