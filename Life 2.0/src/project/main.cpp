#include <iostream>
#include <string>
#include "Entity.h"
#include "Exceptions.h"
#include "Game.h"
#include "Input.h"
#include "Interactions.h"
#include "Inventory.h"
#include "Item.h"
#include "Stats.h"

int main() {
  std::string choice;
  while (true) {
  Game * JokerRooms = new Game();

  JokerRooms->gameStart();

  std::cout << "\n\n Would you like to play again? (y/n): ";
  std::cin >> choice;
  std::cin.clear();
  std::cin.ignore(500, '\n');
  if (choice != "y")
    break;
  choice = "";
  }
  return 0;
}
