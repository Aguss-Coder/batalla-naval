#include <iostream>
#include <fstream>
#include "game.h"
#include "../player/human.h"
#include "../player/bot.h"
#include <string>

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
void Game::loadGame()
{
  cout << "Loading game..." << endl;
  try
  {
    ifstream file("savedGame.txt");

    if (!file.is_open())
    {
      throw runtime_error("Error opening file");
    }

    // function to read the content of the file to the object
  }
  catch (const exception &e)
  {
    cout << "An error ocurred: " << e.what() << '\n';
  }
}