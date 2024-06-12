#include "player.h"
#include <iostream>

using namespace std;

class Bot : public Player
{
public:
  Bot();
  void strategy();
};