#include <iostream>
#include <windows.h>

#include "Menu.hpp"

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice = runMenu();
    // 0 - выход, 1 - запуск игры
    switch (choice)
    {
    case 1:
        std::cout << "Начало игры" << std::endl;
    case 0:
        return 0;
    }

    // проверка юникода
    std::cout << "°dfghgiusdfgпиываылвиаойъ α";
}
