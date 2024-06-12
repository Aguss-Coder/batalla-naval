#include <iostream>
#include "classes/game/game.h"

using namespace std;

int main(int argc, char const *argv[])
{
  Game game;

  cout << "Welcome to Battleship!" << endl;
  cout << "1. New Game" << endl;
  cout << "2. Load Game" << endl;
  int choice;
  cin >> choice;

  if (choice == 1)
  {
    game.newGame();
  }
  else if (choice == 2)
  {
    game.loadGame();
  }
  else
  {
    cout << "Invalid choice. Please try again." << endl;
  }

  return 0;
}
