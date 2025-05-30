/**
 * @file Settings.hpp
 * @brief Система настроек игры
 * @author  Корнилов и дипсик
 * @date 30.05.2025
 * 
 * Реализует паттерн Singleton для управления настройками:
 * - Включение/выключение музыки
 * - Включение/выключение цветов консоли
 * - Сохранение и загрузка настроек
 */

#pragma once
#include <string>

/**
 * @class Settings
 * @brief Управление игровыми настройками
 * 
 * Паттерн Singleton гарантирует единственный экземпляр настроек
 * во время выполнения программы
 */
class Settings {
public:
    /**
     * @brief Получить экземпляр настроек (Singleton)
     * @return Ссылка на единственный экземпляр Settings
     */
    static Settings& getInstance();

    /**
     * @brief Проверить включена ли музыка
     * @return true если музыка включена, иначе false
     */
    bool isMusicEnabled() const;
    
    /**
     * @brief Переключить состояние музыки
     */
    void toggleMusic();
    
    /**
     * @brief Проверить включены ли цвета консоли
     * @return true если цвета включены, иначе false
     */
    bool isColorEnabled() const;
    
    /**
     * @brief Переключить состояние цветов консоли
     */
    void toggleColor();
    
    /**
     * @brief Сохранить настройки в файл
     * 
     * Сохраняет в game_settings.cfg в формате:
     * [musicEnabled]
     * [colorEnabled]
     */
    void saveSettings();
    
    /**
     * @brief Загрузить настройки из файла
     * 
     * Если файл не существует, использует настройки по умолчанию:
     * - musicEnabled = true
     * - colorEnabled = true
     */
    void loadSettings();

    // Запрет копирования
    Settings(const Settings&) = delete;             ///< Запрет конструктора копирования
    Settings& operator=(const Settings&) = delete;  ///< Запрет оператора присваивания

private:
    Settings();  ///< Приватный конструктор
    
    bool musicEnabled;     ///< Флаг включения музыки
    bool colorEnabled;     ///< Флаг включения цветов
    
    const std::string SETTINGS_FILE = "game_settings.cfg"; ///< Файл хранения настроек
};