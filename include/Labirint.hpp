#ifndef LABIRINT_HPP
#define LABIRINT_HPP

void gotoxy(int y, int x);

const int n = 25; ///< Высота игровой карты
const int m = 25; ///< Ширина игровой карты

class Game {
private:
    unsigned char map[n][m];   ///< Массив, представляющий карту лабиринта
    bool visitedMap[n][m];     ///< Карта посещенных игроком клеток
    bool visibilityMap[n][m];  ///< Карта текущей видимости (туман войны)
    
    int player_posX;           ///< Текущая позиция игрока по X
    int player_posY;           ///< Текущая позиция игрока по Y
    int treasure_X;            ///< Позиция сокровища по X
    int treasure_Y;            ///< Позиция сокровища по Y
    char treasureSymbol;       ///< Символ для отображения сокровища
    char playerSymbol;         ///< Символ для отображения игрока
    bool isRunning;            ///< Флаг активности игрового цикла

public:
    Game();
    void run();
    void showStartScreen();

private:
    void displayMap();
    void handleInput();
    void generateMap();
    int count_chet();
    void placeTreasure();
    void tractor_trail(int& tractorX, int& tractorY);
    void updateVisibility();
};

#endif // LABIRINT_HPP