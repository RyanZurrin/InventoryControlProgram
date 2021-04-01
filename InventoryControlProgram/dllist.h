#ifndef DLLIST_H
#define DLLIST_H
#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>

/// <summary>
/// Static Data structure that is used within the nodes to build and hold
/// inventory data. I know this is a public member and that I didnt need to
/// build consturctors to set the members but I like having that option and I
/// felt it was easier to accomplish with a constructor so I used them
/// </summary>
typedef struct Data
{
	char   toolName[35];
	int    quantity;
	double cost;

	Data(){//built a default constructor for it so I could easily make emoty
		//data members
		toolName[0] = '\0';
		quantity = 0;
		cost = 0.00;
	}
	//overloaded constructor to set the structs data members
	Data(std::string tn, int qty, double _cost)
	{
		bool tnCopied = true;
		do
		{
			if (tn.length() <=34)
			{
				int len = tn.length();
				for (int i = 0; i< len; i++)
				{
					toolName[i] = tn[i];
				}
				toolName[len] = '\0';
				tnCopied = true;
			}
			else
			{
				std::cout << "tool name is too long please enter a name "
					      << "less then 35 characters in all\n>>";
				std::cin >> tn;
				tnCopied = false;
			}
		}
		while (!tnCopied);


		quantity  = qty;
		cost = _cost;
	}
	//a display function inside the member to make it faster and easier
	//to print whole inventory items anyplace needed.
	void displayData()const
	{
		const std::string str(toolName);

		std::cout << "item: "<< std::left << std::setw(35) << str.c_str()
				  << "  ";
		std::cout << "stock: "<< std::left<< std::setw(6) << quantity << " ";
		std::cout << std::fixed;
		std::cout << std::setprecision(2);
		std::cout << std::left << std::setw(6) << "cost: "
				  << std::right << std::setw(8)<< cost<< std::endl;

	}
}data;
//end of Data structure
//.............................................................................

/// <summary>
/// node for making list of inventory items, the node holds a data member in it
/// allowing for building dynamic lists with the ability to quickly modify items
/// </summary>
struct node
{
	double key;
	data d;
	node* next;
	node* prev;
};
//end of node structure
//.............................................................................

/// <summary>
/// ADT for working with data and modifying the node members
/// </summary>
class DoublyLinkedList
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="DoublyLinkedList"/> class.
	/// </summary>
	DoublyLinkedList();

	/// <summary>
	/// Initializes a new instance of the <see cref="DoublyLinkedList"/> class.
	/// </summary>
	/// <param name="maxSize">The maximum size.</param>
	DoublyLinkedList(int maxSize);

	/// <summary>
	/// Gets the head pointer location.
	/// </summary>
	/// <returns></returns>
	node* getHead()const;

	/// <summary>
	/// Gets the curr pointer location.
	/// </summary>
	/// <returns></returns>
	node* getCurr()const;

	/// <summary>
	/// Sets the curr pointer to new location. *Handle with care!
	/// </summary>
	/// <param name="ptr">The PTR.</param>
	void setCurr(node* ptr);

	/// <summary>
	/// Adds a new item to the list. I have decided to change the initial
	/// argument to a string which was to help deal with leading 0 inventory
	/// ID numbers that were changing to octal numbers.
	/// </summary>
	/// <param name="_key_">The key.</param>
	/// <param name="_d">The data member to be added to the item node containing
	/// the product inventory information.</param>
	/// <returns>
	/// <c>true</c> if this instance is added; otherwise, <c>false</c>.
	/// </returns>
	bool addItem(const std::string& _key, data& _d);

	/// <summary>
	/// Deletes the specified item from the list if it is there.
	/// </summary>
	/// <param name="_key">The key to be deleted.</param>
	/// <returns>
	/// <c>true</c> if this instance is deleted; otherwise, <c>false</c>.
	/// </returns>
	bool deleteItem(int _key);

	/// <summary>
	/// Finds the item.
	/// </summary>
	/// <param name="_key">The key.</param>
	/// <param name="_d">The data member that gets info saved to it if the
	/// item was found.</param>
	/// <returns>
	/// <c>true</c> if this instance is found; otherwise, <c>false</c>.
	/// </returns>
	bool findItem(int _key, data& _d);

	/// <summary>
	/// Determines whether this instance is empty.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is empty; otherwise, <c>false</c>.
	/// </returns>
	bool isEmpty()const;

	/// <summary>
	/// Determines whether this instance is full.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is full; otherwise, <c>false</c>.
	/// </returns>
	bool isFull()const;

	/// <summary>
	/// Gets the quantity of this instance of list.
	/// </summary>
	/// <returns>the list quantity</returns>
	int getQty()const;

	/// <summary>
	/// Makes this instance of the list empty.
	/// </summary>
	/// <returns></returns>
	bool makeEmpty();

	/// <summary>
	/// Displays all the data for each node in the list
	/// </summary>
	void displayAll();

	/// <summary>
	/// Prints all data contained in this instance to file.
	/// </summary>
	void printToFile()const;

	/// <summary>
	/// Finalizes an instance of the <see cref="DoublyLinkedList"/> class.
	/// </summary>
	~DoublyLinkedList();
private:
	int qty;
	int max;
	node* head;
	node* curr;
};//end of DLL interface
//start of DLL implementation
inline DoublyLinkedList::DoublyLinkedList()
{
	qty = 0;
	max = INT_MAX;
	head = NULL;
	curr = NULL;
}//end of no argument constructor
inline DoublyLinkedList::DoublyLinkedList(int maxSize)
{
	qty = 0;
	if (maxSize > 0)
	{
		max = maxSize;
	}
	else
		max = INT_MAX;
	head = NULL;
	curr = NULL;
}//end of overloaded constructor
inline node * DoublyLinkedList::getHead()const
{
	return head;
}//end of getHead
inline node * DoublyLinkedList::getCurr()const
{
	return curr;
}//end of getCurr
inline void DoublyLinkedList::setCurr(node* ptr)
{
	curr = ptr;
}//end of setCurr
inline bool DoublyLinkedList::addItem(const std::string& _key_, data& _d)
{//I have intentions to refactor this method to make smaller and more efficient
	//but running out of time and had to just leave for now
	std::stringstream ss(_key_);
	int _key;
	ss >> _key;
	node* temp;
	if (isFull())
	{
		return false;
	}
	temp = new node;
	temp->key = _key;
	temp->d = _d;
	if(isEmpty())//first node being added to list
	{
		temp->next = NULL;
		temp->prev = NULL;
		head = temp;
		curr = head;
		qty++;
		return true;
	}
	//only one node in list adding the second node
	else if (head->next == NULL)
	{
		if (head->key == _key)//duplicate, don't add;
		{
			return false;
		}
		else if (_key < head->key)//adding new first node
		{
			temp->next = head;
			head->prev = temp;
			temp->prev = NULL;
			head = temp;
			curr = head;
			qty++;
			return true;
		}
		else//adding second node
		{
			temp->prev = head;
			head->next = temp;
			temp->next = NULL;
			curr = head;
			qty++;
			return true;
		}
	}
	else//every other case
	{
		if (head->key == _key)//duplicate
		{
			return false;
		}
		if (head->key > _key)//adding new first node with list of many nodes
		{
			temp->next = head;
			temp->prev = NULL;
			head->prev = temp;
			head = temp;
			curr = head;
			qty++;
			return true;
		}
		curr = head;
		for (;curr->next != NULL; curr = curr->next)
		{
			if (curr->key == _key)//duplicate
			{
				return false;
			}
			if (curr->key > _key)//adding node to middle of list
			{
				temp->next = curr;
				temp->prev = curr->prev;
				curr->prev->next = temp;
				curr->prev = temp;
				curr = head;
				qty++;
				return true;
			}
		}//end for loop
		if (curr->next == NULL && curr->key < _key)//adding node to end of list
		{
			temp->next = NULL;
			curr->next = temp;
			temp->prev = curr;
			curr = head;
			qty++;
			return true;
		}
		if (curr->next == NULL && curr->key > _key)//adding node to end of list
		{
			temp->next = curr;
			curr->prev->next = temp;
			temp->prev = curr->prev;
			curr = head;
			qty++;
			return true;
		}
	}
	curr = head;
	return false;
}//end of add item
inline bool DoublyLinkedList::deleteItem(int _key)
{
	node* temp;
	data junk;
	if(isEmpty()) {
		return false;
	}
	bool found = findItem(_key, junk);
	if (found)
	{
		temp = curr;
		if (curr == head)
		{
			head = head->next;
			head->prev = NULL;
			curr = head;
		}
		else if (curr->next == NULL)
		{
			curr = curr->prev;
			curr->next = NULL;
		}
		else
		{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
		}
		curr = head;
		delete temp;
		qty--;
		return true;
	}//end if
	return false; // not found
}//end deleteItem
inline bool DoublyLinkedList::findItem(int _key, data& _d)
{
	if (isEmpty())
	{
		return false;
	}
	if (head->key == _key)
	{
		_d = head->d;
		curr = head;
		return true;
	}

	curr = head->next;
	if (curr->key == _key)
	{
		_d = curr->d;
		return true;
	}
	else
	{
		while (curr != NULL)
		{
			if (_key == curr->key)
			{
				_d = curr->d;
				return true;
			}
			curr = curr->next;
		}
	}
	curr = head;
	return false;

}//end of findItem
inline bool DoublyLinkedList::isEmpty() const
{
	return qty==0;
}//end of isEmpty
inline bool DoublyLinkedList::isFull() const
{
	return qty>=max;
}//end of isFull
inline int DoublyLinkedList::getQty() const
{
	return qty;
}//end of getQty
inline bool DoublyLinkedList::makeEmpty()
{
	node* temp;
	if (isEmpty())
	{
		return false;
	}
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	qty = 0;
	return true;
}
inline void DoublyLinkedList::displayAll()
{
	int count = qty;

	if (head != NULL)
	{
		curr = head;
		std::cout << std::endl;
		do {
			std::cout << "key: "<< std::left << std::setw(9)
					  << static_cast<int>(curr->key) << " ";
			curr->d.displayData();
			curr = curr->next;
			count--;
		} while (qty!= 0 && curr!=NULL);
	}
	std::cout << "quantity: " << qty << std::endl << std::endl;
}//end of displayAll
inline void DoublyLinkedList::printToFile()const
{
	std::ofstream output;
	node* printer;
	int count = qty;

	output.open("inventory.txt");
	if (!output)
	{
		std::cerr << "Error: file could not be opened" << std::endl;
		exit(1);
	}
	if (head != NULL)
	{
		printer = head;
		std::cout << std::endl;
		do {
			std::string tn = printer->d.toolName;
			output << static_cast<int>(printer->key) << ";";
			output << tn << ";";
			output << printer->d.quantity << ";";
			output << printer->d.cost << ";";
			output << "\n";
			printer = printer->next;
			count--;
		} while (count!=0);
		output.close();
	}
}//end of printToFile
inline DoublyLinkedList::~DoublyLinkedList()
{
	makeEmpty();
}//end of DoublyLinkedList destructor
//End of Doubly linked list ADT
//............................................................................

/// <summary>
/// Sorted List ADT that allows duplicates and is used to print the list in
/// order of cost.
/// </summary>
class SortedList
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="SortedList"/> class.
	/// </summary>
	SortedList();

	/// <summary>
	/// Initializes a new instance of the <see cref="SortedList"/> class.
	/// </summary>
	/// <param name="max_Size">The maximum size.</param>
	SortedList(int);

	/// <summary>
	/// Determines whether this instance is full.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is full; otherwise, <c>false</c>.
	/// </returns>
	bool isFull()const;

	/// <summary>
	/// Determines whether this instance is empty.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is empty; otherwise, <c>false</c>.
	/// </returns>
	bool isEmpty()const;

	/// <summary>
	///  Empties List and all items are unallocated
	/// </summary>
	void makeEmpty();

	/// <summary>
	/// Gets the length.
	/// </summary>
	/// <returns>the length of list</returns>
	int getLength()const;

	/// <summary>
	/// Finds the specified value.
	/// </summary>
	/// <param name="item">The value.</param>
	/// <returns>true if value is in list: else false</returns>
	bool find(double)const;

	/// <summary>
	/// Adds the specified value.
	/// </summary>
	/// <param name="item">The value.</param>
	/// <returns>true if item is added to list:
	/// else false with error message.</returns>
	bool add(double, data&);

	/// <summary>
	/// Deletes the item.
	/// </summary>
	/// <param name="item">The item.</param>
	/// <returns>true if item is deleted: else false with error message</returns>
	bool deleteItem(double);


	/// <summary>
	/// Prints the list.
	/// </summary>
	void printList()const; //prints the elements in the list

	/// <summary>
	/// Finalizes an instance of the <see cref="SortedList"/> class.
	/// </summary>
	/// Post: List is empty: all items have been unallocated
	~SortedList();

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
}//end of no argument constructor
inline SortedList::SortedList(int max_Size)
{
	head_ = NULL;
	qty_ = 0;
	max_ = max_Size;
}//end of overloaded constructor
inline bool SortedList::isFull()const
{
	if (qty_ == max_)
	{
		return true;
	}
	return false;
}//end of isFull
inline bool SortedList::isEmpty() const
{
	return (head_ == NULL);
}//end of isEmpty
inline void SortedList::makeEmpty()
{
	node* tempPtr;
	while (head_ != NULL) {
		tempPtr = head_;
		head_ = head_->next;
		delete tempPtr;
	}
	qty_ = 0;
}//end of makeEmpty
inline int SortedList::getLength()const
{
	return qty_;
}//end of getLength
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
}//end of find
inline bool SortedList::add(double item, data& _d)
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
		head_->d = _d;
		head_->next = NULL;
		qty_++;
		return true;
	}
	if (head_->key > item)
	{
		temp = new node;
		temp->key = item;
		temp->d = _d;
		temp->next = head_;
		head_ = temp;
		qty_++;
		return true;
	}
	else if (head_->key <= item)
	{
		for (node* scan = head_; scan != NULL; scan = scan->next)
		{

			if ((scan->next == NULL) || (scan->next->key >= item))
			{
				temp = new node;
				temp->key = item;
				temp->d = _d;
				temp->next = scan->next;
				scan->next = temp;
				qty_++;
				return true;
			}
		}
	}
	return false;
}//end of add
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
}//end of deleteItem
inline void SortedList::printList()const
{
	{
		node* temp;

		if (head_ == NULL)     // Report no items in the list
		{
			std::cout << " List is currently empty.\n";
		}
		else
		{
			temp = head_;

			while (temp != NULL)
			{
				//std::cout << "cost: " << temp->key << "\n";
				temp->d.displayData();
				temp = temp->next;
			}
			std::cout << "quantity: " << qty_ << std::endl << std::endl;
		}
	}
}//end of printList
inline SortedList::~SortedList()
{
	makeEmpty();
}//end of SortedList destructor
//end if Sorted List ADT
//.............................................................................

#endif // DLLIST_H
