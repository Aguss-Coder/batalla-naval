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
  vector<pair<int, int>> coordinatesShoted;
  vector<WarShip> ships;
  pair<int, int> shot;
  bool turn;
  bool isPlaying;

public:
  // Constructor
  Player();
  Player(string, GameBoard, pair<int, int>, bool);
  // Setters
  void setName(string);
  void setPlayerBoard();
  void setCoordinatesShoted(vector<pair<int, int>>);
  void setShips(vector<WarShip>);
  void setShot(pair<int, int>);
  void setTurn(bool);
  void setIsPlaying(bool);
  // Getters
  string getName();
  GameBoard &getPlayerBoard();
  vector<pair<int, int>> &getCoordinatesShoted();
  vector<WarShip> &getShips();
  pair<int, int> getShot();
  bool getTurn();
  bool getIsPlaying();
  // Methods
  void showPlayerBoard();
  bool makeShot();
  void changeTurn();
  void placeShips(vector<WarShip> &);
};

#endif