#pragma once
template<typename Type> class DLLIter;
template <typename Type>
class DLList
{
private:
	friend class DLLIter < Type > ;
	struct DListNode
	{
		DListNode(const Type& _data, DListNode* _prev = nullptr, DListNode* _next = nullptr) :data(_data), next(_next), prev(_prev){}
		Type data;
		DListNode *next;
		DListNode *prev;
	};
	DListNode *head;
	DListNode *tail;
	unsigned int count;
public:
	DLList();
	~DLList();
	DLList<Type>& operator=(const DLList<Type>& that);
	DLList(const DLList<Type>& that);
	void addHead(const Type& v);
	void addTail(const Type& v);
	void clear();
	void insert(DLLIter<Type>& index, const Type& v);
	void remove(DLLIter<Type>& index);
};

template<typename Type>
class DLLIter
{
private: 
	friend class DLList < Type > ;
	typename DLList<Type> *info;
	typename DLList<Type>::DListNode *curr;
public:
	DLLIter(DLList<Type>& listToIterate);
	void beginHead();
	void beginTail();
	bool end() const;
	DLLIter<Type>& operator++();
	DLLIter<Type>& operator--();
	Type& current() const;
};


template<typename Type>
DLList<Type> ::DLList()
{
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template<typename Type>
DLList<Type> ::~DLList()
{
	clear();
}

template<typename Type>
DLList<Type>::DLList(const DLList<Type>& that)
{
	head = nullptr;
	tail = nullptr;

	if (that.head != nullptr)
	{
		//addHead(that.head->data);
		DListNode* temp = that.head;
		while (temp != nullptr)
		{
			addTail(temp->data);
			temp = temp->next;
		}
	}
}

template<typename Type>
DLList<Type>& DLList<Type>::operator=(const DLList<Type>& that)
{
	if (this != &that)
	{
		clear();

		if (that.head != nullptr)
		{
			//addHead(that.head->data);
			DListNode* temp = that.head;
			while (temp != nullptr)
			{
				addTail(temp->data);
				temp = temp->next;
			}
		}
	}
	return *this;
}

template<typename Type>
void DLList<Type>::addHead(const Type& v)
{
	if (head != nullptr && tail != nullptr)
	{
		DListNode *newnode = new DListNode(v, nullptr, head);
		head->prev = newnode;
		newnode->next = head;
		newnode->prev = nullptr;
		head = newnode;

	}
	else
	{
		DListNode* newnode = new DListNode(v, nullptr, head);
		head = tail = newnode;
	}
	count++;
}

template<typename Type>
void DLList<Type>::addTail(const Type& v)
{
	if (head != nullptr && tail != nullptr)
	{
		DListNode *newnode = new DListNode(v, tail, nullptr);
		tail->next = newnode;
		newnode->prev = tail;
		newnode->next = nullptr;
		tail = newnode;
	}
	else
	{
		DListNode* newnode = new DListNode(v, tail, nullptr);
		tail = head = newnode;
	}
	count++;
}

template<typename Type>
void DLList<Type>::clear()
{
	/*DListNode* newnode = new DListNode;
	while (head != nullptr)
	{
		newnode = head->next;
		delete head;
		head = node;
		if (head == nullptr)
			tail == nullptr;
	}*/
	while (head != nullptr)
	{
		DListNode *newnode = head;
		head = newnode->next;
		delete newnode;
	}
	head = tail = nullptr;
	count = 0;
}

template<typename Type>
void DLList <Type>::insert(DLLIter<Type>& index, const Type& v)
{
	if (index.curr == nullptr)
	{
		return;
	}
	else //(index.curr != nullptr)
	{

		if (index.curr == head)
		{
			addHead(v);
			index.curr = head;
		}
		else if(index.curr != head || index.curr != tail)
		{
			DListNode* newnode = new DListNode(v, index.curr->prev, index.curr);
			/*newnode->next = index.curr;
			newnode->prev = index.curr->prev;*/
			index.curr->prev->next = newnode;
			index.curr->prev = newnode;
			index.curr = newnode;
		}
		count++;
	}	
}

template<typename Type>
void DLList <Type>::remove(DLLIter<Type>& index)
{
	if (index.curr == nullptr)
	{
		return;
	}
	else
	{
		if (index.curr != head && index.curr != tail)
		{
			DListNode *temp = index.curr;
			index.curr->prev->next = index.curr->next;
			index.curr->next->prev = index.curr->prev;
			index.curr = index.curr->next;
			delete temp;
		}
		else if (index.curr == head && index.curr == tail)
		{
			head = nullptr;
			tail = nullptr;
			delete index.curr;
			index.curr = head;
		}
		else if (index.curr == head)
		{
			head = index.curr->next;
			delete index.curr;
			if (head)
				head->prev = nullptr;
			index.curr = head;
		}
		else if (index.curr == tail)
		{
			tail = index.curr->prev;
			delete index.curr;
			if (tail)
				tail->next = nullptr;
			index.curr = tail;
		}
		count--;
	}
}

template<typename Type>
DLLIter <Type>::DLLIter(DLList<Type>& listToIterate)
{
	info = &listToIterate;
}

template<typename Type>
void DLLIter <Type>::beginHead()
{
	curr = info->head;
}

template<typename Type>
void DLLIter <Type>::beginTail()
{
	curr = info->tail;
}

template<typename Type>
bool DLLIter<Type>::end() const
{
	if (curr == nullptr)

		return true;
	else
		return false;
}

template<typename Type>
DLLIter<Type>& DLLIter<Type>::operator++()
{
	if (curr)
	{
		curr = curr->next;
	}

	return *this;
}

template<typename Type>
DLLIter<Type>& DLLIter<Type>::operator--()
{
	if (curr)
	{
		curr = curr->prev;
	}
	return *this;
}

template<typename Type>
Type& DLLIter<Type>::current() const
{
	return curr->data;
}