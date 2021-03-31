#ifndef DLLIST_H
#define DLLIST_H
#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip>

typedef struct Data
{
	char   toolName[35];
	int    quantity;
	double cost;
	Data(){

		for (int i = 0; i < 35; i++)
		{
			toolName[i] = ' ';
		}

		quantity = 0;
		cost = 0.00;
	}

	Data(std::string tn, int qty, double _cost)
	{
		bool tnCopied = true;
		for (int i = 0; i < 35; i++)
		{
			toolName[i] = ' ';
		}

		do
		{
			if (tn.length() <=34)
			{
				tn.copy (toolName, tn.size()+1);
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

	void displayData()const
	{
		const std::string str(toolName);

		std::cout << "tool name: "<< str.c_str() << std::endl;
		std::cout << "stock: " << quantity << std::endl;
		std::cout << std::fixed;
		std::cout << std::setprecision(2);
		std::cout << "retail cost: " << cost<< std::endl<<std::endl;

	}
}data;

struct node
{
	double key;
	data d;
	node* next;
	node* prev;
};



class DoublyLinkedList
{
public:

	DoublyLinkedList();
	DoublyLinkedList(int maxSize);
	node* getHead()const;
	node* getCurr()const;
	void setCurr(node* ptr);
	bool addItem(const std::string& _key, data& _d);
	bool deleteItem(int _key);
	bool findItem(int _key, data& _d);
	bool isEmpty()const;
	bool isFull()const;
	int getQty()const;
	bool makeEmpty();
	void displayAll()const;
	void printToFile()const;
	~DoublyLinkedList();


private:
	int qty;
	int max;
	node* head;
	node* curr;
};

inline DoublyLinkedList::DoublyLinkedList()
{
	qty = 0;
	max = INT_MAX;
	head = NULL;
	curr = NULL;
}

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
}

inline node * DoublyLinkedList::getHead()const
{
	return head;
}

inline node * DoublyLinkedList::getCurr()const
{
	return curr;
}

inline void DoublyLinkedList::setCurr(node* ptr)
{
	curr = ptr;
}

inline bool DoublyLinkedList::addItem(const std::string& _key_, data& _d)
{

	std::stringstream ss(_key_);
	int _key;
	ss >> _key;
	//std::cout << "in add item, key val: "<< _key << std::endl;
	node* temp;
	if (isFull())
	{
		//std::cout << "cant add item list is full" << std::endl;
		return false;
	}
	temp = new node;
	temp->key = _key;
	temp->d = _d;
	if(isEmpty())//first node being added to list
	{
		//std::cout << "adding first node to list: "<< _key << std::endl;
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
			//std::cout << "duplicate item didn't add: "<<_key<<std::endl;
			return false;
		}
		else if (_key < head->key)//adding new first node
		{
			//std::cout << "adding new node to beginning2: "<< _key<<std::endl;
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
			//std::cout << "adding second node to list: "<<_key<<std::endl;
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
			//std::cout << "duplicate item didn't add: "<<_key<<std::endl;
			return false;
		}
		if (head->key > _key)//adding new first node with list of many nodes
		{
			//std::cout << "adding new node to beginning3+: "<< _key<<std::endl;
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
				//std::cout << "duplicate item didn't add: "<<_key<<std::endl;
				return false;
			}
			if (curr->key > _key)//adding node to middle of list
			{
				//std::cout << "adding node to middle of list: " <<_key << std::endl;
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
			//std::cout << "adding node to end of list: "<<_key << std::endl;
			temp->next = NULL;
			curr->next = temp;
			temp->prev = curr;
			curr = head;
			qty++;
			return true;
		}
		if (curr->next == NULL && curr->key > _key)//adding node to end of list
		{
			//std::cout << "adding node to one before end: "<<_key << std::endl;
			temp->next = curr;
			curr->prev->next = temp;
			temp->prev = curr->prev;
			curr = head;
			qty++;
			return true;
		}
	}
	curr = head;
	//std::cout << "something went wrong and no node added: "<<_key<<std::endl;
	return false;

}

inline bool DoublyLinkedList::deleteItem(int _key)
{
	node* temp;
	data junk;
	if(isEmpty()) {
		//std::cout <<" list not initialized." << std::endl;
		return false;
	}
	bool found = findItem(_key, junk);
	if (found)
	{
		temp = curr;
		if (curr == head)
		{
			//std::cout << "deleting start key"<<std::endl;
			head = head->next;
			head->prev = NULL;
			curr = head;
		}
		else if (curr->next == NULL)
		{
			//std::cout << "deleting last key"<<std::endl;
			curr = curr->prev;
			curr->next = NULL;
		}
		else
		{
			//std::cout << "deleting middle key"<<std::endl;
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
		//std::cout << "in getItem and is empty list" << std::endl;
		return false;
	}
	if (head->key == _key)
	{
		//std::cout << "item found at start of list: "<<_key <<std::endl;
		_d = head->d;
		curr = head;
		return true;
	}

	curr = head->next;
	if (curr->key == _key)
	{
		//std::cout << "item found second slot: "<<_key<<std::endl;
		_d = curr->d;
		return true;
	}
	else
	{
		//std::cout << "in getItem else statement now"<<std::endl;
		while (curr != NULL)
		{
		//	std::cout<< "key: "<< _key << " in while loop checking curr: "<< curr->key<<std::endl;
			if (_key == curr->key)
			{
			//	std::cout << "getItem found: " << _key << std::endl;
				_d = curr->d;
			//	std::cout << "curr at: "<< curr->key <<std::endl;
				return true;
			}
			curr = curr->next;
		}
		//std::cout << "leaving getItem else statement now"<<std::endl;
	}
	//std::cout << "in getItem and item was not found: "<< _key << std::endl;
	curr = head;
	return false;

}

inline bool DoublyLinkedList::isEmpty() const
{
	return qty==0;
}

inline bool DoublyLinkedList::isFull() const
{
	return qty>=max;
}

inline int DoublyLinkedList::getQty() const
{
	return qty;
}

inline bool DoublyLinkedList::makeEmpty()
{
	//std::cout << "In make empty now"<<std::endl;
	node* temp;
	if (isEmpty())
	{
		return false;
	}
	while (qty!=0)
	{
		temp = head;
		head = head->next;
		//std::cout << "deleting key: "<< temp->key<< std::endl;
		delete temp;
		qty--;
	}
	return true;
}

inline void DoublyLinkedList::displayAll() const
{
	int count = qty;

	if (head != NULL)
	{
		node* printer = head;
		std::cout << std::endl;
		do {
			std::cout << "key: " <<static_cast<int>(printer->key) << std::endl;
			printer->d.displayData();
			printer = printer->next;
			count--;
		} while (qty!= 0);
	}
	std::cout << std::endl;
}

inline void DoublyLinkedList::printToFile()const
{
	std::ofstream output;
	node* printer;
	int count = qty;

	output.open("inventory1.txt");
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
}

inline DoublyLinkedList::~DoublyLinkedList()
{
	makeEmpty();
}

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

	bool add(double, data&); // adds an element to the list

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

		if (head_ == NULL)     // Report no items in the list
		{
			std::cout << " List is currently empty.\n";
		}
		else
		{
			temp = head_;
			std::cout << "qty: "<< qty_<<std::endl;
			while (temp != NULL)
			{
				//std::cout << "cost: " << temp->key << "\n";
				temp->d.displayData();
				temp = temp->next;
			}
		}
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
#endif // DLLIST_H
