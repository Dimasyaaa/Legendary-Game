void gotoxy(int y, int x);

const int n = 25; // Высота карты
const int m = 25; // Ширина карты

class Game {
private:
  unsigned char map[n][m]; // Карта
  int player_posX;         // Позиция игрока по X
  int player_posY;         // Позиция игрока по Y
  int treasure_X;          // Позиция сокровища Х
  int treasure_Y;          // Позиция сокровища Y
  char treasureSymbol;     // Символ сокровища
  char playerSymbol;       // Символ игрока
  bool isRunning;          // Флаг для работы основного цикла игры

public:
  Game();
  /**
   * @brief 
   *  Это мой первый коммент)
   *  это мой второй))))
   *  я сегодня в огне
   */
  void run();

private:
  // Метод для инициализации карты
  void initializeMap();
  // метод для вывода карты в консоль
  void displayMap();
  void handleInput();
  void generateMap();
  int count_chet();
  void placeTreasure();
  void tractor_trail();
};