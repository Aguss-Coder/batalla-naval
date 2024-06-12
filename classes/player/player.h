#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "../board/gameBoard.h"
#include "../ship/ship.h"
#include <vector>

using namespace std;

class Player
{
protected:
  string name;
  GameBoard board;
  vector<WarShip> ships;
  pair<int, int> shoot;
  bool turn;

public:
  // Constructor
  Player();
  Player(string, GameBoard, vector<WarShip>, pair<int, int>, bool);
  // Setters
  void setName();
  void setBoard();
  void setShips();
  void setShoot();
  void setTurn();
  // Getters
  string getName();
  GameBoard getBoard();
  vector<WarShip> getShips();
  pair<int, int> getShoot();
  bool getTurn();
  // Methods
  void showBoard();
  pair<int, int> makeShoot(pair<int, int>);
  void changeTurn();
};

#endif