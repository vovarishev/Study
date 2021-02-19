//#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

void AddElements(float*& , int& ,int);
void DelElements(float*& , int& ,int);
float* MemoryArray(int );
void InputArray(int , float* );
void OutputArray(int , float*);
int FindEllement(int , float* );
int FindEllementAvto(int, float*,float);

int main(){
	//int count;
	//cout << "Enter array size" << endl;
	//cin >> count;
	ifstream in("Array.txt");
	if (!in){
		cout << "! --- Error --- ! Can't open file \"Array.txt\" \n";
		system("pause");
		return 0;
	}
	int count = 0, target=-1;
	float x,avto;
	while (in >> x) count++;
	in.close();
	cout << "Sucsesfully make array with size: " << count << endl;
	float* arr = MemoryArray(count);
	InputArray(count, arr);
	char K;
	do{
		cout << "1 - Add element;\n2 - Delet element;\n3 - Add element after finding number;"<<endl
			<< "4 - Delete all chosen elements;\ns - Show Array on string;\nq - Exit"<< endl;
		cin >> K;
		switch (K)
		{
		case '1':
			AddElements(arr, count,-1);
			break;
		case '2':
			DelElements(arr, count,-1);
			break;
		case '3':
			target = FindEllement(count, arr)+1;
			if (target == 0) break;
			AddElements(arr, count, target);
			cout << "Sucsessfully add new ellemnt to [" << target << "] position." << endl;
			target = -1;
			break;
		case '4':
			cout << endl << "Enter chosen number: " << endl;
			cin >> avto;
			do {
				target = FindEllementAvto(count, arr, avto);
				if (target != -1) {
					DelElements(arr, count, target);
					cout << "Sucsessfully delete ellemnt from [" << target << "] position." << endl;
				}
			} while (target != -1);
			break;
		case 's':
			OutputArray(count, arr);
			break;
		default:
			if (K != 'q')
			{
				cout << "Nope. Try again.\n ";
				break;
			}
		}
	} while (K != 'q');
	delete[] arr;
	return 0;
}

float* MemoryArray(int count){
	float* arr = new float[count];
	return arr;
}

void AddElements(float*& arr, int& count,int target)
{
	int index;
	if (target == -1) {
		cout << endl << "Chose position to add element('0' - begin,'-1' - end): " << endl;
		cin >> index; 
		if (index == -1) index = count;
	}
	else index = target;
	if (index < 0 || index > count) {
		cout << "Error" << endl;
	}
	else {
		float* buff = new float[count + 1];
		for (int i = 0; i < index; i++)
		{
			buff[i] = arr[i];
		}
		buff[index] = 10;
		for (int i = index + 1; i < count + 1; i++)
		{
			buff[i] = arr[i - 1];
		}
		delete[] arr;
		arr = buff;
		count += 1;
		//cout << "buff array" << endl;
		//OutputArray(count, buff);
	}
}

void DelElements(float*& arr, int& count,int target) {
	int index;
	if (target == -1) {
		cout << endl << "Chose position to del element('0' - begin,'-1' - end): " << endl;
		cin >> index;
		if (index == -1) index = count;
	}
	else index = target;
	if (index < 0 || index > count) {
		cout << "Error" << endl;
	}
	else {
		float* buff = new float [count - 1] ;
		for (int i = 0; i < index; i++)
		{
			buff[i] = arr[i];
		}
		for (int i = index; i < count - 1; i++)
		{
			buff[i] = arr[i + 1];
		}
		delete[] arr;
		arr = buff;
		count -= 1;
		//cout << "buff array" << endl;
		//OutputArray(count, buff);
	}
}

int FindEllement(int count, float* arr) {
	float chosen;
	int fnum;
	bool a = false;
	cout << endl << "Enter chosen number: " << endl;
	cin >> chosen;
	for (int i = 0; i < count && a == false; i++) {
		if (arr[i] == chosen) {
			a = true;
			fnum = i;
		}
	}
	if (a == false) {
		cout << "! --- Error --- !: can't find chosen number\n";
		return -1;
	}
	else cout << "Index of your number is [" << fnum << "]" << endl;
	return fnum;
}

int FindEllementAvto(int count, float* arr,float avto) {
	int fnum;
	bool a = false;
	for (int i = 0; i < count && a == false; i++) {
		if (arr[i] == avto) {
			a = true;
			fnum = i;
		}
	}
	if (a == false) {
		cout << "! --- Error --- !: can't find chosen number\n";
		return -1;
	}
	else cout << "Index of your number is [" << fnum << "]" << endl;
	return fnum;
}

void InputArray(int count, float* arr)
{
	ifstream in("Array.txt");
	for (int i = 0; i < count; i++)
	{
		in >> arr[i];
	}
	in.close();
}

void OutputArray(int count, float* arr)
{
	cout << "Your array is: ";
	for (int i = 0; i < count; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "Size of Array: " << count << " elements" << endl;
}