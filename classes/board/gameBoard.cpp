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
/**
 * Draws the game board.
 * Prints the current state of the game board, including the row and column indices and the contents of each square.
 */
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
void GameBoard::getShoot(pair<int, int> shoot)
{
  for (int i = 0; i < ships.size(); i++)
  {
    ships[i].takeShoot(shoot);
  }
}
/**
 * Checks if a ship can be placed on the game board.
 *
 * @param coordinates The starting coordinates of the ship.
 * @param size The size of the ship.
 * @param orientation The orientation of the ship ('H' for horizontal, 'V' for vertical).
 * @return True if the ship can be placed, false otherwise.
 */
bool GameBoard::canPlaceShip(pair<int, int> coordinates, pair<int, int> size, char orientation)
{
  if (orientation == 'H')
  {
    if (coordinates.first + size.first > this->size.first)
    {
      return false;
    }
    for (int i = 0; i < size.first; i++)
    {
      if (squares[coordinates.first + i][coordinates.second] != ' ')
      {
        return false;
      }
    }
  }
  else if (orientation == 'V')
  {
    if (coordinates.second + size.second > this->size.second)
    {
      return false;
    }
    for (int i = 0; i < size.second; i++)
    {
      if (squares[coordinates.first][coordinates.second + i] != ' ')
      {
        return false;
      }
    }
  }
  return true;
}
/**
 * @brief Places a ship on the game board.
 *
 * This function is used to place a ship on the game board based on the given coordinates, size, orientation, and symbol.
 *
 * @param coordinates The starting coordinates of the ship.
 * @param size The size of the ship (width and height).
 * @param orientation The orientation of the ship ('H' for horizontal, 'V' for vertical).
 * @param symbol The symbol representing the ship on the game board.
 */
void GameBoard::placeShip(pair<int, int> coordinates, pair<int, int> size, char orientation, char symbol)
{
  if (orientation == 'H')
  {
    for (int i = 0; i < size.first; i++)
    {
      squares[coordinates.first + i][coordinates.second] = symbol;
    }
  }
  else if (orientation == 'V')
  {
    for (int i = 0; i < size.second; i++)
    {
      squares[coordinates.first][coordinates.second + i] = symbol;
    }
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