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

int InputElement() {
	int value;
	cout << "Введіть значення: ";
	cin >> value;
	return value;
}
unsigned InputPosition(unsigned maxPos = 1, unsigned minPos = 0) {
	unsigned pos;
	do {
		cout << "Введіть позицію [" << minPos << " - " << maxPos << "]: ";
		cin >> pos;
	} while (maxPos < pos || pos < minPos);
	return pos;
}

void listPrint(const char* listName, List* list) {
	cout << listName << "  {length = " << list->GetLength() << "}\n\n";
	list->Print();
	cout << "\n\n";
}

int main()
{
	SetConsoleOutputCP(1251);

	List* list1, * list2, * IntersectedList, * MergedList, * ListCopy;

	int arr1[7] = { 4, 5, 1, 6, 10, 8, 129 };
	int arr2[5] = { 13, 8, 125, 4, 0 };

	list1 = new List(arr1, 7);
	list2 = new List(arr2, 5);
	IntersectedList = MergedList = ListCopy = NULL;


	int answ;
	do {
		system("cls");
		listPrint("List1", list1);
		listPrint("List2", list2);
		if (ListCopy) listPrint("Скопійований", ListCopy);
		if (MergedList) listPrint("Склеєний", MergedList);
		if (IntersectedList) listPrint("Переріз", IntersectedList);

		List* list = NULL;
		char whoseList = 0;
		cout << "\n******************************";
		cout << "\n#1 -> Додати на початок";
		cout << "\n#2 -> Додати в кінець=";
		cout << "\n#3 -> Додати після позиції";
		cout << "\n#4 -> Видалити із початку=";
		cout << "\n#5 -> Видалити позицію";
		cout << "\n#6 -> Видалити кожний N-й";
		cout << "\n#7 -> Очистити";
		cout << "\n#8 -> Сортувати";
		cout << "\n#9 -> Пересунути елемент";
		cout << "\n#10 -> Скопіювати список";
		cout << "\n#11 -> Склеїти списки";
		cout << "\n#12 -> Створити переріз";
		cout << "\n#13 -> Видалити";
		cout << "\n******************************";
		cout << "\n\n#0 -> Вихід";

		cout << "\n\nВибір: "; cin >> answ;

		if (answ < 11 && answ > 0) {
			cout << "\nЛіст з яким буде дія";
			cout << "\n#1 -> list1";
			cout << "\n#2 -> list2";
			cout << "\n#3 -> Скопійований";
			cout << "\n#4 -> Склеєний";
			cout << "\n#5 -> Переріз";

			cout << "\n\nВибір: "; cin >> whoseList;

			switch (whoseList) {
			case '1':
				list = list1;
				break;
			case '2':
				list = list2;
				break;
			case '3':
				list = ListCopy;
				break;
			case '4':
				list = MergedList;
				break;
			case '5':
				list = IntersectedList;
				break;
			default:
				list = list1;
				break;
			}
			system("cls");
			if (!list) {
				cout << "Ліста не існує! (далі - будь-який символ)\n";
				cin >> answ;
				continue;
			}
		}

		//cout << "\n\n";

		switch (answ) {
		case 1:	//Ok		Додавання в початок
			list->AddToStart(InputElement());
			break;
		case 2:	//Ok		Додавання в кінець	
			list->AddToEnd(InputElement());
			break;
		case 3:	//Ok		Додавання після позиції
			list->AddAfterPosition(InputPosition(list->GetLength()), InputElement());	//?
			break;
		case 4:	//Ok		Видалення із початку
			list->DeleteFromStart();
			break;
		case 5:	//Ok		Видалення N-го
			list->DeletePosition(InputPosition(list->GetLength(), 1));
			break;
		case 6: {	//Ok	Видалення кожного N-го
			list->Print(); cout << "\n";
			unsigned N;
			cout << "Введіть N: "; cin >> N;
			list->DeleteEveryNth(N);
			break;
		}
		case 7:	//Ok		Очистка
			list->Clear();
			break;
		case 8: {	//Ok	Сортування
			list->Print(); cout << "\n";
			bool sortMode;
			cout << "За зростанням/спаданням (1/0): ";
			cin >> sortMode;
			list->Sort(sortMode);
			break;
		}
		case 9: {	//Ok	Пересування елемента
			list->Print(); cout << "\n";
			int Npos, posOfEl = InputPosition(list->GetLength(), 1);
			cout << "Кількість позицій для пересування: "; cin >> Npos;
			list->MoveElement(posOfEl, Npos);
			break;
		}
		case 10: {	//Ok	Створення копії
			List* copy = list->GetCopy();
			if (ListCopy) delete ListCopy;
			ListCopy = copy;
			break;
		}
		case 11:	//Ok	Склеювання
			if (MergedList) delete MergedList;
			MergedList = List::MergeLists(*list1, *list2);
			break;
		case 12:	//Ok	Переріз
			if (IntersectedList) delete IntersectedList;
			IntersectedList = List::CreateIntersection(*list1, *list2);
			break;
		case 13: {	//Ok	Видалення (копії, склеєного, переізу)
			List** del = NULL;
			cout << "\n#1 -> Скопійований";
			cout << "\n#2 -> Склеєний";
			cout << "\n#3 -> Переріз";
			cout << "\n\nВибір: "; cin >> whoseList;

			switch (whoseList) {
			case '1': del = &ListCopy; break;
			case '2': del = &MergedList; break;
			case '3': del = &IntersectedList; break;
			}

			if (del && *del) {
				delete* del;
				*del = NULL;
			}
			break;
		}
		}


	} while (answ != 0);

	if (list1) delete list1;
	if (list2) delete list2;
	if (ListCopy) delete ListCopy;
	if (MergedList) delete MergedList;
	if (IntersectedList) delete IntersectedList;
}