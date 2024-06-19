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
  void clearScreen();
  void readGameData(Human &, Human &, Bot &);
  void loadGame(Human &, Human &, Bot &);
  void newGame(Human &, Human &, Bot &);
  void choosePlayer(Human &, Human &, Bot &);
  void setHumanGameSettings(Human &, Human &);
  void setBotGameSettings(Human &, Bot &);
  void humanGameplay(Human &, Human &);
  void botGameplay(Human &, Bot &);
};

#endif