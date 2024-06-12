#ifndef GAME_H
#define GAME_H

#include <iostream>

using namespace std;

class Game
{
protected:
  string gameSaved;

public:
  Game();
  void loadGame();
  void newGame();
  void choosePlayer();
  void play();
};

#endif