#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>
#include <windows.h>

using namespace std;

int currentColor = 0;

void startGame() {
    cout << "The game has started!" << endl;
    // BEST GAME EVER!!!
}

void showScores() {
    cout << "Records:" << endl;
    // Таблица рекордов
}

void showSettings() {
    cout << "Settings:" << endl;
    // Здесь мы пропишем настроечки
}

void changeColor() {
    cout << "Select the text color (0 - normal, 1 - red, 2 - green, 3 - blue):";
    cin >> currentColor;

    switch (currentColor) {
    case 0:
        cout << "\033[0m"; // Нормальный цвет
        break;
    case 1:
        cout << "\033[31m"; // Красный
        break;
    case 2:
        cout << "\033[32m"; // Зелёный
        break;
    case 3:
        cout << "\033[34m"; // Синий
        break;
    default:
        cout << "\033[0m";
        cout << "Wrong choice. The color is set by default." << endl;
        break;
    }
}

void showMenu() {
    cout << "===== LABICA =====" << endl;
    cout << "1. Start the game" << endl;
    cout << "2. Records" << endl;
    cout << "3. Settings" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    int choice;

    bool flag = true;
    while (flag){
        showMenu();
        cout << "Select an option (1-4): ";

        cin >> choice;
        switch (choice) {
        case 1:
            startGame();
            {
            string username;
            cout << "Enter your name: " << endl;
            cin >> username;
            ofstream out("IDEA/records.txt", ios::app);
            if (out.is_open()) {
                    out << username << " ";
                }
                out.close();
            }
            break;
        case 2:
            showScores();
            break;
        case 3:
            showSettings();
            changeColor();
            break;
        case 4:
            cout << "Exit the game..." << endl;
            flag = false;
            break;
        default:
            cout << "Wrong choice, try again." << endl;
        }

        cout << endl; // Для удобства
    }

    return 0;
}
