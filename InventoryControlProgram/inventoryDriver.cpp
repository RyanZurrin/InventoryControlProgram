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
void menuOptions(char choice, DoublyLinkedList& dll);
void validatePickLoop(DoublyLinkedList& dll);
void inventoryLoader(DoublyLinkedList& dll);


static bool endProgram;

int main()
{
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

		int pick;
		while (!endProgram)
		{
			std::cout << "\nEnter Menu Option\n>>";
			std::cin >> pick;
				if (pick >= 1 && pick <= 6) {
					menuOptions(pick, dll);
				}
				else
				{
					std::cout << "Invalid choice\n" << std::endl;
					std::cin.clear();
					std::cin.ignore(100, '\n');
				}

	 }
}//end method validatePickLoop

void menuOptions(char choice, DoublyLinkedList& dll)
{
	switch (choice)
	{
		case 'a':
			std::cout << "case 1"<<std::endl;
			break;
		case 'b':
			std::cout << "case 2"<<std::endl;
			break;
		case 'c':
			std::cout << "case 3"<<std::endl;
			break;
		case 'd':
			std::cout << "case 4"<<std::endl;
			break;
		case 'e':
			std::cout << "case 5"<<std::endl;
			break;
		case 'f':
			std::cout << "case 6"<<std::endl;
			break;
		default:
			displayMenu();
			break;
	}
}//end method menuOptions


void inventoryLoader(DoublyLinkedList& dll)
{
	std::ifstream inFile;
	std::string fileName = "inventory.txt";
	int toList;
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
				menuOptions(6,dll);
				exit(0);
			}
		}

		inFile.open(fileName.c_str());
		if (!inFile)
		{
			std::cout << "file not found, type 'exit' to end program, or" << std::endl;
			fileNotFoundError = true;
		}
	} while (!inFile);

	while (!inFile.eof())
	{

	}

	std::cout << "Lists have been successfully loaded." << std::endl;
	inFile.close();
}//end method listLoader





/*
 * 	data t1("hammer", 5, 19.99);
	data t2("saw", 15, 22.50);
	data t3("level", 12, 15.99);
	data t4("nails", 45, 14.99);
	data t5("tape measure", 45, 12.50);
	data t6("ladder", 2, 215.39);
	data found;

	test.addItem(3, t1);
	test.addItem(2, t2);
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();
	test.addItem(5, t3);
	test.displayKeys();
	test.addItem(1, t1);
	test.addItem(6, t2);
	std::cout << "qty: " << test.getQty() << std::endl;
	test.displayKeys();
	test.addItem(4, t3);
	test.displayKeys();
	test.addItem(4, t3);
	test.displayKeys();
	test.deleteItem(4);
	test.findItem(6, found);
	found.displayData();
	test.displayKeys();
	std::cout << "qty: " << test.getQty() << std::endl;
 */