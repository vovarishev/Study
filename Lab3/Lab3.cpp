//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

/*-----------------------------------------------------------------------
-------------------------------------------------------------------------
--!-----------------ОСТОРОЖНО!!! Некачественный код!------------------!--
--!------При попадание некачестенного кода на поверхность глаза,------!--
--!НЕМЕДЛЕННО промыть глаза под холодной водой и выпить чай с ромашкой!--
-------------------------------------------------------------------------
-----------------------------------------------------------------------*/

using namespace std;

//---------------------------------------------------------------------------Структуры
struct Candy {							//------Конфеты
	string name;
	int count;
	int costBuy;
	int costSell;
	void Out();
};

struct Product {						//------Продукт
	int count;
	int costBuy;
};

struct MyStack {						//------Стек
	struct Node {
		Candy data;
		Node* prev;
	};
	Node* Top = NULL;
	int Count=0;
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
	Top->data = data;
	return true;
}

bool MyStack::Pop() {					//------Удаление элемента из стека
	if (!Top) { 
		cout << "--->Stack is empty" << endl;
		return false; 
	}
	Node* temp = Top->prev;
	delete Top;
	Top = temp; 
	Count--;
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

void Candy::Out() {						//------Вывод объекта стека на экран
	cout << "Name:" << name << "\tCount:" << count << "\tBuy cost:" << costBuy << "\tSell cost:" << costSell << endl;
}


struct MyQueue {						//------Очередь
	struct Node {
		Product data;
		Node* next;
	};
	Node* First = NULL;
	int Count=0;
	bool Push(Product);
	bool Pop();
	void Report();
};

bool MyQueue::Push(Product data) {		//------Пополнение очереди
	if (!First) {
		First = new Node;
		First->next = NULL;
		Count = 1;
		First->data = data;
	}
	else {
		Node* temp;
		temp = First;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new Node;
		temp->next->data = data;
		temp->next->next = NULL;
		Count++;
	}
	return true;
}

bool MyQueue::Pop() {					//------Удаление элемента из очереди
	if (!First) {
		cout << "--->Queue is empty" << endl;
		return false;
	}
	Node* temp = First->next;
	delete First;
	First = temp; 
	Count--;
	return true;
}

void MyQueue::Report() {				//------Информация про очередь
	if (!First)
		cout << "--->Queue is empty" << endl;
	else {
		int sell, profit;
		cout << "Queue info: " << endl;
		cout << "Queue size:" << Count << endl;
		cout << "First data:" << endl;
		cout << "Count:" << First->data.count << "\tBuy cost" << First->data.costBuy << endl;
		cout << "Enter sell price:" << endl;
		cin >> sell;
		system("cls");
		if (sell <= First->data.costBuy) cout << "Sell price is low, try sell later;\n";
		else {
			profit = (sell - First->data.costBuy) * First->data.count;
			cout << "If sell "<< First->data.count <<" products by "<<sell<<" cost, Profit is:"<< profit<<endl;
		}
	}
}
//---------------------------------------------------------------------------Функции
int GetNum();
int Queue();
bool QueueSell(MyQueue&);
int Stack();
bool StackGetFile(MyStack&);
bool StackRemoveObject(MyStack&);
//---------------------------------------------------------------------------Много воды (кода) внизу, можно не читать
int main()
{
	char k;
	cout << "---------------------------" << endl;
	cout << "Menu: \ns - Work with Stack; \nq - Work with Queue; \ne - Exit; " << endl;
	cin >> k;
	do {
		switch (k) {
		case 's':
			return Stack();
			break;
		case 'q':
			return Queue();
			break;
		default:
			if (k != 'e')
			{
				cout << "Nope. Try again.\n ";
				break;
			}
		}
	} while (k != 'e');
	return 0;
}

int GetNum()
{
	float n;
	do {
		cin >> n;
		if ((n - (int)n != 0) || n <= 0) cout << " --->Error, enter int number:" << endl;
	} while ((n - (int)n != 0) || n <= 0);
	return n;
}

int Queue() {
	Product prod;
	MyQueue qMain;
	char k;
	system("cls");
	do {								//------Меню
		cout << "---------------------------" << endl;
		cout << "Menu: \nr - Show report about chart; \na - Add product to chart \ns - Sell products \ne - Exit; " << endl;
		cin >> k;
		system("cls");
		switch (k) {
		case 'r':
			qMain.Report();
			break;
		case 'a':
			cout << "Enter \nCount: ";
			prod.count = GetNum();
			system("cls");
			cout << "Enter \nBuy cost: ";
			prod.costBuy = GetNum();
			system("cls");
			qMain.Push(prod);
			cout << "Succesfuly add element to stack! \n";
			break;
		case 's':
			QueueSell(qMain);
			break;
		default:
			if (k != 'e')
			{
				cout << "Nope. Try again.\n ";
				break;
			}
		}
	
	} while (k != 'e');
	return 0;
}

bool QueueSell(MyQueue& qMain) {
	if (!qMain.First) {
		cout << "--->Queue is empty" << endl;
		return false;
	}
	int costSell, countSell;
	cout << "Enter sell count:\n";
	cin >> countSell;
	system("cls");
	while (countSell > 0) {
		if (!qMain.First) {
			cout << "--->Queue is empty" << endl;
			return false;
		}
		cout << "Enter sell cost:\n";
		cin >> costSell;
		system("cls");
		if (costSell <= qMain.First->data.costBuy) {
			cout << "---> Cost is very low for sale\n";
			return false;
		}
		char k;
		if (countSell <= qMain.First->data.count) {
			cout << "Did you want to sell " << countSell << " products from chart with proft: " << countSell * (costSell - qMain.First->data.costBuy) << "? \n(y/n):";
			cin >> k;
			switch (k) {
			case 'y':
				qMain.First->data.count -= countSell;
				countSell = 0;
				if(qMain.First->data.count==0) qMain.Pop();
				k = 'e';
				system("cls");
				cout << "Sucsesfully sell "<< countSell <<" products"<<endl;
				break;
			case'n':
				return false;
				break;
			default:
				if (k != 'e')
				{
					cout << "Nope. Try again.\n ";
					break;
				}
			}
		}
		else {
			cout << "Did you want to sell " << qMain.First->data.count << " products from chart with proft: " << qMain.First->data.count * (costSell - qMain.First->data.costBuy) << "? \n(y/n):";
			cin >> k;
			switch (k) {
			case 'y':
				countSell -= qMain.First->data.count;
				qMain.Pop();
				k = 'e';
				system("cls");
				cout << "Sucsesfully sell " << qMain.First->data.count << " products" << endl;
				break;
			case'n':
				return false;
				break;
			default:
				if (k != 'e')
				{
					cout << "Nope. Try again.\n ";
					break;
				}
			}
		}
	}
	return true;
}

int Stack() {
	Candy candy;
	MyStack sMain;
	char k;
	system("cls");
	do {								//------Меню
		cout << "---------------------------" << endl;
		cout << "Menu: \ni - Show info about stack; \nf - Get parametres from file; \nm - Manualy add object; \nr - Remove object from stack; \nc - Clear stack \ne - Exit; " << endl;
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
			candy.count = GetNum();
			system("cls");
			cout << "Enter \nBuy cost: ";
			candy.costBuy = GetNum();
			system("cls");
			cout << "Enter \nSell cost: ";
			candy.costSell = GetNum();
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
			if (k != 'e')
			{
				cout << "Nope. Try again.\n ";
				break;
			}
		}
	} while (k != 'e');
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
	string candy;
	MyStack sTemp;
	bool stopFind = false, find = false;
	cout << "Enter for delete \nName: ";
	cin >> candy;
	system("cls");
	while (stopFind == false) {
		sTemp.Push(sMain.Top->data);
		sMain.Pop();
		if (sTemp.Top->data.name == candy) {
			find = true;
			stopFind = true;
			break;
		}		
		if (sMain.Top == NULL) {
			stopFind = true;
			break;
		}
	}
	if (find == true) {
		sTemp.Pop();
		cout << "Succesfuly remove " << candy << " named object!\n";
	}
	else {
		cout << "--->Can't find " << candy << " named object!\n";
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
