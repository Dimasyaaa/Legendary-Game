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
    
    // Увеличиваем размер окна консоли
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 600, TRUE);
    
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

void Game::showStartScreen() {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Желтый цвет для заголовка
    SetConsoleTextAttribute(hConsole, 14);
    gotoxy(10, 10);
    cout << "Л А Б И Р И Н Т";
    
    // Зеленый цвет для кнопки старта
    SetConsoleTextAttribute(hConsole, 10);
    gotoxy(12, 10);
    cout << "НАЧАТЬ ИГРУ - НАЖМИТЕ ЛЮБУЮ КЛАВИШУ";
    
    // Сброс цвета
    SetConsoleTextAttribute(hConsole, 7);
    _getch(); // Ожидание нажатия клавиши
}

void Game::run() {
    showStartScreen(); // Показ стартового экрана
    displayMap();      // Инициализация игрового поля
    while (isRunning) {
        handleInput(); // Обработка игрового процесса
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
                cout << FOG_SYMBOL;
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
        cout << "ПОЗДРАВЛЯЕМ!!! Вы нашли сокровище! Нажмите любую клавишу для выхода.";
        _getch();
        isRunning = false;
    }
}

void Game::generateMap() {
    bool flag_end = false;
    int count = 0;
    int chet_pos = count_chet();
    
    // Используем отдельные координаты для генерации
    int tractorX = 1;
    int tractorY = 1;
    
    // Начальная позиция для генерации
    map[tractorX][tractorY] = PATH_SYMBOL;
    
    while (!flag_end) {
        // Прокладываем пути
        for (int i = 0; i < n * m; i++) {
            tractor_trail(tractorX, tractorY);
        }

        // Проверка завершения генерации
        for (int i = 1; i < n; i += 2) {
            for (int j = 1; j < m; j += 2) {
                if (map[i][j] == PATH_SYMBOL) count++;
            }
        }
        
        if (count == chet_pos) flag_end = true;
        else count = 0;
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
            map[tractorX - 1][tractorY] = PATH_SYMBOL;
            map[tractorX - 2][tractorY] = PATH_SYMBOL;
            tractorX -= 2;
        }
        break;
    case 2: // Вправо
        if (tractorY < m - 2 && map[tractorX][tractorY + 2] == WALL_SYMBOL) {
            map[tractorX][tractorY + 1] = PATH_SYMBOL;
            map[tractorX][tractorY + 2] = PATH_SYMBOL;
            tractorY += 2;
        }
        break;
    case 3: // Вниз
        if (tractorX < n - 2 && map[tractorX + 2][tractorY] == WALL_SYMBOL) {
            map[tractorX + 1][tractorY] = PATH_SYMBOL;
            map[tractorX + 2][tractorY] = PATH_SYMBOL;
            tractorX += 2;
        }
        break;
    case 4: // Влево
        if (tractorY > 1 && map[tractorX][tractorY - 2] == WALL_SYMBOL) {
            map[tractorX][tractorY - 1] = PATH_SYMBOL;
            map[tractorX][tractorY - 2] = PATH_SYMBOL;
            tractorY -= 2;
        }
        break;
    }
}

void Game::updateVisibility() {
    // Сброс текущей видимости
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visibilityMap[i][j] = false;
        }
    }

    // Установка видимости в радиусе 2 клеток
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            int nx = player_posX + dx;
            int ny = player_posY + dy;
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                visibilityMap[nx][ny] = true;
                
                // Помечаем видимые полы как посещенные
                if (map[nx][ny] == PATH_SYMBOL) {
                    visitedMap[nx][ny] = true;
                }
            }
        }
    }
    
    // Всегда видим текущую позицию игрока
    visibilityMap[player_posX][player_posY] = true;
}