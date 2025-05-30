/**
 * @file Labirint.cpp
 * @brief Реализация игры "Лабика"
 * @author Команда КОДОЛАБИКИ (Куклин, Корнилов, Зайцева, Мешкова, Трунова)
 * @date 29.05.2025
 * @bug При быстром движении возможны артефакты отрисовки
 */

#include "Labirint.hpp"
#include <cctype>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <time.h>
#include <windows.h>
#include <algorithm>

using namespace std;

random_device rd; ///< Генератор случайных чисел

// Реализация gotoxy
void gotoxy(int y, int x) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ==================== КОНСТАНТЫ ДЛЯ КОРРЕКТНОГО ОТОБРАЖЕНИЯ ====================
const char WALL_SYMBOL = '#';      ///< Символ для стен
const char PLAYER_SYMBOL = '@';    ///< Символ игрока
const char TREASURE_SYMBOL = '$';  ///< Символ сокровища
const char PATH_SYMBOL = '.';      ///< Символ для путей
const char FOG_SYMBOL = '?';       ///< Символ тумана войны

// ==================== РЕАЛИЗАЦИЯ МЕТОДОВ КЛАССА GAME ====================

Game::Game()
    : player_posX(1), player_posY(1), treasure_X(0), treasure_Y(0), 
      treasureSymbol(TREASURE_SYMBOL), playerSymbol(PLAYER_SYMBOL), isRunning(true) {
    
    // Установка кодовой страницы для корректного отображения
    SetConsoleOutputCP(CP_UTF8);
    
    // Инициализация карт
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            map[i][j] = WALL_SYMBOL;
            visitedMap[i][j] = false;
            visibilityMap[i][j] = false;
        }
    }
    
    // Генерация лабиринта
    generateMap();
    
    // Размещение сокровища
    placeTreasure();
    
    // Возврат игрока на стартовую позицию
    player_posX = 1;
    player_posY = 1;
    map[player_posX][player_posY] = PATH_SYMBOL;
    visitedMap[player_posX][player_posY] = true;
    updateVisibility();
}

void Game::run() {
    displayMap();
    while (isRunning) {
        handleInput();
    }
}

void Game::displayMap() {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Видимая область
            if (visibilityMap[i][j]) {
                // Позиция игрока
                if (i == player_posX && j == player_posY) {
                    SetConsoleTextAttribute(hConsole, 15);
                    cout << playerSymbol;
                }
                // Позиция сокровища
                else if (i == treasure_X && j == treasure_Y) {
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << treasureSymbol;
                }
                // Стены
                else if (map[i][j] == WALL_SYMBOL) {
                    SetConsoleTextAttribute(hConsole, 15);
                    cout << WALL_SYMBOL;
                }
                // Пути
                else {
                    SetConsoleTextAttribute(hConsole, 15);
                    cout << PATH_SYMBOL;
                }
            }
            // Посещенные, но невидимые области
            else if (visitedMap[i][j]) {
                // Стены
                if (map[i][j] == WALL_SYMBOL) {
                    SetConsoleTextAttribute(hConsole, 8);
                    cout << WALL_SYMBOL;
                }
                // Пути
                else {
                    SetConsoleTextAttribute(hConsole, 8);
                    cout << PATH_SYMBOL;
                }
            }
            // Неизведанные области
            else {
                SetConsoleTextAttribute(hConsole, 8);
                cout << FOG_SYMBOL;  // Исправлено
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void Game::handleInput() {
    char button = (char)_getch();
    if (button == '=') {
        isRunning = false;
        return;
    }
    
    int newX = player_posX;
    int newY = player_posY;

    // Определение нового положения
    if ((button == 'd' || button == 'D') && player_posY < m - 1) {
        newY++;
    } 
    else if ((button == 'a' || button == 'A') && player_posY > 0) {
        newY--;
    } 
    else if ((button == 's' || button == 'S') && player_posX < n - 1) {
        newX++;
    } 
    else if ((button == 'w' || button == 'W') && player_posX > 0) {
        newX--;
    }

    // Проверка на стену
    if (map[newX][newY] != WALL_SYMBOL) {
        player_posX = newX;
        player_posY = newY;
        visitedMap[player_posX][player_posY] = true;
        updateVisibility();
        displayMap();
    }
    else {
        visitedMap[newX][newY] = true;
        updateVisibility();
        displayMap();
    }

    // Проверка на победу
    if (player_posX == treasure_X && player_posY == treasure_Y) {
        gotoxy(n, 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "You found the treasure! Press any key to exit.";
        _getch();
        isRunning = false;
    }
}

void Game::generateMap() {
    // Инициализация начальной позиции
    int tractorX = 1;
    int tractorY = 1;
    map[tractorX][tractorY] = PATH_SYMBOL;

    // Количество клеток, которые должны стать путями
    int targetPaths = ((n - 1) / 2) * ((m - 1) / 2);
    int createdPaths = 1;

    // Пока не созданы все пути
    while (createdPaths < targetPaths) {
        // Выбираем случайное направление
        int directions[4][2] = {{-2, 0}, {2, 0}, {0, -2}, {0, 2}};
        shuffle(begin(directions), end(directions), mt19937(rd()));

        bool moved = false;
        
        // Пробуем двигаться в каждом направлении
        for (auto &dir : directions) {
            int newX = tractorX + dir[0];
            int newY = tractorY + dir[1];

            // Проверяем границы и что клетка - стена
            if (newX > 0 && newX < n-1 && newY > 0 && newY < m-1 && 
                map[newX][newY] == WALL_SYMBOL) {
                
                // Прокладываем путь
                map[tractorX + dir[0]/2][tractorY + dir[1]/2] = PATH_SYMBOL;
                map[newX][newY] = PATH_SYMBOL;
                tractorX = newX;
                tractorY = newY;
                createdPaths++;
                moved = true;
                break;
            }
        }

        // Если застряли - находим новую стартовую точку
        if (!moved) {
            for (int i = 1; i < n; i += 2) {
                for (int j = 1; j < m; j += 2) {
                    if (map[i][j] == PATH_SYMBOL) {
                        // Проверяем соседей этой точки
                        for (auto &dir : directions) {
                            int newX = i + dir[0];
                            int newY = j + dir[1];
                            if (newX > 0 && newX < n-1 && newY > 0 && newY < m-1 && 
                                map[newX][newY] == WALL_SYMBOL) {
                                tractorX = i;
                                tractorY = j;
                                j = m; // Выход из внутреннего цикла
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

int Game::count_chet() {
    int count_x = 0;
    int count_y = 0;

    for (int x = 2; x < n; x += 2) 
        count_x++;
    for (int y = 2; y < m; y += 2) 
        count_y++;

    return count_x * count_y;
}

void Game::placeTreasure() {
    treasure_X = n - 2;
    treasure_Y = m - 2;
    map[treasure_X][treasure_Y] = treasureSymbol;
}

void Game::tractor_trail(int& tractorX, int& tractorY) {
    mt19937 gen(rd() + time(NULL));
    uniform_int_distribution<> dist(1, 4);
    int vect = dist(gen);
    
    switch (vect) {
    case 1: // Вверх
        if (tractorX > 1 && map[tractorX - 2][tractorY] == WALL_SYMBOL) {
            map[tractorX - 1][tractorY] = PATH_SYMBOL;  // Исправлено
            map[tractorX - 2][tractorY] = PATH_SYMBOL;  // Исправлено
            tractorX -= 2;
        }
        break;
    case 2: // Вправо
        if (tractorY < m - 2 && map[tractorX][tractorY + 2] == WALL_SYMBOL) {
            map[tractorX][tractorY + 1] = PATH_SYMBOL;  // Исправлено
            map[tractorX][tractorY + 2] = PATH_SYMBOL;  // Исправлено
            tractorY += 2;
        }
        break;
    case 3: // Вниз
        if (tractorX < n - 2 && map[tractorX + 2][tractorY] == WALL_SYMBOL) {
            map[tractorX + 1][tractorY] = PATH_SYMBOL;  // Исправлено
            map[tractorX + 2][tractorY] = PATH_SYMBOL;  // Исправлено
            tractorX += 2;
        }
        break;
    case 4: // Влево
        if (tractorY > 1 && map[tractorX][tractorY - 2] == WALL_SYMBOL) {
            map[tractorX][tractorY - 1] = PATH_SYMBOL;  // Исправлено
            map[tractorX][tractorY - 2] = PATH_SYMBOL;  // Исправлено
            tractorY -= 2;
        }
        break;
    }
}

void Game::updateVisibility() {
    // Сбрасываем видимость
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visibilityMap[i][j] = false;
        }
    }

    // Устанавливаем видимость с проверкой стен
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            int x = player_posX + dx;
            int y = player_posY + dy;
            
            if (x >= 0 && x < n && y >= 0 && y < m) {
                // Проверяем, нет ли стены между игроком и клеткой
                bool visible = true;
                int stepX = (dx == 0) ? 0 : (dx > 0) ? 1 : -1;
                int stepY = (dy == 0) ? 0 : (dy > 0) ? 1 : -1;
                
                int currX = player_posX;
                int currY = player_posY;
                
                while (currX != x || currY != y) {
                    currX += stepX;
                    currY += stepY;
                    
                    if (map[currX][currY] == WALL_SYMBOL) {
                        visible = false;
                        break;
                    }
                }
                
                if (visible) {
                    visibilityMap[x][y] = true;
                    if (map[x][y] == PATH_SYMBOL) {
                        visitedMap[x][y] = true;
                    }
                }
            }
        }
    }
    
    // Всегда видим текущую позицию
    visibilityMap[player_posX][player_posY] = true;
}