#include "Menu.hpp"

int currentColor = 0;

void initGame() {
  std::string username;
  std::string color;

  std::filesystem::create_directory("gamedata");

  std::ifstream f_in("gamedate\\config.ini", std::ios::in);
  if (f_in.good()) {
    std::string tmp;
    f_in >> tmp >> tmp >> username;
    f_in >> tmp >> tmp >> color;
  }
  f_in.close();

  std::cout << "Игра началась!" << std::endl;
  std::cout << "Введите имя: " << std::endl;
  std::cin >> username;

  std::ofstream f_out("gamedata\\config.ini", std::ios::out);
  f_out << "username = " << username << std::endl;
  f_out << "color = " << color << std::endl;
  f_out.close();
}

void showScores() {
  std::vector<std::pair<std::string, std::string>> records;
  std::string line;

  std::filesystem::create_directory("gamedata");
  std::ifstream f_in("gamedata\\records.txt", std::ios::in);
  if (!f_in.good()) {
    std::cout << "Рекордов ещё нет!";
    return;
  }
  system("cls");

  while (std::getline(f_in, line)) {
    size_t delimiterPos = line.find('|');
    if (delimiterPos != std::string::npos) {
      std::string name = line.substr(0, delimiterPos);
      std::string score = line.substr(delimiterPos + 1);

      try {
        records.emplace_back(name, score);
      } catch (...) {
        std::cerr << "Неправильный формат рекорда в строке № " << line
                  << std::endl;
      }
    }
  }
  f_in.close();

  int nameWidth = 10; // Минимум для заголовка "Имя"
  int scoreWidth = 7; // Минимум для заголовка "Рекорд"

  for (const auto &record : records) {
    if (record.first.length() > 10)
      nameWidth = record.first.length();
  }

  // Верхняя граница таблицы
  std::cout << "╔";
  for (int i = 0; i < nameWidth + 2; i++)
    std::cout << "═";
  std::cout << "╦";
  for (int i = 0; i < scoreWidth + 2; i++)
    std::cout << "═";
  std::cout << "╗" << std::endl;

  // Заголовок
  std::cout << "║ " << std::left << std::setw(nameWidth + 3) << "Имя " << " ║ "
            << std::right << std::setw(scoreWidth) << "Рекорд " << " ║"
            << std::endl;

  // Разделительная линия
  std::cout << "╠";
  for (int i = 0; i < nameWidth + 2; i++)
    std::cout << "═";
  std::cout << "╬";
  for (int i = 0; i < scoreWidth + 2; i++)
    std::cout << "═";
  std::cout << "╣" << std::endl;

  for (int i = 0; i < records.size(); i++) {
    std::cout << "║ \033[1;36m" << std::left << std::setw(nameWidth)
              << records[i].first;
    std::cout << "\033[0m" << " ║ " << std::right << std::setw(scoreWidth);

    std::cout << records[i].second << "\033[0m ║" << std::endl;
  }

  // Нижняя граница таблицы
  std::cout << "╚";
  for (int i = 0; i < nameWidth + 2; i++)
    std::cout << "═";
  std::cout << "╩";
  for (int i = 0; i < scoreWidth + 2; i++)
    std::cout << "═";
  std::cout << "╝" << std::endl;
}

void showSettings() {
  std::cout << "Настройки:" << std::endl;

  // TODO выбор настроек,
  // changeColor();
  // Здесь мы пропишем настроечки
}

void changeColor() {
  std::cout
      << "Select the text color (0 - normal, 1 - red, 2 - green, 3 - blue):";
  std::cin >> currentColor;

  switch (currentColor) {
  case 0:
    std::cout << "\033[0m"; // Нормальный цвет
    break;
  case 1:
    std::cout << "\033[31m"; // Красный
    break;
  case 2:
    std::cout << "\033[32m"; // Зелёный
    break;
  case 3:
    std::cout << "\033[34m"; // Синий
    break;
  default:
    std::cout << "\033[0m";
    std::cout << "Wrong choice. The color is set by default." << std::endl;
    break;
  }
}

void showMenu() {
  std::cout << "===== LABICA =====" << std::endl
            << "1. Начать игру" << std::endl
            << "2. Рекорды" << std::endl
            << "3. Настройки" << std::endl
            << "4. Выход" << std::endl;
}

int runMenu() {
  int choice;

  while (true) {
    showMenu();
    std::cout << "Выбрать опцию (1-4): ";
    std::cin >> choice;
    switch (choice) {
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
      std::cout << "Выход из игры..." << std::endl;
      return 0;
    default:
      system("cls");
      std::cout << "Неверный выбор, дубина!" << std::endl;
    }
    std::cout << std::endl; // Для удобства
  }
}
