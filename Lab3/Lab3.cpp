//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//---------------------------------------------------------------------------Структуры
struct Candy {							//------Конфеты
	string name;
	int count;
	int costBuy;
	int costSell;
	void Out();
};

struct MyStack {						//------Стек
	struct Node {
		Candy data;
		Node* prev;
	};
	Node* Top = NULL;
	int Count;
	bool Push(Candy);
	bool Pop();
	void Info();
};

bool MyStack::Push(Candy data) {		//------Пополнение стека
	if (!Top) {
		Top = new Node;
		Top->prev = NULL;
		Count = 1;
	}
	else {
		Node* temp;
		temp = new Node;
		temp->prev = Top;
		Top = temp;
		Count++;
	}
	Top->data = data;//!!!Узкое место
	return true;
}

bool MyStack::Pop() {		//------Удаление элемента из стека
	if (!Top) { 
		cout << "--->Stack is empty" << endl;
		return false; 
	}
	Node* temp = Top->prev;
	delete Top;
	Top = temp; Count--;
	return true;
}

void MyStack::Info() {					//------Информация про стек
	if (!Top)
		cout << "--->Stack is empty" << endl;
	else {
		cout << "Stack info: " << endl;
		cout << "Stack size:" << Count << endl;
		cout << "Top data:" << endl;
		Top->data.Out();
	}
}

void Candy::Out() {						//------Вывод объекта на экран
	cout << "Name:" << name << "\tCount:" << count << "\tBuy cost:" << costBuy << "\tSell cost:" << costSell << endl;
}

bool StackGetFile(MyStack&);
bool StackRemoveObject(MyStack&);

int main()
{
	Candy candy;
	MyStack sMain;
	char k;
	do {								//------Меню
		cout << "---------------------------" << endl;
		cout << "Menu: \ni - Show info about stack; \nf - Get parametres from file; \nm - Manualy add object; \nr - Remove object from stack; \nc - Clear stack \nq - Quit; " << endl;
		cin >> k;
		system("cls");
		switch (k) {
		case 'i':
			sMain.Info();
			break;
		case 'f':
			StackGetFile(sMain);
			break;
		case 'm': {
			cout << "Enter \nName: ";
			cin >> candy.name;
			system("cls");
			cout << "Enter \nCount: ";
			cin >> candy.count;
			system("cls");
			cout << "Enter \nBuy cost: ";
			cin >> candy.costBuy;
			system("cls");
			cout << "Enter \nSell cost: ";
			cin >> candy.costSell;
			system("cls");
			sMain.Push(candy);
			cout << "Succesfuly add element to stack! \n";
			sMain.Info();
			break; }
		case 'r':
			StackRemoveObject(sMain);
			break;
		case 'c':
			while (sMain.Pop());
			break;
		default:
			if (k != 'q')
			{
				cout << "Nope. Try again.\n ";
				break;
			}
		}
	}
	while (k != 'q');
	return 0;
}

bool StackGetFile(MyStack& Stack) {			//------Заполнение стека из файла
	ifstream F("List.txt");
	if (!F) {
		cout << "Cant find file" << endl;
		return false;
	}
	Candy candy;

	while (F >> candy.name >> candy.count>>candy.costBuy>>candy.costSell) {
		Stack.Push(candy);
	}
	F.close();
	cout << "Succesfully read file" << endl;
	return true;
}

bool StackRemoveObject(MyStack& sMain) {
	Candy candy;
	MyStack sTemp;
	bool stopFind = false, find = false;
	cout << "Enter for delete \nName: ";
	cin >> candy.name;
	system("cls");
	while (stopFind == false) {
		sTemp.Push(sMain.Top->data);
		sMain.Pop();
		if (sMain.Top == NULL) {
			stopFind = true;
			break;
		}
		if (sTemp.Top->data.name == candy.name) {
			find = true;
			stopFind = true;
			break;
		}
	}
	if (find == true) {
		sTemp.Pop();
		cout << "Succesfuly remove " << candy.name << " named object!\n";
	}
	else {
		cout << "--->Can't find " << candy.name << " named object!\n";
	}

	stopFind = false;
	while (stopFind == false) {
		if (find != true) {
			sMain.Push(sTemp.Top->data);
			sTemp.Pop();
		}
		find = false;
		if (sTemp.Top == NULL) stopFind = true;
	}
	find = false;
	sMain.Info();
	return true;
}
