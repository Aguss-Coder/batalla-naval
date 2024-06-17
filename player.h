#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "gameBoard.h"
#include "ship.h"
#include <vector>

using namespace std;

class Player
{
protected:
  string name;
  GameBoard playerBoard;
  GameBoard enemyBoard;
  vector<WarShip> ships;
  pair<int, int> shot;
  bool turn;

public:
  // Constructor
  Player();
  Player(string, GameBoard, pair<int, int>, bool);
  // Setters
  void setName(string);
  void setPlayerBoard();
  void setEnemyBoard();
  void setShips(vector<WarShip>);
  void setShot(pair<int, int>);
  void setTurn();
  // Getters
  string getName();
  GameBoard &getPlayerBoard();
  GameBoard &getEnemyBoard();
  vector<WarShip> &getShips();
  pair<int, int> getShot();
  bool getTurn();
  // Methods
  void showPlayerBoard();
  void showEnemyBoard();
  bool makeShot();
  void changeTurn();
};

#endif