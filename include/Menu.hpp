/**
 * @file Menu.hpp
 * @brief Система меню для игры "Лабика"
 * @author Команда КОДОЛАБИКИ (Куклин, Корнилов, Зайцева, Мешкова, Трунова)
 * @date 29.05.2025
 *
 * Содержит класс Menu и функции для управления игровым интерфейсом:
 * - Главное меню
 * - Меню настроек
 * - Таблица рекордов
 * - Система сохранения
 */

#pragma once

#include "Labirint.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale.h>
#include <string>
#include <vector>
#include <windows.h>

/**
 * @class Menu
 * @brief Управление игровыми меню
 *
 * Обеспечивает навигацию по:
 * - Главному меню
 * - Меню настроек
 * - Таблице рекордов
 */
class Menu {
public:
  /**
   * @brief Отображает главное меню игры
   */
  void displayMainMenu(Game game);

  /**
   * @brief Отображает меню настроек
   */
  void displaySettingsMenu();
};

/**
 * @brief Инициализация новой игры
 *
 * Создает:
 * - Директорию gamedata
 * - Файл config.ini с именем игрока и настройками цвета
 */
void initGame();

/**
 * @brief Отображает таблицу рекордов
 *
 * Читает рекорды из файла records.txt и отображает их
 * в форматированной таблице
 */
void showScores();

/**
 * @brief Изменение цвета интерфейса
 *
 * Предоставляет выбор из 4 цветовых схем:
 * 0. Стандартный (белый на черном)
 * 1. Красный
 * 2. Зеленый
 * 3. Синий
 *
 * Сохраняет выбор в файл gamedata/color.cfg
 */
void changeColor();