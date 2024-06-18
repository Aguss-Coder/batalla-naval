#include "human.h"
#include <iostream>
#include <exception>
#include <fstream>

using namespace std;

// Constructors
Human::Human()
{
  name = "Player";
  turn = false;
}

// Methods
void Human::saveGame(string fileName)
{
  cout << "Saving game..." << endl;
  try
  {
    ofstream file(fileName, ios::out | ios::trunc);

    if (!file.is_open())
    {
      throw runtime_error("Error opening file");
    }

    // Save logic
    string name = getName();
    bool turn = getTurn();
    GameBoard playerBoard = getPlayerBoard();
    GameBoard opponentBoard = getOpponentBoard();
    vector<WarShip> ships = getShips();

    file << name << endl;
    file << (turn ? "true" : "false") << endl;

    pair<int, int> size = playerBoard.getSize();
    file << size.first << " " << size.second << endl;

    vector<vector<char>> squares = playerBoard.getSquares();
    for (int i = 0; i < size.first; i++)
    {
      for (int j = 0; j < size.second; j++)
      {
        file << squares[i][j] << " ";
      }
      file << endl;
    }

    size = opponentBoard.getSize();
    file << size.first << " " << size.second << endl;

    squares = opponentBoard.getSquares();
    for (int i = 0; i < size.first; i++)
    {
      for (int j = 0; j < size.second; j++)
      {
        file << squares[i][j] << " ";
      }
      file << endl;
    }

    file << ships.size() << endl;
    for (const auto &ship : ships)
    {
      file << ship.getSize() << " " << ship.getSymbol() << " " << ship.getOrientation() << " " << ship.getCoordinates().size() << endl;
      for (const auto &coordinate : ship.getCoordinates())
      {
        file << "(" << coordinate.first << ", " << coordinate.second << ") ";
      }
      file << endl;
    }

    file.close();
    cout << "Game saved successfully" << endl;
  }
  catch (const exception &e)
  {
    cout << "An error ocurred: " << e.what() << '\n';
  }
}