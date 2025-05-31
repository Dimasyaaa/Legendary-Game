#include "Menu.hpp"
#include "ConsoleUtils.hpp"
#include "Labirint.hpp"
#include "Settings.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
namespace fs = filesystem;

// Объявляем функции, которые используются в Menu
void initGame();
void showScores();
void changeColor();

// Реализация методов класса Menu
void Menu::displayMainMenu(Game game) {
  Settings &settings = Settings::getInstance();
  int choice;

  while (true) {
    system("cls");

    // Вывод цветного заголовка
    if (settings.isColorEnabled()) {
      setConsoleColor(Color::GREEN);
    }
    cout << "===== LABICA =====" << endl;
    // resetConsoleColor();

    cout << "1. Начать игру" << endl
         << "2. Рекорды" << endl
         << "3. Настройки" << endl
         << "4. Выход" << endl
         << "Выбрать опцию (1-4): ";

    cin >> choice;

    // Обработка некорректного ввода
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      system("cls");
      cout << "Неверный ввод! Пожалуйста, введите число." << endl;
      continue;
    }

    switch (choice) {
    case 1:
      system("cls");
      initGame();
      game.run();
      break;
    case 2:
      system("cls");
      showScores();
      cout << "\nНажмите Enter для продолжения...";
      cin.ignore();
      cin.get();
      break;
    case 3:
      displaySettingsMenu(); // Вызов меню настроек
      break;
    case 4:
      cout << "Выход из игры..." << endl;
      exit(0);
    default:
      system("cls");
      cout << "Неверный выбор! Пожалуйста, выберите от 1 до 4." << endl;
      cin.ignore();
      cin.get();
    }
  }
}

void Menu::displaySettingsMenu() {
  Settings &settings = Settings::getInstance();
  int choice;

  while (true) {
    system("cls");
    // resetConsoleColor(); // TODO цвет из настроек

    cout << "=== Игровые Настройки ===" << endl << endl;

    cout << "1. Музыка: " << (settings.isMusicEnabled() ? "ВКЛ" : "ВЫКЛ")
         << endl
         << "2. Цвет консоли: "
         << (settings.isColorEnabled() ? "ВКЛ"
                                       : "ВЫКЛ") // TODO починить или убрать
         << endl
         << "3. Изменить цвет текста" << endl
         << "4. Вернуться в главное меню" << endl
         << endl
         << "Выберите опцию: ";

    // Проверка состояния потока ввода
    if (cin.fail()) {
      cin.clear();
    }
    cin >> choice;

    // Обработка некорректного ввода
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Неверный ввод! Пожалуйста, введите число от 1 до 4." << endl;
      cin.get();
      continue;
    }

    switch (choice) {
    case 1:
      settings.toggleMusic();
      cout << "\nМузыка " << (settings.isMusicEnabled() ? "ВКЛ" : "ВЫКЛ")
           << "!";
      cin.ignore();
      cin.get();
      break;
    case 2:
      settings.toggleColor();
      cout << "\nЦвета консоли " << (settings.isColorEnabled() ? "ВКЛ" : "ВЫКЛ")
           << "!";
      cin.ignore();
      cin.get();
      break;
    case 3:
      changeColor();
      break;
    case 4:
      return; // Возврат в главное меню
    default:
      cout << "Неверный выбор! Попробуйте снова." << endl;
      cin.ignore();
      cin.get();
    }
  }
}

void initGame() {
  string username;
  string colorValue = "default";

  if (!fs::exists("gamedata")) {
    fs::create_directory("gamedata");
  }

  ifstream f_in("gamedata/config.ini");
  if (f_in.good()) {
    string tmp;
    f_in >> tmp >> tmp >> username;
    f_in >> tmp >> tmp >> colorValue;
  }
  f_in.close();

  cout << "Игра началась!" << endl;
  cout << "Введите имя: ";
  cin >> username;

  ofstream f_out("gamedata/config.ini");
  if (f_out) {
    f_out << "username = " << username << endl;
    f_out << "color = " << colorValue << endl;
    cout << "Настройки сохранены!" << endl;
  } else {
    cerr << "Ошибка сохранения настроек!" << endl;
  }
  f_out.close();

  cout << "\nНажмите Enter для возврата в меню...";
  cin.ignore();
  cin.get();
}

void showScores() {
  vector<pair<string, string>> records;
  string line;

  if (!fs::exists("gamedata")) {
    fs::create_directory("gamedata");
  }

  ifstream f_in("gamedata/records.txt");

  if (!f_in.is_open()) {
    cout << "Рекордов ещё нет!" << endl;
    return;
  }

  while (getline(f_in, line)) {
    size_t delimiterPos = line.find('|');
    if (delimiterPos != string::npos) {
      string name = line.substr(0, delimiterPos);
      string score = line.substr(delimiterPos + 1);
      records.emplace_back(name, score);
    }
  }
  f_in.close();

  if (records.empty()) {
    cout << "Рекордов ещё нет!" << endl;
    return;
  }

  int nameWidth = 4;
  int scoreWidth = 6;

  for (const auto &record : records) {
    if (record.first.length() > nameWidth)
      nameWidth = record.first.length();
    if (record.second.length() > scoreWidth)
      scoreWidth = record.second.length();
  }

  nameWidth = max(nameWidth, 4);
  scoreWidth = max(scoreWidth, 6);

  cout << "╔";
  for (int i = 0; i < nameWidth + 2; i++)
    cout << "═";
  cout << "╦";
  for (int i = 0; i < scoreWidth + 2; i++)
    cout << "═";
  cout << "╗" << endl;

  cout << "║ " << left << setw(nameWidth) << "Имя" << "  ║ " << right
       << setw(scoreWidth) << "Рекорд" << " ║" << endl;

  cout << "╠";
  for (int i = 0; i < nameWidth + 2; i++)
    cout << "═";
  cout << "╬";
  for (int i = 0; i < scoreWidth + 2; i++)
    cout << "═";
  cout << "╣" << endl;

  for (const auto &record : records) {
    cout << "║ " << left << setw(nameWidth) << record.first << "  ║ " << right
         << setw(scoreWidth) << record.second << " ║" << endl;
  }

  cout << "╚";
  for (int i = 0; i < nameWidth + 2; i++)
    cout << "═";
  cout << "╩";
  for (int i = 0; i < scoreWidth + 2; i++)
    cout << "═";
  cout << "╝" << endl;
}

void changeColor() {
  int colorChoice;
  cout << "Выберите цвет текста:\n"
       << "0: Стандартный\n"
       << "1: Красный\n"
       << "2: Зеленый\n"
       << "3: Жёлтый\n"
       << "4-5 тоже есть\n"
       << "Ваш выбор: ";

  cin >> colorChoice;

  if (!fs::exists("gamedata")) {
    fs::create_directory("gamedata");
  }

  ofstream f_out("gamedata/color.cfg");
  if (f_out) {
    f_out << colorChoice;
    cout << "Цвет изменен!" << endl;
  } else {
    cerr << "Ошибка сохранения цвета!" << endl;
  }
  f_out.close();

  switch (colorChoice) {
  case 0:
    resetConsoleColor();
    break;
  case 1:
    setConsoleColor(Color::RED);
    break;
  case 2:
    setConsoleColor(Color::GREEN);
    break;
  case 3:
    setConsoleColor(Color::YELLOW);
    break;
  case 4:
    setConsoleColor(Color::BLUE);
    break;
  case 5:
    setConsoleColor(Color::CYAN);
    break;
  default:
    resetConsoleColor();
  }

  cout << "\nНажмите Enter для продолжения...";
  cin.ignore();
  cin.get();
}