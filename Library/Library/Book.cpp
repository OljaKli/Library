#include "Book.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//not used here
void Sort(char* pcFirst, int nNumber, int size,
	void(*Swap)(void*, void*), int(*Compare)(void*, void*))
{
	int i;
	for (i = 1; i<nNumber; i++)
		for (int j = nNumber - 1; j >= i; j--)
		{
			char* pCurrent = pcFirst + j * size;
			char* pPrevious = pcFirst + (j - 1)*size;
			if ((*Compare)(pPrevious, pCurrent) > 0)
				(*Swap)(pPrevious, pCurrent);
		}
}

void SwapInt(void* p1, void* p2)
{
	int* pnt1 = static_cast<int*>(p1);
	int* pnt2 = static_cast<int*>(p2);

	int tmp = *pnt1;
	*pnt1 = *pnt2;
	*pnt2 = tmp;
}

void SwapDouble(void* p1, void* p2)
{
	double* pnt1 = static_cast<double*>(p1);
	double* pnt2 = static_cast<double*>(p2);

	double tmp = *pnt1;
	*pnt1 = *pnt2;
	*pnt2 = tmp;
}

void SwapStr(void* p1, void* p2)
{
	char** pnt1 = reinterpret_cast<char**>(p1);
	char** pnt2 = reinterpret_cast<char**>(p2);

	char* tmp;
	tmp = *pnt1;
	*pnt1 = *pnt2;
	*pnt2 = tmp;
}

int CmpStr(void* p1, void* p2)
{
	int nResult;
	char** pnt1 = reinterpret_cast<char**>(p1);
	char** pnt2 = reinterpret_cast<char**>(p2);
	return strcmp(*pnt1, *pnt2);

}

int CmpInt(void* p1, void* p2)
{
	int nResult;
	int* pnt1 = static_cast<int*>(p1);
	int* pnt2 = static_cast<int*>(p2);

	if (*pnt1 > *pnt2) {
		nResult = 1;
	}
	if (*pnt1 < *pnt2) {
		return -1;
	}
	if (*pnt1 == *pnt2) {
		nResult = 0;
	}
	return nResult;
}

int CmpDouble(void* p1, void* p2)
{
	int nResult;
	double* pnt1 = static_cast<double*>(p1);
	double* pnt2 = static_cast<double*>(p2);

	if (*pnt1 > *pnt2) {
		nResult = 1;
	}
	if (*pnt1 < *pnt2) {
		return -1;
	}
	if (*pnt1 == *pnt2) {
		nResult = 0;
	}
	return nResult;
}


const char* ToString(CATEGORY v) {
	switch (v)
	{
	case FICTION:   return "Fiction";
	case DETECTIVE:   return "Detective";
	case HISTORICAL: return "Historical";
	case HUMOR: return "Humor";
	case HORROR: return "Horror";
	case MYSTERY: return "Mystery";
	case BIOGRAPHY: return "Biography";
	case WESTERN: return "Western";
	case SCIENCE: return "Science";

	}
}

void BookScanner(book& book) {
	std::cout << "Please enter the book's author." << std::endl;
	scanf_s("%19s", book.author, sizeof(book.author) - 1);

	std::cout << "Please enter the book's name." << std::endl;
	scanf_s("%19s", book.name, sizeof(book.name) - 1);

	std::cout << "Please enter the book's year of publish." << std::endl;
	int year = INT_MIN;
	scanf_s("%d", &year, sizeof(year));
	if (year >= 1564) {
		//year of books printing start
		book.yearOfPublish = year;
	}
	else {
		std::cout << "Please enter the coorect year of publishing!" << std::endl;
		return;
	}
	std::cout << "Please enter the book's price." << std::endl;
	double price = 0;
	scanf_s("%lf", &price, sizeof(price));
	if (price >= 0) {
		//year of books printing start
		book.price = price;
	}
	else {
		std::cout << "Please enter the coorect price of the book!" << std::endl;
		return;
	}
	std::cout << "Please enter the book's category." << std::endl;
	char categoryB[20];
	scanf_s("%19s", categoryB, sizeof(categoryB) - 1);
	if (strcmp(categoryB, "Fiction") == 0) {
		book.category = FICTION;
	}
	if (strcmp(categoryB, "Detective") == 0) {
		book.category = DETECTIVE;
	}
	if (strcmp(categoryB, "Historical") == 0) {
		book.category = HISTORICAL;
	}
	if (strcmp(categoryB, "Humor") == 0) {
		book.category = HUMOR;
	}
	if (strcmp(categoryB, "Horror") == 0) {
		book.category = HORROR;
	}
	if (strcmp(categoryB, "Mystery") == 0) {
		book.category = MYSTERY;
	}
	if (strcmp(categoryB, "Biography") == 0) {
		book.category = BIOGRAPHY;
	}
	if (strcmp(categoryB, "Western") == 0) {
		book.category = WESTERN;
	}
	if (strcmp(categoryB, "Science") == 0) {
		book.category = SCIENCE;
	}
	else {
		std::cout << "Please enter the coorect category of book from enum!" << std::endl;
		return;
	}
	//{FICTION, DETECTIVE, HISTORICAL, HUMOR, HORROR, MYSTERY, BIOGRAPHY, WESTERN, SCIENCE}
}

void addBook(CARD_INDEX *pCard, book* bookP) {

	int countV = pCard->count;
	if (countV >= pCard->cap) {
		book** tmp = new book*[countV + 1];
		for (int i = 0; i<(countV); i++) {
			tmp[i] = pCard->pBook[i];
		}
		delete[] pCard->pBook;
		pCard->pBook = tmp;
		pCard->cap++;

	}
	pCard->pBook[countV] = bookP;
	(pCard->count)++;
}


void printCatalogue(CARD_INDEX *pCard) {
	int countV = pCard->count; //the number of books in catalogue
	for (int i = 0; i < countV; i++) {
		book* curBook = pCard->pBook[i];
		std::cout << "Information about the book number: " << i + 1 << std::endl;
		printf("Book's author is: %s\nBook's name is: %s\nBook's price is: %g\nBook's year of publish is: %d\nBook's category is %s\n", curBook->author, curBook->name, curBook->price, curBook->yearOfPublish, ToString(curBook->category));
	}
}

void deleteBookByNum(CARD_INDEX *pCard, int n) {
	//number of book starts from 1, its position starts from 0 --> indx = n-1
	int indx = n - 1;
	delete pCard->pBook[indx];
	for (int i = indx; i < (pCard->count) - 1; i++) {
		pCard->pBook[i] = pCard->pBook[i + 1];
	}
	pCard->count--;
}

void scanCatalogue(CARD_INDEX *pCard, char* fileN, int n) {
	FILE* file = fopen(fileN, "r");

	if (file) {
		for (int i = 0; i < n; i++) {
			book* curBook = new book;
			char categoryC[20];
			fscanf_s(file, "%s", categoryC, sizeof(categoryC) - 1);
			curBook->category = getCategory(categoryC);
			fscanf_s(file, "%s", curBook->name, sizeof(curBook->name) - 1);
			fscanf_s(file, "%s", curBook->author, sizeof(curBook->author) - 1);
			fscanf_s(file, "%d", &curBook->yearOfPublish, sizeof(int));
			fscanf_s(file, "%lf", &curBook->price, sizeof(curBook->price));
			addBook(pCard, curBook);
			curBook = nullptr;
		}
	}
	fclose(file);
}
CATEGORY getCategory(const char* str) {
	CATEGORY category;
	if (strcmp(str, "Fiction") == 0) {
		category = FICTION;
	}
	if (strcmp(str, "Detective") == 0) {
		category = DETECTIVE;
	}
	if (strcmp(str, "Historical") == 0) {
		category = HISTORICAL;
	}
	if (strcmp(str, "Humor") == 0) {
		category = HUMOR;
	}
	if (strcmp(str, "Horror") == 0) {
		category = HORROR;
	}
	if (strcmp(str, "Mystery") == 0) {
		category = MYSTERY;
	}
	if (strcmp(str, "Biography") == 0) {
		category = BIOGRAPHY;
	}
	if (strcmp(str, "Western") == 0) {
		category = WESTERN;
	}
	if (strcmp(str, "Science") == 0) {
		category = SCIENCE;
	}
	return category;
}

void writeCatalogue(CARD_INDEX *pCard, char* fileN) {
	FILE* file = fopen(fileN, "w");
	if (file) {
		for (int i = 0; i < pCard->count; i++) {
			fprintf(file, "Book number: %d\n", (i + 1));
			fprintf(file, "Book's author is: %s\nBook's name is: %s\nBook's price is: %g\nBook's year of publish is: %d\nBook's category is %s\n", pCard->pBook[i]->author, pCard->pBook[i]->name, pCard->pBook[i]->price, pCard->pBook[i]->yearOfPublish, ToString(pCard->pBook[i]->category));
		}
		fclose(file);
	}
}

void deleteAllTheBooks(CARD_INDEX *pCard) {
	for (int i = 0; i < pCard->count; i++) {
		delete pCard->pBook[i];

	}
	delete[] pCard->pBook;
	pCard->pBook = nullptr;
	pCard->count = 0;
	pCard->cap = 0;
}


void catalogueSort(CARD_INDEX* pCard, SORTFEATURE feature) {
	switch (feature) {
	case CATEG: {
		bubble_sort_categ(pCard);
		printCatalogue(pCard);
		break;
	}
	case NAME: {
		bubble_sort_name(pCard);
		printCatalogue(pCard);
		break;
	}
	case AUTH: {
		bubble_sort_auth(pCard);
		printCatalogue(pCard);
		break;
	}
	case YEAR: {
		bubble_sort_year(pCard);
		printCatalogue(pCard);
		break;
	}
	case PRICE: {
		bubble_sort_price(pCard);
		printCatalogue(pCard);
		break;
	}

	}

}
//enum SORTFEATURE {CATEG, NAME, AUTH, YEAR, PRICE};

// TODO change all bubble sort methods to one.  
void bubble_sort_categ(CARD_INDEX* pCard)
{
	for (size_t i = 0; i < (pCard->count) - 1; i++)
	{
		for (size_t j = 0; j < (pCard->count) - i - 1; j++)
		{
			if (pCard->pBook[j + 1]->category < pCard->pBook[j]->category)
			{
				book* tmp;
				tmp = pCard->pBook[j];
				pCard->pBook[j] = pCard->pBook[j + 1];
				pCard->pBook[j + 1] = tmp;
			}
		}
	}
}

void bubble_sort_auth(CARD_INDEX* pCard)
{
	for (size_t i = 0; i < (pCard->count) - 1; i++)
	{
		for (size_t j = 0; j < (pCard->count) - i - 1; j++)
		{
			if (strcmp(pCard->pBook[j + 1]->author, pCard->pBook[j]->author) < 0)
			{
				book* tmp;
				tmp = pCard->pBook[j];
				pCard->pBook[j] = pCard->pBook[j + 1];
				pCard->pBook[j + 1] = tmp;
			}
		}
	}
}

void bubble_sort_name(CARD_INDEX* pCard)
{
	for (size_t i = 0; i < (pCard->count) - 1; i++)
	{
		for (size_t j = 0; j < (pCard->count) - i - 1; j++)
		{
			if (strcmp(pCard->pBook[j + 1]->name, pCard->pBook[j]->name) < 0)
			{
				book* tmp;
				tmp = pCard->pBook[j];
				pCard->pBook[j] = pCard->pBook[j + 1];
				pCard->pBook[j + 1] = tmp;
			}
		}
	}
}

void bubble_sort_year(CARD_INDEX* pCard)
{
	for (size_t i = 0; i < (pCard->count) - 1; i++)
	{
		for (size_t j = 0; j < (pCard->count) - i - 1; j++)
		{
			if (pCard->pBook[j + 1]->yearOfPublish > pCard->pBook[j]->yearOfPublish)
			{
				book* tmp;
				tmp = pCard->pBook[j];
				pCard->pBook[j] = pCard->pBook[j + 1];
				pCard->pBook[j + 1] = tmp;
			}
		}
	}
}

void bubble_sort_price(CARD_INDEX* pCard)
{
	for (size_t i = 0; i < (pCard->count) - 1; i++)
	{
		for (size_t j = 0; j < (pCard->count) - i - 1; j++)
		{
			if (pCard->pBook[j + 1]->price > pCard->pBook[j]->price)
			{
				book* tmp;
				tmp = pCard->pBook[j];
				pCard->pBook[j] = pCard->pBook[j + 1];
				pCard->pBook[j + 1] = tmp;
			}
		}
	}
}

void sortCall(CARD_INDEX* catalogue) {
	std::cout << "Please define the sort method: "
		<< "Type (1) to sort books by category;\n"
		<< "Type (2) to sort books by author;\n"
		<< "Type (3) to sort books by name;\n"
		<< "Type (4) to sort books by year of publish;\n"
		<< "Type (5) to sort books by price;\n"
		<< std::endl;
	int answSort;
	std::cin >> answSort;
	switch (answSort) {
	case 1: {
		catalogueSort(catalogue, CATEG);
		break;
	}
	case 2: {
		catalogueSort(catalogue, AUTH);
		break;
	}
	case 3: {
		catalogueSort(catalogue, NAME);
		break;
	}
	case 4: {
		catalogueSort(catalogue, YEAR);
		break;
	}
	case 5: {
		catalogueSort(catalogue, PRICE);
		break;
	}
	}
}