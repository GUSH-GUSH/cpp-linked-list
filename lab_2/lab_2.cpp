#include <iostream>
#include <windows.h>

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
public:

	List() {}

	~List() { Clear(); }

	//Функції додавання
	void AddToStart(const int data) { //Приймає безпосередньо дані, які треба додати

		listItem* newItem = new listItem(data);

		if (head == NULL) head = newItem;
		else {
			newItem->nextItem = head;
			head = newItem;
		}
	}

	void AddToEnd(const int data) {
		listItem* newItem = new listItem(data);

		if (head == NULL) head = newItem;
		else {
			listItem* curr = head;

			while (curr->nextItem) curr = curr->nextItem;

			curr->nextItem = newItem;
		}
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
			}

			position++;
			prevItem = currItem;
			currItem = currItem->nextItem;
		}
	}

	void DeleteFromEnd() {}

	void Clear() {
		while (head) {
			listItem* newHead = head->nextItem;
			delete head;
			head = newHead;
		}
	}


	void Sort(bool sortUp = true) {
		
		for(listItem* i = head; i->nextItem != NULL; i = i->nextItem) {
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






	//Посмотреть про конструктор копирования
	List* GetCopy() {
		List* listCopy = new List;
		
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


	void __debug_print() {
		if (!head) { cout << "Список порожній\n"; return; }
		listItem* currItem = head;

		while (currItem) {
			cout << currItem->data << "  ";
			currItem = currItem->nextItem;
		}

		cout << endl;
	}


	/*static List* CreateIntersection(List& list1, List& list2) {
		List* newList = new List();

		for (listItem* pl1 = list1.head, *pl2 = list2.head; pl1 && pl2; pl1 = pl1->nextItem, pl2 = pl2->nextItem)
			if (pl1->data == pl2->data) newList->AddToEnd(pl1->data);

		return newList;
	}*/
	//Да.. Но нет) Тут он будет идти синхронно по двум спискам, и копировать встретившиееся одинаковые, на одинаковых ПОЗИЦИЯХ
	//А суть задачи немного другая. Пересечение. Тоесть элементы, которые есть в обоих списках, внезависимости от их позиций


	static List* CreateIntersection(List& list1, List& list2) {
		if (!list1.head || !list2.head) return NULL;

		List* newList = new List();

		for (listItem* pl1 = list1.head; pl1; pl1 = pl1->nextItem) {
			
		}
		return newList;
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

	list.Sort();
	list.__debug_print();
	cout << "\n\n";
	

	List* list2 = list.GetCopy();
	list2->DeleteEveryNth(2);

	cout << "\n\n";
	list.__debug_print();
	list2->__debug_print();
	//list1		4 5 1 6 10 8 129
	//list2		4 1 10 129

	list2->AddAfterPosition(3, 8);
	cout << "\n\n";


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