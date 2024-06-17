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

pair<int, int> Bot::strategy()
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
  shot = newPosition;

  cout << "Bot shoots at " << shot.first << ", " << shot.second << endl;

  changeTurn();

  return shot;
}