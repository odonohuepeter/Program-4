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

	if (top < -1)
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
		for (int i = 0; i < (MAX_SIZE - 1) ; ++i)  // remove oldest item from list
		{
			items[i] = items[i + 1];
			result = true;
		}
		items[top] = newEntry;
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
public:
	ItemType item;
	node<ItemType> *next;
	node();
	node(const ItemType& data);
};
#endif

// node class implementations

template <class ItemType>
node<ItemType>::node()
{
	next = nullptr;
}


template <class ItemType>
node<ItemType>::node(const ItemType& data)
{
	item = data;
	next = nullptr;
}

#ifndef LEAKY_LINKED_STACK
#define LEAKY_LINKED_STACK
template <class ItemType>
class LeakyLinkedStack : public LeakyStackInterface<ItemType>
{
public:
	LeakyLinkedStack();
	LeakyLinkedStack(const int& SIZE);
	LeakyLinkedStack(const LeakyLinkedStack<ItemType>& Original);
	~LeakyLinkedStack();
	LeakyLinkedStack<ItemType>operator=(const LeakyLinkedStack& rhs);
	bool isEmpty() const;
	bool push(const ItemType&);
	bool pop();
	ItemType peek() const;
private:
	int size;
	int count;
	node<ItemType> *top;
};
#endif
// leaky linked stack implementations
template <class ItemType>
LeakyLinkedStack<ItemType>::LeakyLinkedStack()
{
	top = nullptr;
	size = 0;
	count = 0;
}

template <class ItemType>
LeakyLinkedStack<ItemType>::LeakyLinkedStack(const int& SIZE)
{
	size = SIZE;
	top = nullptr;
	count = 0;
}

template <class ItemType>
LeakyLinkedStack<ItemType>::LeakyLinkedStack(const LeakyLinkedStack<ItemType>& original)
{
	size = original.size;
	node<ItemType> *copyNode = nullptr;
	node<ItemType> *oldPtr = original.top;

	if (oldPtr == nullptr)
	{
		top = nullptr;
	}
	else
	{
		top = new node<ItemType>(oldPtr->item);
		copyNode = top->next;
		oldPtr = oldPtr->next;
	}
	while (oldPtr != nullptr)
	{
		copyNode = new node<ItemType>(oldPtr->item);
		copyNode = copyNode->next;
		oldPtr = oldPtr->next;
	}
	cout << "Copy constructor called." << endl;
	return *this;
}

template <class ItemType>
LeakyLinkedStack<ItemType>::~LeakyLinkedStack()
{


	while (!isEmpty())
	{
		cout << "test" << endl;
		pop();
	}

	cout << "Destructor called." << endl;

}


template <class ItemType>
LeakyLinkedStack<ItemType>LeakyLinkedStack<ItemType>::operator=(const LeakyLinkedStack<ItemType>& rhs)
{
	this->size = rhs->size;
	node<ItemType>lhsWalker = nullptr;
	node<ItemType> rhsWalker = rhs->top;
	this->top = new node<ItemType>(rhsWalker->item);
	lhsWalker = top->next;
	rhsWalker = rhsWalker->next;

	while (rhsWalker != nullptr)
	{
		lhsWalker = new node<ItemType>(rhsWalker->item);
		lhsWalker = lhsWalker->next;
		rhsWalker = rhsWalker->next;
	}
	cout << "Operator overload called." << endl;
	return *this;
}

template <class ItemType>
bool LeakyLinkedStack<ItemType>::isEmpty() const
{

	if (top == nullptr)
	{
		return true;
	}
	else
		return false;
}

template <class ItemType>
bool LeakyLinkedStack<ItemType>::push(const ItemType& newEntry)
{
	node<ItemType> *tempTop = nullptr;
	if (top == nullptr)
	{
		tempTop = new node<ItemType>;
		tempTop->item = newEntry;
		tempTop->next = nullptr;
		top = tempTop;
		tempTop = nullptr;
		++count;
		return true;
	}

	else if (count == size)
	{

		node<ItemType> *walker = nullptr;
		walker = top;
		while (walker->next != nullptr)
		{
			walker = walker->next;
		}
		delete walker;
		walker = nullptr;
		tempTop = new node<ItemType>;
		tempTop->item = newEntry;
		tempTop->next = top;
		top = tempTop;
		tempTop = nullptr;
		return true;

	}

	else
	{
		tempTop = new node<ItemType>;
		tempTop->item = newEntry;
		tempTop->next = top;
		top = tempTop;
		++count;
		return true;
	}
	return false;
}

template <class ItemType>
ItemType LeakyLinkedStack<ItemType>::peek() const
{
	if (!isEmpty())
	{
		ItemType result = top->item;
		return result;
	}
}

template <class ItemType>
bool LeakyLinkedStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		node<ItemType> *deleteNode = top;
		top = top->next;
		deleteNode->next = nullptr;
		delete deleteNode;
		deleteNode = nullptr;
		--count;
		if (count == 0)
			top = nullptr;
		result = true;
	}
	return result;
}

int main()
{
	LeakyArrayStack<int> arrayStack;
	LeakyLinkedStack<int> linkStack(5);
	arrayStack.push(2);
	arrayStack.push(3);
	arrayStack.push(4);
	cout << arrayStack.peek() << endl;
	arrayStack.push(16);
	arrayStack.push(17);
	arrayStack.push(12);
	cout << "Popped " << arrayStack.peek() << endl;
	arrayStack.pop();
	cout << "Popped " << arrayStack.peek() << endl;
	arrayStack.pop();
	cout << "Popped " << arrayStack.peek() << endl;
	arrayStack.pop();
	cout << "Popped " << arrayStack.peek() << endl;
	arrayStack.pop();
	cout << "Popped " << arrayStack.peek() << endl;
	arrayStack.pop();
	if (!arrayStack.pop())
		cout << "Leaky array stack is empty!" << endl;
	else
		cout << "Leaky array stack is not empty" << endl;
	linkStack.push(2);
	linkStack.push(3);
	linkStack.push(4);
	cout << linkStack.peek() << endl;
	linkStack.push(16);
	linkStack.push(17);
	linkStack.push(12);
	cout << "Popped " << linkStack.peek() << endl;
	linkStack.pop();
	cout << "Popped " << linkStack.peek() << endl;
	linkStack.pop();
	cout << "Popped " << linkStack.peek() << endl;
	linkStack.pop();
	cout << "Popped " << linkStack.peek() << endl;
	linkStack.pop();
	cout << "Popped " << linkStack.peek() << endl;
	linkStack.pop();
	if (!linkStack.pop())
		cout << "Leaky link stack is empty!" << endl;
	else
		cout << "Leaky link stack is not empty." << endl;

	system("pause");
	return 0;
}