#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include <iostream>

using namespace std;

class Human : public Player
{
public:
  Human();
  void saveGame();
};

#endif