/*
Author: Peter O'Donohue
Creation Date: 08/10/17
Modification Date: 08/11/17
Description: FILL IN LATER
*/

#include <iostream>
using namespace std;

#ifndef LEAKY_STACK_INTERFACE
#define LEAKY_STACK_INTERFACE

// interface class
template <class ItemType>
class LeakyStackInterface
{
public:
	//returns whether stack is empty or not
	virtual bool isEmpty() const = 0;

	//adds a new entry to the top of the stack
	//if the stack is full, the bottom item is removed
	//or "leaked" first, and then the new item is set to the top
	//---> If the stack was full when the push was attempted, return false
	//---> If the stack was not full when the push was attempted, return true
	virtual bool push(const ItemType& newEntry) = 0;

	//remove the top item
	//if the stack is empty, return false to indicate failure
	virtual bool pop() = 0;

	//return a copy of the top of the stack
	virtual ItemType peek() const = 0;

	//destroys the stack and frees up memory
	//that was allocated
	virtual ~LeakyStackInterface() {}
};
#endif

#ifndef LEAKY_ARRAY_STACK
#define LEAKY_ARRAY_STACK

template <class ItemType>
class LeakyArrayStack : public LeakyStackInterface<ItemType>
{
public:
	LeakyArrayStack();
	bool isEmpty() const;
	bool push(const ItemType& newEntry);
	bool pop();
	ItemType peek() const;

private:
	static const int MAX_SIZE = 5;
	ItemType items[MAX_SIZE];
	int top;

};
#endif

// leaky array stack implementations
template<class ItemType>
LeakyArrayStack<ItemType>::LeakyArrayStack()
{
	top = -1;
}

template <class ItemType>
bool LeakyArrayStack<ItemType>::isEmpty() const
{

	if (top < 0)
		return true;
	else
		return false;
}
template <class ItemType>
bool LeakyArrayStack<ItemType>::push(const ItemType& newEntry)
{
	bool result = false;
	if (top < MAX_SIZE - 1)
	{
		++top;
		items[top] = newEntry;
		result = true;
	}
	else if (top == MAX_SIZE - 1)  // if stack is full
	{
		for (int i = 0; i < MAX_SIZE - 2; ++i)  // remove oldest item from list
		{
			items[i] = items[i + 1];
			items[top] = newEntry;
			result = true;
		}
	}
	return result;
}
template <class ItemType>
bool LeakyArrayStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		--top;
		result = true;
	}
	return result;
}

template <class ItemType>
ItemType LeakyArrayStack<ItemType>::peek() const
{
	bool result = false;
	if (!isEmpty())
	{
		return items[top];
	}
	return result;

}

#ifndef NODE
#define NODE
template <class ItemType>
class node
{
public :
	node();
	node(ItemType data, ItemType* i);
	ItemType getData();
	ItemType getNext();
private :
	ItemType item;
	ItemType* next;
};
#endif 

// node class implementations

template <class ItemType>
node<ItemType>::node()
{
	next = nullptr;
}


template <class ItemType>
node<ItemType>::node(ItemType data, ItemType* i = nullptr) : item(data), next(i) {};

template <class ItemType>
ItemType node<ItemType>::getData()
{
	return item;
}

template <class ItemType>
ItemType node<ItemType>::getNext()
{
	return next;
}

#ifndef LEAKY_LINKED_STACK
#define LEAKY_LINKED_STACK
template <class ItemType>
class LeakyLinkedStack : public LeakyStackInterface<ItemType>
{
public :
	LeakyLinkedStack();
	LeakyLinkedStack(const int& SIZE);
	LeakyLinkedStack(const LeakyLinkedStack& Original);
	~LeakyLinkedStack();
	LeakyLinkedStack<ItemType>operator=(const LeakyLinkedStack& rhs);
	bool isEmpty() const;
	bool push(const ItemType&);
	bool pop();
	ItemType peek() const;
private :
	int size;
	node<ItemType> *top;

};
#endif
// leaky linked stack implementations
template <class ItemType>
LeakyLinkedStack<ItemType>::LeakyLinkedStack()
{
	top = nullptr;
	size = 0;
}

template <class ItemType>
LeakyLinkedStack<ItemType>::LeakyLinkedStack(const int& SIZE)
{
	size = SIZE;
	top = nullptr;
}

template <class ItemType>
LeakyLinkedStack<ItemType>::LeakyLinkedStack(const LeakyLinkedStack& original)
{
	size = original->size;
	node<ItemType> *oldPtr = original->top;
	node<ItemType> *copyNode = new node<ItemType>(oldPtr->item);
	top = copyNode;
	oldPtr = oldPtr->next;
	copyNode = copyNode->next;

	while (oldPtr != nullptr)
	{
		copyNode = new node<ItemType>(oldPtr->item);
		copyNode = copyNode->next;
		oldPtr = oldPtr->next;
	}
	tail = copyNode;
	cout << "Copy constructor called." << endl;
	return *this;
}

template <class ItemType>
LeakyLinkedStack<ItemType>::~LeakyLinkedStack()
{
	/*
	node<ItemType> *deletePtr = nullptr;
	node<ItemType> *walker = top;

	while (walker != nullptr)
	{
		walker = walker->next;
		delete deletePtr;
		deletePtr = walker;
	}
	top = nullptr;
	deletePtr = nullptr;
	*/
}

template <class ItemType>
LeakyLinkedStack<ItemType>LeakyLinkedStack<ItemType>::operator=(const LeakyLinkedStack<ItemType>& rhs)
{
	this->size = rhs->size;
	node<ItemType> rhsWalker = rhs->top;
	node<ItemType> lhsWalker = new node<ItemType>(rhsWalker->item);
	this->top = lhsWalker;
	rhsWalker = rhsWalker->next;

	while (rhsWalker != nullptr)
	{
		lhsWalker = new node<ItemType>(rhsWalker->item);
		lhswalker = lhsWalker->next;
		rhsWalker = rhswalker->next;
	}
	return *this;
}

template <class ItemType>
bool LeakyLinkedStack<ItemType>::isEmpty() const
	{
		bool result = false;

		if (top == nullptr)
		{
			result = true;
			return result;
		}
		else
			return result;
	}
	
template <class ItemType>
bool LeakyLinkedStack<ItemType>::push(const ItemType& data)
{
	/*
	node<ItemType> *temp = nullptr;
	if (top == nullptr)
	{
		temp = new node<ItemType>(data);
		top = temp;
	}
	else
	{
		temp = top;
		top = new node<ItemType>(data);
		top->next = temp;
	}
	*/
	return false;
}

template <class ItemType>
ItemType LeakyLinkedStack<ItemType>::peek() const
{
	ItemType result = top->getData();
	return result;
}

template <class ItemType>
bool LeakyLinkedStack<ItemType>::pop()
{
	return true;
}
int main()
{
	LeakyArrayStack<int> foo;
	LeakyLinkedStack<int> test(5);

	foo.push(2);
	foo.push(3);
	foo.push(4);
	cout << foo.peek() << endl;
	foo.push(16);
	foo.push(17);
	foo.push(12);
	foo.pop();
	foo.pop();
	foo.pop();
	foo.pop();
	foo.pop();
	if (foo.isEmpty())
		cout << "Leaky stack is empty!" << endl;
	else
		cout << "Not Empty" << endl;


	system("pause");
	return 0;
}