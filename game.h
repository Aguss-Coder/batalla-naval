#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "human.h"
#include "bot.h"

using namespace std;

class Game
{
protected:
  string gameSaved;

public:
  void loadGame();
  void newGame();
  void choosePlayer();
  void setHumanGameSettings(Human &, Human &);
  void setBotGameSettings(Human &, Bot &);
  void humanGameplay();
  void botGameplay();
};

#endif