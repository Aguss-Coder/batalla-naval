#include "gameBoard.h"
#include <iostream>
#include <vector>

using namespace std;

// Constructors
GameBoard::GameBoard()
{
  size = make_pair(10, 10);
  squares = vector<vector<char>>(size.first, vector<char>(size.second, ' '));
}
GameBoard::GameBoard(pair<int, int> _size)
{
  size = _size;
  squares = vector<vector<char>>(size.first, vector<char>(size.second, ' '));
}

// Setters
void GameBoard::setShips(vector<WarShip> _ships)
{
  ships = _ships;
}
void GameBoard::setSize(pair<int, int> _size)
{
  size = _size;
}
void GameBoard::setSquares(vector<vector<char>> _squares)
{
  squares = _squares;
}

// Getters
vector<WarShip> GameBoard::getShips()
{
  return ships;
}
pair<int, int> GameBoard::getSize()
{
  return size;
}
vector<vector<char>> GameBoard::getSquares()
{
  return squares;
}

// Methods
void GameBoard::draw()
{
  cout << "  ";
  for (int i = 0; i < size.first; i++)
  {
    cout << i << " ";
  }
  cout << endl;

  for (int i = 0; i < size.first; i++)
  {
    cout << i << " ";
    for (int j = 0; j < size.second; j++)
    {
      cout << squares[i][j] << " ";
    }
    cout << endl;
  }
}
void GameBoard::getShoot(vector<pair<int, int>> shoot)
{
  for (int i = 0; i < ships.size(); i++)
  {
    ships[i].takeShoot(shoot);
  }
}
bool GameBoard::checkVictory()
{
  for (int i = 0; i < ships.size(); i++)
  {
    if (!ships[i].isSunk())
    {
      return false;
    }
  }
  return true;
}
bool GameBoard::canPlaceShip(vector<pair<int, int>> coordinates, pair<int, int> size, char orientation)
{
  if (orientation == 'H')
  {
    if (coordinates[0].first + size.first > this->size.first)
    {
      return false;
    }
    for (int i = 0; i < size.first; i++)
    {
      if (squares[coordinates[0].first + i][coordinates[0].second] != ' ')
      {
        return false;
      }
    }
  }
  else if (orientation == 'V')
  {
    if (coordinates[0].second + size.second > this->size.second)
    {
      return false;
    }
    for (int i = 0; i < size.second; i++)
    {
      if (squares[coordinates[0].first][coordinates[0].second + i] != ' ')
      {
        return false;
      }
    }
  }
  return true;
}
void GameBoard::placeShip(vector<pair<int, int>> coordinates, pair<int, int> size, char orientation, char symbol)
{
  if (orientation == 'H')
  {
    for (int i = 0; i < size.first; i++)
    {
      squares[coordinates[0].first + i][coordinates[0].second] = symbol;
    }
  }
  else if (orientation == 'V')
  {
    for (int i = 0; i < size.second; i++)
    {
      squares[coordinates[0].first][coordinates[0].second + i] = symbol;
    }
  }
}