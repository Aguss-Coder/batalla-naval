#include <iostream>
#include <fstream>
#include "game.h"
#include "../player/human.h"
#include "../player/bot.h"

using namespace std;

Game::Game()
{
  Human player1;
}
void Game::choosePlayer()
{
  cout << "Choose player: " << endl;
  cout << "1. Human" << endl;
  cout << "2. Bot" << endl;
  int choice;
  cin >> choice;
  if (choice == 1)
  {
    Human player2;
  }
  else if (choice == 2)
  {
    Bot bot;
  }
  else
  {
    cout << "Invalid choice. Please try again." << endl;
    choosePlayer();
  }
}