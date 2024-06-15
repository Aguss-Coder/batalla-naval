#ifndef BOT_H
#define BOT_H

#include "player.h"
#include <iostream>

using namespace std;

class Bot : public Player
{
public:
  Bot();
  void strategy();
};

#endif