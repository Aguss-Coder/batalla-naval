#ifndef WARSHIP_H
#define WARSHIP_H

#include <iostream>
#include <vector>

using namespace std;

class WarShip
{
protected:
  int size;
  vector<pair<int, int>> coordinates;
  bool sunk;
  bool damaged;
  char symbol;
  char orientation;

public:
  // Constructor
  WarShip();
  WarShip(int, char);
  // Setters
  void setSize(int);
  void setCoordinates(vector<pair<int, int>>);
  void setSunk(bool);
  void setDamaged(bool);
  void setSymbol(char);
  void setOrientation(char);
  // Getters
  int getSize() const;
  vector<pair<int, int>> getCoordinates() const;
  bool getSunk();
  bool getDamaged();
  char getSymbol() const;
  char getOrientation() const;
  // Methods
  bool takeShot(pair<int, int>);
  bool isSunk();
};

#endif