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
void Human::saveGame()
{
  cout << "Saving game..." << endl;
  try
  {
    ofstream file("savedGame.txt");

    if (!file.is_open())
    {
      throw runtime_error("Error opening file");
    }

    file << "Player: " << name << endl;
    file << "Turn: " << turn << endl;
    file << "Board: " << endl;
    file << "Size: " << board.getSize().first << "x" << board.getSize().second << endl;
    file << "Squares: " << endl;
    for (size_t i = 0; i < board.getSquares().size(); i++)
    {
      for (size_t j = 0; j < board.getSquares()[i].size(); j++)
      {
        file << board.getSquares()[i][j] << " ";
      }
      file << endl;
    }
    file << "Ships: " << endl;
    for (size_t i = 0; i < ships.size(); i++)
    {
      file << "Ship " << i + 1 << ": " << endl;
      file << "Size: " << ships[i].getSize() << endl;
      file << "Coordinates: ";
      for (size_t j = 0; j < ships[i].getCoordinates().size(); j++)
      {
        file << "(" << ships[i].getCoordinates()[j].first << ", " << ships[i].getCoordinates()[j].second << ") ";
      }
      file << endl;
      file << "Sunk: " << ships[i].getSunk() << endl;
      file << "Damaged: " << ships[i].getDamaged() << endl;
      file << "Symbol: " << ships[i].getSymbol() << endl;
      file << "Orientation: " << ships[i].getOrientation() << endl;
    }
    file.close();
    cout << "Game saved successfully" << endl;
  }
  catch (const exception &e)
  {
    cout << "An error ocurred: " << e.what() << '\n';
  }
}