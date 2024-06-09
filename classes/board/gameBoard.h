#include <iostream>
#include "../ship/ship.h"
#include <vector>

using namespace std;

class GameBoard
{
protected:
  vector<WarShip> ships;
  pair<int, int> size;
  vector<vector<char>> squares;

public:
  // Constructor
  GameBoard();
  GameBoard(pair<int, int>);

  // Setters
  void setShips(vector<WarShip>);
  void setSize(pair<int, int>);
  void setSquares(vector<vector<char>>);

  // Getters
  vector<WarShip> getShips();
  pair<int, int> getSize();
  vector<vector<char>> getSquares();

  // Methods
  void draw();
  void getShoot(vector<pair<int, int>>);
  bool canPlaceShip(vector<pair<int, int>>, pair<int, int>, char);
  void placeShip(vector<pair<int, int>>, pair<int, int>, char, char);
  bool checkVictory();
};