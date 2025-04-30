#include "Menu.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;

int currentColor = 0;

void initGame()
{
    cout << "Игра началась!" << endl;
    string username;
    cout << "Введите имя: " << endl;
    cin >> username;
    fs::current_path(fs::current_path().parent_path());
    fs::path dirPath = fs::current_path() / "gamedata";
    if (!fs::exists(dirPath)) {
        fs::create_directory(dirPath);
    }
    fs::current_path(dirPath);
    fs::path filePath = dirPath / "config.txt";
    ofstream file(filePath, ios::app);
    file << username << endl;
    file.close();
}

void showScores()
{
    cout << "Рекорды:" << endl;
    // TODO Таблица рекордов
}

void showSettings()
{
    cout << "Настройки:" << endl;
    
    // TODO выбор настроек, 
    //changeColor();
    // Здесь мы пропишем настроечки
}

void changeColor()
{
    cout << "Select the text color (0 - normal, 1 - red, 2 - green, 3 - blue):";
    cin >> currentColor;

    switch (currentColor)
    {
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

void showMenu()
{
    cout << "===== LABICA =====" << endl;
    cout << "1. Начать игру" << endl;
    cout << "2. Рекорды" << endl;
    cout << "3. Настройки" << endl;
    cout << "4. Выход" << endl;
}

int runMenu()
{
    int choice;

    while (true)
    {
        showMenu();
        cout << "Выбрать опцию (1-4): ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            initGame();
            return 1;
        case 2:
            showScores();
            break;
        case 3:
            showSettings();
            break;
        case 4:
            cout << "Выход из игры..." << endl;
            return 0;
        default:
            cout << "Неверный выбор, дубина!" << endl;
        }

        // TODO очистка экрана
        cout << endl; // Для удобства
    }
}
