#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int currentColor = 0;

void startGame() {
    cout << "Игра начата!" << endl;
    // BEST GAME EVER!!!
}

void showScores() {
    cout << "Рекорды:" << endl;
    // Таблица рекордов
}

void showSettings() {
    cout << "Настройки:" << endl;
    // Здесь мы пропишем настроечки
}

void changeColor() {
    cout << "Выберите цвет текста (0 - обычный, 1 - красный, 2 - зелёный, 3 - синий): ";
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
        cout << "Неверный выбор. Цвет установлен по умолчанию." << endl;
        break;
    }
}

void showMenu() {
    cout << "===== ЛАБИКА =====" << endl;
    cout << "1. Начать игру" << endl;
    cout << "2. Рекорды" << endl;
    cout << "3. Настройки" << endl;
    cout << "4. Выход" << endl;
}

int main() {
    setlocale(LC_ALL, "Rus");

    int choice;

    do {
        showMenu();
        cout << "Выберите опцию (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1:
            startGame();
            {
                string username;
                cout << "Введите ваше имя: " << endl;
                cin >> username;
                ofstream out("records.txt", ios::app);
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
            cout << "Выход из игры..." << endl;
            break;
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }

        cout << endl; // Для удобства
    } while (choice != 4);

    return 0;
}
