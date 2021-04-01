/**
 * FileName inventoryDriver.cpp
 * Details build a simple inventory control program that may be used by a1
 * business.
 * Author Ryan Zurrin
 * DateStarted  3/27/2021
 * DueDate 4/01/2021
 */
#include <fstream>
#include <string>
#include "dllist.h"

void displayMenu();
void displayModMenu();
void validatePickLoop(DoublyLinkedList* dll);
bool validateModPickLoop(DoublyLinkedList* dll, data _d, int _key);
void inventoryLoader(DoublyLinkedList* dll);

static bool endProgram = false;

int main()
{
	DoublyLinkedList* inventory = new DoublyLinkedList;
	inventoryLoader(inventory);
	displayMenu();
	validatePickLoop(inventory);
	return 0;

}//end main

/// <summary>
/// Displays the main menu.
/// </summary>
void displayMenu() {
	std::cout << "a.)  Add new record" << std::endl;
	std::cout << "b.)  Delete record" << std::endl;
	std::cout << "c.)  Modify record" << std::endl;
	std::cout << "d.)  List all records by inventory number" << std::endl;
	std::cout << "e.)  List all records by COST" << std::endl;
	std::cout << "f.)  Quit and SAVE" << std::endl;
}//end method displayMenu

/// <summary>
/// Displays the mod menu.
/// </summary>
void displayModMenu() {
	std::cout << "a.)  Change name of item on record" << std::endl;
	std::cout << "b.)  Change part number of record" << std::endl;
	std::cout << "c.)  Change stock total" << std::endl;
	std::cout << "d.)  Change cost of item on record" << std::endl;
	std::cout << "e.)  SAVE and update inventory" << std::endl;
}//end method displayMenu


/// <summary>
/// Validates the pick and stays in loop until user chooses to exit program.
/// </summary>
/// <param name="dll">The doubly linked list ADT that hold inventory
/// records for viewing and updating.</param>
void validatePickLoop(DoublyLinkedList* dll)
{
		char pick;
		while (!endProgram)
		{
			std::cout << "\nEnter Menu Option\n>>";
			std::cin >> pick;
			if (pick!='a' && pick!='A' && pick!= '1' &&
				pick!='b' && pick!='B' && pick!= '2' &&
				pick!='c' && pick!='C' && pick!= '3' &&
				pick!='d' && pick!='D' && pick!= '4' &&
				pick!='e' && pick!='E' && pick!= '5' &&
				pick!='f' && pick!='F' && pick!= '6' )
			{
				std::cout << "That was no option! "
				     	  << "Please enter menu choice\n>>";
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cin >> pick;
			}

			//allows the user to enter in a new item into the inventory. The
			//user will be asked to enter each piece of needed data in order to
			//make sure everything is properly added.
			if (pick == 'a' || pick == 'A' || pick == '1') {
				std::string _id;
				std::string _tn;
				int _stock, id;
				double _cost;
				std::cout << "add item to inventory" << std::endl;
				std::cout << "Enter the name of Item to add\n>>";
				std::cin.ignore();
				std::getline(std::cin, _tn, '\n');
				std::cout << "Enter item Inventory number\n>>";
				std::cin >> id;
				while (!std::cin)
				{
					std::cout << "please enter a valid inventory number\n>>";
					std::cin.clear();
					std::cin.ignore(100,'\n');
					std::cin >> id;
				}
				std::cout << "Enter how many are in stock\n>>";
				std::cin >> _stock;
				while (!std::cin || _stock < 0)
				{
					std::cout << "please enter a valid stock number\n>>";
					std::cin.clear();
					std::cin.ignore(100,'\n');
					std::cin >> _stock;
				}
				std::cout << "Enter items cost\n>>";
				std::cin >> _cost;
				while (!std::cin || _cost < 0)
				{
					std::cout << "please enter a valid price\n>>";
					std::cin.clear();
					std::cin.ignore(100,'\n');
					std::cin >> _cost;
				}
				std::ostringstream oss;
				oss << id;
				_id = oss.str();
				data tool(_tn, _stock, _cost);
				dll->addItem(_id, tool);
				displayMenu();
			}
			//allows the user to specifiy a key record for deletion.
			else if (pick == 'b' || pick == 'B' || pick == '2')
			{
				int _key_;
				data toJunk;
				std::cout << "delete record from inventory" << std::endl;
				std::cout << "Enter record key to be deleted\n>>";
				std::cin >> _key_;
				if (dll->findItem(_key_, toJunk))
				{
					std::cout << toJunk.toolName
							  << " has been removed from inventory\n";
					dll->deleteItem(_key_);
				}
				else
				{
					std::cout << "item # " << _key_ << " was not found\n";
				}
				displayMenu();
			}
			//asks the user to enter a key and if key is found it takes user to
			//the item modification menu where they are able to update each
			//piece of data as needed and once the user chooses to exit and
			//save from the modification menu the object will be updated and
			//returned to main menu for further inventory operations.
			else if (pick == 'c' || pick == 'C' || pick == '3')
			{
				int _key_;
				data mod;
				std::string _tn;
				std::cout << "modify record"  << std::endl;
				std::cout << "enter part number of record to change\n>>";
				std::cin >> _key_;
				while (!std::cin || _key_ < 0)
				{
					std::cout << "please enter a valid part number\n>>";
					std::cin.clear();
					std::cin.ignore(100,'\n');
					std::cin >> _key_;
				}
				if (dll->findItem(_key_, mod)==true)
				{

					displayModMenu();
					validateModPickLoop(dll, mod, _key_);

				}
				else if (dll->findItem(_key_, mod) == false)
				{
					std::cout << "Item not found in inventory\n";
				}
				displayMenu();

			}
			//displays the items from list by key value
			else if (pick == 'd' || pick == 'D' || pick == '4')
			{
				std::cout << "list all items by inventory #" << std::endl;
				dll->displayAll();
				displayMenu();
			}
			//creates a sorted linked list object and stores the cost from
			//the dll objects as its keys.It's been modified to hold doubles
			//and have access to a data member as well, which is what allows
			//for a list to be printed in order of the cost instead of by key.
			else if (pick == 'e' || pick == 'E' || pick == '5')
			{
				const int count = dll->getQty();
				DoublyLinkedList* temp = new DoublyLinkedList;
				temp = dll;
				SortedList* costPrint = new SortedList;
				std::cout << "list all items by Cost $" << std::endl;
				temp->setCurr(temp->getHead());
				for (int i = 0; i< count; i++)
				{
					if (temp!=NULL)
					{
						costPrint->add(
							temp->getCurr()->d.cost, temp->getCurr()->d);
						temp->setCurr(temp->getCurr()->next);
					}

				}
				costPrint->printList();
				costPrint->makeEmpty();
				costPrint = NULL;
				temp = NULL;
				delete costPrint;
				delete temp;
				displayMenu();
			}
			//sets endProgram to true breaking the loop and calls the printToFile
			//method allowing the data from the list to be added to the file and
			//saved.
			else if (pick == 'f' || pick == 'F' || pick == '6')
			{
				std::cout << "Exiting program and saving file" << std::endl;
				dll->printToFile();
				endProgram = true;
			}
			else
				displayMenu();

		}//end while loop

		exit(0);
}//end method validatePickLoop

/// <summary>
/// Validates the modification pick loop which is how the user is able to update
/// the information on an item piece by piece
/// </summary>
/// <param name="dll">The DLL object pointer.</param>
/// <param name="_d">The inventory data.</param>
/// <param name="_key">The key that was picked for modification.</param>
/// <returns>true of item updated: else false</returns>
bool validateModPickLoop(DoublyLinkedList* dll, data _d, int _key)
{
		char pick;
		bool endMod = false;
		int _key_ = _key;
		int len;
		data mod = _d;
		std::string _tn, _k;
		std::cout << "Modifying "<< mod.toolName;
		while (!endMod)
		{
			std::cout << "\nEnter Modification Option\n>>";
			std::cin >> pick;
			if (pick!='a' && pick!='A' && pick!= '1' &&
				pick!='b' && pick!='B' && pick!= '2' &&
				pick!='c' && pick!='C' && pick!= '3' &&
				pick!='d' && pick!='D' && pick!= '4' &&
				pick!='e' && pick!='E' && pick!= '5' )
			{
				std::cout << "That was no option! "
				     	  << "Please enter menu choice\n>>";
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cin >> pick;
			}


			if (pick == 'a' || pick == 'A' || pick == '1') {
				std::cout << "Enter the new name for part in inventory\n>>";
				std::cin.ignore();
				std::getline(std::cin, _tn, '\n');
				len = _tn.length();
				for (int i = 0; i< len; i++)
				{
					mod.toolName[i] = _tn[i];
				}
				mod.toolName[len] = '\0';
				std::cout << "item "<< _d.toolName <<" changed to "
						  << mod.toolName << std::endl;

			}
			else if (pick == 'b' || pick == 'B' || pick == '2')
			{
				std::cout << "editing inventory id " << _key << std::endl;
				std::cout << "Enter new item Inventory number\n>>";
				std::cin >> _key_;
				while (!std::cin)
				{
					std::cout << "please enter a valid inventory number\n>>";
					std::cin.clear();
					std::cin.ignore(100, '\n');
					std::cin >> _key_;
				}
				std::cout << "product inventory " << _key << " changed to "
						  << _key_ << std::endl;

			}
			else if (pick == 'c' || pick == 'C' || pick == '3')
			{
				std::cout << "editing stock supply of "<< mod.quantity
						  <<std::endl;
				std::cout << "Enter new amount in stock\n>>";
				std::cin >> mod.quantity;
				while (!std::cin || mod.quantity < 0)
				{
					std::cout << "please enter a valid stock amount\n>>";
					std::cin.clear();
					std::cin.ignore(100, '\n');
					std::cin >> mod.quantity;
				}
				std::cout << "product stock changed from "<<_d.quantity
						  <<" to "<< mod.quantity;
			}
			else if (pick == 'd' || pick == 'D' || pick == '4')
			{
				std::cout << "editing item cost of " << mod.cost<< std::endl;
				std::cout << "Enter new cost of item\n>>";
				std::cin >> mod.cost ;
				while (!std::cin || mod.cost  < 0)
				{
					std::cout << "please enter a valid price\n>>";
					std::cin.clear();
					std::cin.ignore(100, '\n');
					std::cin >> mod.cost ;
				}
				std::cout << "product cost changed from " << _d.cost << " to "
						  << mod.cost << std::endl;

			}
			else if (pick == 'e' || pick == 'E' || pick == '5')
			{
				std::cout << "Item successfully updated in inventory"
						  << std::endl;
				std::ostringstream oss;
				oss << _key_;
				_k = oss.str();
				dll->deleteItem(_key);
				dll->addItem(_k, mod);
				endMod = true;
			}
			else
			{
				std::cout << "Error: item not updated" << std::endl;
				return false;
			}
		}//end while loop
		return true;

}//end method validateModPickLoop


void inventoryLoader(DoublyLinkedList* dll)
{
	std::ifstream inFile;
	std::string fileName = "inventory.txt";
	std::string line;
	std::string tempToolName;
	std::string tempKeyString;
	std::string	tempStockString;
	int tempStock;
	std::string tempCostString;
	double tempCost;
	bool fileNotFoundError = false;

	do
	{
		if (fileNotFoundError)
		{
			std::cout << "enter the name of the file to load from: "
				 <<"then press return.\n>>";
			std::cin >> fileName;
			if (fileName == "exit")
			{
				std::cout << "Good bye";
				exit(0);
			}
		}

		inFile.open(fileName.c_str());
		if (!inFile)
		{
			std::cout << "file not found, type 'exit' to end program, or"
			<< std::endl;
			fileNotFoundError = true;
		}
	} while (!inFile);

	while (std::getline(inFile, line))
	{
		std::stringstream ss(line);
		std::getline(ss, tempKeyString, ';');
		std::stringstream sss(tempKeyString);
		std::getline(ss, tempToolName, ';');
		std::getline(ss, tempStockString, ';');
		std::stringstream ssss(tempStockString);
		ssss >>tempStock;
		std::getline(ss, tempCostString, ';');
		std::stringstream _ss(tempCostString);
		_ss >> tempCost;
		data tempTool(tempToolName, tempStock, tempCost);
		dll->addItem(tempKeyString, tempTool);
	}

	std::cout << "Inventory has been successfully loaded." << std::endl;
	inFile.close();
}//end method listLoader

