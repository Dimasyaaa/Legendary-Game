#include <iostream>
#include <windows.h>

#include "Menu.hpp"

int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    showMenu();

    // проверка юникода
    std::cout << "°dfghgiusdfgпиываылвиаойъ α";
}
