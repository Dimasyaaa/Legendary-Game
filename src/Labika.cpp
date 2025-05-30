#include "Labika.hpp"
#include "Labirint.hpp"
#include "Menu.hpp"

using namespace std;

int main() {
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);

  int choice = runMenu();
  // 0 - выход, 1 - запуск игры
  switch (choice) {
  case 1: {
    cout << "Начало игры" << endl;
    Game game;
    game.run();
    break;
  }
  case 0:
    return 0;
  }
}
