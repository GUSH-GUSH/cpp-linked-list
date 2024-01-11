#include <iostream>
#include <windows.h>
#include "List.h"

using namespace std;

template <typename T>
T InputData(const char* message = "Введіть дані: ") {
	T value;
	cout << message; cin >> value;
	return value;
}

void listPrint(const char* listName, List* list) {
	cout << listName << "  {length = " << list->GetLength() << "}\n\n";
	list->Print();
	cout << "\n\n";
}

int main() {
	SetConsoleOutputCP(1251);

	List* list1, * list2, * IntersectedList, * MergedList, * ListCopy;

	//Стартові дані списків
	int arr1[3] = { 4, 5, 1 };
	int arr2[2] = { 13, 8 };

	list1 = new List(arr1, 3);
	list2 = new List(arr2, 2);
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
		cout << "\n#2 -> Додати в кінець";
		cout << "\n#3 -> Додати після позиції";
		cout << "\n#4 -> Видалити із початку";
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
			case '1': list = list1; break;
			case '2': list = list2; break;
			case '3': list = ListCopy; break;
			case '4': list = MergedList; break;
			case '5': list = IntersectedList; break;
			default: list = list1; break;
			}

			if (!list) {
				cout << "Ліста не існує! (далі - будь-який символ)\n"; cin >> answ;
				continue;
			}
		}

		switch (answ) {
		case 1:	//  		Додавання в початок
			list->AddToStart(InputData<int>("Введіть елемент: ")); break;
		case 2:	//  		Додавання в кінець
			list->AddToEnd(InputData<int>("Введіть елемент: ")); break;
		case 3:	//  		Додавання після позиції
			list->AddAfterPosition(InputData<size_t>("Введіть індекс позиції: "), InputData<int>("Введіть елемент: ")); break;
		case 4:	//  		Видалення із початку
			list->DeleteFromStart(); break;
		case 5:	//  		Видалення N-го
			list->DeletePosition(InputData<size_t>("Введіть iндекс: ")); break;
		case 6:	//  		Видалення кожного N-го
			list->DeleteEveryNth(InputData<size_t>("Введіть N: ")); break;
		case 7:	//  		Очистка
			list->Clear(); break;
		case 8:	//  	Сортування
			list->Sort(InputData<bool>("За зростанням/спаданням (1/0): ")); break;
		case 9: {	//  	Пересування елемента
			int posOfEl = InputData<int>("Індекс елемента: ");
			int Npos = InputData<int>("Кількість позицій для пересування : ");
			list->MoveElement(posOfEl, Npos);
			break;
		}
		case 10: {	//  	Створення копії
			if (ListCopy) delete ListCopy;
			ListCopy = list->GetCopy();
			break;
		}
		case 11:	//  	Склеювання
			if (MergedList) delete MergedList;
			MergedList = List::MergeLists(*list1, *list2);
			break;
		case 12:	//  	Переріз
			if (IntersectedList) delete IntersectedList;
			IntersectedList = List::CreateIntersection(*list1, *list2);
			break;
		case 13: {	//  	Видалення (копії, склеєного, переізу)
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
				delete *del;
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