#include "Settings.hpp"
#include <fstream>

Settings& Settings::getInstance() {
    static Settings instance;
    return instance;
}

Settings::Settings() {
    loadSettings();
}

bool Settings::isMusicEnabled() const {
    return musicEnabled;
}

bool Settings::isColorEnabled() const {
    return colorEnabled;
}

void Settings::toggleMusic() {
    musicEnabled = !musicEnabled;
    saveSettings();
}

void Settings::toggleColor() {
    colorEnabled = !colorEnabled;
    saveSettings();
}

void Settings::saveSettings() {
    std::ofstream file(SETTINGS_FILE);
    if (file.is_open()) {
        file << musicEnabled << '\n'
             << colorEnabled;
    }
}

void Settings::loadSettings() {
    std::ifstream file(SETTINGS_FILE);
    if (file.is_open()) {
        file >> musicEnabled
             >> colorEnabled;
    } else {
        musicEnabled = true;
        colorEnabled = true;
    }
}