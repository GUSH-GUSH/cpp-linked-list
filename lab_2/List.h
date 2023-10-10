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

	List(int* arr, int length) { CopyFromArr(arr, length); }

	~List() { Clear(); }

	unsigned GetLength() { return length; }

	//Функції додавання
	void AddToStart(const int data); //Приймає безпосередньо дані, які треба додати

	void AddToEnd(const int data);

	bool AddAfterPosition(const unsigned int position, const int data);


	//Функції видалення
	bool DeleteFromStart();

	bool DeletePosition(const unsigned int position);

	void DeleteEveryNth(const unsigned int N);

	void Clear();



	//Дописать коменты
	bool MoveElement(const int posOfEl, const int Npos);
	
	void Sort(bool sortUp = true);


	void CopyFromArr(int* arr, int length);

	List* GetCopy();


	void Print();


	static List* MergeLists(List& list1, List& list2);

	static List* CreateIntersection(List& list1, List& list2);
};