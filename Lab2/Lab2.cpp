//#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <cstdlib>

using namespace std;

void PrintMatr(unsigned int N, unsigned int M, double** A);
bool TriangMatr(double** A, double** B, double& determ, int n);
bool Solve(double** A, double** B, double* x, double& determ, int n);
double Delta(double** A, double* x, int n, int m);

void GetMass(int count1, int count2, double** arr);

int main() {
	srand(time(0));
	setlocale(LC_ALL, "rus");

	unsigned int N; //Количесство уравнений
	unsigned int M; //Количесство неизвестных + свободные члены
	double** A; //Исходная матрица
	double** B; //Матрица для вычислений
	double* results; //Вектор решения
	double determ = 1; //Определитель
	short int feelmode; //Режим заполнения

	cout << "\nДанная программа  способна решать матрицы методом СЛАУ и находить для них определитель.\n";
	//-----------------------------------------------------------------------------//Определение матриц
	cout << "\nВведите количество уравнений: ";
	cin >> N;
	cout << "\nВведите количество неизвестных: ";
	cin >> M;
	M++;

	A = new double*[N];
	for (unsigned int i = 0; i < N; i++) A[i] = new double[M];

	B = new double*[N];
	for (unsigned int i = 0; i < N; i++) B[i] = new double[M];

	results = new double[N];

	//-----------------------------------------------------------------------------//Выбор режима ввода
	cout << "\nВыберите режим заполнения (0 - с клавиатуры, 1 - случайные, 2 - из файла): ";
	cin >> feelmode;

	//-----------------------------------------------------------------------------//Заполнение матрицы элементами
	if (feelmode < 2) {
		for (unsigned int i = 0; i < N; i++) for (unsigned int j = 0; j < M; j++) {
			if (feelmode == 0) {
				cout << "\nВведите элемент [" << i + 1 << "][" << j + 1 << "]: ";
				cin >> A[i][j];
			}
			else if (feelmode == 1) A[i][j] = rand() % 100;
		}
	}
	else GetMass(N, M, A);


	//-----------------------------------------------------------------------------//Вывод элементов матрицы на экран
	cout << "\nЗаданная матрица имеет вид:";
	PrintMatr(N, M, A);

	//-----------------------------------------------------------------------------//Решение и вывод решения на экран
	if (Solve(A, B, results, determ, N)) {
		cout << "\nПреобразованная матрица имеет вид:";
		PrintMatr(N, M, B);
		cout << "\nВектор-решение имеет вид: \n";
		for (unsigned int i = 0; i < N; i++) {
			cout << "x[" << i + 1 << "] = " << results[i] << ";" << endl;
		}
		cout << "\nОпределитель матрицы = " << determ << endl;
		cout << "\nМаксимальная погрешность = " << Delta(A, results, N, M) << endl;
	}
	//-----------------------------------------------------------------------------//Освобождение памяти
	for (unsigned int i = 0; i < N; i++) delete[] A[i];
	delete[] A;
	A = NULL;

	for (unsigned int i = 0; i < N; i++) delete[] B[i];
	delete[] B;
	B = NULL;

	delete[] results;
	results = NULL;

	return 0;
}

//-----------------------------------------------------------------------------//Функции
void PrintMatr(unsigned int N, unsigned int M, double** A) {// Вывод матрицы
	cout << endl;
	for (unsigned int i = 0; i < N; i++) {
		for (unsigned j = 0; j < M; j++) {
			cout.width(5);
			cout << A[i][j] << ' ';
		}
		cout << endl;
	}
}

bool TriangMatr(double** A, double** B, double& determ, int n) {// Триангуляция матрицы + Определитель
	double koef;
	double max = 0;
	double zeroCheck;
	unsigned int maxIndex;
	for (unsigned int i = 0; i < n; i++) for (unsigned int j = 0; j < n + 1; j++) B[i][j] = A[i][j];// Заполнение матрицы для вычислений

	for (unsigned int k = 0; k < n; k++) {// Триангуляция построчно
		if (B[k][k] == 0) {// Выбор ведущего элемента
			max = fabs(B[k][k]);
			for (unsigned int i = k + 1; i < n; i++) {// Поиск подходящей строки
				if (fabs(B[i][k]) > max) {
					max = fabs(B[i][k]);
					maxIndex = i;
				}
			}
			if (max > 0) {
				for (unsigned int j = 0; j < n + 1; j++) {
					swap(B[k][j], B[maxIndex][j]);
				}
				determ *= -1;
			}
			else {
				cout << "\nНевозможно выбрать ведущий элемент\n";
				return false;
			}
		}
		zeroCheck = 0;
		for (unsigned int i = 0; i < n + 1; i++) zeroCheck += B[k][i];
		if (zeroCheck == 0) {
			cout << "\nИмеются коллинеарные или нулевые строки\n";
			return false;
		}
		for (unsigned int i = k + 1; i < n; i++) {
			koef = -1 * B[i][k] / B[k][k];
			for (unsigned int j = k; j < n + 1; j++) B[i][j] = B[i][j] + B[k][j] * koef;// Преобразование последующих строк
		}
		determ *= B[k][k];// Вычисление определителя
	}
	//PrintMatr(n, n + 1, B);

	return true;
}

bool Solve(double** A, double** B, double* x, double& determ, int n) {// Решение по Гаусу
	double res = 0;
	double zeroCheck;

	if (TriangMatr(A, B, determ, n) == true) {//Подсчёт вектора-решения
		for (int i = n - 1; i >= 0; i--) {
			res = 0;
			for (int j = i + 1; j <= n - 1; j++) res = res - x[j] * B[i][j];
			res += B[i][n];
			x[i] = res / B[i][i];
		}

		for (unsigned int i = 0; i < n; i++) {//Проверка на нулевые строки
			zeroCheck = 0;
			for (unsigned int j = 0; j < n + 1; j++) {
				zeroCheck += B[i][j];
			}
			if (zeroCheck == 0) {
				cout << "\nИмеются коллинеарные или нулевые строки\n";
				return false;
			}

		}

		return true;
	}

	cout << "\nСистема не имеет единственного решения\n";
	return false;
}

double Delta(double** A, double* x, int n, int m) {// Подсчёт погрешности
	double* y = new double[n];

	for (unsigned int i = 0; i < n; i++) {
		double res = 0;
		for (unsigned int j = 0; j < n; j++) {
			res += A[i][j] * x[j];
		}

		y[i] = res;
		//cout << y[i] << ' ';
	}

	double max;
	max = fabs(y[0] - A[0][m - 1]);
	for (unsigned int i = 1; i < n; i++) {
		if (fabs(y[i] - A[i][m - 1]) > max) max = fabs(y[i] - A[i][m - 1]);
	}


	delete[] y;
	y = NULL;

	return max;
}

void GetMass(int count1, int count2, double** arr) {
	ifstream f("ArrayInput.txt");

	for (unsigned int i = 0; i < count1; i++) {
		for (unsigned int j = 0; j < count2; j++) {
			f >> arr[i][j];
		}

	}

	f.close();
}
