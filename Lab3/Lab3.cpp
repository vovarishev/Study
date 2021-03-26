#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool GetList();

int main()
{
    struct StackChart {//Инициализация стека
        struct Node {
            string name;
            int amount;
            int priceCost;
            int priceSell;
            Node* prev;
        };
        Node* Top = NULL;
        int Count;
    };
    GetList();
}

bool GetList() {
    string str;
    int i = 0;
    ifstream f("List.txt");
    if (!f) {
        cout << "! --- Error --- ! Can't open file \"List.txt\" \n";
        return false;
    }
    while (!f.eof()){
        getline(f, str);
        i++;
    }
    f.close();
    cout <<"Amount of strings in file: "<< i;
    return true;
}