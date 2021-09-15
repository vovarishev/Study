//#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Datetime
{
	unsigned short id;
	unsigned short second;
	unsigned short minute;
	unsigned short hour;
	unsigned short day;
	unsigned short month;
	unsigned short year;
	void Out();
	void ShowId();
	Datetime* prev = NULL;
	Datetime* next = NULL;
};

void Datetime::Out()
{
	cout << id << "\t" 
		<< setfill('0') << setw(4) << year << ":"
		<< setfill('0') << setw(2) << month << ":" 
		<< setfill('0') << setw(2) << day << "\t"
		<< setfill('0') << setw(2) << hour << ":"
		<< setfill('0') << setw(2) << minute << ":"
		<< setfill('0') << setw(2) << second << "\t";

	if (next != NULL) { cout << next->id << "\t"; }
	else cout << "-\t";

	if (prev != NULL) { cout << prev->id << "\t"; }
	else cout << "-\t";
}

bool ChekFile() 
{
	ifstream file("List.txt");
	if (!file) {
		return false;
	}
	return true;
	file.close();
}

Datetime* MemorryArray(int a)
{
	Datetime* arr = new Datetime[a];
	return arr;
}

Datetime *GetFile(int& count) {
	if (ChekFile())
	{
		ifstream file("List.txt");
		char* str = new char[1024];
		ifstream in("List.txt");
		int x;
		while (!in.eof())
		{
			in.getline(str, 1024, '\n');
			count++;
		}
		delete[] str;
		Datetime* Date = MemorryArray(count);
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
		file.close();
		return Date;
	}
	
}

int main()
{	
	cout << "--------------------------- \n~(OuO)~\tWellcome! We a r-ready to work \n--------------------------- " << endl;
	cout << "Press any key for scan file///" << endl << endl;
	system("pause");
	system("cls");
	int count=0;
	Datetime* Date = GetFile(count);

	if (ChekFile())
	{
		cout << "--------------------------- \n<(OuO)\\\tThe file has been successfully scanned \n--------------------------- " << endl;
	}
	else
	{
		cout << "--------------------------- \n(O.O) \tI c-can't find file \"List.xtx\" \n--------------------------- " << endl;
		cout << "Press any key for exit///" << endl << endl;
		system("pause");
		system("cls");
		return 0;
	}

	cout << "|ID\t|YYYY:MM::DD\t|HH:MM:SS\t|nxtID\t|prvID" << endl;
	for (unsigned short i=0; i < count; i++)
	{
		Date[i].Out();
		cout << endl;
	}

	cout << "--------------------------- \n~(OuO)~\tSpecail variantable task time! \n--------------------------- " << endl;
	cout << "Press any key and I show it for you///" << endl << endl;
	system("pause");
	system("cls");

	cout << "--------------------------- \n(O.u)\tMy specail variantable task. I did it myself.\n--------------------------- " << endl;

	for (unsigned short i = 0; i < count; i++)
	{
		if (Date[i].next != NULL && Date[i].next->month != Date[i].month|| i == count - 1)
		{
			Date[i].Out();
			cout << endl;
		}

	}
	cout << "---------------------------" << endl << endl;
	system("pause");
	delete[] Date;
	return 0;
}