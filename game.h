#ifndef GAME_H
#define GAME_H

#include <iostream>

using namespace std;

class Game
{
protected:
  string gameSaved;

public:
  void loadGame();
  void newGame();
  void choosePlayer();
  void humanGameplay();
  void botGameplay();
};

#endif