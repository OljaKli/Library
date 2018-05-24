#include <iostream>
#include "Book.h"

#define	  stop __asm nop	




void main()
{

	book ** pB = new book*[6];
	book* book1 = new book;
	book* book2 = new book;
	book* book3 = new book;
	book* book4 = new book;
	book* book5 = new book;

	//book1 init
	strncpy_s((*book1).author, "Bjarne Stroustrup", sizeof((*book1).author) - 1);
	(*book1).category = SCIENCE;
	strncpy_s((*book1).name, "A Tour of C++", sizeof((*book1).name) - 1);
	(*book1).price = 1000.0;
	(*book1).yearOfPublish = 2013;

	//book2 init
	strncpy_s((*book2).author, "Sergei Dovlatov", sizeof((*book2).author) - 1);
	(*book2).category = HUMOR;
	strncpy_s((*book2).name, "Chemodan", sizeof((*book2).name) - 1);
	(*book2).price = 300.0;
	(*book2).yearOfPublish = 1986;

	//book3 init
	strncpy_s((*book3).author, "Victor Pelevin", sizeof((*book3).author) - 1);
	(*book3).category = FICTION;
	strncpy_s((*book3).name, "Generation Pi", sizeof((*book3).name) - 1);
	(*book3).price = 500.0;
	(*book3).yearOfPublish = 2015;

	//book4 init
	strncpy_s((*book4).author, "Franchesko Petrarka", sizeof((*book4).author) - 1);
	(*book4).category = MYSTERY;
	strncpy_s((*book4).name, "Poems", sizeof((*book4).name) - 1);
	(*book4).price = 1500.0;
	(*book4).yearOfPublish = 2011;

	//book5 init
	strncpy_s((*book5).author, "Vladimir Mayakovskiy", sizeof((*book5).author) - 1);
	(*book5).category = FICTION;
	strncpy_s((*book5).name, "Oblako v shtanakh", sizeof((*book5).name) - 1);
	(*book5).price = 999.0;
	(*book5).yearOfPublish = 2001;

	CARD_INDEX* catalogue = new CARD_INDEX;
	catalogue->pBook = pB;
	catalogue->cap = 6;
	catalogue->count = 0;
	addBook(catalogue, book1);
	addBook(catalogue, book3);
	addBook(catalogue, book2);
	addBook(catalogue, book4);
	addBook(catalogue, book5);

	char fileR[] = { "F:\FileToRead.txt" };
	char fileW[] = { "F:\FileToWrite.txt" }; //TODO change to set by user

	int trigger = 0;
	while (trigger == 0) {
		std::cout << "Please choose the action: " << std::endl
			<< "Type (1) to print the catalogue content;" << std::endl
			<< "Type (2) to add the book to catalogue;" << std::endl
			<< "Type (3) to delete book(s) from catalogue;" << std::endl
			<< "Type (4) to write the catalogue to file;" << std::endl
			<< "Type (5) to read the book(s) from file;" << std::endl
			<< "Type (6) to select the sort method;" << std::endl
			<< "Type (0) to exit;" << std::endl;
		int answer;
		std::cin >> answer;
		switch (answer) {
		case 1: {
			printCatalogue(catalogue);
			break;
		}
		case 2: {
			book* newBook = new book;
			BookScanner(*newBook);
			addBook(catalogue, newBook);
			break;
		}
		case 3: {
			char answerC[3];
			std::cout << "Do you want to delete all the books? type y/n?" << std::endl;
			std::cin >> answerC;
			if (strcmp(answerC, "y") == 0) {
				deleteAllTheBooks(catalogue);
				break;
			}
			else if (strcmp(answerC, "n") == 0) {
				int num;
				std::cout << "So please define the book's number to delete" << std::endl;
				std::cin >> num;
				deleteBookByNum(catalogue, num);
				break;
			}
			else {
				std::cout << "Incorrect answer!" << std::endl;
				break;
			}

		}
		case 4: {
			writeCatalogue(catalogue, fileW);
			break;
		}

		case 5: {
			int fileNum;
			std::cout << "How many books are there in the file?" << std::endl;
			std::cin >> fileNum;
			scanCatalogue(catalogue, fileR, fileNum);
			break;
		}
		case 6: {
			sortCall(catalogue);
			break;
		}

		case 0: {
			trigger = 1;
			break;
		}
		default: {
			std::cout << "Please define the value from the list!" << std::endl;
		}
		}
		printCatalogue(catalogue);
		stop
	}


	deleteAllTheBooks(catalogue);
	delete catalogue;
	stop

}