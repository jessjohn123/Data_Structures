#pragma once
template<typename Type>
class BST
{
private:
	struct BSTNode
	{
		BSTNode(const Type& _data, BSTNode* _left = nullptr, BSTNode *_right = nullptr) :data(_data), left(_left), right(_right){}

		Type data;
		BSTNode *left, *right;
	};
	BSTNode *root;
	//unsigned int count;
public:
	BST();
	~BST();
	BST& operator=(const BST& that);
	BST(const BST& that);
	void insert(const Type& v);
	bool findAndRemove(const Type& v);
	bool find(const Type& v)const;
	void clear();
	void printInOrder()const;
	void inorder(const BSTNode*)const;
	void printPreOrder() const;
	void preorder(const BSTNode*);
	//void printPostOrder() const;
	void postorder(const BSTNode*)const;
	bool isEmpty() const { return root == nullptr; }

};

template<typename Type>
BST<Type>::BST(const BST<Type>& that)
{
	root = nullptr;
	clear();
	preorder(that.root);
}

template<typename Type>
BST<Type>& BST<Type>::operator=(const BST<Type>& that)
{
	if (this != &that)
	{
		preorder(that.root);
	}
	return *this;
}

template<typename Type>
BST<Type>::BST()
{
	root = nullptr;
}

template<typename Type>
BST<Type>::~BST()
{
	clear();
}


template<typename Type>
void BST<Type>::insert(const Type& v)
{
	BSTNode *curr;
	BSTNode *temp = new BSTNode(v, nullptr, nullptr);
	if (isEmpty()) 
	{
		root = temp;
	}
	else
	{
		curr = root;
		if (curr->left == nullptr && v < curr->data)
		{
			curr->left = temp;
		}
		if (curr->right == nullptr && v > curr->data)
		{
			curr->right = temp;
		}

		while (curr->data > v)
		{
			if (curr->left == nullptr)
			{
				curr->left = temp;
				curr = temp;
				return;
			}
			else
			{
				curr = curr->left;
			}
		}
		while (curr->data < v)
		{
			if (curr->right == nullptr)
			{
				curr->right = temp;
				curr = temp;
				return;
			}
			else
			{
				curr = curr->right;
			}
			if (curr->left == nullptr && curr->data > v)
			{
				curr->left = temp;
				curr = temp;
				return;
			}
			while (curr->data > v)
			{
				if (curr->left == nullptr)
				{
					curr->left = temp;
					curr = temp;
				}
				else
				{
					curr = curr->left;
				}
			}
		}
	}
}

template<typename Type>
bool BST<Type>::find(const Type& v)const
{
	BSTNode* temp = root;
	while (temp != NULL)
	{
		if (temp->data == v)
		{
			//cout << "BST contains this node\n";
			return true;
		}
		if (v > temp->data)
			{
				temp = temp->right;
				if (temp == nullptr)
				{
					return false;
				}
			}
		if (v < temp->data)
			{
				temp = temp->left;
				if (temp == nullptr)
				{
					return false;
				}
			}
		
	}
	//cout << "BST does not contain this node\n";
	return false;
}

template<typename Type>
bool BST<Type>::findAndRemove(const Type& v)
{
	BSTNode *curr = root;
	BSTNode *parent;
	
	while (curr)
	{
		if (curr->data == v)
		{
			break;
		}
		else
		{
			parent = curr;
			curr = v > curr->data ? curr->right : curr->left;
		}
	}

	if (curr == nullptr)
	{
		return false;
	}

	//3 cases:
	//1. we are removing a leaf node
	// 2. we are removing a node with a single child
	//3. we are removing a node with 2 children

	//we are looking at a leaf node
	if (curr->left == nullptr && curr->right == nullptr)
	{
		if (curr == root)
		{
			root = nullptr;
		}
		else if (parent->left == curr)
			parent->left = nullptr;
		else
			parent->right = nullptr;
		delete curr;
		return true;
	}
	// Node with single child
	if ((curr->left == nullptr && curr->right != nullptr)||(curr->left != nullptr && curr->right == nullptr)) 
	{
		if (curr->left == nullptr && curr->right != nullptr) 
		{
			if (curr == root)
			{
				root = curr->right;
			}
			else if (parent->left == curr) 
			{
				parent->left = curr->right;
			}
			else 
			{
				parent->right = curr->right;
			}
		}
		else { // left child present, no right child

			if (curr == root)
			{
				root = curr->left;
			}
			else if (parent->left == curr) 
			{
				parent->left = curr->left;
			}
			else 
			{
				parent->right = curr->left;
			}
		}
		delete curr;
		return true;
	}
	
	// Node with 2 children
	// replace node with smallest value in right subtree
	if (curr->left != nullptr && curr->right != nullptr) 
	{
		BSTNode *curr_right = curr->right;
		if (curr_right->left == nullptr && curr_right->right == nullptr) {
			curr->data = curr_right->data;
			delete curr_right;
			curr->right = nullptr;
		}
		else { // right child has children
			//if the node's right child has a left child
			// Move all the way down left to locate smallest element

			if ((curr->right)->left != nullptr) {
				BSTNode* lcurr;
				BSTNode* lcurr_parent;
				lcurr_parent = curr->right;
				lcurr = (curr->right)->left;
				while (lcurr->left != nullptr) {
					lcurr_parent = lcurr;
					lcurr = lcurr->left;
				}
				curr->data = lcurr->data;
				if (lcurr->right != nullptr)
					lcurr_parent->left = lcurr->right;
				else
				lcurr_parent->left = nullptr;
				delete lcurr;
			}
			else { // (curr->right)->right != nullptr
				BSTNode *tmp = curr->right;
				curr->data = tmp->data;
				curr->right = tmp->right;
				delete tmp;
			}
		}
		return true;
	}
}

template<typename Type>
void BST<Type>::clear()
{
	postorder(root);
	root = nullptr;
}

template<typename Type>
void BST<Type>::printInOrder() const
{
	inorder(root);
	cout << endl;
}

template<typename Type>
void BST<Type>::inorder(const BSTNode* p) const
{
	if (p != nullptr)
	{

		inorder(p->left);
		cout << p->data << " ";
		inorder(p->right);
	}
	/*else
		return;*/
}

template<typename Type>
void BST<Type>::printPreOrder() const
{
	preorder(root);
}


template<typename Type>
void BST<Type>::preorder(const BSTNode* p)
{
	if (p != nullptr)
	{
		insert(p->data);
		preorder(p->left);
		preorder(p->right);
	}
}

template<typename Type>
void BST<Type>::postorder(const BSTNode* p)const
{
	if (p != nullptr)
	{
		postorder(p->left);
		postorder(p->right);
		delete p;
		//cout << " " << p->data << " ";
	}
	
}