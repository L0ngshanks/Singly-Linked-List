#pragma once

// forward declaration
template<typename Type> class SLLIter;

//Struct Node of Type

// class SLList
template<typename Type> class SLList
{
	// the iterator is the list’s friend
	friend class SLLIter<Type>;

	// add members/methods here…
	struct Node
	{
		Type element;
		Node* next;
	};

	void recur(Node* spot)
	{
		if (spot == nullptr)
			return;
		recur(spot->next);
		addHead(spot->element);
	}

	Node* head = 0;
	unsigned int count;
public:
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Notes : constructs an empty list
	/////////////////////////////////////////////////////////////////////////////
	SLList()
	{
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : Destroys the list
	/////////////////////////////////////////////////////////////////////////////
	~SLList()
	{
		clear();
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Assignment Operator
	/////////////////////////////////////////////////////////////////////////////
	SLList<Type>& operator=(const SLList<Type>& that)
	{
		if (this != &that)
		{
			clear();
			recur(that.head);
		}

		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : Copy Constructor
	/////////////////////////////////////////////////////////////////////////////
	SLList(const SLList<Type>& that)
	{
		*this = that;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : addHead
	// Parameters :	v - the item to add to the list
	/////////////////////////////////////////////////////////////////////////////
	void addHead(const Type& v)
	{
		typename SLList<Type>::Node* temp = new Node;
		temp->element = v;
		temp->next = head;
		head = temp;

		count++;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the list, freeing any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		Node* temp;
		while(head != nullptr)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
		head = nullptr;
		count = 0;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :	index - an iterator to the location to insert at
	//				v - the item to insert
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void insert(SLLIter<Type>& index, const Type& v)
	{
		if (index.iterator == nullptr)
			return;
		typename SLList<Type>::Node* temp = new Node;
		temp->next = index.iterator;
		if (index.prev != nullptr)
			index.prev->next = temp;
		temp->element = v;
		if(index.iterator == head)
			head = temp;
		index.iterator = temp;
		count++;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : remove
	// Parameters :	index - an iterator to the location to remove from
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void remove(SLLIter<Type>& index)
	{
		if (index.iterator == nullptr)
			return;
		Node* del = index.iterator;

		//Node* temp = index.iterator;
		if (index.iterator != head)
			index.prev->next = index.iterator->next;
		else
			head = head->next;
		index.iterator = index.iterator->next;
		//index.prev->next = temp;
		delete del;
		count--;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : size
	// Return : the number of items stored in the linked list.
	/////////////////////////////////////////////////////////////////////////////
	inline unsigned int size() const
	{
		return count;
	}
};

// class SLLIter
template<typename Type> class SLLIter
{
	// the list is the iterator’s friend
	friend class SLList<Type>;

	// add members/methods here…

	typename SLList<Type>::Node* iterator;
	typename SLList<Type>::Node* prev;
	typename SLList<Type>* originalList;

public:
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Parameters :	listToIterate - the list to iterate
	/////////////////////////////////////////////////////////////////////////////
	SLLIter(SLList<Type>& listToIterate)
	{
		originalList = &listToIterate;
		begin();
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : begin
	// Notes : moves the iterator to the head of the list
	/////////////////////////////////////////////////////////////////////////////
	void begin()
	{
		prev = 0;
		iterator = originalList->head;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : end
	// Notes : returns true if we are at the end of the list, false otherwise
	/////////////////////////////////////////////////////////////////////////////
	bool end() const
	{
		if (iterator != nullptr)
			return false;

		return true;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator++
	// Notes : move the iterator forward one node
	/////////////////////////////////////////////////////////////////////////////
	SLLIter<Type>& operator++()
	{
		if (iterator)
		{
			prev = iterator;
			iterator = iterator->next;
		}

		return *this;
	}

	/////////////////////////////////////////////////////////////////////////////
	// Function : current
	// Notes : returns the item at the current iterator location
	/////////////////////////////////////////////////////////////////////////////
	Type& current() const
	{
		return iterator->element;
	}
};

