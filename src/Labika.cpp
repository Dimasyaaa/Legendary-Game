#include "Labika.hpp"
#include "Labirint.hpp"
#include "Menu.hpp"

using namespace std;

int main() {
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);
  Menu menu;
  Game game;

  menu.displayMainMenu(game);
  // t choice = runMenu();
  //  0 - выход, 1 - запуск игры
  // itch (choice) {
  // ase 1: {
  //  cout << "Начало игры" << endl;
  // Game game;
  // game.run();
  // break;
  //
  // ase 0:
  // return 0;
  //
}
