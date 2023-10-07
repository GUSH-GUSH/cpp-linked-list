#include <iostream>
#include <windows.h>

using namespace std;



class List {
private:
	struct ListItem {
		int data;
		ListItem* nextItem;

		ListItem(int data, ListItem* nextItem = NULL)
		{
			this->data = data;
			this->nextItem = nextItem;
		}
	};

	ListItem* getListItem(const unsigned int index) {
		ListItem* currItem = head;
		int currIndex = 0;

		while (currItem) {
			if (currIndex == index) return currItem;

			currIndex++;
			currItem = currItem->nextItem;
		}
		return NULL;
	}

	ListItem* head = NULL;
public:

	//Функції додавання
	void AddToStart(const int data) { //Приймає безпосередньо дані, які треба додати

		ListItem* newItem = new ListItem(data);

		if (head == NULL) head = newItem;
		else {
			newItem->nextItem = head;
			head = newItem;
		}
	}

	void AddToEnd(const int data) {
		ListItem* newItem = new ListItem(data);

		if (head == NULL) head = newItem;
		else {
			ListItem* curr = head;

			while (curr->nextItem) curr = curr->nextItem;

			curr->nextItem = newItem;
		}
	}

	bool AddAfterPosition(const unsigned int position, const int data) {

		if (position == 0) { AddToStart(data); return true; }

		ListItem* newItem = new ListItem(data);

		ListItem* currItem = head;
		unsigned int currPosition = 1;


		while (currItem) {
			if (currPosition == position) {
				newItem->nextItem = currItem->nextItem;
				currItem->nextItem = newItem;
				return true;
			}

			currPosition++;
			currItem = currItem->nextItem;
		}
		return false;
	}


	//Функції видалення
	bool DeleteFromStart() {
		if (!head) return false;

		ListItem* newHead = head->nextItem;
		delete head;
		head = newHead;
		return true;
	}

	bool DeletePosition(const unsigned int position) {
		if (!position) return false;
		if (position == 1) return DeleteFromStart();

		ListItem* currItem = head->nextItem;
		ListItem* prevItem = head;
		unsigned int currPosition = 2;

		while (currItem) {
			if (currPosition == position) { //Дошли до удаляемого элемента - currItem;
				prevItem->nextItem = currItem->nextItem;
				delete currItem;
				return true;
			}

			currPosition++;
			prevItem = currItem;
			currItem = currItem->nextItem;
		}
		return false;
	}

	void DeleteEveryNth(const unsigned int N) {
		if (!N) return;
		if (N == 1) return Clear();

		ListItem* currItem = head->nextItem;
		ListItem* prevItem = head;

		unsigned int position = 2;

		while (currItem) {
			if (position % N == 0) {
				prevItem->nextItem = currItem->nextItem;
				delete currItem;
				currItem = prevItem;
			}

			position++;
			prevItem = currItem;
			currItem = currItem->nextItem;
		}
	}

	void DeleteFromEnd() {}

	void Clear() {
		while (head) {
			ListItem* newHead = head->nextItem;
			delete head;
			head = newHead;
		}
	}


	/*bool MoveElement(const unsigned int positionOfElement, const int N_position) {

		const int newPosition = positionOfElement + N_position;

		if (positionOfElement < 1 || newPosition < 1) return false;

		int* pointOfElement = Get(positionOfElement-1);

		if (!pointOfElement || !AddAfterPosition(newPosition-1, *pointOfElement)) return false;

		DeletePosition((newPosition <= positionOfElement) ? positionOfElement + 1 : positionOfElement);

		return true;

		//Вроде да, но нет))
	}*/

	// -1  -  ok														  = = ->
	//  1  -  not ok (fix = all what is more than zero must be increased) = -> =

	bool MoveElement(const int posOfEl, const int Npos) {
		if (!head) return false;

		const int newPos = posOfEl + ((Npos > 0) ? (Npos + 1) : Npos);
		if (posOfEl < 1 || newPos < 1 || posOfEl == newPos) return false;	//Якщо некоректні індекси елементів

		int currPos = 2;
		ListItem
			* currItem = head->nextItem,
			* prevItem = head,
			* prevOfNewPos = NULL,
			* prevOfOldPos = NULL,
			* MovingItem = (posOfEl == 1) ? head : NULL;

		while (currItem) {
			if (currPos == posOfEl) { prevOfOldPos = prevItem; MovingItem = currItem; }
			else if (currPos == newPos) prevOfNewPos = prevItem;

			currPos++;
			prevItem = currItem;
			currItem = currItem->nextItem;
		}

		if (!MovingItem) return false;	//Якщо зміщуваний об'экт не було знайдено

		//Виключна ситуація, коли зміщуємо в кінець
		if (currPos == newPos) prevOfNewPos = prevItem;

		//Два виключні випадки, коли або переставляємо У початок, або ІЗ початку
		//Із початку
		if (posOfEl == 1 && prevOfNewPos) {
			head = MovingItem->nextItem;
			MovingItem->nextItem = prevOfNewPos->nextItem;
			prevOfNewPos->nextItem = MovingItem;
			return true;
		}//У початок
		else if (newPos == 1 && prevOfOldPos) {
			prevOfOldPos->nextItem = MovingItem->nextItem;
			MovingItem->nextItem = head;
			head = MovingItem;
			return true;
		}
		else if (!prevOfOldPos || !prevOfNewPos) return false;

		//Тепер перестановка зі старої позиції на 

		prevOfOldPos->nextItem = MovingItem->nextItem;
		MovingItem->nextItem = prevOfNewPos->nextItem;
		prevOfNewPos->nextItem = MovingItem;

		return true;
	}



	int* Get(const unsigned int index) {
		ListItem* currItem = head;
		unsigned int currIndex = 0;

		while (currItem) {
			if (currIndex == index) return &currItem->data;

			currIndex++;
			currItem = currItem->nextItem;
		}

		//Добавить exception

		return NULL;
	}




	void __debug_print() {
		if (!head) { cout << "Список порожній\n"; return; }
		ListItem* currItem = head;

		while (currItem) {
			cout << currItem->data << "  ";
			currItem = currItem->nextItem;
		}

		cout << endl;
	}
};


int main()
{
	SetConsoleOutputCP(1251);

	List list;

	//cout << list.Get(10) << endl;

	list.AddToStart(1);
	list.AddToStart(5);

	list.AddToEnd(6);
	list.AddToEnd(8);

	list.AddAfterPosition(3, 10);

	list.AddAfterPosition(5, 129);

	list.AddAfterPosition(0, 4);

	//4 5 1 6 10 8 129

	list.__debug_print();
	cout << "\n\n";


	list.MoveElement(5, 2);

	list.__debug_print();
	cout << "\n\n";


	/*
	list.DeleteEveryNth(2);
	//4 1 10 129
	list.__debug_print(); cout << "\n\n";
	*/

	/*
	list.DeleteFromStart();
	//5 1 6 10 8 129
	list.__debug_print(); cout << "\n\n";



	list.DeletePosition(3);
	//5 1 10 8 129
	list.__debug_print(); cout << "\n\n";



	list.DeletePosition(1);
	//1 10 8 129
	list.__debug_print(); cout << "\n\n";



	list.DeletePosition(0);
	//1 10 8 129
	list.__debug_print(); cout << "\n\n";



	list.DeletePosition(5);
	//1 10 8 129
	list.__debug_print(); cout << "\n\n";



	list.DeletePosition(4);
	//1 10 8 129
	list.__debug_print(); cout << "\n\n";
	*/

}

