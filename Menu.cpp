#include <iostream>
#include <string>
#include <fstream>

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
            system("cls");
            string username;
            cout << "Введите ваше имя: " << endl;
            cin >> username;
            ofstream out("Legendary-Game/IDEA/records.txt", ios::app);
            //out.open("Legendary-Game/IDEA/records.txt");
            if (out.is_open())
            {
                out << username << " ";
            }
            out.close(); 
            break;
        case 2:
            showScores();
            system("cls");
            break;
        case 3:
            showSettings();
            system("cls");
            break;
        case 4:
            system("cls");
            cout << "Выход из игры..." << endl;
            break;
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }

        cout << endl; // Для удобства
    } while (choice != 4);

    return 0;
}
