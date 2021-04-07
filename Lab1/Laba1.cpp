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
	bool Pop(Candy&);
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

bool MyStack::Pop(Candy& data) {		//------Удаление элемента из стека
	if (!Top) return false;
	Node* temp = Top->prev;
	data = Top->data; 
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

bool GetFile(MyStack&);

int main()
{
	Candy candy;
	MyStack sMain,sTemp;
	char k;
	do {								//------Меню
		cout << "---------------------------" << endl;
		cout << "Menu: \ni - Show info about stack; \nf - Get parametres from file; \nm - Manualy add object; \nq - Quit;" << endl;
		cin >> k;
		system("cls");
		switch (k) {
		case 'i':
			sMain.Info();
			break;
		case 'f':
			GetFile(sMain);
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
	cout << "---------------------------" << endl << endl;
	while (sMain.Pop(candy))
		candy.Out();
	cout << endl;
	cout << "---------------------------" << endl;
	sMain.Info();
}

bool GetFile(MyStack& Stack) {			//------Заполнение стека из файла
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
