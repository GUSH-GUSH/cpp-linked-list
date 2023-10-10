#include <iostream>
#include <windows.h>
#include "List.h"
using namespace std;

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