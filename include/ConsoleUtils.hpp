/**
 * @file ConsoleUtils.hpp
 * @brief Утилиты для работы с консолью (цвет, позиционирование)
 * @author Корнилов и дипсик
 * @date 30.05.2025
 * 
 * Содержит функции для управления цветом текста в консоли
 * и позиционированием курсора.
 */

#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

/**
 * @enum Color
 * @brief Цвета для текста в консоли
 */
enum class Color {
    RED = 12,      ///< Красный текст (Windows)
    GREEN = 10,    ///< Зеленый текст (Windows)
    YELLOW = 14,   ///< Желтый текст (Windows)
    BLUE = 9,      ///< Синий текст (Windows)
    DEFAULT = 7    ///< Стандартный цвет консоли
};

/**
 * @brief Устанавливает цвет текста в консоли
 * @param color Цвет из перечисления Color
 * 
 * Функция работает кросс-платформенно:
 *
 */
inline void setConsoleColor(Color color) {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<int>(color));
    #else
    const char* codes[] = {
        "\033[31m", // RED
        "\033[32m", // GREEN
        "\033[33m", // YELLOW
        "\033[34m", // BLUE
        "\033[0m"   // DEFAULT
    };
    std::cout << codes[static_cast<int>(color)];
    #endif
}

/**
 * @brief Сбрасывает цвет текста в консоли к стандартному
 * 
 * Восстанавливает цвет по умолчанию для текущей консоли
 */
inline void resetConsoleColor() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); // Стандартный цвет
    #else
    std::cout << "\033[0m";
    #endif
}