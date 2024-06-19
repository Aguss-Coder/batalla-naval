#include <iostream>
#include "game.h"
#include "human.h"
#include "bot.h"

using namespace std;

int main(int argc, char const *argv[])
{
  Game game;
  Human player1;
  Human player2;
  Bot Bot;

  cout << "Welcome to Battleship!" << endl;
  cout << "1. New Game" << endl;
  cout << "2. Load Game" << endl;
  int choice;
  cin >> choice;

  if (choice == 1)
  {
    game.newGame(player1, player2, Bot);
  }
  else if (choice == 2)
  {
    game.loadGame(player1, player2, Bot);
  }
  else
  {
    cout << "Invalid choice. Please try again." << endl;
  }

  return 0;
}

// g++ -Wall bot.cpp game.cpp gameBoard.cpp human.cpp main.cpp player.cpp ship.cpp -o battleShip.exe