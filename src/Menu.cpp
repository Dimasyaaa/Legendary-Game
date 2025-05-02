#include "Menu.hpp"

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
    vector<pair<string, double>> records;
    fs::current_path(fs::current_path().parent_path());
    fs::path dirPath = fs::current_path() / "gamedata";
    if (!fs::exists(dirPath)) {
        fs::create_directory(dirPath);
    }
    fs::current_path(dirPath);
    fs::path filePath = dirPath / "records.txt";
    ifstream file(filePath, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << "records.txt" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != string::npos) {
            string name = line.substr(0, delimiterPos);
            string scoreStr = line.substr(delimiterPos + 1);
            
            try {
                double score = stod(scoreStr);
                records.emplace_back(name, score);
            } catch (...) {
                cerr << "Warning: Invalid score format in line: " << line << endl;
            }
        }
    }
    file.close();

    size_t maxNameLength = 4; // Минимум для заголовка "Имя"
    size_t maxScoreLength = 6; // Минимум для заголовка "Результат"

    for (const auto& record : records) {
        maxNameLength = max(maxNameLength, record.first.length());
        maxScoreLength = max(maxScoreLength, to_string(record.second).length());
    }

    const int nameWidth = static_cast<int>(maxNameLength);
    const int scoreWidth = static_cast<int>(maxScoreLength);

    // Верхняя граница таблицы
    cout << "╔";
    for (int i = 0; i < nameWidth + 2; i++) 
        cout << "═";
    cout << "╦";
    for (int i = 0; i < scoreWidth + 2; i++) 
        cout << "═";
    cout << "╗" << endl;

    // Заголовок
    cout << "║ " << left << setw(nameWidth) << "Имя" << "    ║ " << right << setw(scoreWidth) << "Рекорд" << "    ║" << endl;

     // Разделительная линия
    cout << "╠";
    for (int i = 0; i < nameWidth + 2; i++) 
        cout << "═";
    cout << "╬";
    for (int i = 0; i < scoreWidth + 2; i++) 
        cout << "═";
    cout << "╣" << endl;


    for (int i = 0; i < records.size(); i++) {
        cout << "║ \033[1;36m" << left << setw(nameWidth) << records[i].first << "\033[0m ║ " << right << setw(scoreWidth);
        if (records[i].second >= 90) {
            cout << "\033[1;32m"; // Ярко-зеленый для высоких результатов
        } else if (records[i].second >= 70) {
            cout << "\033[1;33m"; // Ярко-желтый
        } else {
            cout << "\033[1;31m"; // Ярко-красный
        }
        cout << fixed << setprecision(2) << records[i].second << "\033[0m   ║";
        cout << endl;
    }

    // Нижняя граница таблицы
    cout << "╚";
    for (int i = 0; i < nameWidth + 2; i++) 
        cout << "═";
    cout << "╩";
    for (int i = 0; i < scoreWidth + 2; i++) 
        cout << "═";
    cout << "╝" << endl;
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
            system("cls");
            initGame();
            return 1;
        case 2:
            system("cls");
            showScores();
            break;
        case 3:
            system("cls");
            showSettings();
            break;
        case 4:
            cout << "Выход из игры..." << endl;
            return 0;
        default:
            system("cls");
            cout << "Неверный выбор, дубина!" << endl;
        }
        
        cout << endl; // Для удобства
    }
}
