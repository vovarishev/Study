#include <iostream>

using namespace std;

int GetN();
void GetSize(int&, int&);
void NewMatrix(double**, int&, int&);
void ManualMatrix(double** ,int&, int&);
void MemClear(double**, int&);

int main(){
	cout << "Wellcome! This programm can solve the system of equations.\n";
	int N = 0, M= 0;
	double** a;
	a = new double* [N];
	MemClear(a, N); //почистить память
    
	char K;
	do {
		cout << "\n1 - Make matrix with manual entered parametres;\nq - Exit.\n";
		cin >> K;
		switch (K)
		{
		case '1':
			NewMatrix(a, N, M);
			ManualMatrix(a,N, M);
			break;
		case '2':
			
			break;
		case '3':
			
			break;
		case '4':

			break;
		case 's':

			break;
		default:
			if (K != 'q')
			{
				cout << "Nope. Try again.\n ";
				break;
			}
		}
	} while (K != 'q');
	//MemClear(a, N); //почистить память
    return 0;
}

void MemClear(double** a, int& N) {
	for (int i = 0; i < N; i++) {
		delete[]a[i];
	}
	delete[] a;
	a = NULL;
	cout << "Sucsesfully clear memory" << endl;
}

int GetN(){
    float n;
    do {
        cin >> n;
        if (n <= 0 || n - (int)n != 0)
            cout << "!--- Error, try int number..." << endl;
    } while (n <= 0 || n - (int)n != 0);
    return n;
}

void GetSize(int& N, int& M){
	cout << "Enter size of two-dimensional matrix: \n";
    N = GetN(); M = GetN();
	N--; M--;
}

void NewMatrix(double** a, int& N, int& M){
    GetSize(N, M);
    cout << "Matrix have size: " << N+1 << "x" << M+1 << endl;
    a = new double* [N];
    for (int i = 0; i < N; i++) {
        a[i] = new double[M];
    }
    cout << "Sucsesfully get memory for matrix" << endl;
}

void ManualMatrix(double** a,int& N, int& M) {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			cout << "\nEnter [" << i << "][" << j << "] element: ";
			cin >> a[i][j];
			cout << a[i][j];
		}
		cout << "OMG!!! Das work" << endl;//debug !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
}
