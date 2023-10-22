#pragma once

#include <iostream>
using namespace std;

class List {
private:
	struct listItem {
		int data;
		listItem* nextItem;

		listItem(int data, listItem* nextItem = NULL)
		{
			this->data = data;
			this->nextItem = nextItem;
		}
	};

	listItem* head = NULL;
	unsigned length = 0;
public:

	List() {}

	List(int* arr, int length) { CopyFromArr(arr, length); }	//Конструктор для копіювання із масиву

	~List() { Clear(); }

	unsigned GetLength() { return length; }

	//Функції додавання
	void AddToStart(const int data);							//Додати в початок

	void AddToEnd(const int data);								//Додати в кінець

	bool AddAfterPosition(const unsigned int position, const int data);		//Додати після позиції


	//Функції видалення
	bool DeleteFromStart();										//Видалити з початку

	bool DeletePosition(const unsigned int position);			//Видалити позицію (позиція від 1-го)

	void DeleteEveryNth(const unsigned int N);					//Видалення кожного N-го

	void Clear();


	bool MoveElement(const int posOfEl, const int Npos);		//Пересування елемента
	
	void Sort(bool sortUp = true);								//Сортування


	void CopyFromArr(int* arr, int length);						//Заповнння ліста із масиву

	List* GetCopy();											//Копіювання ліста


	void Print();


	static List* MergeLists(List& list1, List& list2);			//Склеювання двох лістів
	
	static List* CreateIntersection(List& list1, List& list2);	//Створення перерізу з двох лістів
};