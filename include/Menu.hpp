#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace std::string_literals;

// @warning вот тут настраивается конфиг. При изменении требуются обновления
void initGame();

void showScores();
void showSettings();

// @todo заменить текст на русский. Ввести константы цветов
void changeColor();
void showMenu();
int runMenu();