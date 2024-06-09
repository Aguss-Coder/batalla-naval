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
  WarShip(int, vector<pair<int, int>>, bool, bool, char, char);
  // Setters
  void setSize(int);
  void setCoordinates(vector<pair<int, int>>);
  void setSunk(bool);
  void setDamaged(bool);
  void setSymbol(char);
  void setOrientation(char);
  // Getters
  int getSize();
  vector<pair<int, int>> getCoordinates();
  bool getSunk();
  bool getDamaged();
  char getSymbol();
  char getOrientation();
  // Methods
  void takeShoot(vector<pair<int, int>>);
  bool isSunk();
};