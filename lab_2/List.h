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
	void AddToStart(const int data) { //Приймає безпосередньо дані, які треба додати

		listItem* newItem = new listItem(data);

		if (head == NULL) head = newItem;
		else {
			newItem->nextItem = head;
			head = newItem;
		}
		this->length++;
	}

	void AddToEnd(const int data) {
		listItem* newItem = new listItem(data);

		if (head == NULL) head = newItem;
		else {
			listItem* curr = head;

			while (curr->nextItem) curr = curr->nextItem;

			curr->nextItem = newItem;
		}
		this->length++;
	}

	bool AddAfterPosition(const unsigned int position, const int data) {

		if (position == 0) { AddToStart(data); return true; }

		listItem* newItem = new listItem(data);

		listItem* currItem = head;
		unsigned int currPosition = 1;


		while (currItem) {
			if (currPosition == position) {
				newItem->nextItem = currItem->nextItem;
				currItem->nextItem = newItem;
				this->length++;
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

		listItem* newHead = head->nextItem;
		delete head;
		head = newHead;
		this->length--;
		return true;
	}

	bool DeletePosition(const unsigned int position) {
		if (!position) return false;
		if (position == 1) return DeleteFromStart();

		listItem* currItem = head->nextItem;
		listItem* prevItem = head;
		unsigned int currPosition = 2;

		while (currItem) {
			if (currPosition == position) { //Дошли до удаляемого элемента - currItem;
				prevItem->nextItem = currItem->nextItem;
				delete currItem;
				this->length--;
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

		listItem* currItem = head->nextItem;
		listItem* prevItem = head;

		unsigned int position = 2;

		while (currItem) {
			if (position % N == 0) {
				prevItem->nextItem = currItem->nextItem;
				delete currItem;
				currItem = prevItem;

				this->length--;
			}

			position++;
			prevItem = currItem;
			currItem = currItem->nextItem;
		}
	}

	//void DeleteFromEnd() {}

	void Clear() {
		length = 0;
		while (head) {
			listItem* newHead = head->nextItem;
			delete head;
			head = newHead;
		}
	}

	void Sort(bool sortUp = true) {
		if (!head) return;
		for (listItem* i = head; i->nextItem != NULL; i = i->nextItem) {
			listItem* RequiredItem = i;

			for (listItem* j = i->nextItem; j != NULL; j = j->nextItem)
				if ((RequiredItem->data > j->data) == sortUp) RequiredItem = j; //Добавить опциональную сортировку (вверх, вниз)

			if (RequiredItem->data != i->data) {
				int temp = i->data;
				i->data = RequiredItem->data;
				RequiredItem->data = temp;
			}
		}
	}


	//Дописать коменты
	bool MoveElement(const int posOfEl, const int Npos) {
		// -1  -  ok														  = = ->
		//  1  -  not ok (fix = all what is more than zero must be increased) = -> =

		if (!head) return false;

		const int newPos = posOfEl + ((Npos > 0) ? (Npos + 1) : Npos);
		if (posOfEl < 1 || newPos < 1 || posOfEl == newPos) return false;	//Якщо некоректні позиції елементів

		int currPos = 2;
		listItem
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

		listItem** p_prevOfOldPos_NI = NULL, ** p_prevOfNewPos_NI = NULL;

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


	void CopyFromArr(int* arr, int length) {
		Clear();
		for (int i = length - 1; i >= 0; i--)
			AddToStart(arr[i]);
	}



	//Посмотреть про конструктор копирования
	List* GetCopy() {
		List* listCopy = new List(*this);

		listItem* currItem = head;
		listItem** currItemCopy = &listCopy->head;

		while (currItem) {
			*currItemCopy = new listItem(currItem->data);

			currItem = currItem->nextItem;
			currItemCopy = &((*currItemCopy)->nextItem);
		}
		return listCopy;
	}
	//Проверить


	int* Get(const unsigned int index) {
		listItem* currItem = head;
		unsigned int currIndex = 0;

		while (currItem) {
			if (currIndex == index) return &currItem->data;

			currIndex++;
			currItem = currItem->nextItem;
		}

		//Добавить exception

		return NULL;
	}


	void Print() {
		if (!head) { cout << "Список порожній\n"; return; }
		listItem* currItem = head;

		while (currItem) {
			cout << currItem->data << "  ";
			currItem = currItem->nextItem;
		}

		cout << endl;
	}

	static List* MergeLists(List& list1, List& list2) {
		if (!list1.head && !list2.head) return NULL;
		else if (!list1.head) return list2.GetCopy();
		else if (!list2.head) return list1.GetCopy();

		List* newList = list1.GetCopy();	//За основу нового ліста береться копія list1

		listItem* lastItem = newList->head;
		while (lastItem->nextItem) lastItem = lastItem->nextItem;	//Шукається останній елемент

		List* secondPart = list2.GetCopy();		//Створюється копія list2
		lastItem->nextItem = secondPart->head;	//У кінець новго ліста записується початок копії list2
		newList->length += secondPart->length;	//Сумується поле length

		secondPart->head = NULL;				//У копії list2 затирається посилання head
		delete secondPart;						//Аби при очищенні пам'яті елементи не стерлися
		return newList;
	}

	static List* CreateIntersection(List& list1, List& list2) {
		if (!list1.head || !list2.head) return NULL;

		List* newList = new List();
		List* smallerList = &list1, * largerList = &list2;

		if (list1.length > list2.length) { smallerList = &list2; largerList = &list1; }

		for (listItem* pl1 = smallerList->head; pl1; pl1 = pl1->nextItem) {
			bool isAdded = false;

			for (listItem* pnl = newList->head; pnl; pnl = pnl->nextItem)
				if (pnl->data == pl1->data) { isAdded = true; break; }

			if (isAdded) continue;

			for (listItem* pl2 = largerList->head; pl2; pl2 = pl2->nextItem) {
				if (pl1->data == pl2->data) {
					newList->AddToEnd(pl1->data);
					break;
				}
			}
		}
		return newList;
	}
};