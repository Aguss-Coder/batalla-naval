#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include <iostream>
#include "bot.h"

using namespace std;

class Human : public Player
{
public:
  Human();
  void saveGameData(Human, Human, Bot);
};

#endif