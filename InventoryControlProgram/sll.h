#pragma once
/**
 * @class SortedList
 * @details interface for a sorted list ADT
 * @author Ryan Zurrin
 * @date 2/10/2021
 * @LastModified 2/12/2021
 */
 #pragma once

#include <iostream>


using namespace std;

class SortedList
{
public:
	SortedList(); //Constructor

	SortedList(int); //overloaded constructor

	~SortedList(); //Destructor

	void makeEmpty(); // empties the list

	bool isFull()const; // checks if list is full

	bool isEmpty()const; // checks if list is empty

	int getLength()const; // returns the length of the list

	bool find(double)const; // searches list for an item

	bool add(double); // adds an element to the list

	bool deleteItem(double); // deletes an item from the list

	void printList()const; //prints the elements in the list

protected:
	node* head_; //pointer to start of list
	int qty_; // quantity of items in the list
	int max_; // max elements list can be

};
inline SortedList::SortedList()
{
	head_ = NULL;
	qty_ = 0;
	max_ = INT_MAX;
}

/// <summary>
/// Initializes a new instance of the <see cref="UnsortedList"/> class.
/// </summary>
/// <param name="max_Size">The maximum size.</param>
inline SortedList::SortedList(int max_Size)
{
	head_ = NULL;
	qty_ = 0;
	max_ = max_Size;
}

/// <summary>
/// Determines whether this instance is full.
/// </summary>
/// <returns>
///   <c>true</c> if this instance is full; otherwise, <c>false</c>.
/// </returns>
inline bool SortedList::isFull()const
{
	if (qty_ == max_)
	{
		return true;
	}
	return false;
}

/// <summary>
/// Determines whether this instance is empty.
/// </summary>
/// <returns>
///   <c>true</c> if this instance is empty; otherwise, <c>false</c>.
/// </returns>
inline bool SortedList::isEmpty() const
{
	return (head_ == NULL);
}

/// <summary>
///  Empties List and all items are unallocated
/// </summary>
inline void SortedList::makeEmpty()
{
	node* tempPtr;
	while (head_ != NULL) {
		tempPtr = head_;
		head_ = head_->next;
		delete tempPtr;
	}
	qty_ = 0;
}

/// <summary>
/// Gets the length.
/// </summary>
/// <returns>the length of list</returns>
inline int SortedList::getLength()const
{
	return qty_;
}

/// <summary>
/// Finds the specified value.
/// </summary>
/// <param name="item">The value.</param>
/// <returns>true if value is in list: else false</returns>
inline bool SortedList::find(double item) const
{
	for (node* scan = head_; scan != NULL; scan = scan->next)
	{
		if (scan->key > item)
		{
			return false;
		}
		if (scan->key == item)
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// Adds the specified value.
/// </summary>
/// <param name="item">The value.</param>
/// <returns>true if item is added to list:
/// else false with error message.</returns>
inline bool SortedList::add(double item)
{
	node* temp;

	if (qty_ == max_)
	{
		return false;
	}
	if (isEmpty())
	{
		head_ = new node;
		head_->key = item;
		head_->next = NULL;
		qty_++;
		return true;
	}
	if (head_->key > item)
	{
		temp = new node;
		temp->key = item;
		temp->next = head_;
		head_ = temp;
		qty_++;
		return true;
	}
	else if (head_->key < item)
	{
		for (node* scan = head_; scan != NULL; scan = scan->next)
		{
			//if (scan->val == item)
			//{
			//	return false;
		//	}
			if ((scan->next == NULL) || (scan->next->key > item))
			{
				temp = new node;
				temp->key = item;
				temp->next = scan->next;
				scan->next = temp;
				qty_++;
				return true;
			}
		}
	}
	return false;
}

/// <summary>
/// Deletes the item.
/// </summary>
/// <param name="item">The item.</param>
/// <returns>true if item is deleted: else false with error message</returns>
inline bool SortedList::deleteItem(double item)
{
	node* temp;

	if (isEmpty()) {
		return false;
	}

	if (head_->key == item)
	{
		temp = head_;
		head_ = head_->next;
		delete temp;
		qty_--;
		return true;
	}
	for (node* scan = head_; scan->next != NULL; scan = scan->next)
	{
		if (scan->key > item)
		{
			return false;
		}
		if (scan->next->key == item)
		{
			// Unlink the node from linked list
			temp = scan->next;
			scan->next = temp->next;
			// Free memory
			delete temp;
			qty_--;
			return true;
		}
	}
	return false;
}

/// <summary>
/// Prints the list.
/// </summary>
inline void SortedList::printList()const
{
	{
		node* temp;

		cout << "\n\nItems in the Sorted List\n";
		cout << "----------------------------------------------\n";
		cout << "Pos#\t\t\tData\n";
		cout << "----------------------------------------------\n";
		if (head_ == NULL)     // Report no items in the list
		{
			cout << " List is currently empty.\n";
		}
		else
		{
			temp = head_;
			int place = 1;
			while (temp != NULL)
			{
				cout << place << "\t\t\t" << temp->key << "\n";
				temp = temp->next;
				place++;
			}
		}
		cout << "---------------------------------------------\n";
	}
}

/// <summary>
/// Finalizes an instance of the <see cref="UnsortedList"/> class.
/// </summary>
/// Post: List is empty: all items have been unallocated
inline SortedList::~SortedList()
{
	makeEmpty();
}
