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
  void loadGame(string);
  void newGame();
  void choosePlayer();
  void setHumanGameSettings(Human &, Human &);
  void setBotGameSettings(Human &, Bot &);
  void humanGameplay();
  void botGameplay();
};

#endif