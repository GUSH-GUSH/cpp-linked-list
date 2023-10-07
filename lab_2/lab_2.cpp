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


	// -1  -  ok														  = = ->
	//  1  -  not ok (fix = all what is more than zero must be increased) = -> =

	//Дописать коменты
	bool MoveElement(const int posOfEl, const int Npos) {
		if (!head) return false;

		const int newPos = posOfEl + ((Npos > 0) ? (Npos + 1) : Npos);
		if (posOfEl < 1 || newPos < 1 || posOfEl == newPos) return false;	//Якщо некоректні позиції елементів

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

		ListItem** p_prevOfOldPos_NI = NULL, ** p_prevOfNewPos_NI = NULL;

		//Два виключні випадки, коли або переставляємо У початок, або ІЗ початку
		if (posOfEl == 1 && prevOfNewPos) p_prevOfOldPos_NI = &head; //Із початку
		else if (newPos == 1 && prevOfOldPos) p_prevOfNewPos_NI = &head; //У початок
		else if (!prevOfOldPos || !prevOfNewPos) return false;


		if (!p_prevOfOldPos_NI) p_prevOfOldPos_NI = &prevOfOldPos->nextItem;
		if (!p_prevOfNewPos_NI) p_prevOfNewPos_NI = &prevOfNewPos->nextItem;


		*p_prevOfOldPos_NI = MovingItem->nextItem;
		MovingItem->nextItem = *p_prevOfNewPos_NI;
		*p_prevOfNewPos_NI = MovingItem;

		return true;
	}

	//Посмотреть про конструктор копирования
	List* GetCopy() {
		List* listCopy = new List;
		
		ListItem* currItem = head, **currItemCopy = &listCopy->head;

		while (currItem) {
			*currItemCopy = new ListItem(currItem->data);
			
			currItem = currItem->nextItem;
			currItemCopy = &((*currItemCopy)->nextItem);
		}
		return listCopy;
	}
	//Проверить

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


	~List() { Clear(); }


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


	cout << (list.MoveElement(-5, 0) ? "Сместилось" : "Не сместилось(") << "\n\n\n";
	list.__debug_print();

	List* list2 = list.GetCopy();
	list2->DeleteEveryNth(2);

	cout << "\n\n";
	list.__debug_print();
	list2->__debug_print();
	
	char exit;
	cin >> exit;
	do {
		system("cls");

		int pos, N;

		list.__debug_print();
		
		cout << "\n\n";
		cout << "Введите номер элемента: ";
		cin >> pos;
		cout << "Введите количество позиций: ";
		cin >> N;
		
		cout << "\n" << (list.MoveElement(pos, N) ? "Сместилось" : "Не сместилось(") << "\n\n\n";

		list.__debug_print();

		cin >> exit;

	} while (exit != 'e');

	cout << "\n\n";
}