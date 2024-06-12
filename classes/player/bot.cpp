#include "bot.h"
#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

// Constructors
#include <set>

Bot::Bot()
{
  name = "Bot";
  turn = false;
}

// Methods

void Bot::strategy()
{
  cout << "Bot is thinking..." << endl;
  srand(time(0));

  set<pair<int, int>> shooted;

  pair<int, int> newPosition;

  do
  {
    newPosition = make_pair(rand() % board.getSize().first, rand() % board.getSize().second);
  } while (shooted.find(newPosition) != shooted.end());

  shooted.insert(newPosition);
  shoot = newPosition;

  cout << "Bot shoots at " << shoot.first << ", " << shoot.second << endl;

  changeTurn();

  return;

}