#include <iostream>
#include "Add.h"

int main()
{
    int x, y;
    std::cout << "Insert 2 numbers (int): ";
    std::cin >> x >> y;
    std::cout << "\nResult: " << add(x, y);
    system("pause");
    return 0;
}