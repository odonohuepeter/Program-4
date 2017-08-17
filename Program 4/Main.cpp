/*
Author: Peter O'Donohue
Creation Date: 08/10/17
Modification Date: 08/17/17
Description: The classes below allow the user to create two different types of objects, an object that contains an
array based implementation of the stack ADT, as well as an object that contains a link list based implementation of 
the stack ADT. Both objects contain the same methods, but each object implements these methods differently. To use,
create an object of type 'LeakyArrayStack' or 'LeakyLinkedStack' and specify the type of data you're working with. 
To push an item onto the stack, call the method 'push'. To remove an item from the top of the stack, call the method
'pop'. To check if a function is empty or full, call 'isEmpty'. And finally, to view the item on top of the stack, 
call the method 'peek'. 
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
	/*
	PRE: An instance of type 'LeakyArrayStack has been declared, with the data type specified by the client and the instance
	passing through the default argument.
    POST: An instance of type 'LeakyArrayStack' has been initialized with top = -1.
	*/
	top = -1;
}

template <class ItemType>
bool LeakyArrayStack<ItemType>::isEmpty() const
{
	/*
	PRE: An instance of type 'LeakyArrayStack' has been initialized and has called this function.
	POST: The function returns true if the stack is empty, and false otherwise. 
	*/
	if (top < 0)
		return true;
	else
		return false;
}
template <class ItemType>
bool LeakyArrayStack<ItemType>::push(const ItemType& newEntry)
{
	/*
	PRE: An instance of type 'LeakyArrayStack' has been initialized, called this function, and is passing through
	data of type 'ItemType'.
	POST: The function inserts an item on top of the stack, and returns true if the item was successfully placed on 
	top of the stack, and returns false if otherwise.
	*/
	bool result = false;
	if (top < MAX_SIZE - 1)
	{
		++top;
		items[top] = newEntry;
		result = true;
	}
	else if (top == MAX_SIZE - 1)  // if stack is full
	{
		for (int i = 0; i < (MAX_SIZE - 1) ; ++i)  // remove oldest item from stack
		{
			items[i] = items[i + 1];  // push new item on top of stack
			result = true;
		}
		items[top] = newEntry;
	}
	return result;
}
template <class ItemType>
bool LeakyArrayStack<ItemType>::pop()
{
	/*
	PRE: An instance of type 'LeakyArrayStack' has been initialized, and has called this function.
	POST: The function returns true if the stack is empty, and false otherwise.
	*/
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
	/*
	PRE: An instance of type 'LeakyArrayStack' has been initialized and has called this function.
	POST: The function returns the top item to the client, and otherwise returns false.
	*/
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
	/*
	PRE: An instance of type 'node' has been declared with the default argument.
	POST: The instance has been initialized with next = nullptr
	*/
	next = nullptr;
}


template <class ItemType>
node<ItemType>::node(const ItemType& data)
{
	/*
	PRE: An instance of type 'node' has been declared with the client passing through a non default argument.
	POST: The instance has been initialized with next = nullptr and item = data.
	*/
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
	/*
	PRE: An instance of type 'LeakyLinkedStack' has been declared with the default argument.
	POST: The instance has been initialized with next = nullptr, size = 0, and count = 0.
	*/
	top = nullptr;
	size = 0;
	count = 0;
}

template <class ItemType>
LeakyLinkedStack<ItemType>::LeakyLinkedStack(const int& SIZE)
{
	/*
	PRE: An instance of type 'LeakyLinkedStack' has been declared with a non default argument.
	POST: The instance has been initialized with next = nullptr, size = SIZE, and count = 0.
	*/
	if (SIZE >= 0)
	{
		size = SIZE;
		top = nullptr;
		count = 0;
	}
}

template <class ItemType>
LeakyLinkedStack<ItemType>::LeakyLinkedStack(const LeakyLinkedStack<ItemType>& original)
{
	/*
	PRE: An operation requiring a copy of an instance of type 'LeakyLinkedStack' has been initiated.
	POST: The instance has been deep copied.
	*/
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
}

template <class ItemType>
LeakyLinkedStack<ItemType>::~LeakyLinkedStack()
{
	/*
	PRE: An instance of type 'LeakyLinkedStack' has left scope, and or a copy constructor or assignment overload has 
	been performed.
	POST: The instance has been deallocated from memory.
	*/
	while (!isEmpty())
	{
		pop();
	}
}


template <class ItemType>
LeakyLinkedStack<ItemType>LeakyLinkedStack<ItemType>::operator=(const LeakyLinkedStack<ItemType>& rhs)
{
	/*
	PRE: An assignment operation on an instance of type 'LeakyLinkedStack' has been initialized.
	POST: The instance on the right hand side has been copied the the instance on the left hand side.
	*/
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
	/*
	PRE: An instance of type 'LeakyLinkedStack' has been initialized and has called this function.
	POST: The function returns true if the stack is empty, and false otherwise.
	*/
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
	/*
	PRE: An instance of type 'LeakyLinkedStack' has been initialized and has called this function, passing through
	a data argument of type 'ItemType'
	POST: the data in the argument has been pushed onto the stack, and the function returns true if successfull, and false
	if unsuccessfull.
	*/
	node<ItemType> *tempTop = nullptr;
	if (top == nullptr)
	{
		tempTop = new node<ItemType>;
		tempTop->item = newEntry;
		tempTop->next = nullptr;
		top = tempTop;
		tempTop = nullptr;
		if (count < size);
			++count;
		return true;
	}

	else if (count == size) // if stack is full
	{
		node<ItemType> *walker = nullptr;
		walker = top;
		while (walker->next != nullptr)
		{
			walker = walker->next;
		}
		delete walker;  // remove oldest item from stack
		walker = nullptr;
		tempTop = new node<ItemType>;  // place new item on top of stack
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
		if (count < size)
			++count;
		return true;
	}
	return false;
}

template <class ItemType>
ItemType LeakyLinkedStack<ItemType>::peek() const
{
	/*
	PRE: An instance of type 'LeakyLinkedStack' has been initialized and has called this function.
	POST: The function returns the item on top of the stack to the client if the stack is not empty.
	*/
	if (!isEmpty())
	{
		ItemType result = top->item;
		return result;
	}
}

template <class ItemType>
bool LeakyLinkedStack<ItemType>::pop()
{
	/*
	PRE: An instance of type 'LeakyLinkedStack' has been initialized and has called this function.
	POST: The function removes the top item from the stack if not empty, and returns true is successfull, and false if
	unsuccessfull.
	*/
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

// unit test protoypes
template <class ItemType>
bool testPushAndPop(LeakyArrayStack<ItemType> a, LeakyLinkedStack<ItemType> b);  // tests push and pop
template <class ItemType>
bool testIsEmpty(LeakyArrayStack<ItemType> a, LeakyLinkedStack<ItemType> b);  // tests isEmpty
template <class ItemType>
bool testPeek(LeakyArrayStack<ItemType> a, LeakyLinkedStack<ItemType> b);  // tests peek

int main()
{
	LeakyArrayStack<int> c;  // for unit tests
	LeakyLinkedStack<int> d(5);  // for unit tests
	LeakyArrayStack<int> e;  // for unit tests
	LeakyLinkedStack<int> f(5);  // for unit tests
	LeakyArrayStack<int> g;  // for unit tests
	LeakyLinkedStack<int> h(5);  // for unit tests
	LeakyArrayStack<int> arrayStack;  // test sample input and output
	LeakyLinkedStack<int> linkStack(5);  // test sample input and output
	
	// test sample input and output
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

	//unit tests
	if (!testPushAndPop(e, f))
		cout << "testPushAndPop failed unit test." << endl;
	else
		cout << "testPushAndPop passed unit test." << endl;
	if (!testIsEmpty(e, f))
		cout << "testIsEmpty failed unit test." << endl;
	else
		cout << "testIsEmpty passed unit test." << endl;
	if (!testPeek(g, h))
		cout << "testIsFull failed unit test." << endl;
	else
		cout << "testIsFull passed unit test." << endl;

	system("pause");
	return 0;
}

// unit tests implementations
template <class ItemType>
bool testPushAndPop(LeakyArrayStack<ItemType> a, LeakyLinkedStack<ItemType> b)
{
	bool result = true;
	for (int i = 0; i <= 5; ++i)  // fill stack and push when stack is full
	{
		int foo;
		a.push(i);
		foo = a.peek();
		if (foo != i)
			result = false;
		b.push(i);
		foo = b.peek();
		if (foo != i)
			result = false;
	}
	for (int i = 0; i < 5; ++i)  // empty stack
	{
		a.pop();
		b.pop();
	}
	
	if (!a.isEmpty())
		result = false;
	if (!b.isEmpty())
	    result = false;
	return result;
}

template <class ItemType>
bool testIsEmpty(LeakyArrayStack<ItemType> a, LeakyLinkedStack<ItemType> b)
{
	bool result = true;

	// verify initialized stacks are empty.
	if (!a.isEmpty())
		result = false;
	if (!b.isEmpty())
		result = false;

	// test isEmpty after one push
	a.push(5);
	b.push(5);
	if (a.isEmpty())
		result = false;
	if (b.isEmpty())
		result = false;

	// test isEmpty after each stack has been empty
	a.pop();
	b.pop();
	if (!a.isEmpty())
		result = false;
	if (!b.isEmpty())
		result = false;

	return result;
}

template <class ItemType>
bool testPeek(LeakyArrayStack<ItemType> a, LeakyLinkedStack<ItemType> b)
{
	bool result = true;
	if (a.peek())
		result = false;
	if (a.peek())
		result = false;

	for (int i = 0; i <= 5; ++i)  // fill stack and test peek for each item
	{
		int foo;
		a.push(i);
		foo = a.peek();
		if (foo != i)
			result = false;
		b.push(i);
		foo = b.peek();
		if (foo != i)
			result = false;
	}
	return result;

	
}