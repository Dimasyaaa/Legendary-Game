#include "Menu.hpp"

using namespace std;

int currentColor = 0;

void initGame()
{
    cout << "Игра началась!" << endl;
    string username;
    cout << "Введите имя: " << endl;
    cin >> username;
    ofstream out("gamedata/records.txt", ios::app);
    if (out.is_open())
    {
        out << username << " ";
    }
    out.close();
    // TODO записывать имя в конфиг
    //  BEST GAME EVER!!!
}

void showScores()
{
    vector<pair<string, double>> records = {
        {"Alice Johnson", 95.50},
        {"Bob Smith", 82.30},
        {"Charlie Brown", 76.80},
        {"Diana Prince", 99.99},
        {"Ethan Hunt", 65.45},
        {"Fiona Gallagher", 88.20},
        {"George Washington", 72.10}
    };

    cout << "Рекорды:" << endl;
    
    size_t maxNameLength = 4; // Минимум для заголовка "Имя"
    size_t maxScoreLength = 6; // Минимум для заголовка "Результат"

    for (const auto& record : records) {
        maxNameLength = max(maxNameLength, record.first.length());
        maxScoreLength = max(maxScoreLength, to_string(record.second).length());
    }

    const int nameWidth = static_cast<int>(maxNameLength);
    const int scoreWidth = static_cast<int>(maxScoreLength);

    // Верхняя граница таблицы
    cout << "╔" << string(nameWidth + 2, '=') << "╗" << endl;

    

    // Нижняя граница таблицы
    cout << "╚" << string(nameWidth + 2, '=') << "╩" << string(scoreWidth + 2, '=') << "╝" << endl;
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
