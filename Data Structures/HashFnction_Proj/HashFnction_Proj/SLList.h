#pragma once
template<typename Type> class SLLIter;
template <typename Type>
class SLList
{
private:
	friend class SLLIter < Type > ;
	struct SListNode
	{
		SListNode() :next(nullptr){}
		SListNode(const Type& _data, SListNode* _next = nullptr) :data(_data), next(_next){}
		Type data;
		SListNode *next;
	};
	SListNode *head;
	unsigned int count;
public:
	SLList();
	~SLList();
	SLList<Type>& operator=(const SLList<Type>& that);
	SLList(const SLList<Type>& that);
	void addHead(const Type& v);
	void clear(); void insert(SLLIter<Type>& index, const Type& v);
	void remove(SLLIter<Type>& index);
	inline unsigned int size() const { return count; }
};

template<typename Type>
class SLLIter
{
private:
	friend class SLList < Type > ;  // helps in accessing the private data members of SLIST
	typename SLList<Type> *createList;
	typename SLList<Type>::SListNode *prev;
	typename SLList<Type>::SListNode *curr;
public:
	SLLIter(SLList<Type>& listToIterate);
	void begin();
	bool end() const; SLLIter<Type>& operator++();
	Type& current() const;
};

template<typename Type>
SLList<Type>::SLList(const SLList<Type>& that)
{
	SListNode* newnode = that.head;
	SListNode* thisnode = 0;
	head = thisnode;
	count = that.count;
	if (newnode)
	{
		thisnode = new SListNode(newnode->data);
		newnode = newnode->next;
		head = thisnode;
		while (newnode)
		{
			thisnode->next = new SListNode(newnode->data);
			newnode = newnode->next;
			thisnode = thisnode->next;
		}
	}
}

template<typename Type>
SLList<Type>::SLList()
{
	head = nullptr;
	count = 0;
}

template<typename Type>
SLList<Type>::~SLList()
{
	clear();
}

template<typename Type>
SLList<Type>& SLList<Type>::operator=(const SLList<Type>& that)
{
	if (this != &that)
	{
		clear();
		SListNode* newnode = that.head;
		SListNode* thisnode = 0;
		head = thisnode;
		count = that.count;
		if (newnode)
		{
			thisnode = new SListNode(newnode->data);
			newnode = newnode->next;
			head = thisnode;
			while (newnode)
			{
				thisnode->next = new SListNode(newnode->data);
				newnode = newnode->next;
				thisnode = thisnode->next;
			}
		}

	}
	return *this;
}

template<typename Type>
void SLList<Type>::addHead(const Type & v)
{
	//creating a new node
	SListNode* newnode = new SListNode;
	newnode->data = v;
	//making the newnode point to the next node
	newnode->next = head;
	//make the previous node point to the new node
	head = newnode;
	count++;
}

template<typename Type>
void SLList<Type>::clear()
{
	while (head != nullptr)
	{
		// create temporary node
		SListNode* newnode = head;
		//save the pointer to the next node
		head = newnode->next;
		//delete the current node
		delete newnode;
	}
	//update the count
	count = 0;
}

template<typename Type>
void SLList<Type>::insert(SLLIter<Type>& index, const Type& v)
{
	if (index.curr != nullptr)
	{

		if (index.curr == head)
		{
			SListNode* newnode = new SListNode;
			newnode->data = v;
			newnode->next = head;
			head = newnode;
			index.curr = newnode;
		}

		else
		{
			SListNode* newnode = new SListNode;
			newnode->next = index.curr;
			index.prev->next = newnode;
			newnode->data = v;
			index.curr = newnode;
		}


		count++;
	}
}

template<typename Type>
void SLList<Type>::remove(SLLIter<Type>& index)
{
	if (index.curr != nullptr)
	{
		if (index.prev == nullptr)
		{
			head = head->next;
			delete index.curr;
			index.curr = head;
		}
		else
		{
			index.prev->next = index.curr->next;
			delete index.curr;
			index.curr = index.prev->next;
		}
		count--;
	}
}



template<typename Type>
SLLIter <Type>::SLLIter(SLList<Type>& listToIterate)
{
	createList = &listToIterate;
}

template<typename Type>
void SLLIter <Type>::begin()
{
	curr = createList->head;
	prev = nullptr;
}

template<typename Type>
bool SLLIter <Type>::end() const
{
	return !curr;
	 
}

template<typename Type>
SLLIter <Type>& SLLIter<Type>::operator++()
{
	if (curr)
	{
		prev = curr;
		curr = curr->next;
	}
	return *this;
}


template<typename Type>
Type& SLLIter<Type>::current() const
{
	return curr->data;
}