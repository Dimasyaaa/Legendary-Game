//              Игра ЛАБИКА
//  Авторы: Вся команда КОДОЛАБИКИ (Куклин, Корнилов, Зайцева, Мешкова, Трунова)

#include "Labirint.hpp"
#include <cctype>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <time.h>
#include <windows.h>

using namespace std;

// рандомное зерно для генераций
random_device rd;

// функция переносса курсора на заданную позицию
void gotoxy(int y, int x) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

unsigned char map_symbol = 219;

Game::Game()
    : player_posX(1), player_posY(1), treasureSymbol(253), playerSymbol(245),
      isRunning(true) {
  initializeMap();
  generateMap();
  placeTreasure();
}

void Game::run() {
  displayMap();
  while (isRunning) {
    //            displayMap();
    handleInput();
  }
}

// Метод для инициализации карты
void Game::initializeMap() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      map[i][j] = map_symbol; // Заполнение карты границами
    }
  }
  map[player_posX][player_posY] =
      playerSymbol; // Установка начальной позиции игрока
}
// метод для вывода карты в консоль
void Game::displayMap() {
  system("cls");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      cout << map[i][j];
    cout << endl;
  }
}

void Game::handleInput() {
  char button = (char)_getch();
  if (button == '=') {
    isRunning = false; // Выход из игры
    return;
  }
  gotoxy(player_posX, player_posY);
  cout << ' ';
  map[player_posX][player_posY] =
      ' '; // Убираем символ игрока с текущей позиции

  // Обработка перемещения игрока
  if ((button == 'd' || button == 'D') &&
      map[player_posX][player_posY + 1] != map_symbol) {
    player_posY++;
  } else if ((button == 'a' || button == 'A') &&
             map[player_posX][player_posY - 1] != map_symbol) {
    player_posY--;
  } else if ((button == 's' || button == 'S') &&
             map[player_posX + 1][player_posY] != map_symbol) {
    player_posX++;
  } else if ((button == 'w' || button == 'W') &&
             map[player_posX - 1][player_posY] != map_symbol) {
    player_posX--;
  }

  gotoxy(player_posX, player_posY);
  cout << playerSymbol;
  map[player_posX][player_posY] =
      playerSymbol; // Установка символа игрока на новую позицию

  // Проверка на победу
  if (player_posX == treasure_X && player_posY == treasure_Y) {
    gotoxy(n, 1);
    cout << "You found a treasure!" << endl;
    isRunning = false;
  }
}

void Game::generateMap() {
  // флаг очистки всех четных клеток (x и y четные числа)
  bool flag_end = false;

  int count = 0;
  int chet_pos = count_chet();
  while (!flag_end) {
    // провека четных клеток на пустоту
    for (int i = 0; i < n * m; i++)
      tractor_trail();

    for (int i = 1; i < n; i += 2) {
      for (int j = 1; j < m; j += 2) {
        if (map[i][j] == ' ')
          count++;
      }
    }
    if (count == chet_pos)
      flag_end = true;

    count = 0;
  }
}

int Game::count_chet() {
  int count_x = 0;
  int count_y = 0;

  // Считаем количество четных ячеек
  for (int x = 2; x < n; x += 2)
    count_x++;
  for (int y = 2; y < m; y += 2)
    count_y++;

  return count_x * count_y; // Возвращаем общее количество четных ячеек
}

void Game::placeTreasure() {
  treasure_X = n - 1 - player_posX;
  treasure_Y = m - 1 - player_posY;
  map[treasure_X][treasure_Y] = treasureSymbol; // Помещение сокровища на карту
}

void Game::tractor_trail() {
  // Записывает рандомное в vect рандомное число от 1 до 4
  int vect; // Изменено на int, так как используется для выбора кейса
  mt19937 gen(rd() + time(NULL));
  uniform_int_distribution<> dist(1, 4);
  vect = dist(gen);
  switch (vect) {
  case 1: {
    if ((player_posX > 1) &&
        (map[player_posX - 2][player_posY] == map_symbol)) {
      player_posX--;
      map[player_posX + 1][player_posY] = ' ';
      player_posX--;
      map[player_posX + 1][player_posY] = ' ';
    } else {
      if (player_posX > 1) {
        player_posX = player_posX - 2;
        map[player_posX + 2][player_posY] = ' ';
      }
    }
  } break;
  case 2: {
    if ((player_posY < m - 2) &&
        (map[player_posX][player_posY + 2] == map_symbol)) {
      player_posY++;
      map[player_posX][player_posY - 1] = ' ';
      player_posY++;
      map[player_posX][player_posY - 1] = ' ';
    } else {
      if (player_posY < m - 2) {
        player_posY = player_posY + 2;
        map[player_posX][player_posY - 2] = ' ';
      }
    }
  } break;
  case 3: {
    if ((player_posX < n - 2) &&
        (map[player_posX + 2][player_posY] == map_symbol)) {
      player_posX++;
      map[player_posX - 1][player_posY] = ' ';
      player_posX++;
      map[player_posX - 1][player_posY] = ' ';
    } else {
      if (player_posX < n - 2) {
        player_posX = player_posX + 2;
        map[player_posX - 2][player_posY] = ' ';
      }
    }
  } break;
  case 4: {
    if ((player_posY > 1) &&
        (map[player_posX][player_posY - 2] == map_symbol)) {
      player_posY--;
      map[player_posX][player_posY + 1] = ' ';
      player_posY--;
      map[player_posX][player_posY + 1] = ' ';
    } else {
      if (player_posY > 1) {
        player_posY = player_posY - 2;
        map[player_posX][player_posY + 2] = ' ';
      }
    }
  } break;
  }
}
