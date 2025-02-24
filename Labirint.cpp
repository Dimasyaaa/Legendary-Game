//              Игра ЛАБИКИ
//  Авторы: Вся команда КОДОЛАБИКИ (Куклин, Корнилов, Поляков, Зайцева, Мешкова, Трунова)

#include <iostream>
#include <conio.h>
#include <cctype>
#include <cstdlib>
#include <random>
#include <time.h>
#include <windows.h>
using namespace std;

//рандомное зерно для генераций
random_device rd;

//функция переносса курсора на заданную позицию
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

const int n = 25;  // Высота карты
const int m = 25;  // Ширина карты

unsigned char map_symbol = 219;

class Game {
private:
    unsigned char map[n][m];     // Карта
    int player_posX;    // Позиция игрока по X
    int player_posY;    // Позиция игрока по Y
    char treasureSymbol;// Символ сокровища
    char playerSymbol;  // Символ игрока
    bool isRunning;     // Флаг для работы основного цикла игры

public:
    Game() : player_posX(1), player_posY(1), treasureSymbol(253), playerSymbol(245), isRunning(true) {
        initializeMap();
        generateMap();
        placeTreasure();
    }

    void run() {
        displayMap();
        while (isRunning) {
//            displayMap();
            handleInput();
        }
    }

private:
    //Метод для инициализации карты
    void initializeMap() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                map[i][j] = map_symbol; // Заполнение карты границами
            }
        }
        map[player_posX][player_posY] = playerSymbol; // Установка начальной позиции игрока
    }
    //метод для вывода карты в консоль
    void displayMap() {
        system("cls");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << map[i][j] ;
            cout << endl;
        }

    }

    void handleInput() {
        char button = (char)_getch();
        if (button == '=') {
            isRunning = false; // Выход из игры
            return;
        }
        gotoxy(player_posX,player_posY);
        cout << ' ';
        map[player_posX][player_posY] = ' '; // Убираем символ игрока с текущей позиции



        // Обработка перемещения игрока
        if ((button == 'd' || button == 'D') && map[player_posX + 1][player_posY] !=  map_symbol) {
            gotoxy(1,m+1);
            cout<<"Cym_map:"<<map[player_posX + 1][player_posY];
            player_posX++;

        }
        else if ((button == 'a' || button == 'A') && map[player_posX - 1][player_posY] !=  map_symbol) {
            gotoxy(1,m+1);
            cout<<"Cym_map:"<<map[player_posX - 1][player_posY];
            player_posX--;
        }
        else if ((button == 's' || button == 'S') && map[player_posX ][player_posY+ 1] !=  map_symbol) {
            gotoxy(1,m+1);
            cout<<"Cym_map:"<<map[player_posX ][player_posY+ 1];
            player_posY++;
        }
        else if ((button == 'w' || button == 'W') && map[player_posX ][player_posY- 1] !=  map_symbol) {
            gotoxy(1,m+1);
            cout<<"Cym_map:"<<map[player_posX ][player_posY- 1];
            player_posY--;
        }

        // Проверка на победу
        if (map[player_posX][player_posY] == treasureSymbol) {
            cout << "Вы нашли сокровище!" << endl;
            isRunning = false;
        }
        gotoxy(player_posX,player_posY);
        cout << playerSymbol;
        map[player_posX][player_posY] = playerSymbol; // Установка символа игрока на новую позицию

    }

    void generateMap() {
        // флаг очистки всех четных клеток (x и y четные числа)
        bool flag_end = false;

        int count = 0;
        int chet_pos = count_chet();
        while (!flag_end) {
            // провека четных клеток на пустоту
            for (int i = 0; i < n*m; i++) tractor_trail();

            for (int i = 1; i < n; i += 2) {
                for (int j = 1; j < m; j += 2) {
                    if (map[i][j] == ' ') count++;
                }
            }
            if (count == chet_pos) flag_end = true;

            count = 0;
        }
    }

    int count_chet() {
        int count_x = 0;
        int count_y = 0;

        // Считаем количество четных ячеек
        for (int x = 2; x < n; x += 2) count_x++;
        for (int y = 2; y < m; y += 2) count_y++;

        return count_x * count_y; // Возвращаем общее количество четных ячеек
    }

    void placeTreasure() {
        int treasure_x = n - 1 - player_posX;
        int treasure_y = m - 1 - player_posY;
        map[treasure_x][treasure_y] = treasureSymbol; // Помещение сокровища на карту
    }

    void tractor_trail() {
        // Записывает рандомное в vect рандомное число от 1 до 4
        int vect; // Изменено на int, так как используется для выбора кейса
        mt19937 gen(rd()+time(NULL));
        uniform_int_distribution<> dist(1, 4);
        vect = dist(gen);
        switch (vect) {
        case 1: {
            if ((player_posX > 1) && (map[player_posX - 2][player_posY] ==  map_symbol)) {
                player_posX--;
                map[player_posX + 1][player_posY] = ' ';
                player_posX--;
                map[player_posX + 1][player_posY] = ' ';
            }
            else {
                if (player_posX > 1) {
                    player_posX = player_posX - 2;
                    map[player_posX + 2][player_posY] = ' ';
                }
            }
        } break;
        case 2: {
            if ((player_posY < m - 2) && (map[player_posX][player_posY + 2] ==  map_symbol)) {
                player_posY++;
                map[player_posX][player_posY - 1] = ' ';
                player_posY++;
                map[player_posX][player_posY - 1] = ' ';
            }
            else {
                if (player_posY < m - 2) {
                    player_posY = player_posY + 2;
                    map[player_posX][player_posY - 2] = ' ';
                }
            }
        } break;
        case 3: {
            if ((player_posX < n - 2) && (map[player_posX + 2][player_posY] ==  map_symbol)) {
                player_posX++;
                map[player_posX - 1][player_posY] = ' ';
                player_posX++;
                map[player_posX - 1][player_posY] = ' ';
            }
            else {
                if (player_posX < n - 2) {
                    player_posX = player_posX + 2;
                    map[player_posX - 2][player_posY] = ' ';
                }
            }
        } break;
        case 4: {
            if ((player_posY > 1) && (map[player_posX][player_posY - 2] ==  map_symbol)) {
                player_posY--;
                map[player_posX][player_posY + 1] = ' ';
                player_posY--;
                map[player_posX][player_posY + 1] = ' ';
            }
            else {
                if (player_posY > 1) {
                    player_posY = player_posY - 2;
                    map[player_posX][player_posY + 2] = ' ';
                }
            }
        } break;
        }
    }
};

int main() {

    Game game;
    game.run();

    return 0;
}
