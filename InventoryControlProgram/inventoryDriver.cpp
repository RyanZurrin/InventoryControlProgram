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

void displayMenu() {
	std::cout << "a.)  Add new record" << std::endl;
	std::cout << "b.)  Delete record" << std::endl;
	std::cout << "c.)  Modify record" << std::endl;
	std::cout << "d.)  List all records by inventory number" << std::endl;
	std::cout << "e.)  List all records by COST" << std::endl;
	std::cout << "f.)  Quit and SAVE" << std::endl;
}//end method displayMenu

void displayModMenu() {
	std::cout << "a.)  Change name of item on record" << std::endl;
	std::cout << "b.)  Change part number of record" << std::endl;
	std::cout << "c.)  Change stock total" << std::endl;
	std::cout << "d.)  Change cost of item on record" << std::endl;
	std::cout << "e.)  SAVE and update inventory" << std::endl;
}//end method displayMenu


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
			else if (pick == 'b' || pick == 'B' || pick == '2')
			{
				int _key_;
				bool wasDeleted;
				std::cout << "delete record from inventory" << std::endl;
				std::cout << "Enter record key to be deleted\n>>";
				std::cin >> _key_;
				wasDeleted = dll->deleteItem(_key_);
				if (wasDeleted)
				{
					std::cout << "item # " << _key_ << " has been removed\n";
				}
				else
				{
					std::cout << "item # " << _key_ << " has not found\n";
				}
				displayMenu();
			}
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
				if (dll->findItem(_key_, mod) == false)
				{
					std::cout << "Item not found in inventory\n";
				}
				displayMenu();

			}
			else if (pick == 'd' || pick == 'D' || pick == '4')
			{
				std::cout << "list all items by inventory #" << std::endl;
				dll->displayAll();
				displayMenu();
			}
			else if (pick == 'e' || pick == 'E' || pick == '5')
			{
				int count = dll->getQty();
				DoublyLinkedList* temp = new DoublyLinkedList;
				temp = dll;
				SortedList* costPrint = new SortedList;
				std::cout << "list all items by Cost $" << std::endl;
				temp->setCurr(temp->getHead());
				for (int i = 0; i< count; i++)
				{
					costPrint->add(temp->getCurr()->d.cost, temp->getCurr()->d);
					temp->setCurr(temp->getCurr()->next);
				}
				costPrint->printList();
				costPrint->makeEmpty();
				costPrint = NULL;
				temp = NULL;
				delete costPrint;
				delete temp;
				displayMenu();
			}
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




bool validateModPickLoop(DoublyLinkedList* dll, data _d, int _key)
{

		char pick;
		bool endMod = false;
		int _key_ = _key;
		int _stock = _d.quantity;
		int id = _key;
		double _cost = _d.cost;
		data mod = _d;
		std::string _tn, _k;

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

			}
			else if (pick == 'b' || pick == 'B' || pick == '2')
			{
				std::cout << "Enter new item Inventory number\n>>";
				std::cin >> _key_;
				while (!std::cin)
				{
					std::cout << "please enter a valid inventory number\n>>";
					std::cin.clear();
					std::cin.ignore(100,'\n');
					std::cin >> _key_;
				}
			}
			else if (pick == 'c' || pick == 'C' || pick == '3')
			{
				std::cout << "Enter the total items stock\n>>";
				std::cin >> _stock;
				while (!std::cin || _stock < 0)
				{
					std::cout << "please enter a valid stock amount\n>>";
					std::cin.clear();
					std::cin.ignore(100,'\n');
					std::cin >> _stock;
				}
			}
			else if (pick == 'd' || pick == 'D' || pick == '4')
			{
				std::cout << "Enter new cost of item\n>>";
				std::cin >> _cost;
				while (!std::cin || _cost < 0)
				{
					std::cout << "please enter a valid price\n>>";
					std::cin.clear();
					std::cin.ignore(100,'\n');
					std::cin >> _cost;
				}

			}
			else if (pick == 'e' || pick == 'E' || pick == '5')
			{
				dll->deleteItem(_key);
				for (int i = 0; i < 35; i++)
				{
					mod.toolName[i] = ' ';
				}
				std::ostringstream oss;
				oss << _key_;
				_k = oss.str();
				_tn.copy(mod.toolName, _tn.size() + 1);
				mod.quantity = _stock;
				mod.cost = _cost;
				dll->addItem(_k, mod);
				endMod = true;
			}
			else
				displayMenu();

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

	std::cout << "Lists have been successfully loaded." << std::endl;
	inFile.close();
}//end method listLoader

