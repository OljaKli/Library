#pragma once

#include <cstdio>
#include <string>
#include <fstream>

double Sum(double a, double b);
double Sub(double a, double b);
double Mul(double a, double b);
double Div(double a, double b);


void Sort(char* pcFirst, int nNumber, int size,
	void(*Swap)(void*, void*), int(*Compare)(void*, void*));
void SwapInt(void* p1, void* p2);
int CmpInt(void* p1, void* p2);

void SwapDouble(void* p1, void* p2);
int CmpDouble(void* p1, void* p2);

void SwapStr(void* p1, void* p2);
int CmpStr(void* p1, void* p2);

const char* GetString1();
const char* GetString2();
const char* GetString3();
const char* GetString4();
const char* GetString5();

const char str[] = "Lollipop";
const char str1[] = "MiuMiu";
const char str2[] = "Oklisho";
const char str3[] = "RedHotChiliPeppers";
const char str4[] = "GunsNRoses";

enum CATEGORY { BIOGRAPHY, DETECTIVE, FICTION, HISTORICAL, HORROR, HUMOR, MYSTERY, SCIENCE, WESTERN };
enum SORTFEATURE { CATEG, NAME, AUTH, YEAR, PRICE };

struct book {
	CATEGORY category;
	char name[80];
	char author[30];
	int yearOfPublish;
	double price;
};
struct CARD_INDEX {
	book** pBook;
	size_t count;
	size_t cap;
};

const char* ToString(CATEGORY v);
void BookScanner(book& book);

void addBook(CARD_INDEX *pCard, book* bookP);
void printCatalogue(CARD_INDEX *pCard);
void deleteBookByNum(CARD_INDEX *pCard, int n);

void scanCatalogue(CARD_INDEX *pCard, char* file, int n);
void writeCatalogue(CARD_INDEX *pCard, char* file);
CATEGORY getCategory(const char* str);

void deleteAllTheBooks(CARD_INDEX *pCard);

void catalogueSort(CARD_INDEX* pCard, SORTFEATURE feature);

void bubble_sort_categ(CARD_INDEX* pCard);
void bubble_sort_year(CARD_INDEX* pCard);
void bubble_sort_price(CARD_INDEX* pCard);
void bubble_sort_auth(CARD_INDEX* pCard);
void bubble_sort_name(CARD_INDEX* pCard);

void sortCall(CARD_INDEX* pCard);