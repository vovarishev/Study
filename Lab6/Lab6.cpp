//#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

/*-------------------!-----------------ОСТОРОЖНО!!! Некачественный код!------------------!---------------------
---------------------!------При попадание некачестенного кода на поверхность глаза,------!---------------------
---------------------!НЕМЕДЛЕННО промыть глаза под холодной водой и выпить чай с ромашкой!---------------------
---------------------!--------------Ответственный за работу кода: Арышев В.--------------!-------------------*/

//-----------------------------------------------------------------------------------------------Глава1:Объекты
//Конфеты как объект
struct Candy
{
	int id;
	string name;
	bool choc;
	float cost;
	void Out();
};

//------Вывод информации о конфетах
void Candy::Out()
{
	cout << "ID: " << id << "\tName: " << name << "\tChocolate: " << choc << "\tCost: " << cost << endl;
}
//-----Дерево
struct Tree
{																								  
	Candy data;
	Tree* lBr = NULL;
	Tree* rBr = NULL;
};
//-------------------------------------------------------------------------------------------------Глава1/Конец

//-----------------------------------------------------------------------------------------------Глава2:Функции
//------Добавление объектов с сортировкой по имени (режим 0) и по ИД (режим 1):
void Add(Tree*& T, Candy data, int type)
{
	if (!T)
	{
		T = new Tree;
		T->data = data;
		return;
	}
	if (type == 0)
	{
		if (data.name < T->data.name)
		{
			Add(T->lBr, data, 0);
		}
		else
		{
			Add(T->rBr, data, 0);
		}
	}
	else if (type == 1)
	{
		if (data.id < T->data.id)
		{
			Add(T->lBr, data, 1);
		}
		else
		{
			Add(T->rBr, data, 1);
		}
	}
}
//------Рекурсивная очистка дерева:
void Delete(Tree*& T)
{
	if (T)
	{
		if (T->lBr)
		{
			Delete(T->lBr);
		}
		if (T->rBr)
		{
			Delete(T->rBr);
		}
		delete T;
		T = NULL;
	}
	else
	{
		cout << "---!: tree is already empty" << endl;
	}
}
//------Получение данных из файла:
bool GetFile(Tree*& T, int type)
{
	Candy data;
	ifstream F("List.txt");
	if (!F)
	{
		cout << "---!: cant find file" << endl;
		cout << "---------------------------" << endl;
		return false;
	}
	while (F >> data.id >> data.name >> data.choc >> data.cost)
	{
		Add(T, data, type);
	}
	F.close();
	cout << "Sucsesfully read file!" << endl;
	cout << "---------------------------" << endl;
}
//------Вывод на экран и в файл:
void Print(Tree* T, ofstream& F,int& lght)
{
	if (!T)
	{
		return;
	}
	Print(T->lBr, F, lght);
	T->data.Out();
	F << T->data.id << " " << T->data.name << " " << T->data.choc << " " << T->data.cost << endl;
	Print(T->rBr, F, lght);
	lght++;
}
//------Поиск и вывод на экран(режимы:0 - по имени, 1 - по числу)
void SeeknPrint(Tree* T, Candy data, int type, int& lght)
{
	if (!T)
	{
		return;
	}
	SeeknPrint(T->lBr, data, type, lght);
	if (type == 0)
	{
		if (T->data.name[0] == data.name[0])
		{
			T->data.Out();
			lght++;
		}
	}
	else if (type == 1)
	{
		if (T->data.id < data.id)
		{
			T->data.Out();
			lght++;
		}
	}
	SeeknPrint(T->rBr, data, type, lght);
}
//-------------------------------------------------------------------------------------------------Глава2/Конец

//---------------------------------------------------------------------Глава3:main и пользовательский интерфейс
int main()
{
	ofstream F;
	Tree* T = NULL;
	Candy data;
	char symbol = '0';
	int key = 0, lght;
	do
	{
		cout << "--------------------------- \nMenu:" << endl;
		cout << "1) Sort by name" << endl
			<< "2) Sort by ID" << endl
			<< "3) Information up to a given ID" << endl
			<< "4) Information on the entered symbol" << endl
			<< "0) Exit" << endl;
		cout << endl << "Select an action: ";
		cin >> key;
		cout << "---------------------------" << endl;
		switch (key)
		{
		case 1:
			system("cls");
			lght = 0;
			F.open("SortedByNameCandies.txt");
			GetFile(T, 0);
			Print(T, F, lght);
			cout << "---------------------------" << endl;
			cout << "Count of branches: " << lght << endl;
			Delete(T);
			F.close();
			break;
		case 2:
			system("cls");
			lght = 0;
			F.open("SortedByIDCandies.txt");
			GetFile(T, 1);
			Print(T, F, lght);
			cout << "---------------------------" << endl;
			cout << "Count of branches: " << lght << endl;
			Delete(T);
			F.close();
			break;
		case 3:
			lght = 0;
			cout << "Enter candy id: ";
			cin >> data.id;
			system("cls");
			GetFile(T, 1);
			SeeknPrint(T, data, 1,lght);
			cout << "---------------------------" << endl;
			cout << "Count of branches: " << lght << endl;
			Delete(T);
			break;
		case 4:
			lght = 0;
			cout << "Enter symbol (сase sensitive): ";
			cin >> data.name;
			system("cls");
			GetFile(T, 0);
			SeeknPrint(T, data, 0, lght);
			cout << "---------------------------" << endl;
			cout << "Count of branches: " << lght << endl;
			Delete(T);
			break;
		default:
			if (key != 0)
			{
				cout << "Nope. Try again.\n ";
			}
			break;
		}
	} while (key != 0);
	if (T) Delete(T);
	system("cls");
	cout << "--------------------------- \nThank you for choosing our software!" << endl;
	return 0;
}
//-------------------------------------------------------------------------------------------------Глава3/Конец