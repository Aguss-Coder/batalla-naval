#include "gameBoard.h"
#include <iostream>
#include <vector>

using namespace std;

// Constructors
GameBoard::GameBoard()
{
  size.first = 10;
  size.second = 10;
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
  size.first = _size.first;
  size.second = _size.second;
}
void GameBoard::setSquares(vector<WarShip> _ships, pair<int, int> _size)
{
  squares.resize(_size.first, vector<char>(_size.second, '~'));

  for (const WarShip &ship : _ships)
  {
    for (const auto &coord : ship.getCoordinates())
    {
      if (coord.first >= 0 && coord.first < _size.first && coord.second >= 0 && coord.second < _size.second)
      {
        squares[coord.first][coord.second] = ship.getSymbol();
      }
    }
  }
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
  // Imprime el índice de las columnas con un espacio adicional para alinear con los bordes de las celdas
  cout << "    "; // Espacios adicionales para alinear los índices de las columnas
  for (int col = 0; col < size.second; col++)
  {
    cout << col << " ";
  }
  cout << endl;

  // Imprime la línea superior del tablero
  cout << "   +"; // Espacios adicionales para alinear con los índices de las columnas
  for (int col = 0; col < size.second; col++)
  {
    cout << "--"; // Doble línea para cada columna
  }
  cout << "+" << endl; // Cierra el borde superior del tablero

  // Imprime el índice de las filas, el contenido de cada celda y los bordes verticales
  for (int row = 0; row < size.first; row++)
  {
    // Asegura que el índice de las filas esté alineado correctamente
    if (row < 10)
    {
      cout << " " << row << " |"; // Espacio adicional para filas de un solo dígito
    }
    else
    {
      cout << row << " |";
    }

    // Imprime el contenido de cada celda con un borde a su derecha
    for (int col = 0; col < size.second; col++)
    {
      cout << squares[row][col] << "|"; // Asume que squares es accesible y contiene el contenido de cada celda
    }
    cout << endl;

    // Imprime la línea divisoria entre filas
    cout << "   +"; // Alinea con los índices de las columnas
    for (int col = 0; col < size.second; col++)
    {
      cout << "--"; // Doble línea para cada columna
    }
    cout << "+" << endl; // Cierra la línea divisoria
  }
}
bool GameBoard::receiveShot(pair<int, int> shot)
{
  for (size_t i = 0; i < ships.size(); i++)
  {
    if (ships[i].takeShot(shot))
    {
      squares[shot.first][shot.second] = 'X';
      return true;
    }
  }
  squares[shot.first][shot.second] = 'O';
  return false;
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
  for (size_t i = 0; i < ships.size(); i++)
  {
    if (!ships[i].isSunk())
    {
      return false;
    }
  }
  return true;
}