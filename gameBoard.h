#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include "ship.h"
#include <vector>

using namespace std;

class GameBoard
{
protected:
  vector<WarShip> ships;
  vector<pair<int, int>> waterPosition;
  pair<int, int> size;
  vector<vector<char>> squares;

public:
  // Constructor
  GameBoard();
  GameBoard(pair<int, int>);

  // Setters
  void setShips(vector<WarShip>);
  void setSize(pair<int, int>);
  void setSquares(vector<WarShip>, pair<int, int>);

  // Getters
  vector<WarShip> getShips();
  pair<int, int> getSize();
  vector<vector<char>> getSquares();

  // Methods
  void draw();
  bool receiveShot(pair<int, int>);
  bool canPlaceShip(pair<int, int>, pair<int, int>, char);
  void placeShip(pair<int, int>, pair<int, int>, char, char);
  bool checkVictory();
};

#endif