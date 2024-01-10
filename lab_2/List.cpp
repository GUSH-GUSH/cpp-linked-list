#include "List.h"

//Функції додавання
void List::AddToStart(const int data) {
	listItem* newItem = new listItem(data);

	if (head == NULL) head = newItem;
	else {
		newItem->nextItem = head;
		head = newItem;
	}
	this->length++;
}

void List::AddToEnd(const int data) {
	listItem* newItem = new listItem(data);

	if (head == NULL) head = newItem;
	else {
		listItem* curr = head;
		while (curr->nextItem) curr = curr->nextItem;
		curr->nextItem = newItem;
	}
	this->length++;
}

bool List::AddAfterPosition(const unsigned int index, const int data) {
	if (!head) return false;
	
	listItem* newItem = new listItem(data);
	listItem* currItem = head;
	unsigned int currIndex = 0;

	while (currItem) {
		if (currIndex == index) {
			newItem->nextItem = currItem->nextItem;
			currItem->nextItem = newItem;
			this->length++;
			return true;
		}

		currIndex++;
		currItem = currItem->nextItem;
	}
	return false;
}


//Функції видалення
bool List::DeleteFromStart() {
	if (!head) return false;

	listItem* newHead = head->nextItem;
	delete head;
	head = newHead;
	this->length--;
	return true;
}

bool List::DeletePosition(const unsigned int index) {
	if (!head) return false;
	if (index == 0) return DeleteFromStart();

	listItem* currItem = head->nextItem;
	listItem* prevItem = head;
	unsigned int currIndex = 1;

	while (currItem) {
		if (currIndex == index) {	//Дошли до удаляемого элемента
			prevItem->nextItem = currItem->nextItem;
			delete currItem;
			this->length--;
			return true;
		}

		currIndex++;
		prevItem = currItem;
		currItem = currItem->nextItem;
	}
	return false;
}

void List::DeleteEveryNth(const unsigned int N) {
	if (!head) return;
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

void List::Clear() {
	length = 0;
	while (head) {
		listItem* newHead = head->nextItem;
		delete head;
		head = newHead;
	}
}


//Варіант із переміщенням безпосередньо елемента
void List::Sort(bool sortUp) {
	if (!head) return;
	int index_i = 0;
	for (listItem* i = head; i->nextItem != NULL; i = i->nextItem, index_i++) {
		listItem* requiredItem = i;
		int requiredIndex = index_i, index_j = index_i + 1;

		for (listItem* j = i->nextItem; j != NULL; j = j->nextItem, index_j++)
			if ((requiredItem->data > j->data) == sortUp) { requiredItem = j; requiredIndex = index_j; }
		
		if (requiredIndex != index_i) {
			i = requiredItem;
			MoveElement(requiredIndex, index_i - requiredIndex); //Переміщуємо необхдний елемент на місце поточного
		}
	}
}

bool List::MoveElement(const int index, const int Npos) {
	if (!head) return false;

	const int newIndex = index + ((Npos > 0) ? (Npos + 1) : Npos);
	if (index < 0 || newIndex < 0 || index == newIndex) return false;

	int currIndex = 1;
	listItem
		* currItem = head->nextItem,
		* prevItem = head,
		* prevOfNewPos = NULL,
		* prevOfOldPos = NULL,
		* MovingItem = (index == 0) ? head : NULL;

	while (currItem && (!MovingItem || !prevOfNewPos)) {
		if (currIndex == index) { prevOfOldPos = prevItem; MovingItem = currItem; }
		else if (currIndex == newIndex) prevOfNewPos = prevItem;

		currIndex++;
		prevItem = currItem;
		currItem = currItem->nextItem;
	}

	if (!MovingItem) return false;	//Якщо зміщуваний об'экт не було знайдено

	//Виключна ситуація, коли зміщуємо в кінець
	if (currIndex == newIndex) prevOfNewPos = prevItem;

	listItem** p_prevOfOldPos_NI = NULL, ** p_prevOfNewPos_NI = NULL;

	//Виключні випадки, коли або переставляємо У початок, або ІЗ початку
	if (index == 0 && prevOfNewPos) p_prevOfOldPos_NI = &head; //Із початку
	else if (newIndex == 0 && prevOfOldPos) p_prevOfNewPos_NI = &head; //У початок
	else if (!prevOfOldPos || !prevOfNewPos) return false;

	//Якщо жоден з виключних випадків не спрацював, заповнюємо звичайними значеннями
	if (!p_prevOfOldPos_NI) p_prevOfOldPos_NI = &prevOfOldPos->nextItem;
	if (!p_prevOfNewPos_NI) p_prevOfNewPos_NI = &prevOfNewPos->nextItem;

	//Переставляємо елемент								(оновлюємо посилання)
	*p_prevOfOldPos_NI = MovingItem->nextItem;	//Попередньму елементу старої позиції
	MovingItem->nextItem = *p_prevOfNewPos_NI;	//Зміщуваному елементу оновлюємо посилання
	*p_prevOfNewPos_NI = MovingItem;			//Попередньму елементу нової позиції

	return true;
}


void List::CopyFromArr(int* arr, int length) {
	Clear();
	for (int i = length - 1; i >= 0; i--) AddToStart(arr[i]);
}

List* List::GetCopy() {
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

void List::Print() {
	if (!head) { cout << "Список порожній\n"; return; }
	for (listItem* currItem = head; currItem != NULL; currItem = currItem->nextItem) cout << currItem->data << "  ";
	cout << endl;
}


List* List::MergeLists(List& list1, List& list2) {
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
	delete secondPart;						//Аби при очищенні пам'яті елементи не видалялися
	return newList;
}

List* List::CreateIntersection(List& list1, List& list2) {
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