#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class Datetime
{
public:
	unsigned short id;
	unsigned short second;
	unsigned short minute;
	unsigned short hour;
	unsigned short day;
	unsigned short month;
	unsigned short year;
	Datetime* prev = NULL;
	Datetime* next = NULL;

};

class Application
{
public:
	Datetime * Date = NULL;
	void start();
	void Out(Datetime);
	void show();
	void spec();
	void stop();
	unsigned short count;
};

void Application::Out(Datetime Date)
{
	cout << "\|" << Date.id << "\t"
		<< "\|" << setfill('0') << setw(4) << Date.year << ":"
		<< setfill('0') << setw(2) << Date.month << ":"
		<< setfill('0') << setw(2) << Date.day << "\t"
		<< "\|" << setfill('0') << setw(2) << Date.hour << ":"
		<< setfill('0') << setw(2) << Date.minute << ":"
		<< setfill('0') << setw(2) << Date.second << "\t";

	if (Date.next != NULL) { cout << "\|" << Date.next->id << "\t"; }
	else cout << "\|" << "-\t";

	if (Date.prev != NULL) { cout << "\|" << Date.prev->id << "\t"; }
	else cout << "\|" << "-\t";
}

void Application::show()
{
	cout << "|ID\t|YYYY:MM:DD\t|HH:MM:SS\t|nxtID\t|prvID" << endl;
	for (unsigned short i = 0; i < count; i++)
	{
		Out(Date[i]);
		cout << endl;
	}
}

void Application::spec()
{
	cout << "|ID\t|YYYY:MM:DD\t|HH:MM:SS\t|nxtID\t|prvID" << endl;
	for (unsigned short i = 0; i < count; i++)
	{
		if (Date[i].next != NULL && Date[i].next->month != Date[i].month || i == count - 1)
		{
			Out(Date[i]);
			cout << endl;
		}
	}
}

void Application::start()
{
	cout << "We start here!" << endl;
	ifstream file("List.txt");
	if (!file) cout << "cant find file \"List.txt\"" << endl;
	else
	{
		char* str = new char[1024];
		ifstream in("List.txt");
		while (!in.eof())
		{
			in.getline(str, 1024, '\n');
			count++;
		}
		delete[] str;
		Date = new Datetime[count];
		int i = 0;
		while (file >> Date[i].year >> Date[i].month >> Date[i].day >> Date[i].hour >> Date[i].minute >> Date[i].second)
		{
			Date[i].id = i;
			if (i != 0)
			{
				Date[i].prev = &Date[i - 1];
				Date[i].prev->next = &Date[i];
			}
			i++;
		}
	}
	file.close();
}

void Application::stop()
{
	if (Date) delete[] Date;
	cout << "See you latter!" << endl;
	system("pause");
}

int main()
{
	Application app;
	app.start();
	app.show();
	app.spec();
	app.stop();
	return 0;
}

