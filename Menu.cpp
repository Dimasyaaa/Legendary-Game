#include <iostream>
#include <string>

using namespace std;

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

int main() {
    
    setlocale(LC_ALL, "Rus");

    int choice;

    do {
        cout << "===== ЛАБИКА =====" << endl;
        cout << "1. Начать игру" << endl;
        cout << "2. Рекорды" << endl;
        cout << "3. Настройки" << endl;
        cout << "4. Выход" << endl;
        cout << "Выберите опцию (1-4): ";
        cin >> choice;

        switch (choice) {
        case 1:
            startGame();
            break;
        case 2:
            showScores();
            break;
        case 3:
            showSettings();
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
