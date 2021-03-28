/**
 * FileName inventoryDriver.cpp
 * Details build a simple inventory control program that may be used by a
 * business.
 * Author Ryan Zurrin
 * DateStarted  3/27/2021
 * DueDate 4/01/2021
 */
#include <fstream>
#include <sstream>
#include <ostream>
#include <iostream>
#include "dllist.h"


void displayMenu();
void validatePickLoop(DoublyLinkedList& dll);
void inventoryLoader(DoublyLinkedList& dll);


static bool endProgram = false;
/*
12345;Eastwing Hammer;50;29.99
45678;10d Galvanized Nails;80000;0.10
134;Stainley #2 Phillips Screwdriver;28;2.95
0123765;Dewalt Circular Saw;15;199.95
9345;Miter Box;4;23.95
*/

int main()
{

	DoublyLinkedList test(8);
	data t1("Eastwing Hammer", 50, 29.99);
	data t2("10d Galvanized Nails", 80000, 0.10);
	data t3("Stainley #2 Phillips Screwdriver", 28, 2.95);
	data t4("Dewalt Circular Saw", 15, 199.95);
	data t5("Miter Box", 4, 23.95);
	data t6("ladder", 20, 215.39);


	data found;

	std::cout<<"is empty: "<< test.isEmpty() <<std::endl;
	std::cout<<"is full: "<< test.isFull() <<std::endl;
	test.addItem("12345", t1);
	test.addItem("45678", t2);
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();
	test.addItem("134", t3);
	test.displayKeys();
	test.addItem("0123765", t4);
	test.addItem("9345", t5);
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();
	test.addItem("9437", t6);
	test.displayKeys();
	test.findItem(45678, found);
	found.displayData();
	test.displayKeys();
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();
	test.makeEmpty();
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();

	return 0;





	/*
	DoublyLinkedList inventory;
	inventoryLoader(inventory);
	displayMenu();
	validatePickLoop(inventory);
	return 0;
	*/

}//end main

void displayMenu() {
	std::cout << "a.)  Add new record" << std::endl;
	std::cout << "b.)  Delete record" << std::endl;
	std::cout << "c.)  Modify record" << std::endl;
	std::cout << "d.)  List all records by inventory number" << std::endl;
	std::cout << "e.)  List all records by COST" << std::endl;
	std::cout << "f.)  Quit and SAVE" << std::endl;
}//end method displayMenu

void validatePickLoop(DoublyLinkedList& dll)
{

		char pick;
		std::string _tn;

		while (!endProgram)
		{
			std::cout << "\nEnter Menu Option\n>>";
			std::cin >> pick;
			if (pick!='a'&&pick!='b'&&pick!='c'&&
				pick!='d'&&pick!='e'&&pick!='f')
			{
				std::cout << "That was no option! "
				     	  << "Please enter menu choice\n>>";
				std::cin.clear();
				std::cin.ignore();
				std::cin >> pick;
			}


			if (pick == 'a') {
				std::cout << "add item to inventory" << std::endl;
				std::string _id;
				int _stock;
				double _cost;
				std::cout << "Enter the name of Item to add\n>>";
				std::cin >> _tn;
				std::cout << "Enter item Inventory number\n>>";
				std::cin >> _id;
				std::cout << "Enter how many are in stock\n>>";
				std::cin >> _stock;
				std::cout << "Enter items cost\n>>";
				std::cin >> _cost;
				data tool(_tn, _stock, _cost);
				dll.addItem(_id, tool);
			}
			else if (pick == 'b')
			{
				std::cout << "case 2"<<std::endl;
			}
			else if (pick =='c')
			{
				std::cout << "case 3"<<std::endl;
			}
			else if (pick == 'd')
			{
				std::cout << "list all items by inventory #"<<std::endl;
				dll.displayKeys();
			}
			else if (pick == 'e')
			{
				std::cout << "case 5"<<std::endl;
			}
			else if (pick == 'f')
			{
				std::cout << "Exiting program and saving file"<<std::endl;
				endProgram = true;
			}

		}//end while loop
		exit(0);
}//end method validatePickLoop



void inventoryLoader(DoublyLinkedList& dll)
{

	std::ifstream inFile;
	std::string fileName = "inventory.txt";
	std::string line;
	std::string tempToolName;
	std::string tempKeyString;
	int tempKey;
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
		//std::cout << "line: " << line << std::endl;
		std::getline(ss, tempKeyString, ';');
		//std::cout << "temp-key: " << tempKeyString << std::endl;
		std::stringstream sss(tempKeyString);
		//sss >> tempKey; //std::stoi(tempKeyString);
		//std::cout << "int key: " << tempKey << std::endl;
		std::getline(ss, tempToolName, ';');
		//std::cout << "temp-tool-name: " << tempToolName<<std::endl;
		std::getline(ss, tempStockString, ';');
		//std::cout << "temp stock: " << tempStockString <<std::endl;
		std::stringstream ssss(tempStockString);
		ssss >>tempStock; // = std::stoi(tempStockString);
		//std::cout << "int stock: " << tempStock <<std::endl;
		std::getline(ss, tempCostString, ';');
		//std::cout << "temp cost: " << tempCostString<<std::endl;
		std::stringstream _ss(tempCostString);
		_ss >> tempCost;// = std::stod(tempCostString);
		//std::cout << "double cost: " << tempCost <<std::endl;
		data tempTool(tempToolName, tempStock, tempCost);
		dll.addItem(tempKeyString, tempTool);
	}

	std::cout << "Lists have been successfully loaded." << std::endl;
	inFile.close();
}//end method listLoader

/*
bool validateID(int _id)
{

}

bool validateCost(double _c)
{

}

bool validateStock(int _s)
{

}


DoublyLinkedList test(8);
	data t1("hammer", 5, 19.99);
	data t2("saw", 15, 22.50);
	data t3("level", 12, 15.99);
	data t4("nails", 45, 14.99);
	data t5("tape measure", 45, 12.50);
	data t6("ladder", 2, 215.39);
	data t7("hammer", 5, 19.99);
	data t8("saw", 15, 22.50);
	data t9("level", 12, 15.99);

	data found;

	std::cout<<"is empty: "<< test.isEmpty() <<std::endl;
	std::cout<<"is full: "<< test.isFull() <<std::endl;
	test.addItem(3, t1);
	test.addItem(2, t2);
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();
	test.addItem(5, t3);
	test.displayKeys();
	test.findItem(4, found);
	found.displayData();
	test.addItem(1, t4);
	test.addItem(6, t5);
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();
	test.addItem(4, t6);
	test.displayKeys();
	test.addItem(4, t6);
	test.displayKeys();
	test.deleteItem(4);
	test.findItem(6, found);
	found.displayData();
	test.displayKeys();
	std::cout << "qty: " << test.getQty() << std::endl;
	test.addItem(7, t7);
	test.displayKeys();
	test.addItem(8, t8);
	test.displayKeys();
	test.deleteItem(4);
	test.findItem(1, found);
	found.displayData();
	test.displayKeys();
	test.addItem(9, t9);
	test.addItem(10, found);
	std::cout<<"is empty: "<< test.isEmpty() <<std::endl;
	std::cout<<"is full: "<< test.isFull() <<std::endl;
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();
	test.makeEmpty();
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();

	return 0;


 */
