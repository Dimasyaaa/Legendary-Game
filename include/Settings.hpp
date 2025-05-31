#pragma once

/**
 * @class Settings
 * @brief Класс для управления настройками игры
 * 
 * Реализован как синглтон, обеспечивает доступ к настройкам
 * из любой части программы.
 */
class Settings {
private:
    static constexpr const char* SETTINGS_FILE = "settings.cfg";
    bool musicEnabled;
    bool colorEnabled;
    
    Settings();
    void loadSettings();
    void saveSettings();

public:
    /**
     * @brief Получает единственный экземпляр класса Settings
     * @return Ссылка на экземпляр Settings
     */
    static Settings& getInstance();
    
    /**
     * @brief Проверяет, включена ли музыка
     * @return true если музыка включена, иначе false
     */
    bool isMusicEnabled() const;
    
    /**
     * @brief Проверяет, включены ли цвета консоли
     * @return true если цвета включены, иначе false
     */
    bool isColorEnabled() const;
    
    /**
     * @brief Переключает состояние музыки
     */
    void toggleMusic();
    
    /**
     * @brief Переключает состояние цветов консоли
     */
    void toggleColor();
};